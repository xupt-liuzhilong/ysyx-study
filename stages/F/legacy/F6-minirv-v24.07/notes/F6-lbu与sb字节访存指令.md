# 学习记录：F6 lbu 与 sb 字节访存指令实现

## 一、学习概况

今天继续完成一生一芯 F6 阶段 miniRV 处理器的访存指令部分。

在前面已经完成：

```text
addi
jalr
add
lui
lw
sw
```

的基础上，今天继续实现最后两条字节访存指令：

```text
lbu
sb
```

并进行了 8 条指令整体联调测试。

目前 miniRV 支持的 8 条指令已经全部通过测试：

```text
add
addi
lui
lw
lbu
sw
sb
jalr
```

------

## 二、lbu 指令实现

### 1. lbu 指令功能

`lbu` 全称是：

```text
load byte unsigned
```

格式：

```asm
lbu rd, imm(rs1)
```

功能：

```text
R[rd] = zero_extend(MEM[R[rs1] + imm])
```

也就是：

```text
从内存中读取 1 个字节
再把这个字节零扩展成 32 位
最后写回 rd
```

注意：`lbu` 中的 `u` 是 unsigned，所以高位补 0。

------

### 2. lbu 指令格式

`lbu` 是 I 型指令，格式和 `lw/addi/jalr` 类似：

```text
31        20 19   15 14 12 11    7 6      0
imm[11:0]   rs1    funct3   rd     opcode
```

字段：

```text
imm    = instr[31:20]
rs1    = instr[19:15]
funct3 = instr[14:12]
rd     = instr[11:7]
opcode = instr[6:0]
```

对于 `lbu`：

```text
opcode = 0000011
funct3 = 100
```

因此控制信号为：

```text
is_lbu = (opcode == 0000011) & (funct3 == 100)
```

------

### 3. lbu 地址计算

`lbu` 和 `lw` 一样，都需要先计算访存地址：

```text
mem_addr = R[rs1] + sign_extend(imm)
```

所以可以直接复用之前 `lw` 的地址计算通路：

```text
rdata1 + imm_i_ext → add_result
```

其中：

```text
add_result = mem_addr
```

由于 RISC-V 使用字节地址，而 Logisim 中的 RAM 设置为 32 位宽，一个 RAM 地址对应 4 个字节，所以 RAM 地址应取：

```text
RAM_addr = mem_addr[7:2]
```

也就是：

```text
add_result[7:2] → RAM Address
```

------

### 4. lbu 的字节选择

`lw` 读取整个 32 位 word，而 `lbu` 只读取其中 1 个字节。

例如：

```text
RAM[1] = 12345678
```

按小端序理解：

```text
地址 4 → 78
地址 5 → 56
地址 6 → 34
地址 7 → 12
```

因此需要使用地址低两位来选择 word 内部的字节：

```text
byte_sel = mem_addr[1:0]
```

对应关系：

```text
byte_sel = 00 → RAM_DataOut[7:0]
byte_sel = 01 → RAM_DataOut[15:8]
byte_sel = 10 → RAM_DataOut[23:16]
byte_sel = 11 → RAM_DataOut[31:24]
```

在 Logisim 中的实现方式：

```text
RAM_DataOut[31:0] 拆成 4 个 8 位数据
通过 4 选 1 MUX 选择其中一个 byte
选择信号为 add_result[1:0]
```

------

### 5. lbu 零扩展

4 选 1 MUX 输出的是 8 位：

```text
lbu_byte[7:0]
```

然后通过 Extender 零扩展为 32 位：

```text
lbu_data = zero_extend(lbu_byte)
```

例如：

```text
lbu_byte = 78
lbu_data = 00000078
```

------

### 6. lbu 写回通路

原来的 `lw` 写回数据是：

```text
RAM_DataOut
```

现在需要在 `lw` 和 `lbu` 之间选择：

```text
lw  → RAM_DataOut
lbu → lbu_data
```

因此加入一个内存写回数据 MUX：

```text
is_lbu = 0 → RAM_DataOut
is_lbu = 1 → lbu_data
```

输出为：

```text
mem_wb_data
```

再送入原来的写回 MUX 的 memory 输入端。

写回 MUX 当前可以理解为：

