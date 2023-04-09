#!/usr/bin/env bash

#
# Сравнивает результат выполнения программы с ожидаемым,
# предварительно извлекая необходимые данные
# Коды возврата:
#       0   -   результаты совпадают
#       1   -   результаты различаются
#

# Сравнение действительных чисел с игнорированием всего остального содержимого

regex="[+-]?([0-9]+[.,]?[0-9]*|[0-9]*[.,]?[0-9]+)"

got=$(grep -Eoh "$regex" "$1")
expected=$(grep -Eoh "$regex" "$2")

result=0
if [[ "$got" != "$expected" ]]; then
    result=1
fi

exit $result