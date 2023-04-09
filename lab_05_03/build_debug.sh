#!/usr/bin/env bash

lm=""
if [[ $OSTYPE =~ "linux" ]]; then
    lm="-lm"
fi

if gcc -std=c99 -DDEBUG=1 -ggdb -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c ./*.c; then
    gcc -o app.exe ./*.o "$lm"
fi