```text
00 → add_result
01 → PC + 4
10 → lui_data
11 → mem_wb_data
```

因此 `lw` 和 `lbu` 都选择：

```text
wb_sel = 11
```

控制信号更新为：

```text
GPR_wen = is_addi | is_jalr | is_add | is_lui | is_lw | is_lbu
```

`lbu` 会写寄存器，所以要加入 GPR 写使能。

------

### 7. lbu 测试

RAM 地址 1 中填入：

```text
12345678
```

测试程序：

```asm
lbu x6, 4(x0)
lbu x7, 5(x0)
lbu x8, 6(x0)
lbu x9, 7(x0)
```

对应机器码：

```text
00404303
00504383
00604403
00704483
```

预期结果：

```text
x6 = 00000078
x7 = 00000056
x8 = 00000034
x9 = 00000012
```

测试结果正确，说明：

```text
RAM_addr = add_result[7:2] 正确
byte_sel = add_result[1:0] 正确
4 选 1 字节选择逻辑正确
零扩展逻辑正确
lbu 写回寄存器正确
```

------

## 三、sb 指令实现

### 1. sb 指令功能

`sb` 全称是：

```text
store byte
```

格式：

```asm
sb rs2, imm(rs1)
```

功能：

```text
MEM[R[rs1] + imm] = R[rs2][7:0]
```

也就是：

```text
计算内存地址
把 rs2 的低 8 位写入内存指定字节
```

注意：`sb` 只写 1 个字节，不应该覆盖整个 32 位 word。

------

### 2. sb 指令格式

`sb` 是 S 型指令，和 `sw` 类型相同：

```text
31        25 24   20 19   15 14 12 11     7 6      0
imm[11:5]   rs2     rs1    funct3   imm[4:0] opcode
```

字段：

```text
imm[11:5] = instr[31:25]
rs2       = instr[24:20]
rs1       = instr[19:15]
funct3    = instr[14:12]
imm[4:0]  = instr[11:7]
opcode    = instr[6:0]
```

对于 `sb`：

```text
opcode = 0100011
funct3 = 000
```

因此控制信号为：

```text
is_sb = (opcode == 0100011) & (funct3 == 000)
```

------

### 3. sb 的 S 型立即数

`sb` 和 `sw` 一样，都是 Store 类指令，所以使用 S 型立即数。

S 型立即数不是连续的，需要拼接：

```text
imm_s[11:5] = instr[31:25]
imm_s[4:0]  = instr[11:7]
```

即：

```text
imm_s = {instr[31:25], instr[11:7]}
```

再符号扩展为 32 位：

```text
imm_s_ext = sign_extend(imm_s)
```

地址计算为：

```text
mem_addr = rdata1 + imm_s_ext
```

因此立即数选择逻辑应为：

```text
addi / lw / lbu / jalr → 使用 I 型立即数
sw / sb                → 使用 S 型立即数
```

所以立即数 MUX 的选择信号应为：

```text
is_store = is_sw | is_sb
```

而不是只使用 `is_sw`。

------

### 4. sb 的地址拆分

`sb` 的访存地址仍然是字节地址：

```text
mem_addr = rdata1 + imm_s_ext
```

其中：

```text
RAM_addr = mem_addr[7:2]
byte_sel = mem_addr[1:0]
```

含义：

```text
RAM_addr 用来选择 RAM 中的哪个 32 位 word
byte_sel 用来选择这个 word 中的哪个 byte
```

例如：

```asm
sb x7, 5(x0)
```

由于：

```text
mem_addr = 5
```

所以：

```text
RAM_addr = 5 >> 2 = 1
byte_sel = 01
```

也就是写入 RAM 地址 1 中的 byte1。

------

### 5. RAM 字节写使能

为了实现 `sb`，RAM 属性改为支持字节写：

```text
Enables = Use byte enables
Read write control = Use byte enables
```

对于 32 位 RAM，有 4 个 byte enable：

```text
byte0 → RAM_Data[7:0]
byte1 → RAM_Data[15:8]
byte2 → RAM_Data[23:16]
byte3 → RAM_Data[31:24]
```

`sw` 写整个 word，所以：

```text
sw → byte_enable = 1111
```

`sb` 只写其中一个 byte，所以：

