# 第一讲：课程概览与 Shell 学习总结

日期：2026-07-25  
阶段：一生一芯 E3 Linux  
课程：Missing Semester 第一讲——课程概览与 Shell

## 一、Shell 的基本作用

Shell 是用户与操作系统交互的重要工具。它可以：

- 执行程序
- 管理文件和目录
- 组合多个命令
- 进行输入输出重定向
- 编写自动化脚本

常见 Shell：

```text
bash
zsh
sh
```

本次学习环境使用：

```bash
echo "$SHELL"
```

结果：

```text
/bin/bash
```

---

## 二、文件与目录操作

常用命令：

```bash
pwd
ls
ls -l
ls -la
cd 目录
cd ..
cd ~
mkdir 目录
mkdir -p 多级目录
touch 文件
rm 文件
rm -r 目录
cp 源文件 目标位置
mv 源文件 目标位置
```

### 路径

- 绝对路径：从根目录 `/` 开始
- 相对路径：相对于当前目录
- `.`：当前目录
- `..`：上一级目录
- `~`：当前用户主目录

例如：

```bash
cd /tmp/missing
cd ~/ysyx-study
```

---

## 三、查看帮助文档

常用方式：

```bash
man 命令
命令 --help
```

例如：

```bash
man touch
man chmod
```

在 `man` 中：

```text
/关键字    搜索
n          下一个匹配
q          退出
```

Linux 命令和参数不需要全部背下来，重点是会查文档。

---

## 四、文件权限

使用：

```bash
ls -l 文件
```

可以查看权限，例如：

```text
-rw-rw-r--
```

权限分为三组：

```text
u    文件所有者
g    文件所属组
o    其他用户
```

权限类型：

```text
r    读
w    写
x    执行
```

### 添加执行权限

```bash
chmod u+x semester
```

修改前：

```text
-rw-rw-r--
```

修改后：

```text
-rwxrw-r--
```

没有执行权限时：

```bash
./semester
```

会提示：

```text
Permission denied
```

---

## 五、Shebang

脚本第一行：

```bash
#!/bin/sh
```

或：

```bash
#!/bin/bash
```

称为 shebang。

它告诉系统应该使用哪个解释器执行脚本。

例如：

```bash
#!/bin/sh
curl --head --silent https://missing.csail.mit.edu
```

添加执行权限后：

```bash
chmod u+x semester
./semester
```

系统会根据 shebang 调用 `/bin/sh`。

---

## 六、标准输入、标准输出与标准错误

Linux 程序常用三个文件描述符：

```text
0    标准输入 stdin
1    标准输出 stdout
2    标准错误 stderr
```

### 输出重定向

覆盖写入：

```bash
命令 > 文件
```

追加写入：

```bash
命令 >> 文件
```

标准错误写入文件：

```bash
命令 2> error.log
```

标准输出和标准错误分别保存：

```bash
命令 > stdout.log 2> stderr.log
```

### 输入重定向

```bash
命令 < 文件
```

例如：

```bash
tr '[:upper:]' '[:lower:]' < input.txt
```

---

## 七、管道

管道符：

```bash
|
```

用于把左边命令的标准输出交给右边命令作为标准输入。

例如：

```bash
grep 'ERROR' access.log | wc -l
```

处理过程：

```text
grep 筛选 ERROR 行
        ↓
管道传递结果
        ↓
wc -l 统计行数
```

另一个例子：

```bash
stat -c '%y' semester | cut -d'.' -f1
```

---

## 八、`/sys` 系统接口

`/sys` 目录提供部分内核和硬件信息。

本次检查：

```bash
ls -la /sys/class/power_supply/
```

虚拟机只暴露了：

```text
ACAD
```

它表示交流电源适配器。

查看：

```bash
cat /sys/class/power_supply/ACAD/type
cat /sys/class/power_supply/ACAD/online
```

可能得到：

```text
Mains
1
```

含义：

- `Mains`：交流电源
- `1`：电源在线

虚拟机没有暴露 `BAT0` 或 `BAT1`，因此不能直接读取宿主机电池容量。这不是命令错误，而是虚拟硬件没有提供对应接口。

---

## 九、完成的练习

完成了：

- 确认当前 Shell
- 创建 `/tmp/missing`
- 使用 `man touch`
- 创建 `semester`
- 使用 `>` 和 `>>` 写脚本
- 观察没有执行权限时的错误
- 使用 `chmod u+x`
- 运行 shebang 脚本
- 使用管道和重定向处理文件时间
- 探索 `/sys/class/power_supply`

---

## 十、核心理解

```text
Shell      负责执行和组合命令
chmod      修改文件权限
shebang    指定脚本解释器
>          覆盖写入
>>         追加写入
2>         重定向标准错误
|          把一个命令的输出交给另一个命令
man        查阅命令文档
/sys       查看部分内核与硬件接口
```

学习 Linux 命令时，不追求一次记住所有参数，应先理解命令用途，再通过 `man` 和 `--help` 查询细节。
