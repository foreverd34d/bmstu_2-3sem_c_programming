#!/usr/bin/env bash
# Сравнение действительных чисел с игнорированием всего остального содержимого

regex="[+-]?([0-9]+[.,]?[0-9]*|[0-9]*[.,]?[0-9]+)"

got=$(grep -Eoh "$regex" "$1")
expected=$(grep -Eoh "$regex" "$2")

result=0
if [[ "$got" != "$expected" ]]; then
    result=1
fi

exit $result