```text
byte_sel = 00 → byte_enable = 0001
byte_sel = 01 → byte_enable = 0010
byte_sel = 10 → byte_enable = 0100
byte_sel = 11 → byte_enable = 1000
```

最终逻辑：

```text
BE0 = is_sw | (is_sb & byte_sel == 00)
BE1 = is_sw | (is_sb & byte_sel == 01)
BE2 = is_sw | (is_sb & byte_sel == 10)
BE3 = is_sw | (is_sb & byte_sel == 11)
```

这样：

```text
sw：四个字节全部写
sb：只写目标字节
其他指令：不写 RAM
```

------

### 6. sb 写入数据生成

`sb` 只写 `rdata2[7:0]`。

但是 RAM DataIn 是 32 位，所以需要根据 `byte_sel` 把这个 8 位数据放到对应位置：

```text
byte_sel = 00 → RAM_DataIn = 000000AA
byte_sel = 01 → RAM_DataIn = 0000AA00
byte_sel = 10 → RAM_DataIn = 00AA0000
byte_sel = 11 → RAM_DataIn = AA000000
```

因此可以用一个 4 选 1 MUX 生成 `sb_wdata`：

```text
input0 = {24'b0, rdata2[7:0]}
input1 = {16'b0, rdata2[7:0], 8'b0}
input2 = {8'b0,  rdata2[7:0], 16'b0}
input3 = {rdata2[7:0], 24'b0}
select = byte_sel
```

然后 RAM 写入数据选择：

```text
sw → rdata2
sb → sb_wdata
```

即：

```text
RAM_DataIn = is_sb ? sb_wdata : rdata2
```

------

### 7. sb 不写 GPR

`sb` 是 Store 类指令，只写 RAM，不写寄存器。

所以 GPR 写使能不能包含 `sb`：

```text
GPR_wen = is_addi | is_jalr | is_add | is_lui | is_lw | is_lbu
```

不能写成：

```text
GPR_wen = ... | is_sw | is_sb
```

------

### 8. sb 测试

单独测试程序：

```asm
addi x5, x0, 0xAA
sb   x5, 5(x0)
```

机器码：

```text
0AA00293
005002A3
```

如果初始：

```text
RAM[1] = 12345678
```

执行后预期：

```text
RAM[1] = 1234AA78
```

因为：

```text
地址 5 对应 RAM[1] 的 byte1
byte1 原来是 56
写入 AA 后变成 1234AA78
```

测试结果正确，说明：

```text
is_sb 判断正确
S 型立即数拼接正确
byte_sel 选择正确
sb_wdata 生成正确
byte_enable 控制正确
sb 只写 RAM，不写 GPR
```

------

## 四、8 条指令整体联调测试

为了验证 8 条指令能同时工作，使用如下整体测试程序：

```asm
addi x1, x0, 10
addi x2, x0, 20
add  x3, x1, x2
lui  x4, 0x12345

sw   x3, 4(x0)
lw   x5, 4(x0)
lbu  x6, 4(x0)

addi x7, x0, 0xAA
sb   x7, 5(x0)
lbu  x8, 5(x0)

jalr x0, 40(x0)
```

机器码：

```text
00A00093
01400113
002081B3
12345237
00302223
00402283
00404303
0AA00393
007002A3
00504403
02800067
```

预期结果：

```text
x1 = 0000000A
x2 = 00000014
x3 = 0000001E
x4 = 12345000
x5 = 0000001E
x6 = 0000001E
x7 = 000000AA
x8 = 000000AA
RAM[1] = 0000AA1E
PC = 00000028
```

测试结果全部通过。

说明当前 miniRV 处理器的 8 条指令已经可以整体协同运行。

------

## 五、当前完成情况

当前已经完成 miniRV 8 条指令：

```text
add
addi
lui
lw
lbu
sw
sb
jalr
```

核心数据通路包括：

```text
PC + 4 取指
jalr 跳转
gpr16x32 寄存器堆
x0 恒为 0
ALU 加法通路
lui 立即数写回
lw word 读取
lbu byte 读取与零扩展
sw word 写入
sb byte 写入
写回 MUX
立即数选择 MUX
RAM byte enable
```

至此，F6 阶段“功能完备的迷你 RISC-V 处理器”已经初步完成。