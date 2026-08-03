#!/bin/bash

if [ $# -ne 1 ]; then
    echo "用法：$0 <PID>"
    exit 1
fi

pid=$1

echo "等待进程 $pid 结束……"

while kill -0 "$pid" 2>/dev/null; do
    sleep 1
done

echo "进程 $pid 已结束"
