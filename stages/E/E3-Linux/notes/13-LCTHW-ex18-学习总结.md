# Ex18 函数指针学习总结

- 所属阶段：一生一芯 E3-Linux → Learn C The Hard Way
- 整理日期：2026-09-06
- 学习边界：8 月 29 日已介绍函数指针的最小示例；9 月 6 日继续完成主体、“如何使它崩溃”和 5 项附加题。
- 当前总进度：Ex19 也已完成本轮练习；**Ex20 尚未开始。**

## 一、这一章解决什么问题

同一个排序算法可以按照不同规则工作。把比较函数传给排序函数，就能在不改冒泡循环的情况下切换升序、降序或实验性的比较规则。附加题又把排序算法本身也变成参数，使“用什么算法”和“按什么规则比较”分别可选。

~~~text
test_sorting
    │
    ├── sorter：bubble_sort / selection_sort
    │
    └── cmp：sorted_order / reverse_order
~~~

这一章的核心是**用类型明确的函数指针传递行为**。

## 二、函数指针的声明、赋值和调用

### 1. 从名字向外读声明

~~~c
int (*tester)(int a, int b);
~~~

`tester` 是指针，指向接收两个 `int`、返回 `int` 的函数。括号不可省略：

| 声明 | 含义 |
| --- | --- |
| `int (*tester)(int, int);` | 函数指针变量 |
| `int *tester(int, int);` | 返回 `int *` 的函数 |

把函数赋给指针并调用：

~~~c
int sorted_order(int a, int b)
{
    return a - b;
}

int (*tester)(int, int) = sorted_order;
int result = tester(2, 3);
~~~

在这个赋值场景中，函数名会转换为函数指针；写 `&sorted_order` 也可以。`sorted_order` 是传递函数，`sorted_order(2, 3)` 是立即调用函数并取得结果。

### 2. 用 typedef 给类型命名

~~~c
typedef int (*compare_cb)(int a, int b);

compare_cb cmp = sorted_order;
~~~

`compare_cb` 是类型名，`cmp` 才是变量名。它等价于声明一个 `int (*)(int, int)` 类型的指针，不能随意传入参数个数或返回类型不兼容的函数。

## 三、主体程序的数据流与内存责任

主体包含 `die`、`bubble_sort`、三个比较函数、`test_sorting` 和 `main`。

~~~text
命令行字符串 argv[1..]
    ↓ atoi
numbers：整数数组
    ↓ bubble_sort 申请 target 并 memcpy
target：在副本上比较、交换
    ↓ return target
sorted：由 test_sorting 打印并 free
    ↓
main 最后 free(numbers)
~~~

关键接口：

~~~c
int *bubble_sort(int *numbers, int count, compare_cb cmp);
void test_sorting(int *numbers, int count, compare_cb cmp);
~~~

`main` 中：

~~~c
int count = argc - 1;
char **inputs = argv + 1;
~~~

`argv[0]` 是程序名，因此用 `argv + 1` 跳过它。`atoi(inputs[i])` 把字符串转为整数，存入新申请的 `numbers`。

排序函数先创建副本：

~~~c
int *target = malloc(count * sizeof(int));
if (!target)
    die("Memory error.");

memcpy(target, numbers, count * sizeof(int));
~~~

然后用回调控制交换：

~~~c
if (cmp(target[j], target[j + 1]) > 0) {
    temp = target[j + 1];
    target[j + 1] = target[j];
    target[j] = temp;
}
~~~

返回值约定是：在这里，`cmp(a, b) > 0` 表示当前两项顺序需要调整。真正决定这个条件何时成立的是比较函数。

| 内存 | 申请者 | 正常路径释放者 |
| --- | --- | --- |
| 原数组 `numbers` | `main` | `main` |
| 每次排序返回的数组 `target/sorted` | 排序函数 | `test_sorting` |

