#!/usr/bin/env bash

#
# Собирает отладочную версию программы (есть отладочная информация, включен макрос DEBUG)
#

lm=""
if [[ $OSTYPE =~ "linux" ]]; then
    lm="-lm"
fi

if clang -std=c99 -DDEBUG=1 -ggdb -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c ./*.c; then
    clang -o app.exe ./*.o "$lm"
fi
