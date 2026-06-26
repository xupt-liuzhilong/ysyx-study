# 一生一芯学习记录

## 仓库说明

本仓库用于记录我学习“一生一芯”过程中的学习笔记、实验电路、代码文件、问题记录、运行截图和阶段复盘。

当前状态：

```text
F 阶段已基本完成
```

F 阶段从 Logisim 入门开始，逐步完成组合逻辑、时序逻辑、状态机建模、简单处理器设计，并最终实现了一个支持 miniRV 8 条指令的处理器，能够运行官方 `mem.hex`、`sum.hex` 和 `vga.hex`，并通过 RGB Video 显示“一生一芯”logo。

---

## 学习目标

- 补齐计算机系统基础
- 学习数字逻辑与计算机组成原理
- 理解 CPU 执行程序的基本过程
- 掌握 Logisim / Verilog 等硬件设计基础
- 逐步进入一生一芯后续阶段和 PA 实验
- 将学习过程、代码、电路和问题持续记录到 GitHub

---

## 目录结构

```text
logs/          每日或每周学习记录
notes/         系统整理后的知识点笔记
problems/      报错、卡点和解决过程
code/          代码、电路文件和实验文件
screenshots/   实验截图、运行结果截图
```

---

## 当前进度概览

| 阶段 | 内容                     | 状态   |
| ---- | ------------------------ | ------ |
| F1   | 科学提问                 | 已完成 |
| F2   | Logisim 入门             | 已完成 |
| F3   | 数字逻辑基础与综合实验   | 已完成 |
| F4   | 计算机系统的状态机模型   | 已完成 |
| F5   | 支持数列求和的简单处理器 | 已完成 |
| F6   | 功能完备的 miniRV 处理器 | 已完成 |

---

## F 阶段成果总览

F 阶段完成内容可以概括为：

```text
从逻辑门
到组合逻辑
到时序逻辑
到状态机
到简单 CPU
到 miniRV 处理器
到官方程序运行
到 VGA 图形显示
```

当前已经完成：

- 基本门电路与组合逻辑实验
- 加法器、减法器、补码加减法器、简易 ALU
- 译码器、编码器、优先编码器、多路选择器
- 七段数码管、比较器、计数器、电子时钟
- 锁存器、触发器、寄存器
- 数列求和电路
- sISA 状态机理解
- 支持数列求和的 sCPU
- miniRV 8 条指令处理器
- 官方 `mem.hex` / `sum.hex` 测试
- VGA / RGB Video 图形显示
- 成功显示“一生一芯”logo

---

## 阶段学习记录

### F1：科学提问

完成内容：

- 理解科学提问的重要性
- 学会描述目标、现象、尝试过程和自己的猜测
- 明确遇到问题时要记录截图、代码、报错信息

学习记录：

- [F1-F3 前半部分学习记录](notes/F阶段/F1-F3前半部分学习记录.md)

---

### F2：Logisim 入门

完成内容：

- 完成 Logisim 基本使用
- 完成 A AND B 点亮 LED 实验
- 完成 2 选 1 MUX 实验
- 掌握输入 Pin、逻辑门、LED 输出和基本连线方法

学习记录：

- [F1-F3 前半部分学习记录](notes/F阶段/F1-F3前半部分学习记录.md)

---

### F3：数字逻辑基础与综合实验

F3 阶段主要学习组合逻辑、算术逻辑、时序逻辑和综合电路实验。

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

核心理解：

```text
组合逻辑负责计算
时序逻辑负责保存状态
复杂系统可以由小模块逐步组合而成
```

学习记录：

- [F3 补码加减法器与简易 4 位 ALU](notes/F阶段/F3-补码加减法器与简易ALU.md)
- [F3 译码器、编码器、选择器与数码管](notes/F阶段/F3-译码器编码器选择器与数码管.md)
- [F3 比较器与借位减法器](notes/F阶段/F3-比较器与借位减法器.md)
- [F3 时序逻辑入门与寄存器](notes/F阶段/F3-时序逻辑入门与寄存器.md)
- [F3 计数器、数列求和电路与电子时钟](notes/F阶段/F3-计数器求和电路与电子时钟.md)

---

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

核心理解：

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

---

### F5：支持数列求和的简单处理器

F5 阶段把 F3 的数字电路模块和 F4 的状态机模型结合起来，设计一个能够执行简单指令序列的 sCPU。

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

支持的 sISA 指令：

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

核心理解：

```text
CPU 设计 = 用数字电路实现 ISA 状态机
```

学习记录：

- [F5 支持数列求和的简单处理器](notes/F阶段/F5-支持数列求和的简单处理器.md)

问题记录：

- [F5 sCPU 设计过程中的问题与解决](problems/F阶段/F5-sCPU设计问题记录.md)

---

### F6：功能完备的 miniRV 处理器

F6 阶段从 F5 的自定义 sISA 处理器进一步升级到 miniRV 处理器，并完成官方测试程序和 VGA 图形显示。

当前 F6 阶段已经完成。

#### 已实现 miniRV 指令

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

#### 已完成内容

- 搭建 32 位 PC 取指模块
- 实现 `PC + 4`
- 使用 32 位 ROM 指令输出
- 搭建 `gpr16x32` 通用寄存器堆
- 实现 `x0` 恒为 0
- 实现 `addi`
- 实现 `jalr`
- 实现 `add`
- 实现 `lui`
- 加入 Data RAM
- 实现 `lw`
- 实现 `sw`
- 实现 `lbu`
- 实现 `sb`
- 完成 8 条指令整体联调
- 完成 `addi` 负立即数测试
- 完成 `sb` 四字节覆盖测试
- 添加 `cycle_counter64`
- 通过 `mem.hex` 官方测试
- 通过 `sum.hex` 官方测试
- 实现 VGA 地址译码
- 接入 RGB Video
- 通过 `vga.hex` 测试
- 成功显示“一生一芯”logo

