# 学习记录：F6 addi、jalr、add、lui 指令实现

## 一、学习概况

今天继续学习一生一芯 F6 阶段：功能完备的迷你 RISC-V 处理器。

在前一次已经完成 F6 基础取指模块、`gpr16x32` 寄存器堆和 `addi` 指令的基础上，今天继续扩展 miniRV 处理器，完成了：

- 验证 `addi + jalr` 两条指令处理器
- 理解 `jalr` 的跳转和返回逻辑
- 实现 `add` 指令
- 实现 `lui` 指令
- 将写回通路改造成 4 选 1 MUX
- 规范写回数据来源选择
- 完成 `addi / jalr / add / lui` 四条指令测试

目前 miniRV 已支持：

```text
addi
jalr
add
lui
```

------

## 二、当前 miniRV 处理器基础结构

当前处理器已经包含：

```text
32 位 PC
PC + 4
ROM 32 位取指
PC[5:2] 作为 ROM 地址
gpr16x32 通用寄存器堆
x0 恒为 0
32 位加法器
立即数符号扩展
jalr 跳转选择逻辑
4 选 1 写回 MUX
```

处理器基本流程为：

```text
PC → ROM → instr[31:0]
        ↓
      指令译码
        ↓
  读寄存器 / 生成立即数
        ↓
   ALU / PC+4 / lui_data
        ↓
      写回 GPR
        ↓
      更新 PC
```

------

## 三、jalr 指令验证

### 1. jalr 指令功能

`jalr` 指令格式：

```asm
jalr rd, imm(rs1)
```

功能：

```text
rd = PC + 4
PC = (rs1 + imm) & ~1
```

它同时完成两件事：

```text
1. 把返回地址 PC + 4 写入 rd
2. 跳转到 rs1 + imm 计算出的地址
```

其中 `& ~1` 表示把跳转地址最低位清 0。

------

### 2. 测试程序

ROM 中使用的测试程序：

```asm
0x00: addi a0, zero, 20
0x04: jalr ra, 16(zero)
0x08: jalr ra, 12(zero)
0x0C: jalr zero, 12(zero)
0x10: addi a0, a0, 10
0x14: jalr zero, 0(ra)
```

对应机器码：

```text
01400513
010000E7
00C000E7
00C00067
00A50513
00008067
```

------

### 3. 执行过程

初始：

```text
PC  = 00000000
x1  = 00000000
x10 = 00000000
```

执行第一条：

```asm
addi a0, zero, 20
```

结果：

```text
PC  = 00000004
x10 = 00000014
```

执行第二条：

```asm
jalr ra, 16(zero)
```

当前 PC 为 `00000004`，因此：

```text
x1 = PC + 4 = 00000008
PC = x0 + 16 = 00000010
```

结果：

```text
PC  = 00000010
x1  = 00000008
x10 = 00000014
```

执行地址 `0x10` 的指令：

```asm
addi a0, a0, 10
```

结果：

```text
x10 = 20 + 10 = 30
x10 = 0000001E
PC  = 00000014
```

执行地址 `0x14` 的指令：

```asm
jalr zero, 0(ra)
```

由于：

```text
ra = x1 = 00000008
```

所以：

```text
PC = 00000008
```

测试结果符合预期，说明：

```text
jalr 跳转目标计算正确
jalr 写回 PC+4 正确
jalr zero, 0(ra) 返回逻辑正确
x0 恒为 0 正确
```

------

## 四、add 指令实现

### 1. add 指令功能

`add` 指令格式：

```asm
add rd, rs1, rs2
```

功能：

```text
R[rd] = R[rs1] + R[rs2]
PC = PC + 4
```

它和 F5 中的 `add` 类似，只是现在变成了：

```text
32 位寄存器
32 位加法
RISC-V 指令格式
```

------

### 2. add 指令格式

`add` 是 R 型指令：

```text
31     25 24   20 19   15 14 12 11    7 6      0
funct7    rs2     rs1    funct3   rd     opcode
```

字段：

```text
funct7 = instr[31:25]
rs2    = instr[24:20]
rs1    = instr[19:15]
funct3 = instr[14:12]
rd     = instr[11:7]
opcode = instr[6:0]
```

对于 `add`：

```text
opcode = 0110011
funct3 = 000
funct7 = 0000000
```

------

### 3. add 数据通路

`addi` 的数据通路是：

```text
R[rs1] + imm_ext → R[rd]
```

`add` 的数据通路是：

```text
R[rs1] + R[rs2] → R[rd]
```

因此需要给加法器 B 输入增加一个选择器：

```text
adder.B = imm_ext    // addi
adder.B = rdata2     // add
```

连接方式：

```text
instr[19:15] → raddr1
instr[24:20] → raddr2
rdata1 → adder.A
rdata2 → adder.B 的 MUX 输入
adder.S → 写回数据来源之一
```

------

### 4. add 测试

测试程序：

```asm
0x00: addi x1, x0, 10
0x04: addi x2, x0, 20
0x08: add  x3, x1, x2
```

机器码：

```text
00A00093
01400113
002081B3
```

预期结果：

```text
x1 = 0000000A
x2 = 00000014
x3 = 0000001E
```

实际测试结果正确：

