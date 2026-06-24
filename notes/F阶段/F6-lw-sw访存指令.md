# 学习记录：F6 lw 与 sw 访存指令实现

## 一、学习概况

今天继续学习一生一芯 F6 阶段：功能完备的迷你 RISC-V 处理器。

在前面已经完成 `addi`、`jalr`、`add`、`lui` 四条指令的基础上，今天开始加入数据 RAM，学习并实现访存指令。

今天主要完成：

- 理解访存指令的基本作用
- 加入 Data RAM
- 实现 `lw` 指令
- 理解 RISC-V 字节地址和 Logisim RAM 地址之间的关系
- 实现 `sw` 指令
- 理解 S 型立即数拼接
- 理解 RAM 不一定随 CPU 的 CLR 清零
- 当前 miniRV 已支持 `addi`、`jalr`、`add`、`lui`、`lw`、`sw`

------

## 二、访存指令的基本理解

之前实现的指令主要操作寄存器：

```text
addi
jalr
add
lui
```

这些指令的数据主要在 GPR、ALU、PC 之间流动。

从 `lw` 和 `sw` 开始，需要加入数据存储器：

```text
Data RAM
```

需要区分：

```text
ROM：指令存储器，保存程序指令
RAM：数据存储器，保存程序运行过程中的数据
```

处理器结构变成：

```text
PC → ROM → instr

ALU 计算数据地址
↓
RAM 读 / 写数据
```

------

## 三、lw 指令实现

### 1. lw 指令功能

`lw` 全称是：

```text
load word
```

格式：

```asm
lw rd, imm(rs1)
```

功能：

```text
R[rd] = MEM[R[rs1] + sign_extend(imm)]
```

也就是：

```text
用 rs1 + imm 计算内存地址
从 RAM 中读出 32 位数据
写回 rd
```

------

### 2. lw 指令格式

`lw` 是 I 型指令：

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

对于 `lw`：

```text
opcode = 0000011
funct3 = 010
```

判断信号：

```text
is_lw = (opcode == 0000011) & (funct3 == 010)
```

------

### 3. lw 数据通路

`lw` 和 `addi` 前半部分很像。

`addi`：

```text
R[rd] = R[rs1] + imm
```

`lw`：

```text
addr = R[rs1] + imm
R[rd] = RAM[addr]
```

所以地址计算可以复用原来的加法器：

```text
rdata1 + imm_ext → add_result
```

在 `lw` 中：

```text
add_result = mem_addr
```

然后：

```text
mem_addr[7:2] → RAM Address
RAM DataOut → 写回 MUX input3
```

------

## 四、RISC-V 地址和 RAM 地址的关系

RISC-V 中的地址是字节地址。

但是 Logisim 中如果 RAM 设置为：

```text
Data Bit Width = 32
```

那么 RAM 的一个地址单元就是 32 位，也就是 4 字节。

因此：

```text
RAM_addr = mem_addr >> 2
```

如果 RAM 地址宽度为 6 位，则连接：

```text
mem_addr[7:2] → RAM Address[5:0]
```

对应关系：

| RISC-V 字节地址 | RAM 地址 |
| --------------- | -------- |
| 0               | 0        |
| 4               | 1        |
| 8               | 2        |
| 12              | 3        |

这和取指时：

```text
ROM_addr = PC >> 2
```

是同一个道理。

------

## 五、lw 测试

测试指令：

```asm
lw x5, 4(x0)
```

机器码：

```text
00402283
```

含义：

```text
x5 = MEM[x0 + 4]
```

由于：

```text
x0 = 0
```

所以：

```text
mem_addr = 4
RAM_addr = 4 >> 2 = 1
```

在 RAM 地址 1 预先填入：

```text
12345678
```

执行一拍后，预期：

```text
x5 = 12345678
```

测试结果正确，说明：

```text
lw 地址计算正确
RAM 地址右移 2 正确
RAM 数据读出正确
写回 MUX 选择 mem_data 正确
lw 写回 rd 正确
```

------

## 六、sw 指令实现

### 1. sw 指令功能

`sw` 全称是：

```text
store word
```

格式：

```asm
sw rs2, imm(rs1)
```

功能：

```text
MEM[R[rs1] + sign_extend(imm)] = R[rs2]
```

也就是：

```text
用 rs1 + imm 计算内存地址
把 rs2 中的数据写入 RAM
```

------

### 2. sw 指令格式

`sw` 是 S 型指令：

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

对于 `sw`：

```text
opcode = 0100011
funct3 = 010
```

