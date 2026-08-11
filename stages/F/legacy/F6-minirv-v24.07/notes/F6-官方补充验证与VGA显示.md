# 学习记录：F6 官方补充验证与 VGA 图形显示

## 一、学习概况

今天继续完成一生一芯 F6 阶段后半部分内容。

在前面已经完成 miniRV 8 条指令：

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

的基础上，今天主要补充完成了三部分内容：

```text
1. 补验证
2. 补官方笔记
3. 做展示功能
```

最终完成：

```text
addi 负立即数测试通过
sb 四字节覆盖测试通过
mem.hex 官方测试通过
sum.hex 官方测试通过
cycle_counter64 完成
VGA / RGB Video 显示功能完成
vga.hex 运行成功
成功显示“一生一芯”logo
```

至此，F6 阶段功能完备的 miniRV 处理器基本完成。

------

## 二、补验证：addi 负立即数测试

### 1. 测试目的

之前测试 `addi` 时，主要使用的是正数立即数，例如：

```asm
addi x1, x0, 10
addi x2, x0, 20
addi x7, x0, 0xAA
```

这些只能证明加法和写回通路基本正确，不能证明立即数符号扩展是否正确。

因此补充测试负立即数：

```text
验证 I 型立即数 sign_extend 是否正确
```

------

### 2. 测试程序

```asm
addi x1, x0, -1
addi x2, x0, -2
addi x3, x1, 1
addi x4, x2, 2
jalr x0, 16(x0)
```

机器码：

```text
FFF00093
FFE00113
00108193
00210213
01000067
```

------

### 3. 预期结果

```text
x1 = FFFFFFFF
x2 = FFFFFFFE
x3 = 00000000
x4 = 00000000
PC = 00000010
```

测试结果正确，说明：

```text
I 型立即数符号扩展正确
addi 对负立即数支持正确
写回通路正常
```

------

## 三、补验证：sb 四字节覆盖测试

### 1. 测试目的

之前已经测试过：

```asm
sb x7, 5(x0)
```

能把 `AA` 写入 `RAM[1]` 的 byte1。

但是为了完整验证 `sb`，还需要确认 4 个字节位置都能正确写入。

重点验证：

```text
byte_sel = 00 / 01 / 10 / 11
BE0 / BE1 / BE2 / BE3
sb_wdata 四路选择
小端序字节位置
```

------

### 2. 初始 RAM

先将：

```text
RAM[1] = 12345678
```

------

### 3. 测试程序

```asm
lw   x5, 4(x0)

addi x6, x0, 0x90
sb   x6, 7(x0)

addi x6, x0, 0xAB
sb   x6, 6(x0)

addi x6, x0, 0xCD
sb   x6, 5(x0)

addi x6, x0, 0xEF
sb   x6, 4(x0)

lw   x7, 4(x0)
jalr x0, 40(x0)
```

机器码：

```text
00402283
09000313
006003A3
0AB00313
00600323
0CD00313
006002A3
0EF00313
00600223
00402383
02800067
```

------

### 4. 预期结果

执行过程：

```text
初始 RAM[1] = 12345678

sb x6, 7(x0) → RAM[1] = 90345678
sb x6, 6(x0) → RAM[1] = 90AB5678
sb x6, 5(x0) → RAM[1] = 90ABCD78
sb x6, 4(x0) → RAM[1] = 90ABCDEF
```

最终：

```text
x7 = 90ABCDEF
RAM[1] = 90ABCDEF
```

测试结果正确，说明：

```text
sb 四个字节位置全部正确
byte_enable 控制正确
sb_wdata 生成正确
lbu/sb 字节顺序一致
```

------

## 四、补官方笔记：RISC-V 与 miniRV 基本理解

### 1. PC 位宽

当前 miniRV 按 32 位地址设计：

```text
PC = 32 bit
```

RISC-V 基础指令宽度为 32 位，所以正常顺序执行时：

```text
PC = PC + 4
```

取指 ROM 使用 word 地址，因此：

```text
ROM_addr = PC >> 2
```

在 Logisim 中就是取：

```text
PC[高位:2]
```

------

### 2. GPR 理解

RISC-V 中：

```text
RV32I 有 32 个通用寄存器 x0 ~ x31
RV32E 只有 16 个通用寄存器 x0 ~ x15
```

