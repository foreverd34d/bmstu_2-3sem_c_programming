#!/usr/bin/env bash

./clean.sh
./build_coverage.sh

cd func_tests/scripts || exit 1
./func_tests.sh
cd ../.. || exit 1

gcov -- *.c
if lcov -c -d . -o cov.info; then
    genhtml cov.info -o coverage
fi
