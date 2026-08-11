#!/bin/bash

trap 'echo "收到 SIGTERM，但程序暂时不退出"' TERM

echo "程序 PID：$$"

while true; do
    sleep 1
done