#### 核心理解

```text
RISC-V 指令宽度为 32 位
PC 默认每次 +4
ROM 地址使用 PC 右移 2 位后的 word 地址
x0 永远为 0
miniRV 当前使用 16 个 32 位通用寄存器
lw/sw 访问 word
lbu/sb 访问 byte
RISC-V 使用字节地址
Logisim RAM/ROM 使用 word 地址时需要右移 2 位
sw/sb 使用 S 型立即数
lbu/sb 需要使用地址低 2 位选择 word 内部字节
官方 hex 文件需要同时加载到 ROM 和 RAM
VGA 显示通过内存映射 I/O 实现
```

#### 官方测试结果

```text
addi 负立即数测试：通过
sb 四字节覆盖测试：通过
mem.hex：通过
sum.hex：通过
vga.hex：通过
```

#### VGA 显示

```text
显存地址范围：0x20000000 ~ 0x2003FFFF

isVGA = mem_addr[31:18] == 0x0800
isMem = ~isVGA

RAM_WE = (is_sw | is_sb) & isMem
VGA_WE = is_sw & isVGA

X = mem_addr[9:2]
Y = mem_addr[17:10]
Color = rdata2[23:0]
```

#### 学习记录

- [F6 miniRV 基础与 addi 指令](notes/F阶段/F6-miniRV基础与addi指令.md)
- [F6 addi、jalr、add、lui 指令实现](notes/F阶段/F6-addi-jalr-add-lui指令.md)
- [F6 lw 与 sw 访存指令实现](notes/F阶段/F6-lw-sw访存指令.md)
- [F6 lbu 与 sb 字节访存指令实现](notes/F阶段/F6-lbu与sb字节访存指令.md)
- [F6 官方补充验证与 VGA 显示](notes/F阶段/F6-官方补充验证与VGA显示.md)

#### 问题记录

- [F6 RAM 访存问题记录](problems/F阶段/F6-RAM访存问题记录.md)
- [F6 lbu、sb 与整体联调问题记录](problems/F阶段/F6-lbu-sb与整体联调问题记录.md)
- [F6 官方测试与 VGA 显示问题记录](problems/F阶段/F6-官方测试与VGA显示问题记录.md)

#### 阶段结论

```text
F6：功能完备的 miniRV 处理器完成
```

---

## 当前模块积累

### 算术模块

```text
half_adder
full_adder
adder4
adder8
adder32
add_sub4
alu4
half_subtractor
full_subtractor
subtractor4
```

### 组合逻辑模块

```text
decoder
encoder
priority_encoder
seven_segment_decoder
mux_1bit_4_1
mux_3bit_4_1
equal4
compare4
```

### 时序逻辑模块

```text
S_R_latch
D_latch
D_flip_flop
reg1
reg4
reg8
reg32
counter4
cycle_counter64
```

### 综合电路模块

```text
counter_mod10
counter_mod6
digital_clock
sequence_sum
```

### 简单处理器 / miniRV 模块

```text
PC_reg
ROM
Data_RAM
gpr4x8
gpr16x32
adder32
sign_extend
lui_data
control_logic
writeback_mux
sCPU
miniRV_fetch
miniRV_datapath
RGB_Video
VGA_addr_decode
```

---

## 问题记录总览

学习过程中遇到的问题整理在 `problems/` 目录中，主要包括：

- Logisim 反馈电路出现红线
- Clock 元件和普通 Pin 的区别
- `.circ` 文件导入时 `MAIN` 命名冲突
- 多项目导入导致子电路依赖混乱
- 寄存器初始状态未知导致输出红色 E
- `bner0` 分支指令比较器取反问题
- PC 分支选择逻辑接线问题
- RAM 异步读和同步读导致 `lw` 写回失败
- RAM 修改属性后内容被清空
- RAM 不随 CPU 的 CLR 清零
- `sb` 使用 I 型立即数导致写错字节
- 官方 hex 文件需要同时加载到 ROM 和 RAM
- VGA 写入时需要屏蔽 RAM 写使能
- RGB Video 引脚和 X/Y 坐标生成问题

---

## 学习记录规范

每次学习后记录：

1. 今天学了什么
2. 完成了什么实验或代码
3. 遇到了什么问题
4. 如何解决
5. 下一步计划

---

## Commit 规范

- `学习记录：完成 xxxx`
- `代码练习：完成 xxxx`
- `问题记录：解决 xxxx 报错`
- `环境配置：完成 xxxx 安装`
- `文档整理：更新 xxxx`

---

## 下一步计划

F 阶段已经基本完成，后续计划：

- 备份当前通过测试的 `.circ` 文件
- 整理 F 阶段关键截图
- 补充 F 阶段阶段复盘
- 根据一生一芯后续路线继续进入下一阶段学习
- 进一步学习 C 语言、Linux、Verilog 和 PA 预学习内容
- 对比当前 miniRV 和真实 RISC-V CPU 的差距
- 逐步从 Logisim 手工搭电路过渡到更系统的硬件设计方法

---

## 阶段总结

F 阶段最大的收获是：从最基础的逻辑门开始，逐步理解了计算机硬件是如何从小模块构成复杂系统的。

```text
逻辑门
↓
组合逻辑
↓
时序逻辑
↓
状态机
↓
ISA
↓
CPU 数据通路
↓
访存
↓
内存映射 I/O
```

通过 F 阶段的学习，我对“程序是如何在 CPU 上执行的”有了更具体的认识，也更加理解后续学习计算机系统、操作系统、编译器和体系结构的基础意义。