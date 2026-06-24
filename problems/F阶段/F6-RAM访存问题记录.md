# 问题记录：F6 RAM 访存指令调试问题

## 一、问题概况

在 F6 阶段实现 `lw` 和 `sw` 访存指令时，主要遇到了 RAM 读写相关问题。

问题集中在：

- RAM 读写端口配置
- RAM 是否异步读
- 修改 RAM 属性后内容被清空
- RAM 不随 CPU 的 CLR 清零
- `lw` 写回时序问题

这些问题都和“RAM 是数据存储器”以及“CPU 单周期访存”有关。

------

## 二、问题一：RAM_DataOut 一开始为 0，x5 写不进去

### 现象

测试指令：

```asm
lw x5, 4(x0)
```

RAM 地址 1 中预先填入：

```text
12345678
```

但是执行时出现：

```text
清零后 RAM_DataOut = 0
第 1 个 CLK 后 RAM_DataOut 才变成 12345678
x5 仍然是 0
```

------

### 原因分析

这个现象说明 RAM 当时表现为同步读：

```text
地址给进去
↓
等一次时钟
↓
RAM_DataOut 才更新
```

而当前处理器按单周期 `lw` 来设计，希望在同一个周期内完成：

```text
计算地址
↓
RAM 输出数据
↓
写回寄存器
```

如果 RAM_DataOut 要等时钟后才变，那么 GPR 在这一拍写入时拿到的还是旧数据。

------

### 解决方法

将 RAM 的读行为设置为异步读：

```text
Asynchronous read = Yes
```

这样：

```text
RAM_addr 一变化
RAM_DataOut 立即输出对应数据
```

于是执行 `lw` 时，在时钟上升沿到来前：

```text
RAM_DataOut 已经是 12345678
```

GPR 就可以在这一拍正确写入：

```text
x5 = 12345678
```

------

## 三、问题二：RAM 读写共用数据总线导致观察混乱

### 现象

一开始 RAM 的数据输入和数据输出不够清晰，容易分不清：

```text
哪个是写入 RAM 的数据
哪个是 RAM 读出的数据
```

------

### 解决方法

修改 RAM 属性：

```text
Data bus implementation = Separate data bus for read and write
```

也就是：

```text
读数据总线和写数据总线分开
```

这样 RAM 会有更清晰的接口：

```text
Data In  ：写 RAM 的数据
Data Out ：从 RAM 读出的数据
```

对于 `lw`：

```text
RAM DataOut → 写回 MUX
```

对于 `sw`：

```text
rdata2 → RAM DataIn
```

这样数据通路更清楚，也更适合 CPU 设计。

------

## 四、问题三：修改 RAM 属性后内容被清空

### 现象

修改 RAM 属性后，重新测试 `lw`，发现：

```text
RAM_DataOut 一直是 0
x5 也一直写不进去
```

后来发现 RAM 地址 1 中原来填的：

```text
12345678
```

消失了。

------

### 原因分析

修改 RAM 的某些属性后，Logisim 可能会清空或重置 RAM 内容。

因此虽然地址和控制信号都接对了，但 RAM 地址 1 实际已经变成：

```text
00000000
```

读出来自然也是 0。

------

### 解决方法

修改 RAM 属性后，重新检查 RAM 内容：

```text
右键 RAM → Edit Contents
```

确认测试地址中仍然有预期数据。

例如测试 `lw` 时，需要重新确认：

```text
RAM[1] = 12345678
```

------

### 经验总结

修改 RAM 属性后，要重新检查 RAM 内容是否还在。

尤其在测试：

```text
lw
lbu
sw
sb
```

这些访存指令时，RAM 内容是测试结果的关键。

------

## 五、问题四：RAM 不随 CPU 的 CLR 清零

### 现象

执行测试程序：

```asm
addi x5, x0, 99
sw   x5, 4(x0)
```

执行后：

```text
RAM[1] = 00000063
```

