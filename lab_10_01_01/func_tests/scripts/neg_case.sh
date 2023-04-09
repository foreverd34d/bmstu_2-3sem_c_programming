#!/usr/bin/env bash

#
# Выполняет негативный тест программы
#
# Использование:
#   ./neg_case.sh входной_файл [файл_аргументов]
#
# Переменные окружения:
#   USE_VALGRIND – запускает программу в оболочке valgrind
#                  для проверки работы с памятью
# Коды выхода:
#   0   –   негативный тест пройден (программа вернула ненулевой код)
#   1   -   негативный тест провален
#

app="./app.exe"
# fin=$1

if [[ -s $2 ]]; then
    fargs=$(cat "$2")
    # echo "$fargs"
fi

if [[ -v USE_VALGRIND && $OSTYPE =~ "linux" ]]; then
    valgrind="valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=./memcheck.txt"
fi

result=1
if ! $valgrind $app $fargs &> /dev/null; then # $fargs is unquoted intentionally
    result=0
fi

exit $result
