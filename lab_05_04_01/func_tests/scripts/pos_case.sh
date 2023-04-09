#!/usr/bin/env bash

app="../../app.exe"
fgot="fgot.txt"
fin=$1
fexpect=$2

if [[ -s $3 ]]; then
    fargs=$(cat "$3")
fi

if [[ -v USE_VALGRIND && $OSTYPE =~ "linux" ]]; then
    valgrind="valgrind --leak-check=full --track-origins=yes --log-file=./memcheck.txt"
fi

result=1
if $valgrind $app "$fargs" < "$fin" > "$fgot"; then
    if ./comparator.sh "$fgot" "$fexpect"; then
        result=0
    fi
fi

exit $result
