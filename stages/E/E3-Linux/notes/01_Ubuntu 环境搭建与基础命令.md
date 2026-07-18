# Linux 学习记录：Ubuntu 环境搭建与基础命令

## 一、本次学习目标

完成 Ubuntu 22.04 虚拟机开发环境搭建，并掌握 Linux 文件、目录、权限、重定向、管道和通配符等基础操作。

------

## 二、环境搭建完成情况

### 1. 虚拟机配置

使用 VMware Workstation 17 创建 Ubuntu 虚拟机：

```text
系统：Ubuntu 22.04.5 LTS
CPU：4 核
内存：8 GB
虚拟硬盘：100 GB
网络模式：NAT
虚拟机名称：Ubuntu-22.04-YSYX
主机名：ubuntu-ysyx
用户名：liuzhilong
```

安装了 VMware 增强工具：

```bash
sudo apt install -y open-vm-tools open-vm-tools-desktop
```

显示设置：

```text
分辨率：3840 × 2160
缩放：200%
刷新率：约 60 Hz
```

### 2. 系统和开发工具

完成系统更新：

```bash
sudo apt update
sudo apt upgrade -y
```

安装基础开发工具：

```bash
sudo apt install -y build-essential gdb git openssh-server vim curl wget tree unzip zip
```

已确认：

```text
GCC：11.4.0
GDB：12.1
Git：2.34.1
SSH 服务：active
```

### 3. Xshell 远程连接

通过 Windows 上的 Xshell 成功连接 Ubuntu：

```text
协议：SSH
端口：22
用户名：liuzhilong
虚拟机 IP：192.168.77.138
```

验证命令：

```bash
pwd
hostname
```

输出：

```text
/home/liuzhilong
ubuntu-ysyx
```

注意：NAT 模式下 IP 地址以后可能变化，可重新执行：

```bash
hostname -I
```

------

## 三、第一个 Linux C 程序

创建目录：

```bash
mkdir -p ~/linux-study/01-hello
cd ~/linux-study/01-hello
```

创建 `hello.c`：

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, Linux!\n");
    return 0;
}
```

编译并运行：

```bash
gcc -Wall -Wextra -g hello.c -o hello
./hello
```

成功输出：

```text
Hello, Linux!
```

理解了：

```text
hello.c：C 源代码文件
hello：编译生成的可执行文件
./hello：运行当前目录下的程序
```

------

## 四、文件和目录操作

练习目录：

```text
~/linux-study/02-file-basic
```

掌握的命令：

```bash
pwd
cd
mkdir
touch
echo
cat
cp
mv
rm
rmdir
ls
tree
```

常用路径符号：

```text
/     Linux 根目录
~     当前用户的主目录
.     当前目录
..    上一级目录
```

最终练习目录结构：

```text
.
├── dir2
│   └── renamed.txt
└── file1.txt
```

掌握了绝对路径和相对路径：

```bash
cd /home/liuzhilong/linux-study/02-file-basic
cd dir2
cd ..
cd ~
```

------

## 五、文件权限

练习目录：

```text
~/linux-study/03-permission
```

创建脚本：

```bash
#!/bin/bash

echo "Permission test passed"
```

没有执行权限时：

```text
-rw-rw-r--
```

运行：

```bash
./hello.sh
```

提示：

```text
Permission denied
```

添加执行权限：

```bash
chmod u+x hello.sh
```

权限变为：

```text
-rwxrw-r--
```

之后可以正常执行：

```bash
./hello.sh
```

### 数字权限

```text
r = 4
w = 2
x = 1
```

常见权限：

```bash
chmod 755 hello.sh
chmod 644 hello.sh
```

对应：

```text
755 = rwxr-xr-x
644 = rw-r--r--
```

理解了两种脚本运行方式：

```bash
./hello.sh
```

要求脚本本身具有执行权限。

```bash
bash hello.sh
```

执行的是 Bash 解释器，脚本具有读取权限即可。

------

## 六、重定向和管道

练习目录：

```text
~/linux-study/04-redirect-pipe
```

### 1. 输出重定向

覆盖写入：

```bash
echo "apple" > fruits.txt
```

追加写入：

```bash
echo "orange" >> fruits.txt
```

输入重定向：

```bash
wc -l < fruits.txt
```

### 2. 管道

```bash
cat fruits.txt | grep "an"
```

输出：

```text
banana
orange
```

统计行数：

```bash
cat fruits.txt | wc -l
```

输出：

```text
3
```

管道的作用：

> 将前一个命令的输出，作为后一个命令的输入。

### 3. 标准输出和标准错误

```text
1：标准输出 stdout
2：标准错误 stderr
```

保存正常输出：

```bash
命令 > success.txt
```

保存错误输出：

```bash
命令 2> error.txt
```

同时保存正常输出和错误输出：

```bash
命令 > all.txt 2>&1
```

简写：

```bash
命令 &> all.txt
```

成功验证：

```bash
ls fruits.txt not-exist.txt > all.txt 2>&1
```

------

## 七、Shell 通配符

练习目录：

```text
~/linux-study/05-wildcard
```

创建的测试文件包括：

```text
file1.txt
file2.txt
file10.txt
main.c
test1.c
test2.c
image1.png
image2.jpg
```

### `*`：匹配任意多个字符

```bash
ls *.txt
```

匹配：

```text
file1.txt
file2.txt
file10.txt
```

### `?`：匹配任意一个字符

```bash
ls file?.txt
```

只匹配：

```text
file1.txt
file2.txt
```

不会匹配 `file10.txt`。

### `[]`：匹配指定范围内的一个字符

```bash
ls file[12].txt
```

匹配：

```text
file1.txt
file2.txt
```

### Shell 展开

```bash
echo *.c
```

输出：

```text
main.c test1.c test2.c
```

说明通配符首先由 Shell 展开成文件名，然后再传给具体命令。

------

## 八、本次出现的错误与收获

### 1. 命令拼写错误

误写：

```bash
acho
```

正确：

```bash
echo
```

Linux 命令必须准确拼写。

### 2. 路径拼写错误

误写：

```bash
mv file2.txt die2/renamed.txt
```

正确：

```bash
mv file2.txt dir2/renamed.txt
```

Linux 路径和文件名区分大小写，并且必须完全匹配。

### 3. 文件名写错

本应写入：

```bash
file1.txt
```

实际写成：

```bash
file.txt
```

导致 `file1.txt` 仍为空文件。之后通过 `rm` 和 `mv` 整理正确。

### 4. 忘记在通配符前添加命令

直接输入：

```bash
file[12].txt
```

Shell 展开后会尝试把文件当成命令执行。

正确写法：

```bash
ls file[12].txt
```

------

## 九、当前学习目录

```text
~/linux-study
├── 01-hello
├── 02-file-basic
├── 03-permission
├── 04-redirect-pipe
└── 05-wildcard
```

------

## 十、下次学习内容

下一次从以下内容继续：

```text
1. find：按名称、类型等条件查找文件
2. grep：在文件中搜索文本内容
3. head、tail、less：查看文本文件
4. sort、uniq、wc：文本处理
5. Linux 进程和任务管理
6. Vim 基础操作
```

本次已经完成了从 **Ubuntu 虚拟机安装、SSH 连接、C 程序编译运行，到 Linux 基础命令操作** 的完整入门流程。