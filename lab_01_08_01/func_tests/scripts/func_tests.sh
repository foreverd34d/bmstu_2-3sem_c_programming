#!/usr/bin/env bash

#
# Выполняет функциональное тестирование проекта
#
# Переменные окружения:
#   USE_VALGRIND – запускает программу в оболочке valgrind
#                  для проверки работы с памятью
# Коды выхода:
#   0   –   все тесты выполнены успешно
#   >0  –   кол-во проваленных тестов
#

tests_dir="../data"

# Colors
red="\e[31m"
bold="\e[1m"
resetc="\e[0m"

# Get number of tests
pos_amount=$(find "$tests_dir" -name "pos_*_in.txt" | wc -l)
neg_amount=$(find "$tests_dir" -name "neg_*_in.txt" | wc -l)


# Run negative tests
neg_result=0
echo -e "${bold}Running negative tests...${resetc}"

for ((i=1; i <= neg_amount ; i++)); do
    args_file=""
    if [[ $i -lt 10 ]]; then
        test_file="$tests_dir/neg_0${i}_in.txt"
        if [[ -f $tests_dir/neg_0${i}_args ]]; then
            args_file="$tests_dir/neg_0${i}_args"
        fi
    else
        test_file="$tests_dir/neg_${i}_in.txt"
        if [[ -f $tests_dir/neg_${i}_args ]]; then
            args_file="$tests_dir/neg_${i}_args"
        fi
    fi

    if ! ./neg_case.sh "$test_file" "$args_file"; then
        echo -e "${red}Negative test $i failed!${resetc}"
        (( neg_result++ ))
    else
        echo "Negative test $i passed"
    fi
done


# Run positive tests
pos_result=0
echo
echo -e "${bold}Running positive tests...${resetc}"

for ((i=1; i <= pos_amount ; i++)); do
    args_file=""
    if [[ $i -lt 10 ]]; then
        input_file="$tests_dir/pos_0${i}_in.txt"
        output_file="$tests_dir/pos_0${i}_out.txt"
        if [[ -f $tests_dir/pos_0${i}_args.txt ]]; then
            args_file="$tests_dir/pos_0${i}_args.txt"
        fi
    else
        input_file="$tests_dir/pos_${i}_in.txt"
        output_file="$tests_dir/pos_${i}_out.txt"
        if [[ -f $tests_dir/pos_${i}_args.txt ]]; then
            args_file="$tests_dir/pos_${i}_args.txt"
        fi
    fi

    if ! ./pos_case.sh "$input_file" "$output_file" "$args_file"; then
        echo -e "${red}Positive test $i failed!${resetc}"
        echo "Expected: $(cat "$output_file")"
        echo "Got: $(cat "./fgot.txt")"
        echo
        (( pos_result++ ))
    else
        echo "Positive test $i passed"
    fi
done

# Remove fgot.txt temp file
rm fgot.txt


# Print summary
echo
echo -e "${bold}Summary:${resetc}"
echo "Positive tests: $(( pos_amount - pos_result )) of $(( pos_amount )) passed"
echo "Negative tests: $(( neg_amount - neg_result )) of $(( neg_amount )) passed"

exit $(( pos_result + neg_result ))
