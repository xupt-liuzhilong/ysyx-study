# LCTHW ex04-ex08：基础语法与数据表示

## ex04：变量与未初始化值

局部变量如果没有初始化，其值不能直接依赖。

```c
int height;
printf("%d\n", height);
```

编译器可能警告：

```text
'height' is used uninitialized
```

Valgrind 可能报告：

```text
Conditional jump or move depends on uninitialised value(s)
```

正确习惯：

```c
int height = 72;
```

常用编译方式：

```bash
gcc -Wall -Wextra -g file.c -o file
```

- `-Wall`：常用警告；
- `-Wextra`：额外警告；
- `-g`：加入调试信息。

## ex05：变量与输出

```c
int distance = 100;
printf("You are %d miles away.\n", distance);
```

建立：

```text
变量保存数据
↓
printf 按格式解释数据
↓
输出
```

## ex06：格式说明符与类型

常见对应：

```text
int      -> %d
unsigned -> %u
char     -> %c
char *   -> %s
double   -> %f
pointer  -> %p
```

错误示例：

```c
char initial = 'A';
printf("%s\n", initial);
```

`%s` 需要 `char *`，却传入一个字符值，可能产生：

- `-Wformat` 警告；
- Valgrind `Invalid read`；
- `SIGSEGV`。

## ex07：计算与类型转换

整数除法：

```c
5 / 2
```

结果为：

```text
2
```

浮点除法：

```c
5.0 / 2
```

结果为：

```text
2.5
```

显式转换：

```c
(double)a / b
```

用于明确控制运算类型。

## ex08：数组与 sizeof

```c
int areas[5] = {10, 12, 13, 14, 20};
```

若：

```text
sizeof(int) = 4
```

则：

```text
sizeof(areas) = 20
```

数组元素个数：

```c
sizeof(areas) / sizeof(areas[0])
```

字符数组：

```c
char name[] = "Zed";
```

内存：

```text
Z e d \0
```

因此：

```text
sizeof(name) = 4
```

### `\0` 的意义

实验：

```c
char demo[] = "ZedX";
demo[3] = '\0';
printf("%s\n", demo);
```

输出：

```text
Zed
```

说明 C 字符串从首地址开始读取，遇到 `\0` 停止。

## 本阶段重点

```text
C 源代码
↓
变量和类型
↓
编译器检查
↓
内存中的真实数据
↓
运行行为
```

这套思维会直接用于后续系统程序和模拟器。

