# LCTHW ex13-ex14：Switch 与函数

## ex13：switch / case / break

基本结构：

```c
switch (value) {
    case A:
        ...
        break;

    case B:
        ...
        break;

    default:
        ...
        break;
}
```

### fall-through

故意删除：

```c
break;
```

后，GCC 给出：

```text
warning: this statement may fall through
```

运行时对 `e` 连续执行了 `E` 和 `I` 两段代码。

关键理解：

> `switch` 只在进入时寻找一次匹配入口。进入某个 `case` 后，如果没有 `break`，程序会继续向下顺序执行。

模型：

```text
找到 case
↓
进入
↓
顺序执行
↓
没有 break
↓
继续向下
↓
直到 break 或 switch 结束
```

`default` 用于处理所有未匹配情况。

## ex14：函数

函数调用关系：

```text
main
 ↓
print_arguments
 ↓
print_letters
 ↓
can_print_it
 ↓
isalpha / isblank
```

返回值函数：

```c
int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}
```

`void` 函数：

```c
void print_letters(char arg[])
{
    ...
}
```

`void` 表示不返回结果值。

### ctype.h

```c
#include <ctype.h>
```

使用：

```c
isalpha(ch)
isblank(ch)
```

用于判断字母和空白字符。

### 函数声明与函数定义

声明：

```c
int can_print_it(char ch);
```

定义：

```c
int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}
```

函数声明用于提前告诉编译器函数名称、参数和返回类型。以后 `.h` 头文件中会大量出现函数声明。

## 本阶段意义

```text
switch
↓
根据值选择执行路径

函数
↓
把程序拆成独立功能单元
```

下一节 ex15 将进入：

```text
地址
↓
指针
↓
解引用
↓
数组和指针
↓
char **
```

这是后续 NEMU / PA 代码阅读的重要基础。

