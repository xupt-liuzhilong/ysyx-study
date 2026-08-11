#!/bin/bash

count=0

> stdout.log
> stderr.log

while true; do
    count=$((count+1))

    ./random.sh >> stdout.log 2>> stderr.log
    status=$?

    if [ "$status" -ne 0 ]; then
        echo "程序在第 $count 次运行失败"
        echo "退出状态：$status"

        echo "==== 标准输出 ===="
        cat stdout.log

        echo "==== 标准错误 ===="
        cat stderr.log

        break
    fi
done
