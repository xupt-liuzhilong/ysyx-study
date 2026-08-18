# 07-Learn C The Hard Way ex00-ex04 学习总结

## 一、今日学习范围

今天继续按照一生一芯 v26.07 学习路线推进 E3-Linux，在 `07_learn_c_the_hard_way` 中完成了前五个小节的练习。

- ex00：Linux 下 C 程序编译、运行与基础工具
- ex01：GCC / Make / GDB 工具检查
- ex02：Makefile 基础与增量编译
- ex03：`printf` 格式化输出
- ex04：GDB 调试与段错误定位

## 二、ex00：编译与基础工具

完成了：

```bash
gcc ex1.c -o ex1
./ex1
file ex1.c
file ex1
ls -l
ls -lh
cp
mv
man
```

认识到 `.c` 文件是 C 源代码文本，编译后的程序是 ELF 可执行文件。

通过故意制造语法错误观察 GCC 报错，并继续使用：

```bash
gcc -Wall -Wextra ex1.c -o ex1
```

其中 `-Wall` 和 `-Wextra` 用于开启常见和额外警告。

## 三、ex01：开发工具检查

确认当前 Ubuntu 中 GCC、Make、GDB 均可正常使用：

```bash
gcc --version
make --version
gdb --version
command -v gcc
command -v make
command -v gdb
```

## 四、ex02：Makefile 与增量编译

练习了：

```bash
make ex1
make
make clean
touch ex1.c
make
```

理解了 Make 会根据目标文件与依赖文件的时间戳判断是否需要重新构建。

如果源文件没有变化，`make` 会提示：

```text
Nothing to be done
```

## 五、ex03：printf 格式化输出

掌握了常用格式：

```text
%d    十进制整数
%x    十六进制（小写）
%X    十六进制（大写）
%o    八进制
%s    字符串
%f    浮点数
```

宽度和精度：

```text
%8d     宽度至少 8，右对齐
%-8d    宽度至少 8，左对齐
%08d    宽度至少 8，不足补 0
%.2f    保留两位小数
%10.2f  总宽度至少 10，小数两位
```

重点掌握：

```c
printf("PC = 0x%08x\n", pc);
```

其中 `%08x` 表示十六进制固定 8 位，不足部分补 0。

还练习了：

```text
\n    换行
\t    Tab
\"    输出双引号
\\    输出反斜杠
```

## 六、ex04：GDB 调试

编译时加入调试信息：

```bash
gcc -Wall -Wextra -g ex4.c -o ex4
```

练习了常用 GDB 命令：

```text
list          查看源码
break / b     设置断点
run / r       运行
next / n      单步，不进入函数
step / s      单步，进入函数
print / p     查看变量
info args     查看函数参数
info locals   查看局部变量
backtrace/bt  查看调用栈
frame         切换栈帧
finish        执行完当前函数
continue / c  继续运行
quit / q      退出
```

理解了 GDB 停在某一行时，通常表示该行“准备执行”，执行 `next` 或 `step` 后变量状态才会更新。

## 七、使用 GDB 定位段错误

通过空指针示例：

```c
int *ptr = NULL;
print_value(ptr);
```

并在函数中执行：

```c
printf("value = %d\n", *p);
```

运行出现 `Segmentation fault`。

随后使用：

```gdb
run
bt
list
print p
frame 1
```

定位到：

```text
p = 0x0
```

最终确认问题为“空指针解引用”。

修复：

```c
int value = 42;
int *ptr = &value;
```

重新编译运行后程序正常。

## 八、今日收获

今天已经能够把 Linux 下 C 开发流程串起来：

```text
写代码
→ GCC 编译
→ 查看 warning / error
→ Make 管理构建
→ 运行程序
→ GDB 调试
→ 定位并修复问题
```

目前已经具备继续后续 E 阶段和 PA / NEMU 初期调试所需要的基础工具能力。

## 九、后续计划

下一次从 `ex05` 开始继续。

后续策略：

- 已掌握的 C 基础快速通过
- Linux 开发工具链重点练习
- 指针、内存、调试、编译等系统相关内容重点理解
- 与一生一芯后续 PA / NEMU 直接相关的知识做好记录

