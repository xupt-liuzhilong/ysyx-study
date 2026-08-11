#!/bin/bash

output="boot_times.txt"
> "$output"

for offset in 0 -1 -2 -3 -4 -5 -6 -7 -8 -9; do
    line=$(
        journalctl -b "$offset" -o cat --no-pager 2>/dev/null |
        grep -m1 -E 'Startup finished in .*kernel.*userspace.*='
    )

    if [ -z "$line" ]; then
        echo "启动记录 $offset：未找到总启动时间" >&2
        continue
    fi

    seconds=$(
        printf '%s\n' "$line" |
        sed -En 's/.*= ([0-9.]+)s.*/\1/p'
    )

    if [ -n "$seconds" ]; then
        printf '%s\n' "$seconds" >> "$output"
        echo "启动记录 $offset：${seconds}s"
    fi
done
