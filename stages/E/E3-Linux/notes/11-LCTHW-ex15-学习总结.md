# Learn C The Hard Way：Ex15 指针与数组学习总结

## 1. 核心目标

Ex15 的重点是理解：

- 数组与指针访问的关系；
- 指针算术；
- `*` 解引用；
- 指针类型；
- 指针与数组边界；
- `char **` 这类二级指针；
- 命令行参数 `argv` 与指针的关系。

最重要的等价关系：

```c
a[i] == *(a + i)
```

例如：

```c
ages[i] == *(ages + i)
names[i] == *(names + i)
```

---

## 2. 一维整数数组与指针

```c
int ages[] = {23, 43, 12, 89, 2};
int *cur_age = ages;
```

于是：

```c
ages[0]
*ages
*cur_age
```

都可以得到：

```text
23
```

进一步：

```c
ages[2]
*(ages + 2)
*(cur_age + 2)
cur_age[2]
```

都可以访问第三个元素 `12`。

---

## 3. 字符串指针数组与 `char **`

```c
char *names[] = {
    "Alan", "Frank",
    "Mary", "John", "Lisa"
};
```

`names` 的每个元素类型是：

```c
char *
```

因此：

```c
char **cur_name = names;
```

可以理解为：

```text
cur_name
   |
   v
+---------+---------+---------+
| char *  | char *  | char *  |
+----|----+----|----+----|----+
     |         |         |
     v         v         v
   "Alan"    "Frank"   "Mary"
```

所以：

```c
*cur_name
```

得到的是一个 `char *`，也就是 `"Alan"` 的地址。

---

## 4. 为什么 `a[i]` 等价于 `*(a+i)`

```c
ages + i
```

表示从 `ages` 首元素地址开始移动 `i` 个 `int`。

然后：

```c
*(ages + i)
```

解引用该地址，取得对应元素。

因此：

```c
ages[i]
```

本质上可以理解成：

```c
*(ages + i)
```

---

## 5. 指针算术不是普通整数加法

实验中观察真实地址：

```text
ages + 0 = ...f70
ages + 1 = ...f74
ages + 2 = ...f78
```

每次增加 4 字节，因为：

```c
sizeof(int) == 4
```

对于：

```c
char **cur_name = names;
```

实验中：

```text
names + 0 = ...f90
names + 1 = ...f98
names + 2 = ...fa0
```

每次增加 8 字节，因为当前 64 位环境中：

```c
sizeof(char *) == 8
```

因此：

> 指针加 1，表示移动一个“该指针所指类型”的元素，而不是简单移动 1 字节。

---

## 6. 数组与指针的 `sizeof` 区别

实验结果：

```text
sizeof(ages) = 20
sizeof(cur_age) = 8

sizeof(names) = 40
sizeof(cur_name) = 8
```

原因：

```c
int ages[5];
```

整个数组占：

```text
5 * 4 = 20 字节
```

而：

```c
int *cur_age;
```

只是一个指针变量，在当前 64 位环境中占 8 字节。

同理：

```c
char *names[5];
```

是 5 个指针组成的数组：

```text
5 * 8 = 40 字节
```

而：

```c
char **cur_name;
```

本身仍然只是一个指针，所以为 8 字节。

这说明：

> 数组和指针虽然访问语法关系密切，但它们本身不是同一个东西。

---

## 7. 指针类型非常重要

错误实验：

```c
int *cur_age = (int *)names;
```

`names` 原本是字符串指针数组，但强制转换后，被当作 `int *` 使用。

结果打印出了错误的大整数年龄。

原因：

```text
原来的内存内容
   ↓
char * 指针地址
   ↓
错误地按照 int 数据读取
```

强制类型转换只是告诉编译器“按照这个类型解释”，并不会自动让底层数据变成正确类型。

因此：

> 指针类型决定了内存如何被解释，以及指针算术每次移动多少字节。

---

## 8. 数组边界和尾后指针

长度为 5：

```c
int ages[5];
```

合法下标：

```text
0 1 2 3 4
```

可以形成：

```c
ages + 5
```

它是尾后位置，可以用于比较或表示循环终点。

但不能：

```c
*(ages + 5)
```

因为这等价于：

