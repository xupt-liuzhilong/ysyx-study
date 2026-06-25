# 一生一芯学习记录

## 仓库说明

本仓库用于记录我学习“一生一芯”过程中的笔记、实验电路、代码、问题总结和阶段复盘。

当前已完成 F 阶段中从 Logisim 入门到简单处理器设计的主要内容，后续将继续补充 Verilog、C 语言、Linux、PA 预学习等内容。

------

## 学习目标

- 补齐计算机系统基础
- 学习数字逻辑与计算机组成原理
- 理解处理器执行程序的基本过程
- 掌握 Logisim / Verilog 等硬件设计基础
- 逐步完成一生一芯 F 阶段、预学习和 PA 实验

------

## 目录结构

```text
logs/          每日或每周学习记录
notes/         系统整理后的知识点笔记
problems/      报错、卡点和解决过程
code/          代码、电路文件和实验文件
screenshots/   实验截图、运行结果截图
```

------

## 当前进度概览

| 阶段 | 内容                         | 状态   |
| ---- | ---------------------------- | ------ |
| F1   | 科学提问                     | 已完成 |
| F2   | Logisim 入门                 | 已完成 |
| F3   | 数字逻辑基础与综合实验       | 已完成 |
| F4   | 计算机系统的状态机模型       | 已完成 |
| F5   | 支持数列求和的简单处理器     | 已完成 |
| F6   | 功能完备的迷你 RISC-V 处理器 | 学习中 |

------

## 阶段学习记录

### F1：科学提问

完成内容：

- 理解科学提问的重要性
- 学会描述目标、现象、尝试过程和自己的猜测
- 明确遇到问题时要记录截图、代码、报错信息

学习记录：

- [F1-F3 前半部分学习记录](notes/F阶段/F1-F3前半部分学习记录.md)

------

### F2：Logisim 入门

完成内容：

- 完成 Logisim 基本使用
- 完成 A AND B 点亮 LED 实验
- 完成 2 选 1 MUX 实验
- 掌握输入 Pin、逻辑门、LED 输出和基本连线方法

学习记录：

- [F1-F3 前半部分学习记录](notes/F阶段/F1-F3前半部分学习记录.md)

------

### F3：数字逻辑基础与综合实验

F3 阶段主要完成组合逻辑、算术逻辑、时序逻辑和综合电路实验。

完成内容：

- 基本门电路
- 半加器、全加器、4 位加法器
- 补码加减法器
- 简易 4 位 ALU
- 译码器、编码器、优先编码器
- 多路选择器
- 七段数码管显示
- 比较器
- 半减器、全减器、4 位借位减法器
- S-R 锁存器
- D 锁存器
- 主从 D 触发器
- 1 位寄存器、4 位寄存器、8 位寄存器
- 4 位计数器
- 数列求和电路
- 模 10 / 模 6 计数器
- 电子时钟

F3 核心理解：

```text
组合逻辑负责计算
时序逻辑负责保存状态
小模块可以组合成更复杂的硬件系统
```

学习记录：

- [F3 补码加减法器与简易 4 位 ALU](notes/F阶段/F3-补码加减法器与简易ALU.md)
- [F3 译码器、编码器、选择器与数码管](notes/F阶段/F3-译码器编码器选择器与数码管.md)
- [F3 比较器与借位减法器](notes/F阶段/F3-比较器与借位减法器.md)
- [F3 时序逻辑入门与寄存器](c/notes/F阶段/F3-时序逻辑入门与寄存器.md)
- [F3 计数器、数列求和电路与电子时钟](notes/F阶段/F3-计数器求和电路与电子时钟.md)

------

### F4：计算机系统的状态机模型

F4 阶段主要从状态机角度理解计算机系统。

完成内容：

- 理解处理器执行程序的基本过程
- 理解 PC、GPR、ISA、指令语义的含义
- 使用 `(PC, r0, r1, r2, r3)` 表示简单处理器状态
- 手推官方数列求和程序 `1+2+...+10`
- 编写并手推 10 以内奇数求和程序
- 理解 C 程序、ISA 和数字电路都可以看作状态机
- 理解编译器和 CPU 设计在计算机系统中的作用

F4 核心理解：

```text
程序执行 = 状态不断转移
```

C 程序、ISA、数字电路之间的关系：

```text
C 程序
↓ 编译器
ISA 指令序列
↓ CPU 硬件实现
数字电路状态机
```

学习记录：

- [F4 计算机系统的状态机模型](notes/F阶段/F4-计算机系统的状态机模型.md)

------

### F5：支持数列求和的简单处理器

F5 阶段主要把 F3 的数字电路模块和 F4 的状态机模型结合起来，设计一个能够执行简单指令序列的 sCPU。

完成内容：

- PC 寄存器
- PC + 1 自增逻辑
- ROM 指令存储器
- 指令取指 Fetch
- 指令字段拆分
- `gpr4x8` 通用寄存器堆
- 双读端口
- 单写端口
- `li` 指令
- `add` 指令
- `bner0` 分支指令
- PC 分支选择逻辑
- 完整数列求和程序运行

支持的指令：

```text
li
add
bner0
```

最终运行结果：

```text
PC = 7
r0 = 10
r1 = 10
r2 = 55
r3 = 1
```

