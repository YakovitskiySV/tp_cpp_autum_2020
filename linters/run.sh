#!/usr/bin/env bash
set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

cflags="--suppressions-list=.suppressions-list.txt --std=c99 --enable=all -inconclusive"
cppflags="--suppressions-list=.suppressions-list.txt --std=c++20 --enable=all -inconclusive"

print_header "RUN CPP CHECK"

cppcheck $cflags source/*.c
cppcheck $cflags includes/*.h
cppcheck $cppflags tests/*.cpp


print_header "RUN cpplint.py"
python3 ./linters/cpplint/cpplint.py --extensions=c source/*
python3 ./linters/cpplint/cpplint.py --extensions=cpp tests/*
python3 ./linters/cpplint/cpplint.py --extensions=h includes/*



print_header "SUCCESS"
