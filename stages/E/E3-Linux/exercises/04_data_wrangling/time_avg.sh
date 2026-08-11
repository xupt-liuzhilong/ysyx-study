#!/bin/bash

awk '{
    values[NR] = $1
    sum += $1
}
END {
    if (NR == 0) {
        print "没有可用的启动时间数据"
        exit 1
    }

    if (NR % 2 == 1) {
        median = values[(NR + 1) / 2]
    } else {
        median = ((values[NR / 2] + values[NR / 2 + 1])) / 2
    }

    printf "样本数：%d\n", NR
    printf "平均值：%.3f s\n", sum / NR
    printf "中位数：%.3f s\n", median
    printf "最大值：%.3f s\n", values[NR]
}
' sorted_boot_times.txt
