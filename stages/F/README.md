# F 阶段学习记录

## 阶段说明

F 阶段主要围绕 Logisim、数字逻辑、状态机模型和简单处理器设计展开。

本阶段从基础逻辑门开始，逐步完成组合逻辑、时序逻辑、状态机建模、简单处理器设计，并最终实现了一个支持 miniRV 8 条指令的处理器。当前 miniRV 已经能够运行官方 `mem.hex`、`sum.hex` 和 `vga.hex`，并通过 RGB Video 显示“一生一芯”logo。

当前状态：

```text
F 阶段已基本完成
```

---

## 阶段目录

```text
logs/          F 阶段学习日志
notes/         F 阶段知识笔记
problems/      F 阶段问题记录
screenshots/   F 阶段截图
code/logisim/  F 阶段 Logisim 电路文件
```

Logisim 电路目录：

```text
code/logisim/F2/              Logisim 入门电路
code/logisim/F3/              数字逻辑基础电路
code/logisim/F5/              sCPU 电路与 ROM
code/logisim/F6/              miniRV 电路与检查点
code/logisim/official-tests/  官方 mem/sum/vga 测试文件
```

---

## 当前进度概览

| 阶段 | 内容 | 状态 |
| ---- | ---- | ---- |
| F1 | 科学提问 | 已完成 |
| F2 | Logisim 入门 | 已完成 |
| F3 | 数字逻辑基础与综合实验 | 已完成 |
| F4 | 计算机系统的状态机模型 | 已完成 |
| F5 | 支持数列求和的简单处理器 | 已完成 |
| F6 | 功能完备的 miniRV 处理器 | 已完成 |

---

## F 阶段成果总览

F 阶段完成内容可以概括为：

```text
逻辑门
↓
组合逻辑
↓
时序逻辑
↓
状态机
↓
简单 CPU
↓
miniRV 处理器
↓
官方程序运行
↓
VGA 图形显示
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
- 官方 `mem.hex` / `sum.hex` / `vga.hex` 测试
- VGA / RGB Video 图形显示
- 成功显示“一生一芯”logo

---

## F6 miniRV 完成情况

已实现 miniRV 指令：

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

已完成内容：

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

官方测试结果：

```text
addi 负立即数测试：通过
sb 四字节覆盖测试：通过
mem.hex：通过
sum.hex：通过
vga.hex：通过
```

VGA 显示相关逻辑：

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

---

## 相关文件

### Logisim 电路

- `code/logisim/F2/mux2-1.circ`
- `code/logisim/F3/`
- `code/logisim/F5/f5-scpu.circ`
- `code/logisim/F5/f5-scpu-rom.hex`
- `code/logisim/F6/f6-minirv-final.circ`
- `code/logisim/F6/f6-minirv-rom.hex`
- `code/logisim/F6/f6-minirv-ram.hex`
- `code/logisim/F6/checkpoints/f6-minirv-dev.circ`
- `code/logisim/F6/checkpoints/f6-minirv-mem-sum-pass.circ`
- `code/logisim/official-tests/mem.hex`
- `code/logisim/official-tests/sum.hex`
- `code/logisim/official-tests/vga.hex`

---

## 学习笔记

- [F1-F3 前半部分学习记录](notes/F1-F3前半部分学习记录.md)
- [F3 补码加减法器与简易 4 位 ALU](notes/F3-补码加减法器与简易4位ALU.md)
- [F3 译码器、编码器、选择器与数码管](notes/F3-译码器编码器选择器与数码管.md)
- [F3 比较器与借位减法器](notes/F3-比较器与借位减法器.md)
- [F3 时序逻辑入门与寄存器](notes/F3-时序逻辑入门与寄存器.md)
- [F3 计数器、数列求和电路与电子时钟](notes/F3-计数器数列求和电路与电子时钟.md)
- [F4 计算机系统的状态机模型](notes/F4-计算机系统的状态机模型.md)
- [F5 支持数列求和的简单处理器](notes/F5-支持数列求和的简单处理器.md)
- [F6 miniRV 基础与 addi 指令](notes/F6-miniRV基础与addi指令.md)
- [F6 addi、jalr、add、lui 指令实现](notes/F6-addi-jalr-add-lui指令.md)
- [F6 lw 与 sw 访存指令实现](notes/F6-lw-sw访存指令.md)
- [F6 lbu 与 sb 字节访存指令实现](notes/F6-lbu与sb字节访存指令.md)
- [F6 官方补充验证与 VGA 显示](notes/F6-官方补充验证与VGA显示.md)

---

## 问题记录

- [F5 sCPU 设计问题记录](problems/F5-sCPU设计问题记录.md)
- [F6 RAM 访存问题记录](problems/F6-RAM访存问题记录.md)
- [F6 lbu、sb 与整体联调问题记录](problems/F6-lbu-sb与整体联调问题记录.md)
- [F6 官方测试与 VGA 显示问题记录](problems/F6-官方测试与VGA显示问题记录.md)

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

通过 F 阶段的学习，我对“程序是如何在 CPU 上执行的”有了更具体的认识，也为后续学习计算机系统、操作系统、编译器和体系结构打下基础。