本阶段 miniRV 使用：

```text
gpr16x32
```

也就是：

```text
16 个寄存器
每个寄存器 32 位
```

其中：

```text
x0 永远为 0
```

所以硬件实现时，x0 不需要真正保存数据，可以直接接常量 0。

------

### 3. x0 和 F5 sISA 的 r0 不同

F5 sISA 中的 `r0` 是普通寄存器，可以被写入。

但 RISC-V 中的 `x0` 是硬件规定恒为 0 的寄存器：

```text
读 x0 永远得到 0
写 x0 的结果会被丢弃
```

因此当前 miniRV 的 `gpr16x32` 中：

```text
x0 = constant 0
x1 ~ x15 = 真实寄存器
```

------

### 4. 指令格式

本阶段涉及的主要格式：

```text
R 型：add
I 型：addi / lw / lbu / jalr
S 型：sw / sb
U 型：lui
```

其中：

```text
add   使用 R 型
addi  使用 I 型
lui   使用 U 型
lw    使用 I 型
lbu   使用 I 型
sw    使用 S 型
sb    使用 S 型
jalr  使用 I 型
```

------

### 5. funct3 对应关系

| 指令 | opcode  | funct3 | 说明                  |
| ---- | ------- | ------ | --------------------- |
| add  | 0110011 | 000    | 还要看 funct7=0000000 |
| addi | 0010011 | 000    | I 型立即数加法        |
| lui  | 0110111 | 无     | U 型指令没有 funct3   |
| lw   | 0000011 | 010    | load word             |
| lbu  | 0000011 | 100    | load byte unsigned    |
| sw   | 0100011 | 010    | store word            |
| sb   | 0100011 | 000    | store byte            |
| jalr | 1100111 | 000    | 跳转并链接寄存器      |

------

## 五、官方程序测试：mem.hex

### 1. 测试准备

运行官方 `.hex` 文件时，需要：

```text
ROM 加载 mem.hex
RAM 加载 mem.hex
```

因为 `.hex` 中既包含指令，也包含程序运行需要的数据。

同时，RAM 不能被 CLR 清空，只清 CPU 状态：

```text
PC
GPR
cycle_counter
```

------

### 2. 地址位宽调整

`mem.hex` 使用到较高内存地址，所以 ROM/RAM 地址位宽不能再用之前的小地址。

测试时将地址位宽扩大，并连接对应地址线：

```text
ROM Address ← PC[18:2]
RAM Address ← mem_addr[18:2]
```

------

### 3. 测试结果

运行后：

```text
x10 / a0 = 00000000
PC 在 00001218 / 0000121C / 00001220 附近循环
```

说明程序正常进入 halt，`mem.hex` 测试通过。

------

## 六、官方程序测试：sum.hex

### 1. 测试流程

和 `mem.hex` 一样：

```text
ROM 加载 sum.hex
RAM 加载 sum.hex
CLR 清 PC / GPR / cycle_counter
RUN 自动运行
```

------

### 2. 测试结果

运行后：

```text
x10 / a0 = 00000000
PC 在 00000224 / 00000228 附近循环
```

说明程序正常进入 halt，`sum.hex` 测试通过。

------

## 七、cycle_counter64

### 1. 添加目的

官方程序运行周期较多，不能再靠手动点 CLK 判断。

因此加入：

```text
cycle_counter64
```

用于统计 CPU 运行了多少个时钟周期。

------

### 2. 基本逻辑

输入：

```text
CLK
CLR
RUN
```

输出：

```text
cycle[63:0]
```

行为：

```text
CLR = 1 → cycle = 0
RUN = 1 → 每个 CLK 上升沿 cycle + 1
RUN = 0 → 保持
```

实现方式：

```text
64 位寄存器
64 位加法器
常量 1
MUX
```

测试结果正确。

------

## 八、做展示功能：VGA / RGB Video

### 1. 目标

F6 最后的展示功能是：

```text
通过 CPU 执行 sw 指令写显存
让 RGB Video 显示“一生一芯”logo
```

这属于内存映射 I/O。

CPU 不需要新增专门的显示指令，仍然使用普通的 `sw` 指令。

区别在于访问地址不同：