`target` 和 `sorted` 是不同函数里指向同一块返回数组的变量，不是两次分配。因为每次排序都复制 `numbers`，三种规则可以从同一份原始输入开始。

## 四、三个比较器与实际输出

~~~c
int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}
~~~

对今天的小整数输入：

~~~bash
./ex18 4 1 7 3 2 0 8
~~~

对话确认的输出：

~~~text
0 1 2 3 4 7 8
8 7 4 3 2 1 0
3 4 2 7 1 0 8
~~~

- `sorted_order` 返回 `a-b`，让较大的数向后移动，得到升序。
- `reverse_order` 返回 `b-a`，得到降序。
- `strange_order` 中，`7 % 3` 和 `3 % 7` 都为正，不能表达一致的普通大小关系。它用来观察回调如何改变算法行为，不能作为通用排序比较器。

**整理补充，未计作今天已修改的代码：** 对任意 `int` 使用 `a-b` 可能发生有符号溢出。更稳妥的升序比较表达式是 `(a > b) - (a < b)`，降序则是 `(a < b) - (a > b)`。有符号结果超出类型可表示范围的问题可对照 [C11 委员会草案 N1570 `6.5](https://open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)。今天的少量小整数输出正确，不代表已覆盖极值输入。

`atoi` 的使用属于本次教材版本；非法输入、范围检查及改用 `strtol` 尚未作为完成项。

## 五、“如何使它崩溃”：读取函数开头的字节

当时在 `test_sorting` 中加入：

~~~c
unsigned char *data = (unsigned char *)cmp;

for (i = 0; i < 25; i++) {
    printf("%02x:", data[i]);
}
printf("\n");
~~~

这次实际观察到了比较函数开头的 25 个字节；前缀类似：

~~~text
f3:0f:1e:fa:55:48:89:e5:89:7d:fc:89:75:f8:...
~~~

升序与降序函数结构接近，开头有相似字节；`strange_order` 还包含条件分支和取余，字节序列存在差异。机器码随平台、编译器及选项变化，不能把这组字节当作固定答案。

这里虽然属于教材“如何使它崩溃”部分，本次读取字节的步骤实际成功输出，并没有因此崩溃；随后 NULL 回调实验才明确触发了段错误。

**适用范围：** 把函数指针转成字节指针并读取代码，是这次 Linux 环境下的观察实验，ISO C 不保证其在所有平台可移植。不要把它推广为普通数据访问方式；函数指针与对象指针的转换边界见 [N1570 `6.3.2.3、附录 J.5.7](https://open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)。

## 六、5 项附加题及排错记录

### 1. 在 ELF 中寻找机器码

本次使用的查看方式：

~~~bash
xxd -g 1 ex18 | less
~~~

ELF 开头的魔数为：

~~~text
7f 45 4c 46
~~~

还使用连续十六进制输出搜索前缀：

~~~bash
xxd -p ex18 | tr -d '\n' | grep -o 'f30f1efa554889e5'
~~~

这一步按原对话已作为附加题完成。需要区分：搜索短前缀可以说明文件中有相同字节，不能仅凭共同前缀唯一定位某一个函数；函数开头可能相同。

### 2. 修改可执行文件中的字符串

目标：保留 `ex18.c` 和原版 `ex18`，只修改可执行文件副本中的提示文字。

~~~text
USAGE → HELLO
55 53 41 47 45 → 48 45 4c 4c 4f
~~~

两边都是 5 字节，保持文件布局长度不变；编辑 `xxd` 转储时应改十六进制数据区，右侧 ASCII 是阅读辅助。

本次实际经历了两个问题：

| 问题 | 判断及处理 |
| --- | --- |
| `E45: 'readonly' option is set` | 先用 `:set noreadonly` 处理 Vim 缓冲区选项；若仍不能写，再检查文件权限 |
| `ex18_mod` 段错误，原版 `ex18` 正常 | 说明修改后的副本异常；没有定位到具体被误改的字节，不能断言损坏了哪条指令 |

之后从原版重新导出十六进制文本，修改后生成新的文件：

~~~bash
xxd ex18 > ex18.hex
vim ex18.hex
xxd -r ex18.hex ex18_mod2
chmod +x ex18_mod2
./ex18_mod2
~~~

上面整理为便于复习的流程；关键操作是在 Vim 中把目标 5 字节改为 `HELLO`。最终截图确认：

~~~text
ERROR: HELLO: ex18 4 3 1 5 6
~~~

`cmp ex18 ex18_mod` 可用于检查副本是否与原版一致；`cmp -l` 可帮助列出不同字节。保留正常版本，可以把问题缩小到本轮二进制编辑，而不是误改源码来“修复”。

### 3. 传入类型不匹配的函数

在 `ex18_bad.c` 中故意加入：

~~~c
int wrong_order(int a)
{
    return a;
}

test_sorting(numbers, count, wrong_order);
~~~

编译：

~~~bash
gcc -Wall -Wextra -g ex18_bad.c -o ex18_bad
~~~

截图中的核心诊断：

~~~text
warning: passing argument 3 of 'test_sorting' from incompatible pointer type
expected 'compare_cb' {aka 'int (*)(int, int)'}
but argument is of type 'int (*)(int)'
~~~

本次 GCC 给出的是警告。此实验确认了函数指针签名不兼容；不同编译器和选项可能把诊断升级为错误，不能概括成“永远只警告”。没有把运行这个不兼容版本作为成功实验；通过不兼容函数指针调用函数会有未定义行为。

### 4. NULL 回调与 Valgrind

在副本 `ex18_null.c` 的三个正常测试后，再加：

~~~c
test_sorting(numbers, count, NULL);
~~~

本次输入：

~~~bash
./ex18_null 4 1 7 3 2 0 8
valgrind ./ex18_null 4 1 7 3 2 0 8
~~~

前面三个排序完成，第四次实际调用 `cmp(...)` 时发生：

~~~text
main
  → test_sorting(..., NULL)
  → bubble_sort(..., cmp)
  → cmp(target[j], target[j + 1])
  → 向 0x0 非法跳转
  → SIGSEGV
~~~

用户粘贴的报告摘录：

~~~text
Jump to the invalid address stated on the next line
at 0x0: ???
by ...: test_sorting (ex18_null.c:66)
by ...: main (ex18_null.c:108)
Process terminating with default action of signal 11 (SIGSEGV)

in use at exit: 1,080 bytes in 3 blocks
total heap usage: 6 allocs, 3 frees, 1,164 bytes allocated
definitely lost: 0 bytes in 0 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
still reachable: 1,080 bytes in 3 blocks
ERROR SUMMARY: 1 errors from 1 contexts
~~~

读取这份报告时先看**非法跳转与调用栈**，再看内存分类。它不是普通的数据读取错误；当前环境中是在尝试从无效地址执行代码。

`still reachable` 表示检查时仍可通过指针链找到相应堆块，不表示已经释放。程序异常终止，正常的 `free(sorted)` 与 `free(numbers)` 没有执行完。分类含义可对照 [Valgrind Memcheck 内存泄漏检测说明](https://valgrind.org/docs/manual/mc-manual.html#mc-manual.leaks)。

当时对 1,080 字节的解释是两个 28 字节数组加上可能的标准 I/O 缓冲区。两个数组与 7 个整数的输入相符，但缓冲区归属是结合环境的推测，摘要本身不能证明每一块内存的来源。

结论：**NULL 崩溃实验完成；这个故意破坏的版本并未通过内存安全检查。** “definitely lost 为 0”与“程序没有错误”是不同判断。

### 5. 再实现选择排序，增加算法回调

在 `ex18_extra.c` 中增加：

~~~c
typedef int *(*sort_cb)(int *numbers, int count, compare_cb cmp);
~~~

两个排序函数具有相同签名：

~~~c
int *bubble_sort(int *numbers, int count, compare_cb cmp);
int *selection_sort(int *numbers, int count, compare_cb cmp);
~~~

选择排序每一轮从未处理的区间选出按 `cmp` 应排在最前面的元素，再交换到当前位置。关键循环为：

~~~c
for (i = 0; i < count - 1; i++) {
    selected = i;

    for (j = i + 1; j < count; j++) {
        if (cmp(target[selected], target[j]) > 0) {
            selected = j;
        }
    }

    if (selected != i) {
        temp = target[i];
        target[i] = target[selected];
        target[selected] = temp;
    }
}
~~~

它仍先申请并复制数组，返回的内存仍由调用者释放。

改造后的测试函数接收两个回调：

~~~c
void test_sorting(int *numbers, int count,
                  sort_cb sorter, compare_cb cmp)
{
    int *sorted = sorter(numbers, count, cmp);

    if (!sorted)
        die("Failed to sort as requested.");

    for (int i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }

    printf("\n");
    free(sorted);
}
~~~

上面用局部循环变量压缩展示，核心与当时版本相同：原来的 `bubble_sort(...)` 改为 `sorter(...)`。

四组调用：

~~~c
test_sorting(numbers, count, bubble_sort, sorted_order);
test_sorting(numbers, count, bubble_sort, reverse_order);
test_sorting(numbers, count, selection_sort, sorted_order);
test_sorting(numbers, count, selection_sort, reverse_order);
~~~

编译运行：

~~~bash
gcc -Wall -Wextra -g ex18_extra.c -o ex18_extra
./ex18_extra 4 1 7 3 2 0 8
~~~

截图确认：

~~~text
Bubble sort:
0 1 2 3 4 7 8
8 7 4 3 2 1 0
Selection sort:
0 1 2 3 4 7 8
8 7 4 3 2 1 0
~~~

相同的有效比较规则配合两种算法，得到相同结果。本次最终对照的是升序和降序，没有把 `strange_order` 在不同算法间结果一致作为完成条件。

## 七、编译与实验版本管理

| 文件或产物 | 用途 |
| --- | --- |
| `ex18.c / ex18` | 主体及正常参照版本 |
| `ex18_mod` | 首次二进制编辑副本，曾发生段错误 |
| `ex18.hex` | 用于编辑的十六进制文本 |
| `ex18_mod2` | 重新生成并成功输出 HELLO 的版本 |
| `ex18_bad.c` | 回调类型不兼容实验 |
| `ex18_null.c` | NULL 回调崩溃与 Valgrind 实验 |
| `ex18_extra.c` | 冒泡、选择排序及双层回调 |

`make ex18` 利用 Makefile 中的编译选项构建程序；本章几个独立实验也使用了显式 GCC 命令。`-Wall -Wextra` 增加诊断，`-g` 保留调试信息；`gcc ... -c` 只生成目标文件，不执行最终链接。这为 Ex19 的多文件构建做了准备。

本次记录没有普通版或附加题版完整“Valgrind 零错误、零泄漏”的终局报告，因此不把它写入验收结果。

## 八、复习自检

以下是复习问题，不是新完成的测试：

- 能否区分 `int (*f)(int, int)` 与 `int *f(int, int)`？
- 能否说明 `compare_cb`、`cmp`、`cmp(a, b)` 分别是什么？
- 能否画出 `main → test_sorting → sorter → cmp` 的调用链？
- 能否指出原数组和返回数组分别由谁释放？
- 能否解释为什么 NULL 回调报告的是非法跳转？
- 能否说明 `still reachable`、没有确定泄漏、没有运行错误之间的区别？
- 能否解释为什么 `strange_order` 不适合用来验证两种算法结果一致？

Ex18 本轮练习已经完成。后续 Ex19 正是把本章的函数指针放入结构体中，用来表示对象的行为；**Ex20 尚未开始**。

