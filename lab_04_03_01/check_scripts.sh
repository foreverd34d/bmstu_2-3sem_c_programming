#!/usr/bin/env bash

err=0

while IFS= read -r -d '' name
do
    if ! shellcheck "$name"; then
        err=1
    fi
done < <(find . -name "*.sh" -print0)

green='\033[0;32m'
default='\033[0m'

if [ $err -eq 0 ]; then
    echo -e "${green}Everything's fine${default}"
fi

exit $err