其中：

```text
r2 = 55
```

表示成功计算：

```text
1 + 2 + 3 + ... + 10 = 55
```

F5 核心理解：

```text
CPU 设计 = 用数字电路实现 ISA 状态机
```

学习记录：

- [F5 支持数列求和的简单处理器](notes/F阶段/F5-支持数列求和的简单处理器.md)

问题记录：

- [F5 sCPU 设计过程中的问题与解决](problems/F阶段/F5-sCPU设计问题记录.md)

------

### F6：功能完备的迷你 RISC-V 处理器

F6 阶段开始从 F5 自定义 sISA 处理器过渡到更加接近真实 RISC-V 的 miniRV 处理器。

当前 F6 阶段已经完成 miniRV 8 条指令的设计、实现和整体联调。

已实现指令：

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

当前已完成内容：

- 搭建 32 位 PC 取指模块
- 将 ROM 改为 32 位指令输出
- 理解 RISC-V 中 PC 每次加 4
- 使用 `PC[5:2]` 作为 ROM 地址
- 搭建 `gpr16x32` 通用寄存器堆
- 实现 `x0` 恒为 0
- 实现 `addi` 指令
- 实现 `jalr` 指令
- 实现 `add` 指令
- 实现 `lui` 指令
- 加入 Data RAM
- 实现 `lw` 指令
- 实现 `sw` 指令
- 实现 `lbu` 指令
- 实现 `sb` 指令
- 完成 8 条 miniRV 指令整体联调测试

核心理解：

```text
RISC-V 指令宽度为 32 位
PC 默认每次 +4
ROM 地址使用 PC[5:2]
x0 永远为 0
RISC-V 使用字节地址
访问 32 位 ROM/RAM 时需要将地址右移 2 位
lw/sw 访问 32 位 word
lbu/sb 访问 8 位 byte
lbu/sb 需要使用地址低两位选择 word 内部的 byte
sw/sb 都是 S 型指令，需要使用 S 型立即数
```

整体测试程序：

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

整体测试结果：

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

学习记录：

- [F6 miniRV 基础与 addi 指令](notes/F阶段/F6-miniRV基础与addi指令.md)
- [F6 addi、jalr、add、lui 指令实现](notes/F阶段/F6-addi-jalr-add-lui指令.md)
- [F6 lw 与 sw 访存指令实现](notes/F阶段/F6-lw-sw访存指令.md)
- [F6 lbu 与 sb 字节访存指令实现](notes/F阶段/F6-lbu与sb字节访存指令.md)

问题记录：

- [F6 RAM 访存问题记录](problems/F阶段/F6-RAM访存问题记录.md)
- [F6 lbu、sb 与整体联调问题记录](problems/F阶段/F6-lbu-sb与整体联调问题记录.md)

当前阶段结论：

```text
F6 miniRV 8 条指令处理器已经初步完成
```

## 当前模块积累

### 算术模块

```text
half_adder
→ full_adder
→ adder4
→ add_sub4
→ alu4
adder4
→ adder8
half_subtractor
→ full_subtractor
→ subtractor4
```

------

### 组合逻辑模块

```text
decoder
→ seven_segment_decoder
→ encoder
→ priority_encoder
→ mux_1bit_4_1
→ mux_3bit_4_1
→ equal4
→ compare4
```

------

### 时序逻辑模块

```text
S_R_latch
→ D_latch
→ D_flip_flop
→ reg1
→ reg4
→ reg8
```

------

### 综合电路模块

```text
reg4 + adder4
→ counter4
→ counter_mod10 / counter_mod6
→ digital_clock
reg4 + adder4 + reg8 + adder8
→ sequence_sum
```

------

### 简单处理器 / miniRV 模块

```text
PC_reg
ROM
gpr4x8
gpr16x32
adder32
sign_extend
lui_data
Data_RAM
control_logic
writeback_mux
sCPU
miniRV_fetch
miniRV_addi_datapath
miniRV_jalr_datapath
miniRV_add_datapath
miniRV_lui_datapath
miniRV_lw_datapath
miniRV_sw_datapath
```

------

## 问题记录

学习过程中遇到的问题会整理到 `problems/` 目录中，例如：

- Logisim 反馈电路出现红线
- Clock 元件和普通 Pin 的区别
- `.circ` 文件导入时 `MAIN` 命名冲突
- 多项目导入导致子电路依赖混乱
- 寄存器初始状态未知导致输出红色 E
- `bner0` 分支指令比较器取反问题
- PC 分支选择逻辑接线问题

------

## 学习记录规范

每次学习后记录：

1. 今天学了什么
2. 完成了什么实验或代码
3. 遇到了什么问题
4. 如何解决
5. 下一步计划

------

## Commit 规范

- `学习记录：完成 xxxx`
- `代码练习：完成 xxxx`
- `问题记录：解决 xxxx 报错`
- `环境配置：完成 xxxx 安装`
- `文档整理：更新 xxxx`

------

## 下一步计划

- 保存并备份当前通过测试的 `.circ` 文件
- 整理 F6 阶段截图
- 根据一生一芯后续要求继续进入下一阶段学习
- 进一步思考当前 miniRV 和真实 RISC-V CPU 的差距