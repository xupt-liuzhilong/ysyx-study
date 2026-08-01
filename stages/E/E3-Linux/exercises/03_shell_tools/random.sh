#!/bin/bash

n=$((RANDOM & 10))

if [ "$n" -eq 0 ]; then
    echo "程序运行失败，随机数为：$n" >&2
    exit 1
fi

echo "程序运行成功，随机数为：$n"
exit 0
