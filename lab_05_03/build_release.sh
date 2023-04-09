#!/usr/bin/env bash

lm=""
if [[ $OSTYPE =~ "linux" ]]; then
    lm="-lm"
fi

if gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -O2 -c ./*.c; then
    gcc -o app.exe ./*.o "$lm"
fi
