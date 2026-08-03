#!/bin/bash

awk '{
    sum[$1] += $2
    count[$1]++
}
END {
    for (user in sum) {
         printf "%.2f %s\n", sum[user] / count[user], user
    }
}' latency.log | sort -nr
