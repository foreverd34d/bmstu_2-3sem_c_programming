#!/usr/bin/env bash

#
# Собирает релизную версию программы (включены оптимизации, нет отладочной информации)
#

lm=""
if [[ $OSTYPE =~ "linux" ]]; then
    lm="-lm"
fi

if clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -O2 -c ./*.c; then
    clang -o app.exe ./*.o "$lm"
fi
