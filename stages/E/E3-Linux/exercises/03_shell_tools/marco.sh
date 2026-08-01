#!/bin/bash

marco() {
    export MARCO_DIR="$(pwd)"
    echo "已记录目录：$MARCO_DIR"
}

polo() {
    if [ -z "MARCO_DIR" ]; then
        echo "尚未执行 marco"
        return 1
    fi

    cd "$MARCO_DIR" || return 1
    echo "已返回目录：$(pwd)"
}
