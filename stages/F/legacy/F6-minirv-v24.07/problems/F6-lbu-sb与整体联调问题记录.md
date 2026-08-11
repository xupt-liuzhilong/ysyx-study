# 问题记录：F6 lbu、sb 与整体联调问题

## 一、问题概况

在实现 `lbu`、`sb` 和整体联调测试过程中，主要遇到的问题集中在：

```text
1. 字节选择逻辑
2. RAM byte enable 配置
3. sb 写入数据位置
4. Store 类指令立即数选择
5. 整体测试中 sb 写错字节
```

这些问题都和 RISC-V 的字节地址、Logisim RAM 的 32 位 word 地址，以及小端序有关。

------

## 二、问题一：lbu 需要同时使用 mem_addr[7:2] 和 mem_addr[1:0]

### 现象

一开始容易只关注 RAM 地址：

```text
RAM_addr = add_result[7:2]
```

但 `lbu` 读取的是字节，不是整个 word，所以还需要选择 word 内部的某个 byte。

------

### 原因分析

RISC-V 使用字节地址。

Logisim RAM 设置为 32 位宽时，一个 RAM 地址对应 4 个字节。

因此：

```text
add_result[7:2] 用来选择哪个 32 位 word
add_result[1:0] 用来选择这个 word 中的哪个 byte
```

例如：

```text
RAM[1] = 12345678
```

小端序下：

```text
地址 4 → 78
地址 5 → 56
地址 6 → 34
地址 7 → 12
```

------

### 解决方法

实现 `lbu` 时加入 4 选 1 字节选择 MUX：

```text
byte_sel = add_result[1:0]
```

对应关系：

```text
00 → RAM_DataOut[7:0]
01 → RAM_DataOut[15:8]
10 → RAM_DataOut[23:16]
11 → RAM_DataOut[31:24]
```

选择出的 8 位数据再零扩展为 32 位写回寄存器。

------

## 三、问题二：sb 必须使用 RAM byte enable

### 现象

`sw` 可以直接写整个 32 位 word，但是 `sb` 只写 1 个字节。

如果 RAM 仍然设置为：

```text
Whole word read/write only
```

就无法方便地只修改一个 byte。

------

### 解决方法

将 RAM 属性改为：

```text
Enables = Use byte enables
Read write control = Use byte enables
```

这样 RAM 会出现 4 个字节写使能。

对于 `sw`：

```text
byte_enable = 1111
```

对于 `sb`：

```text
byte_sel = 00 → byte_enable = 0001
byte_sel = 01 → byte_enable = 0010
byte_sel = 10 → byte_enable = 0100
byte_sel = 11 → byte_enable = 1000
```

------

## 四、问题三：sb 写入数据要放到对应字节位置

### 现象

`sb` 只写 `rdata2[7:0]`，但 RAM DataIn 是 32 位。

如果直接把低 8 位接到 RAM DataIn 的低 8 位，那么只能正确写 byte0，不能正确写 byte1、byte2、byte3。

------

### 解决方法

根据 `byte_sel` 生成不同位置的 `sb_wdata`：

```text
byte_sel = 00 → 000000AA
byte_sel = 01 → 0000AA00
byte_sel = 10 → 00AA0000
byte_sel = 11 → AA000000
```

实现方式：

```text
用 rdata2[7:0] 构造 4 路 32 位数据
再通过 4 选 1 MUX 选择
选择信号为 add_result[1:0]
```

最后：

```text
sw → RAM_DataIn = rdata2
sb → RAM_DataIn = sb_wdata
```

------

## 五、问题四：整体联调时 RAM[1] 变成 AA00001E

### 现象

整体测试程序中，执行到第 9 拍：

```asm
sb x7, 5(x0)
```

预期：

```text
RAM[1] = 0000AA1E
```

但实际得到：

```text
RAM[1] = AA00001E
```

随后执行：

```asm
lbu x8, 5(x0)
```

结果：

```text
x8 = 00000000
```

而不是预期的：

```text
x8 = 000000AA
```

------

### 初步分析

`RAM[1] = AA00001E` 说明 `AA` 被写到了最高字节 byte3。

而 `lbu x8, 5(x0)` 读取的是 byte1，所以读到的是 0。

这说明 `lbu` 本身没有错，问题集中在 `sb` 的写入地址或字节选择上。

------

### 进一步定位

停在执行：

```asm
sb x7, 5(x0)
```

时观察信号，发现：

```text
RAM_DataIn = AA000000
add_result[1:0] = 11
```

这说明当前 `byte_sel` 选中了 byte3。

但是 `sb x7, 5(x0)` 正确地址应该是：

```text
mem_addr = 5
byte_sel = 01
RAM_DataIn = 0000AA00
```

实际 `byte_sel = 11`，说明地址算成了：

```text
mem_addr = 7
```

------

### 根本原因

`sb` 地址计算时错误使用了 I 型立即数。

对于机器码：

```text
007002A3
```

如果错误使用 I 型立即数：

```text
imm_i = instr[31:20] = 7
```

于是：

```text
mem_addr = x0 + 7
byte_sel = 11
RAM_DataIn = AA000000
```

而 `sb` 是 S 型指令，正确立即数应为：

```text
imm_s = {instr[31:25], instr[11:7]} = 5
```

所以正确应为：

```text
mem_addr = x0 + 5
byte_sel = 01
RAM_DataIn = 0000AA00
```

------

### 解决方法

将立即数选择信号从：

```text
select = is_sw
```

修改为：

```text
select = is_sw | is_sb
```

也就是定义：

```text
is_store = is_sw | is_sb
```

立即数选择：

```text
is_store = 0 → imm_i_ext
is_store = 1 → imm_s_ext
```

这样：

```text
addi / lw / lbu / jalr 使用 I 型立即数
sw / sb 使用 S 型立即数
```

修改后重新测试，结果正确：

```text
RAM[1] = 0000AA1E
x8 = 000000AA
```

------

## 六、问题五：sb 和 lbu 的 byte 顺序必须一致

### 经验

前面 `lbu` 已经验证：

```text
RAM[1] = 12345678
```

对应：

```text
地址 4 → 78
地址 5 → 56
地址 6 → 34
地址 7 → 12
```

因此 `sb` 也必须按照同样顺序写：

```text
地址 4 → 写 RAM_Data[7:0]
地址 5 → 写 RAM_Data[15:8]
地址 6 → 写 RAM_Data[23:16]
地址 7 → 写 RAM_Data[31:24]
```

否则就会出现写入位置和读取位置不一致的问题。

------

## 七、整体测试程序

用于最终联调的程序：

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

最终结果：

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

测试全部通过。

------

## 八、经验总结

本次调试的关键经验：

1. `lbu` 是读 byte，不是读 word。
2. `lbu` 需要用 `mem_addr[1:0]` 选择 32 位 word 中的某个字节。
3. `lbu` 读出的 8 位数据需要零扩展为 32 位。
4. `sb` 是写 byte，不是写 word。
5. `sb` 需要 RAM 支持 byte enable。
6. `sb` 的写入数据要根据 `byte_sel` 放到对应字节位置。
7. `sw` 和 `sb` 都是 S 型指令，都必须使用 S 型立即数。
8. Store 类指令的立即数选择信号应为 `is_sw | is_sb`。
9. 如果 `sb` 写到了错误字节，不要只怀疑 byte MUX，也要检查地址计算是否正确。
10. `lbu` 和 `sb` 的字节顺序必须保持一致。