再次按 CPU 的 `CLR` 后发现：

```text
PC 和 GPR 被清零
但 RAM[1] 仍然是 00000063
```

------

### 原因分析

当前全局 `CLR` 只接到了 PC 和 GPR，没有接到 RAM。

并且从系统角度看，RAM 是数据存储器，它不一定要随着 CPU reset 被清空。

真实计算机系统中，reset 通常让 CPU 回到初始状态，但 RAM 内容不一定全部清零。

------

### 解决方法

本阶段不强制给 RAM 加清零端。

测试时可以采用两种方式：

### 方法一：手动初始化 RAM

测试前打开 RAM 内容，手动清空或填入指定测试数据。

例如测试 `sw` 前：

```text
RAM[1] = 00000000
```

执行后检查：

```text
RAM[1] 是否变为 00000063
```

### 方法二：由程序初始化 RAM

后续可以通过程序自己执行 `sw` 指令来初始化内存。

例如：

```asm
addi x5, x0, 99
sw   x5, 4(x0)
```

这样 RAM 的内容由程序自己决定。

------

## 六、问题五：lw 的 RAM 地址不能直接接 add_result 低位

### 现象

容易误以为：

```text
RAM Address = add_result[5:0]
```

但这样会导致地址不符合 RISC-V 字节地址规则。

------

### 原因分析

RISC-V 使用字节地址。

但 Logisim RAM 如果设置为：

```text
Data Bit Width = 32
```

则一个 RAM 地址对应 32 位，也就是 4 字节。

所以需要：

```text
RAM_addr = mem_addr >> 2
```

也就是：

```text
add_result[7:2] → RAM Address
```

------

### 经验总结

取指 ROM 和数据 RAM 都有类似问题：

```text
ROM_addr = PC >> 2
RAM_addr = mem_addr >> 2
```

因为一条指令或一个 word 都是 4 字节。

------

## 七、当前 RAM 推荐配置

当前阶段 RAM 推荐配置：

```text
Address Bit Width = 6
Data Bit Width = 32
Data bus implementation = Separate data bus for read and write
Asynchronous read = Yes
Read behavior = Read after write
Read write control = Whole word read/write only
```

其中最重要的是：

```text
Separate data bus for read and write
Asynchronous read = Yes
```

------

## 八、调试访存指令时建议观察的信号

调试 `lw/sw` 时，不要只看最终寄存器或 RAM 内容，应该观察中间信号：

```text
instr
opcode
funct3
is_lw
is_sw
rs1
rs2
rd
imm_i_ext
imm_s_ext
rdata1
rdata2
add_result / mem_addr
RAM_addr
RAM_DataIn
RAM_DataOut
RAM_WE
wb_sel
GPR_wen
```

对于 `lw x5, 4(x0)`，正确状态应为：

```text
mem_addr = 00000004
RAM_addr = 1
RAM_DataOut = RAM[1]
wb_sel = 11
GPR_wen = 1
waddr = x5
```

对于 `sw x5, 4(x0)`，正确状态应为：

```text
mem_addr = 00000004
RAM_addr = 1
RAM_DataIn = x5
RAM_WE = 1
GPR_wen = 0
```

------

## 九、整体经验总结

通过本次 RAM 访存调试，主要经验有：

1. 访存指令一定要区分 ROM 和 RAM。
2. RISC-V 使用字节地址，Logisim RAM 使用 word 地址时要右移 2 位。
3. 单周期 `lw` 需要 RAM 支持异步读。
4. RAM 最好设置为读写数据总线分离。
5. 修改 RAM 属性后要重新检查 RAM 内容。
6. CPU 的 CLR 不一定清空 RAM。
7. `lw` 写 GPR，`sw` 写 RAM。
8. `sw` 不应该让 GPR_wen 有效。
9. 调试访存时要观察地址、RAM 输入、RAM 输出、写使能和写回选择。