```text
x3 = x1 + x2 = 10 + 20 = 30
x3 = 0000001E
```

说明 `add` 指令实现正确。

------

## 五、lui 指令实现

### 1. lui 指令功能

`lui` 全称是：

```text
Load Upper Immediate
```

功能是把立即数放入寄存器高 20 位，低 12 位补 0：

```text
R[rd] = imm << 12
```

例如：

```asm
lui x4, 0x12345
```

执行后：

```text
x4 = 12345000
```

------

### 2. lui 指令格式

`lui` 是 U 型指令：

```text
31        12 11    7 6      0
imm[31:12]   rd     opcode
```

字段：

```text
imm    = instr[31:12]
rd     = instr[11:7]
opcode = instr[6:0]
```

对于 `lui`：

```text
opcode = 0110111
```

------

### 3. lui 数据生成

`lui` 不需要读寄存器，也不需要加法器。

它的数据生成方式是：

```text
lui_data[31:12] = instr[31:12]
lui_data[11:0]  = 000000000000
```

也就是：

```text
lui_data = instr[31:12] << 12
```

然后：

```text
lui_data → 写回 MUX → gpr16x32.wdata
```

------

### 4. lui 测试

测试程序：

```asm
0x00: addi x1, x0, 10
0x04: addi x2, x0, 20
0x08: add  x3, x1, x2
0x0C: lui  x4, 0x12345
```

机器码：

```text
00A00093
01400113
002081B3
12345237
```

预期结果：

```text
x1 = 0000000A
x2 = 00000014
x3 = 0000001E
x4 = 12345000
```

实际测试结果正确：

```text
x4 = 12345000
```

说明 `lui` 指令实现正确。

------

## 六、写回通路改造

随着指令增加，写回数据来源不再只有一种。

当前写回来源包括：

```text
add_result
PC + 4
lui_data
```

后面加入 `lw / lbu` 时，还会增加：

```text
mem_data
```

因此今天将写回通路改造成 4 选 1 MUX。

------

### 1. 写回 MUX 输入安排

写回 MUX 设置：

```text
Select Bits = 2
Data Bits = 32
```

输入安排：

| 选择值 | 写回数据来源 | 对应指令             |
| ------ | ------------ | -------------------- |
| `00`   | `add_result` | `addi`、`add`        |
| `01`   | `PC + 4`     | `jalr`               |
| `10`   | `lui_data`   | `lui`                |
| `11`   | `mem_data`   | 后续 `lw / lbu` 预留 |

MUX 输出：

```text
wdata → gpr16x32.wdata
```

------

### 2. 写回选择控制

定义写回选择信号：

```text
wb_sel[1:0]
```

当前编码：

```text
addi / add → wb_sel = 00
jalr       → wb_sel = 01
lui        → wb_sel = 10
lw / lbu   → wb_sel = 11
```

当前可以用：

```text
wb_sel[0] = is_jalr
wb_sel[1] = is_lui
```

因为：

| 指令 | is_lui | is_jalr | wb_sel |
| ---- | ------ | ------- | ------ |
| addi | 0      | 0       | 00     |
| add  | 0      | 0       | 00     |
| jalr | 0      | 1       | 01     |
| lui  | 1      | 0       | 10     |

------

### 3. 写寄存器使能 wen

当前会写寄存器的指令有：

```text
addi
jalr
add
lui
```

所以：

```text
wen = is_addi | is_jalr | is_add | is_lui
```

后续加入 `sw / sb` 后，这两条指令不会写寄存器，因此不能一直让 `wen = 1`。

------

## 七、当前支持的指令

目前 miniRV 处理器已经支持 4 条指令：

```text
addi
jalr
add
lui
```

对应功能：

| 指令   | 功能                                 |
| ------ | ------------------------------------ |
| `addi` | `rd = rs1 + imm`                     |
| `jalr` | `rd = PC + 4; PC = (rs1 + imm) & ~1` |
| `add`  | `rd = rs1 + rs2`                     |
| `lui`  | `rd = imm << 12`                     |

------

## 八、当前收获

今天主要收获：

1. 理解了 `jalr` 不只是跳转，还要把 `PC+4` 写入 `rd`。
2. 理解了 `jalr zero, 0(ra)` 可以实现返回。
3. 理解了 `add` 是 R 型指令，需要同时读取 `rs1` 和 `rs2`。
4. 理解了 `addi` 和 `add` 可以共用同一个加法器。
5. 理解了 `lui` 是 U 型指令，不需要 ALU，只需要立即数拼接。
6. 学会了把写回通路改造成 4 选 1 MUX。
7. 理解了不同指令通过控制信号选择不同写回数据。
8. 为后续加入 `lw / lbu` 的内存读数据写回预留了通路。

------

## 九、下一步计划

下一次继续 F6 访存指令：

```text
lw
lbu
sw
sb
```

下一步重点：

- 加入数据 RAM
- 理解 `rs1 + imm` 如何生成访存地址
- 实现 `lw` 读取 32 位数据
- 实现 `lbu` 读取 1 字节并零扩展
- 实现 `sw` 写入 32 位数据
- 实现 `sb` 写入 1 字节数据
- 将 RAM 读数据接入写回 MUX 的第 4 路