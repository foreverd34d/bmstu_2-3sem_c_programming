#!/usr/bin/env bash
# Сравнение строк после слова 'Result: '

got=$(grep '^Result: ' "$1")
expected=$(grep '^Result: ' "$2")

result=0
if [[ "$got" != "$expected" ]]; then
    result=1
fi

exit $result
