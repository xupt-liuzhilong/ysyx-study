# 一生一芯学习记录

## 仓库说明

本仓库用于记录我学习“一生一芯”过程中的笔记、实验电路、代码、问题总结和阶段复盘。

当前主要学习内容为 F 阶段，后续会继续补充 Linux、C 语言、Verilog、PA 实验等内容。

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

| 阶段 | 内容                   | 状态   |
| ---- | ---------------------- | ------ |
| F1   | 科学提问               | 已完成 |
| F2   | Logisim 入门           | 已完成 |
| F3   | 数字逻辑基础与综合实验 | 已完成 |
| F4   | 计算机系统的状态机模型 | 学习中 |
| F5   | 简单处理器设计         | 未开始 |

------

## 阶段学习记录

### F1：科学提问

- 理解科学提问的重要性
- 学会描述目标、现象、尝试过程和自己的猜测
- 明确遇到问题时要记录截图、代码、报错信息

学习记录：

- [F1-F3 前半部分学习记录](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F1-F3前半部分学习记录.md)

------

### F2：Logisim 入门

- 完成 Logisim 基本使用
- 完成 A AND B 点亮 LED 实验
- 完成 2 选 1 MUX 实验
- 掌握输入 Pin、逻辑门、LED 输出和基本连线方法

学习记录：

- [F1-F3 前半部分学习记录](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F1-F3前半部分学习记录.md)

------

### F3：数字逻辑基础与综合实验

F3 阶段主要完成了组合逻辑、算术逻辑、时序逻辑和综合电路实验。

已完成内容包括：

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

- [F3 补码加减法器与简易 4 位 ALU](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F3-补码加减法器与简易ALU.md)
- [F3 译码器、编码器、选择器与数码管](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F3-译码器编码器选择器与数码管.md)
- [F3 比较器与借位减法器](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F3-比较器与借位减法器.md)
- [F3 时序逻辑入门与寄存器](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F3-时序逻辑入门与寄存器.md)
- [F3 计数器、数列求和电路与电子时钟](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F3-计数器求和电路与电子时钟.md)

------

### F4：计算机系统的状态机模型

F4 阶段开始从更高层理解计算机系统。

当前已学习：

- 处理器执行程序的基本过程
- PC、GPR、ISA、指令语义的含义
- 使用 `(PC, r0, r1, r2, r3)` 表示简单处理器状态
- 手推官方数列求和程序 `1+2+...+10`
- 编写并手推 10 以内奇数求和程序
- 理解 C 程序、ISA 和数字电路都可以看作状态机

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

- [F4 计算机系统的状态机模型](https://chatgpt.com/g/g-p-6a1ff1a4a1908191a24e2153b56a0a0f/c/notes/F阶段/F4-计算机系统的状态机模型.md)

------

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

## 问题记录

学习过程中遇到的问题会整理到 `problems/` 目录中，例如：

- Logisim 反馈电路出现红线
- Clock 元件和普通 Pin 的区别
- `.circ` 文件导入时 `MAIN` 命名冲突
- 寄存器初始状态未知导致电路无反应

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

------

## 下一步计划

- 继续完成 F4 阶段学习
- 理解 ISA 和 CPU 实现之间的关系
- 学习 PC、GPR、指令译码和控制信号
- 为 F5 简单处理器设计做准备
- 从 Logisim 电路思维逐步过渡到 Verilog / C / PA 预学习