```text
普通内存地址 → 写 RAM
VGA 显存地址 → 写 RGB Video
```

------

### 2. VGA 显存地址范围

VGA 显存地址范围：

```text
0x20000000 ~ 0x2003FFFF
```

大小：

```text
0x40000 = 256KB
```

对应：

```text
256 × 256 × 4B
```

也就是 256×256 的屏幕，每个像素按 4 字节对齐。

------

### 3. 地址译码

用 `mem_addr` 判断当前访存是否访问 VGA。

因为：

```text
0x20000000 >> 18 = 0x0800
```

所以判断：

```text
isVGA = mem_addr[31:18] == 0x0800
isMem = ~isVGA
```

------

### 4. RAM 写保护

原来的 RAM 写使能是：

```text
RAM_WE = is_sw | is_sb
```

加入 VGA 后，需要避免写 VGA 时错误写 RAM：

```text
RAM_WE = (is_sw | is_sb) & isMem
```

VGA 写使能：

```text
VGA_WE = is_sw & isVGA
```

------

### 5. RGB Video 连接

RGB Video 设置：

```text
Color Model = 888 RGB
Width = 256
Height = 256
```

引脚连接：

```text
Reset  ← CLR
Clock  ← CLK
WE     ← is_sw & isVGA
X      ← mem_addr[9:2]
Y      ← mem_addr[17:10]
Data   ← rdata2[23:0]
```

其中：

```text
pixel_index = (mem_addr - 0x20000000) >> 2
x = pixel_index[7:0]  = mem_addr[9:2]
y = pixel_index[15:8] = mem_addr[17:10]
```

------

### 6. 最小像素测试

在运行 `vga.hex` 前，先写一个最小程序测试 VGA 写入通路：

```asm
lui  x1, 0x20000
lui  x2, 0x00FF0
sw   x2, 0(x1)

lui  x3, 0x000FF
sw   x3, 4(x1)

jalr x0, 20(x0)
```

机器码：

```text
200000B7
00FF0137
0020A023
000FF1B7
0030A223
01400067
```

测试结果：

```text
屏幕左上角出现两个像素点变化
```

说明：

```text
VGA 地址译码正确
VGA_WE 正确
X/Y 坐标生成正确
RGB Video 写入通路正确
```

------

## 九、运行 vga.hex

### 1. 地址位宽

`vga.hex` 使用的地址范围更大。

测试时使用：

```text
ROM Address Bit Width = 18
RAM Address Bit Width = 18
```

地址连接：

```text
ROM Address ← PC[19:2]
RAM Address ← mem_addr[19:2]
```

原因：

```text
vga 程序使用到 0x93000 附近的内存地址
17 位 word 地址不够
18 位 word 地址可以覆盖到 0x100000 字节
```

------

### 2. 加载程序

和前面一样：

```text
ROM 加载 vga.hex
RAM 加载 vga.hex
```

------

### 3. 运行结果

运行后，RGB Video 成功显示：

```text
“一生一芯”logo
```

说明：

```text
vga.hex 测试通过
VGA 图形显示功能完成
```

如果程序最终 PC 在：

```text
00000DB0
00000DB4
00000DB8
```

附近循环，则说明已经进入 halt。

------

## 十、当前 F6 完成情况

目前 F6 阶段已经完成：

```text
1. miniRV 8 条指令实现
2. addi 负立即数测试
3. sb 四字节覆盖测试
4. cycle_counter64
5. mem.hex 官方测试
6. sum.hex 官方测试
7. VGA 地址译码
8. RGB Video 显示通路
9. vga.hex 显示“一生一芯”logo
```

可以总结为：

```text
F6：功能完备的 miniRV 处理器完成
```

------

## 十一、下一步思考

通过 F6 可以明显感受到：

```text
Logisim 搭建 CPU 很直观
但电路规模变大后，连线复杂、调试困难、仿真速度慢
```

后续继续学习时，需要从 Logisim 手工搭电路逐步过渡到现代硬件设计方法，例如：

```text
使用硬件描述语言
使用更系统的仿真方法
使用自动化测试
使用更清晰的模块化设计
```

F6 阶段的重点不是只做出显示效果，而是理解：

```text
CPU 如何取指
如何译码
如何执行指令
如何访存
如何通过内存映射 I/O 控制外设
```