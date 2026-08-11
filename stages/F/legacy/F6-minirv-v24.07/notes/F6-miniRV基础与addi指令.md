# 学习记录：F6 miniRV 基础与 addi 指令

## 一、学习概况

今天开始学习一生一芯 F6 阶段：功能完备的迷你 RISC-V 处理器。

F6 阶段和 F5 不同。F5 中实现的是自己定义的简单 sCPU，只支持 `li`、`add`、`bner0` 三条指令；而 F6 开始要从自定义的 sISA 过渡到更加接近真实处理器的 miniRV，也就是简化版 RISC-V 处理器。

今天主要完成了：

- 理解 F6 和 F5 的区别
- 理解 miniRV 和 sISA 的区别
- 了解 miniRV 支持的 8 条指令
- 搭建 32 位 PC 取指模块
- 将 ROM 改为 32 位指令输出
- 理解 RISC-V 中 PC 每次加 4
- 使用 `PC[5:2]` 作为 ROM 地址
- 搭建 `gpr16x32` 通用寄存器堆
- 实现 `x0` 恒为 0
- 拆解 `addi` 指令字段
- 完成 12 位立即数符号扩展到 32 位
- 成功执行第一条 miniRV 指令：`addi a0, zero, 20`

------

## 二、F6 和 F5 的区别

F5 中的 sCPU 使用的是自定义的简单指令集 sISA：

```text
PC：4 位
GPR：4 个寄存器，每个 8 位
指令宽度：8 位
支持指令：li、add、bner0
```

F6 中的 miniRV 更接近真实 RISC-V：

```text
PC：32 位
GPR：16 个寄存器，每个 32 位
指令宽度：32 位
支持 RISC-V 风格指令
```

两者对比：

| 项目     | F5 sCPU       | F6 miniRV             |
| -------- | ------------- | --------------------- |
| 指令集   | 自定义 sISA   | 简化版 RISC-V         |
| 指令位宽 | 8 位          | 32 位                 |
| PC 位宽  | 4 位          | 32 位                 |
| PC 更新  | PC + 1        | PC + 4                |
| GPR 数量 | 4 个          | 16 个                 |
| GPR 位宽 | 8 位          | 32 位                 |
| r0/x0    | F5 中 r0 可写 | RISC-V 中 x0 永远为 0 |

F6 的核心目标是：

```text
把 F5 中的玩具 sCPU 升级为 miniRV 处理器
```

------

## 三、miniRV 支持的指令

F6 中 miniRV 支持 8 条指令：

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

按功能分类：

| 类型           | 指令   | 功能                    |
| -------------- | ------ | ----------------------- |
| 算术运算       | `add`  | `rd = rs1 + rs2`        |
| 立即数运算     | `addi` | `rd = rs1 + imm`        |
| 高位立即数装载 | `lui`  | `rd = imm << 12`        |
| 读内存         | `lw`   | 从内存读 32 位          |
| 读字节         | `lbu`  | 从内存读 1 字节并零扩展 |
| 写内存         | `sw`   | 写 32 位到内存          |
| 写字节         | `sb`   | 写 1 字节到内存         |
| 跳转           | `jalr` | 跳转并保存返回地址      |

今天重点学习并实现的是：

```text
addi
```

------

## 四、F6 取指模块

F6 中 RISC-V 指令宽度是 32 位，也就是 4 个字节。

因此 PC 不再像 F5 那样每次加 1，而是：

```text
PC_next = PC + 4
```

取指模块结构：

```text
PC Register
↓
PC[5:2]
↓
ROM Address
↓
instr[31:0]
```

其中：

```text
ROM_addr = PC >> 2
```

也就是使用：

```text
PC[5:2] → ROM Address
```

原因是：

| PC   | ROM 地址 |
| ---- | -------- |
| 0    | 0        |
| 4    | 1        |
| 8    | 2        |
| 12   | 3        |
| 16   | 4        |

ROM 设置：

```text
Address Bit Width = 4
Data Bit Width = 32
```

测试程序机器码：

```text
01400513
010000E7
00C000E7
00C00067
00A50513
00008067
```

测试结果：

| PC         | ROM_addr | instr      |
| ---------- | -------- | ---------- |
| `00000000` | 0        | `01400513` |
| `00000004` | 1        | `010000E7` |
| `00000008` | 2        | `00C000E7` |
| `0000000C` | 3        | `00C00067` |
| `00000010` | 4        | `00A50513` |
| `00000014` | 5        | `00008067` |

说明 32 位取指模块工作正常。

------

## 五、PC 清零与运行控制

今天搭建 PC 时发现：

```text
清零时 RUN 也必须为 1，PC 才会清零
```

原因是 PC Register 的写使能接了 `RUN`。当 `RUN = 0` 时，即使 `CLR = 1`，MUX 已经选择了 0，但寄存器不允许写入，因此 PC 不会清零。

改进方法：

```text
PC_WE = RUN | CLR
```

这样：

| RUN  | CLR  | PC 行为  |
| ---- | ---- | -------- |
| 0    | 0    | 保持     |
| 1    | 0    | 正常运行 |
| 0    | 1    | 清零     |
| 1    | 1    | 清零     |

这样清零时不需要打开 RUN。

------

## 六、gpr16x32 寄存器堆

F6 中需要实现 16 个 32 位通用寄存器：

```text
x0 ~ x15
```

封装模块：

```text
gpr16x32
```

接口设计：

输入：

```text
CLK
wen
waddr[3:0]
wdata[31:0]
raddr1[3:0]
raddr2[3:0]
```

输出：

```text
rdata1[31:0]
rdata2[31:0]
x0_debug[31:0]
x1_debug[31:0]
x10_debug[31:0]
```

