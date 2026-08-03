#!/bin/bash

awk '{
for (i = 1; i <= NF; i++) {
        if ($i ~ /^user=/) {
            split($i, parts, "=")
             users[parts[2]]++
        }
    }
}
END {
    for (user in users) {
        print users[user], user
    }
}' access.log | sort -nr
