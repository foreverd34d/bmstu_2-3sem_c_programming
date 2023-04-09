#!/usr/bin/env bash

#
# Выполняет позитивный тест программы
#
# Использование:
#   ./pos_case.sh входной_файл выходной_файл [файл_аргументов]
#
# Переменные окружения:
#   USE_VALGRIND – запускает программу в оболочке valgrind
#                  для проверки работы с памятью
# Коды выхода:
#   0   –   позитивный тест пройден (программа вернула ненулевой код
#                                    и ее результат совпал с ожидаемым)
#   1   -   позитивный тест провален
#

app="./app.exe"
fgot="./fgot.txt"
# fin=$1
fexpect=$2

if [[ -s $3 ]]; then
    fargs=$(cat "$3")
fi

if [[ -v USE_VALGRIND && $OSTYPE =~ "linux" ]]; then
    valgrind="valgrind --leak-check=full --track-origins=yes --log-file=./memcheck.txt"
fi

result=1
if $valgrind $app $fargs > "$fgot"; then # $fargs is unquoted intentionally
    if ./func_tests/scripts/comparator.sh "$fgot" "$fexpect"; then
        result=0
    fi
fi

exit $result
