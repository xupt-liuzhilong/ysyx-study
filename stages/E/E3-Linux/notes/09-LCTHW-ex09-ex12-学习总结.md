# LCTHW ex09-ex12：数组、字符串与流程控制

## ex09：数组与字符串

```c
char name[4] = {'a'};
```

实际相当于：

```text
'a' '\0' '\0' '\0'
```

所以 `%s` 只输出 `a`。

比较：

```c
char name[4] = "Zed";
char *another = "Zed";
```

- `name` 是字符数组；
- `another` 是指针变量。

在当前 64 位环境中通常：

```text
sizeof(name) = 4
sizeof(another) = 8
```

结论：

> 数组和指针关系密切，但数组不是指针。

## ex10：字符串数组与 argv

执行：

```bash
./ex10 hello ysyx linux
```

结构：

```text
argc = 4
argv[0] -> "./ex10"
argv[1] -> "hello"
argv[2] -> "ysyx"
argv[3] -> "linux"
argv[4] -> NULL
```

`char *argv[]` 可以理解为字符指针数组。

```c
argv[1]
```

得到 `"hello"` 的首地址。

```c
argv[1][0]
```

得到 `'h'`。

实验验证：

```c
argv[1] == &argv[1][0]
```

## ex11：while 循环

```c
for (i = 0; i < argc; i++) {
    ...
}
```

可理解为：

```c
i = 0;

while (i < argc) {
    ...
    i++;
}
```

注意忘记更新循环变量可能形成死循环。

## ex12：if / else-if / else

```c
if (argc == 1) {
    ...
} else if (argc > 1 && argc < 4) {
    ...
} else {
    ...
}
```

测试：

```text
argc = 1   -> if
argc = 2/3 -> else if
argc >= 4  -> else
```

判断链从上向下执行，找到第一个成立条件后整条链结束。

## 本阶段知识连接

```text
字符数组
↓
C 字符串
↓
字符串首地址
↓
char *
↓
char *argv[]
↓
命令行参数
↓
循环
↓
条件判断
```

为正式学习指针做准备。

