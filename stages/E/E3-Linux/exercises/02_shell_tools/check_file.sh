#!/bin/bash

# 如果参数数量不等于1继续执行
if [ $# -ne 1 ]; then
    echo "用法：$0 <文件路径>"
    exit 2    #返回状态码2
fi

# 判断第一个参数所表示的文件或目录是否存在
if [ -e "$1" ]; then
    echo "文件存在：$1"
    exit 0
else
    echo "文件不存在：$1"
    exit 1
fi