其中：

- `wen`：写使能
- `waddr`：写寄存器地址
- `wdata`：写入数据
- `raddr1`：读端口 1 地址
- `raddr2`：读端口 2 地址
- `rdata1`：读端口 1 输出
- `rdata2`：读端口 2 输出

------

## 七、x0 恒为 0 的实现

RISC-V 中 `x0` 是特殊寄存器：

```text
x0 永远等于 0
写入 x0 不会改变它的值
```

今天采用方案 B 实现：

```text
x0 = 常量 0
x1 ~ x15 = 15 个 32 位寄存器
```

也就是说，不真正放置 x0 寄存器，而是让 MUX 的 input0 接常量 0。

这样天然保证：

```text
读 x0 一定得到 0
写 x0 不会改变任何寄存器
```

这是比“放一个 x0 寄存器但禁止写入”更稳定的做法。

------

## 八、gpr16x32 测试

测试内容包括：

### 1. 写 x1

```text
wen = 1
waddr = 0001
wdata = 0000000A
CLK 上升沿
```

预期：

```text
x1 = 0000000A
```

### 2. 写 x10

```text
wen = 1
waddr = 1010
wdata = 00000014
CLK 上升沿
```

预期：

```text
x10 = 00000014
```

### 3. 读端口测试

设置：

```text
raddr1 = 0001
raddr2 = 1010
```

预期：

```text
rdata1 = 0000000A
rdata2 = 00000014
```

### 4. x0 测试

设置：

```text
raddr1 = 0000
```

预期：

```text
rdata1 = 00000000
```

测试结果均符合预期，说明 `gpr16x32` 工作正常。

------

## 九、addi 指令格式

`addi` 是 I 型指令。

指令格式：

```text
31        20 19   15 14 12 11    7 6      0
imm[11:0]   rs1    funct3   rd     opcode
```

字段拆分：

```text
opcode = instr[6:0]
rd     = instr[11:7]
funct3 = instr[14:12]
rs1    = instr[19:15]
imm    = instr[31:20]
```

`addi` 的功能：

```text
R[rd] = R[rs1] + sign_extend(imm[11:0])
PC = PC + 4
```

对于第一条指令：

```text
instr = 01400513
```

对应汇编：

```asm
addi a0, zero, 20
```

也就是：

```asm
addi x10, x0, 20
```

字段拆分结果：

```text
rd  = 01010  → x10
rs1 = 00000  → x0
imm = 000000010100 → 20
```

因为当前 `gpr16x32` 只有 16 个寄存器，所以连接时使用寄存器编号低 4 位：

```text
rd[3:0]  → waddr
rs1[3:0] → raddr1
```

对于 `x10`：

```text
rd = 01010
rd[3:0] = 1010
```

正好对应 `x10`。

------

## 十、addi 立即数符号扩展

`addi` 的立即数是 12 位，但寄存器和 ALU 都是 32 位，所以需要符号扩展。

符号扩展规则：

```text
imm_ext[11:0]  = imm[11:0]
imm_ext[31:12] = 重复 imm[11]
```

如果 `imm[11] = 0`，说明是正数，高位补 0。

如果 `imm[11] = 1`，说明是负数，高位补 1。

本次指令：

```text
imm = 000000010100
```

最高位为 0，所以扩展后：

```text
imm_ext = 00000014
```

在 Logisim 中使用：

```text
Bit Extender
```

设置：

```text
Input Bit Width = 12
Output Bit Width = 32
Extension Type = Sign
```

------

## 十一、addi 数据通路

`addi` 的数据通路为：

```text
instr[19:15] → rs1 → gpr16x32.raddr1
gpr16x32.rdata1 → adder32.A

instr[31:20] → sign extend → imm_ext
imm_ext → adder32.B

adder32.S → gpr16x32.wdata
instr[11:7] → rd → gpr16x32.waddr
wen = 1
```

也就是：

```text
GPR[rs1] + sign_extend(imm) → GPR[rd]
```

执行第一条指令时：

```text
x0 + 20 → x10
```

因为：

```text
x0 = 0
```

所以：

```text
x10 = 20
```

------

## 十二、addi 测试结果

初始状态：

```text
PC = 00000000
instr = 01400513
x10 = 00000000
```

执行一次时钟后：

```text
PC = 00000004
instr = 010000E7
x10 = 00000014
```

其中：

```text
00000014 = 20
```

说明成功执行：

```asm
addi a0, zero, 20
```

也就是：

```text
x10 = x0 + 20
```

结果正确。

------

## 十三、今天的核心理解

今天最重要的理解有：

1. F6 是从自定义 sCPU 升级到 miniRV 处理器。
2. RISC-V 指令宽度是 32 位。
3. RISC-V 中 PC 默认每次加 4。
4. ROM 地址不能直接接 PC 低位，而要用 `PC[5:2]`。
5. F6 的 GPR 是 16×32 位。
6. RISC-V 的 `x0` 永远为 0。
7. `addi` 是 I 型指令。
8. `addi` 的立即数需要符号扩展。
9. `addi a0, zero, 20` 本质上就是把 20 写入 `x10`。
10. F6 的数据通路仍然延续 F5 思想：取指、译码、执行、写回、更新 PC。

------

## 十四、下一步计划

下一次继续学习并实现：

```text
jalr
```

`jalr` 指令功能为：

```text
rd = PC + 4
PC = (rs1 + imm) & ~1
```

下一步重点：

- 拆解 `jalr` 指令字段
- 理解跳转目标地址计算
- 理解为什么要把地址最低位清 0
- 实现 PC 在 `PC+4` 和跳转地址之间选择
- 实现把 `PC+4` 写回 `rd`