判断信号：

```text
is_sw = (opcode == 0100011) & (funct3 == 010)
```

------

## 七、S 型立即数拼接

`sw` 的立即数不是连续的，需要从两段指令字段拼接：

```text
imm_s[11:5] = instr[31:25]
imm_s[4:0]  = instr[11:7]
```

也就是：

```text
imm_s = { instr[31:25], instr[11:7] }
```

然后符号扩展为 32 位：

```text
imm_s_ext = sign_extend(imm_s)
```

为了同时支持 I 型和 S 型立即数，加入立即数选择 MUX：

```text
is_sw = 0 → imm_i_ext
is_sw = 1 → imm_s_ext
```

最终送入加法器计算地址：

```text
rdata1 + imm_final → mem_addr
```

------

## 八、sw 数据通路

`sw` 需要两个读端口：

```text
raddr1 = rs1
raddr2 = rs2
```

其中：

```text
rdata1 = R[rs1]  // 用来计算地址
rdata2 = R[rs2]  // 要写入 RAM 的数据
```

连接方式：

```text
rdata1 + imm_s_ext → mem_addr
mem_addr[7:2] → RAM Address
rdata2 → RAM Data In
is_sw → RAM Write Enable
```

注意：

```text
sw 不写 GPR
```

所以：

```text
GPR_wen 不包含 is_sw
```

当前 GPR 写使能为：

```text
wen = is_addi | is_jalr | is_add | is_lui | is_lw
```

不能写成：

```text
wen = ... | is_sw
```

------

## 九、sw 测试

测试程序：

```asm
addi x5, x0, 99
sw   x5, 4(x0)
```

机器码：

```text
06300293
00502223
```

执行过程：

第一拍：

```text
x5 = 00000063
```

第二拍执行：

```asm
sw x5, 4(x0)
```

此时：

```text
rs1 = x0
rs2 = x5
imm_s = 4
rdata1 = 00000000
rdata2 = 00000063
mem_addr = 00000004
RAM_addr = 1
RAM_DataIn = 00000063
RAM_WE = 1
GPR_wen = 0
```

执行后：

```text
RAM[1] = 00000063
```

测试结果正确，说明：

```text
S 型立即数拼接正确
sw 地址计算正确
rs2 数据正确送入 RAM
RAM 写使能正确
sw 不写 GPR 正确
```

------

## 十、RAM 不随 CLR 清零的理解

测试 `sw` 时发现：

```text
CPU 清零后，RAM 中的数据不会自动清零
```

例如第一次执行：

```asm
sw x5, 4(x0)
```

后：

```text
RAM[1] = 00000063
```

再次按 CPU 的 `CLR` 后：

```text
PC 和 GPR 被清零
RAM[1] 仍然保持 00000063
```

这是正常现象。

理解：

```text
CLR/Reset 主要用于让 CPU 的状态回到初始状态
例如 PC、GPR、控制状态等
```

而 RAM 属于数据存储器，它里面的数据可以保留，或者由程序自己初始化。

因此后续不强制让 RAM 跟随 CLR 清零，而是让程序在需要时自行初始化内存。

这更接近真实计算机系统。

------

## 十一、当前支持的指令

目前 miniRV 处理器已经支持 6 条指令：

```text
addi
jalr
add
lui
lw
sw
```

剩余待实现：

```text
lbu
sb
```

------

## 十二、当前收获

今天主要收获：

1. 理解了 ROM 和 RAM 的区别。
2. 理解了 `lw` 是从 RAM 读 32 位数据写回寄存器。
3. 理解了 `sw` 是把寄存器数据写入 RAM。
4. 理解了 RISC-V 字节地址和 Logisim RAM 地址之间需要右移 2 位。
5. 理解了 `lw` 可以复用 `addi` 的地址计算通路。
6. 理解了 `sw` 是 S 型指令，立即数需要重新拼接。
7. 理解了 `sw` 不写 GPR，只写 RAM。
8. 理解了 RAM 不一定跟随 CPU 的 CLR 清零，可以由程序自行初始化。
9. 进一步理解了处理器的数据通路和控制信号如何随着指令增加而扩展。

------

## 十三、下一步计划

下一次继续实现剩余两条字节访存指令：

```text
lbu
sb
```

重点内容：

- `lbu` 读取 1 字节并零扩展到 32 位
- `sb` 只写入寄存器低 8 位
- 理解字节地址的低 2 位如何选择 word 内部的某个字节
- 实现字节选择逻辑
- 完成 miniRV 8 条指令支持