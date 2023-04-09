#!/usr/bin/env bash

app="../../app.exe"
fin=$1

if [[ -s $2 ]]; then
    fargs=$(cat "$2")
fi

if [[ -v USE_VALGRIND && $OSTYPE =~ "linux" ]]; then
    valgrind="valgrind --leak-check=full --track-origins=yes --log-file=./memcheck.txt"
fi

result=1
if ! $valgrind $app "$fargs" < "$fin" > /dev/null; then
    result=0
fi

exit $result
