#!/usr/bin/env bash

#
# Собирает отладочную версию программы с проверками ошибок работы с памятью
#

lm=""
if [[ $OSTYPE =~ "linux" ]]; then
    lm="-lm"
fi

if clang -std=c99 -DDEBUG=1 -ggdb -fsanitize=address -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c ./*.c; then
    clang -fsanitize=address -o app.exe ./*.o "$lm"
fi
