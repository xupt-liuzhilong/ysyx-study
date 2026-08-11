# 问题记录：F6 官方测试与 VGA 显示调试

## 一、问题概况

今天在 F6 后半部分主要调试了官方测试程序和 VGA 显示功能。

遇到和需要注意的问题主要包括：

```text
1. ROM/RAM 地址位宽不够
2. 官方 hex 需要同时加载到 ROM 和 RAM
3. RAM 不能被 CLR 清空
4. mem.hex/sum.hex 需要通过 PC 和 a0 判断结果
5. RGB Video 引脚不熟悉
6. VGA 地址译码
7. 写 VGA 时不能误写 RAM
8. vga.hex 需要更大的地址位宽
```

------

## 二、问题一：ROM/RAM 地址位宽不够

### 现象

之前手写小程序时，ROM/RAM 地址位宽较小，例如：

```text
Address Bit Width = 6
```

这只能访问很小的范围。

运行官方程序时，如果地址位宽不够，会出现：

```text
PC 跳转异常
取指错误
读写 RAM 错误
程序无法进入 halt
```

------

### 原因

官方程序中使用了较大的内存地址。

例如：

```text
mem.hex / sum.hex 需要访问高地址栈空间
vga.hex 使用到更大的数据区和图像数据
```

所以 ROM 和 RAM 的地址宽度必须扩大。

------

### 解决

运行 `mem.hex/sum.hex` 时，扩大 ROM/RAM 地址范围。

运行 `vga.hex` 时，使用：

```text
ROM Address Bit Width = 18
RAM Address Bit Width = 18
ROM Address = PC[19:2]
RAM Address = mem_addr[19:2]
```

------

## 三、问题二：hex 文件要同时加载 ROM 和 RAM

### 现象

如果只把 `.hex` 加载到 ROM，程序可能能取指，但运行中访问 RAM 时会读不到正确数据。

------

### 原因

官方 `.hex` 文件中不仅有指令，还有程序运行需要的数据。

因此：

```text
ROM 负责取指
RAM 负责数据访问
```

两边都需要同样的初始内容。

------

### 解决

每次运行官方程序都要：

```text
ROM → Load Image → xxx.hex
RAM → Load Image → xxx.hex
```

例如：

```text
ROM 加载 mem.hex
RAM 加载 mem.hex
ROM 加载 sum.hex
RAM 加载 sum.hex
ROM 加载 vga.hex
RAM 加载 vga.hex
```

------

## 四、问题三：CLR 不应该清 RAM

### 现象

运行官方程序前，需要清零 CPU 状态。

但如果 RAM 被清空，程序运行会出错。

------

### 原因

RAM 中存放了程序运行需要的数据。

如果 CLR 清了 RAM，就相当于把数据区清空。

------

### 解决

CLR 只清：

```text
PC
GPR
cycle_counter
```

不要清 RAM。

RAM 的初始化依靠：

```text
Load Image
```

------

## 五、问题四：如何判断 mem.hex/sum.hex 是否通过

### 判断标准

不能只看程序有没有跑，而要看：

```text
x10 / a0 是否为 0
PC 是否进入 halt 附近循环
```

------

### mem.hex 结果

```text
x10 = 00000000
PC 在 00001218 / 0000121C / 00001220 附近循环
```

结论：

```text
mem.hex 测试通过
```

------

### sum.hex 结果

```text
x10 = 00000000
PC 在 00000224 / 00000228 附近循环
```

结论：

```text
sum.hex 测试通过
```

------

## 六、问题五：RGB Video 引脚不熟悉

### 现象

一开始不清楚 RGB Video 底部几个引脚分别是什么。

网上查到的例子中有：

```text
dx
dy
color
stopped
pix_pos
continue
```

这些容易误以为是 RGB Video 的原生引脚。

------

### 原因

那些信号属于别人自己封装的图形控制模块，不是 RGB Video 本体。

------

### RGB Video 实际需要的核心信号

按照当前用法，RGB Video 主要连接：

```text
Reset
Clock
Write Enable
X coordinate
Y coordinate
Data / Color
```

本项目中连接为：

```text
Reset  ← CLR
Clock  ← CLK
WE     ← is_sw & isVGA
X      ← mem_addr[9:2]
Y      ← mem_addr[17:10]
Data   ← rdata2[23:0]
```

------

## 七、问题六：VGA 地址译码

### 目标

当 CPU 访问普通 RAM 地址时：

```text
写 RAM
```

当 CPU 访问 VGA 地址时：

```text
写 RGB Video
```

VGA 地址范围：

```text
0x20000000 ~ 0x2003FFFF
```

------

### 实现

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

## 八、问题七：写 VGA 时不能误写 RAM

### 现象

如果仍然保持原来的 RAM 写使能：

```text
RAM_WE = is_sw | is_sb
```

那么执行写 VGA 的 `sw` 时，可能同时写普通 RAM。

------

### 解决

增加 `isMem` 保护：

```text
RAM_WE = (is_sw | is_sb) & isMem
```

VGA 写使能：

```text
VGA_WE = is_sw & isVGA
```

这样：

```text
普通内存 store → 写 RAM
VGA 地址 sw    → 写 RGB Video
```

------

## 九、问题八：先做最小像素测试

### 原因

如果直接运行 `vga.hex`，出问题时难以判断是 CPU 错、地址译码错，还是 RGB Video 没接对。

------

### 解决

先写最小测试程序：

```asm
lui  x1, 0x20000
lui  x2, 0x00FF0
sw   x2, 0(x1)

lui  x3, 0x000FF
sw   x3, 4(x1)

jalr x0, 20(x0)
```

结果：

```text
屏幕左上角出现两个像素点变化
```

说明：

```text
RGB Video 写入通路正确
```

------

## 十、问题九：vga.hex 地址位宽

### 现象

运行 `vga.hex` 时，如果仍使用 17 位地址，程序可能无法正常运行。

------

### 原因

`vga.hex` 使用到更高地址的数据区和栈空间。

------

### 解决

使用：

```text
ROM Address Bit Width = 18
RAM Address Bit Width = 18
ROM Address = PC[19:2]
RAM Address = mem_addr[19:2]
```

这样地址空间足够运行 `vga.hex`。

------

## 十一、最终结果

运行 `vga.hex` 后，RGB Video 成功显示：

```text
“一生一芯”logo
```

说明：

```text
VGA 显示功能测试通过
F6 阶段完成
```

------

## 十二、经验总结

本次调试的主要经验：

1. 官方 hex 文件需要同时加载 ROM 和 RAM。
2. CPU 的 CLR 不应该清空 RAM。
3. 运行复杂程序时必须扩大 ROM/RAM 地址位宽。
4. 用 cycle_counter64 辅助观察运行周期。
5. 判断官方程序是否通过，要看 a0 和 PC 是否进入 halt。
6. VGA 显示属于内存映射 I/O。
7. `sw` 不一定只写 RAM，也可以通过地址译码写外设。
8. VGA 地址范围需要通过高位地址判断。
9. 写 VGA 时要屏蔽 RAM 写使能。
10. 复杂功能要先用最小测试程序验证，再跑官方大程序。