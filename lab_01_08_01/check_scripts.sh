#!/usr/bin/env bash

#
# Проверяет скрипты на ошибки при помощи shellcheck
# Возвращает кол-во скриптов с ошибками
#

err=0
green='\033[0;32m'
default='\033[0m'

while IFS= read -r -d '' name
do
    if ! shellcheck "$name"; then
        (( err++ ))
    fi
done < <(find . -name "*.sh" -print0)

if [[ $err -eq 0 ]]; then
    echo -e "${green}Everything's fine${default}"
fi

exit "$err"
