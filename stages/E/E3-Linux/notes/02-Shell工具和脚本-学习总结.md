# 第二讲：Shell 工具和脚本学习总结

日期：2026-07-27  
阶段：一生一芯 E3 Linux  
课程：Missing Semester 第二讲——Shell 工具和脚本

## 一、Shell 脚本参数

示例脚本：

```bash
#!/bin/bash

echo "脚本名称：$0"
echo "第一个参数：$1"
echo "第二个参数：$2"
echo "参数数量：$#"
echo "全部参数：$@"
echo "当前进程号：$$"
```

执行：

```bash
./args.sh hello ysyx
```

常用特殊变量：

```text
$0    脚本名称
$1    第一个参数
$2    第二个参数
$#    参数数量
$@    全部参数
$$    当前脚本进程号
$?    上一条命令的退出状态
```

---

## 二、退出状态

Linux 命令执行后会返回退出状态：

```text
0       成功
非 0    失败或异常
```

测试：

```bash
true
echo $?

false
echo $?
```

结果：

```text
0
1
```

`$?` 只保存紧挨着的上一条命令状态，执行其他命令后会被覆盖。

---

## 三、条件判断

文件检查脚本：

```bash
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "用法：$0 <文件路径>"
    exit 2
fi

if [ -e "$1" ]; then
    echo "文件存在：$1"
    exit 0
else
    echo "文件不存在：$1"
    exit 1
fi
```

### 条件语法

```bash
if 条件; then
    命令
else
    命令
fi
```

常用判断：

```text
-ne    不等于
-e     路径存在
-z     字符串为空
-n     字符串非空
```

注意：

```bash
[ 条件 ]
```

中括号两侧必须有空格。

---

## 四、`&&` 与 `||`

```bash
命令1 && 命令2
```

只有命令1成功时才执行命令2。

```bash
命令1 || 命令2
```

只有命令1失败时才执行命令2。

例如：

```bash
./check_file.sh args.sh && echo "可以继续处理"
```

```bash
./check_file.sh hello.txt || echo "无法继续处理"
```

---

## 五、Shell 函数与 `source`

函数定义：

```bash
marco() {
    export MARCO_DIR="$(pwd)"
    echo "已记录目录：$MARCO_DIR"
}

polo() {
    if [ -z "$MARCO_DIR" ]; then
        echo "尚未执行 marco"
        return 1
    fi

    cd "$MARCO_DIR" || return 1
    echo "已返回目录：$(pwd)"
}
```

加载函数：

```bash
source marco.sh
```

也可以写：

```bash
. marco.sh
```

### 为什么使用 `source`

直接运行：

```bash
./marco.sh
```

会在子 Shell 中执行，脚本结束后函数定义消失。

使用：

```bash
source marco.sh
```

会让当前 Shell 直接读取脚本，因此函数可以继续调用。

### `return` 和 `exit`

```text
return    结束当前函数
exit      结束整个脚本或 Shell
```

函数执行到 `}` 时会自动结束，不需要主动关闭。

---

## 六、命令替换与算术运算

命令替换：

```bash
current_dir="$(pwd)"
current_time="$(date)"
```

语法：

```bash
变量="$(命令)"
```

算术运算：

```bash
count=$((count + 1))
```

随机数：

```bash
n=$((RANDOM % 10))
```

---

## 七、循环

### for 循环

```bash
for i in {1..10}; do
    ./random.sh
    echo "退出状态：$?"
done
```

### while 循环

```bash
while true; do
    ...
done
```

`true` 始终返回 0，因此循环会持续执行。

退出循环：

```bash
break
```

---

## 八、随机失败脚本

```bash
#!/bin/bash

n=$((RANDOM % 10))

if [ "$n" -eq 0 ]; then
    echo "程序运行失败，随机数为：$n" >&2
    exit 1
fi

echo "程序运行成功，随机数为：$n"
exit 0
```

其中：

```bash
>&2
```

表示把输出写到标准错误。

---

## 九、重复运行直到失败

```bash
#!/bin/bash

count=0

while true; do
    count=$((count + 1))

    ./random.sh > stdout.log 2> stderr.log
    status=$?

    if [ "$status" -ne 0 ]; then
        echo "程序在第 $count 次运行时失败"
        echo "退出状态：$status"

        echo "===== 标准输出 ====="
        cat stdout.log

        echo "===== 标准错误 ====="
        cat stderr.log

        break
    fi
done
```

关键点：

- 运行后立即保存 `$?`
- `>` 每次覆盖旧文件
- `2>` 保存错误信息
- 失败后通过 `break` 结束循环

如果要保留所有运行结果，可以使用：

```bash
>> stdout.log
2>> stderr.log
```

并在循环前清空旧日志。

---

## 十、find、xargs 与文件名空格

查找 HTML 文件：

```bash
find . -type f -name '*.html'
```

结构：

```text
find              查找工具
.                 从当前目录开始
-type f           只匹配普通文件
-name '*.html'    文件名以 .html 结尾
```

安全打包：

```bash
find . -type f -name '*.html' -print0 |
    xargs -0 zip html_files.zip
```

其中：

```text
-print0    使用空字符分隔文件名
xargs -0   按空字符读取输入
```

这样可以正确处理：

```text
hello world.html
```

而不会把它错误拆成两个参数。

---

## 十一、按修改时间查找文件

输出文件修改时间和路径：

```bash
find . -type f -printf '%T@ %p\n'
```

按时间从新到旧排序：

```bash
find . -type f -printf '%T@ %p\n' |
    sort -nr
```

只取最近修改的文件：

```bash
find . -type f -printf '%T@ %p\n' |
    sort -nr |
    head -n 1 |
    cut -d' ' -f2-
```

工具分工：

```text
find    找文件
sort    排序
head    取第一条
cut     去掉时间字段
```

---

## 十二、完成的练习

完成了：

- 脚本参数和特殊变量
- 退出状态
- `if` 条件判断
- `&&` 和 `||`
- Shell 函数
- `source`
- `return` 与 `exit`
- 随机失败脚本
- `for` 和 `while`
- 标准输出与标准错误分离
- 重复运行直到失败
- `find` 和 `xargs`
- 安全处理带空格文件名
- 按修改时间查找文件

---

## 十三、核心理解

```text
$?          上一条命令的状态
if          根据条件执行
&&          成功后执行
||          失败后执行
source      在当前 Shell 中加载脚本
return      结束函数
exit        结束脚本
for         固定次数或遍历
while       条件循环
break       跳出循环
find        查找文件
xargs       把输入转换为命令参数
```

复杂 Shell 命令应拆成多个小步骤，逐步观察结果，不应只照抄完整命令。