```c
ages[5]
```

属于越界访问。

实验中把：

```c
(cur_age - ages) < count
```

改成：

```c
(cur_age - ages) <= count
```

最终运行到：

```text
offset = 5
Segmentation fault (core dumped)
```

因此：

> 尾后指针允许存在，但不能被解引用。

---

## 9. 安全的倒序指针遍历

更稳妥的方式：

```c
cur_age = ages + count;
cur_name = names + count;

while (cur_age != ages) {
    cur_age--;
    cur_name--;

    printf("%s lived %d years so far.\n",
           *cur_name, *cur_age);
}
```

逻辑：

```text
尾后位置
   ↓
先 --
   ↓
最后一个元素
   ↓
不断 --
   ↓
第一个元素
   ↓
停止
```

---

## 10. `*&` 和 `&*`

```c
int age = 23;
int *p = &age;
```

### `*(&age)`

```c
&age
```

取得 `age` 地址。

再：

```c
*(&age)
```

从地址取值，所以得到 `23`。

可以理解：

```text
*&x -> x
```

### `&(*p)`

```c
*p
```

找到 `p` 所指向的对象。

再：

```c
&(*p)
```

重新取得这个对象的地址。

在 `p` 是合法可解引用指针的情况下：

```c
&(*p) == p
```

为真。

---

## 11. `argv` 与二级指针

```c
int main(int argc, char *argv[])
```

其中：

```c
argv
```

可以按：

```c
char **
```

来理解。

例如：

```c
char **cur_arg = argv;
```

然后：

```c
while (*cur_arg != NULL) {
    printf("%s\n", *cur_arg);
    cur_arg++;
}
```

运行：

```bash
./ex15_args hello ysyx linux
```

可以依次得到：

```text
./ex15_args
hello
ysyx
linux
```

结构：

```text
argv
 |
 v
+---------+---------+---------+---------+------+
| char *  | char *  | char *  | char *  | NULL |
+----|----+----|----+----|----+----|----+------+
     |         |         |         |
     v         v         v         v
  程序名    "hello"    "ysyx"   "linux"
```

---

## 12. 数组传入函数

扩展实验：

```c
void print_by_index(char **names, int *ages, int count)
{
    for (int i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
               names[i], ages[i]);
    }
}
```

调用：

```c
print_by_index(names, ages, count);
```

虽然函数形参写成：

```c
char **names
int *ages
```

但函数内部仍然可以使用：

```c
names[i]
ages[i]
```

访问原数组。

也可以改为：

```c
*(names + i)
*(ages + i)
```

> 这部分函数化练习属于为了理解指针传参而增加的扩展，不是官方 Ex15 原附加题。

---

## 13. `%p` 打印地址

打印指针时使用：

```c
printf("%p\n", (void *)ptr);
```

通过实际地址可以验证：

```c
ages + i == cur_age
names + i == cur_name
```

也能直接观察不同类型指针的移动步长。

> `%p` 地址观察同样属于理解指针算术的扩展实验。

---

## 14. 最终需要记住的核心

不需要死记 Ex15 中的每一种循环，真正需要掌握的是：

```c
a[i] == *(a + i)
```

```c
int *p = ages;
char **q = names;
```

```text
p + 1
移动 sizeof(*p) 字节
```

```text
数组 != 指针
```

```text
尾后指针可以存在
尾后指针不能解引用
```

```text
指针类型决定：
1. 如何解释内存
2. 每次指针运算移动多少
```

以及：

```text
char ** -> 指向 char * 的指针
```

这些内容会直接帮助后续理解：

- 命令行参数；
- 字符串；
- 动态内存；
- 数据结构；
- NEMU 中的内存访问；
- 模拟器中的指针操作。

---

## 学习状态

Ex15 已基本掌握：

- [x] 数组下标访问
- [x] 指针偏移访问
- [x] 指针自增
- [x] 二级指针
- [x] 指针类型错误实验
- [x] 数组越界实验
- [x] 倒序遍历
- [x] `argv` 指针遍历
- [x] `*&` / `&*`
- [x] 地址观察
- [x] 函数指针传参扩展

下一步：按照官方 Learn C The Hard Way 文档收尾 Ex15，并进入 Ex16。

