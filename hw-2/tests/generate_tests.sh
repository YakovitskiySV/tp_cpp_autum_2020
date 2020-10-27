#!/usr/bin/env bash

g++ -std=c++11 number-generator.cpp -o number_generator.o

./number_generator.o size_100mb_1.test 26214400  # кол-во чисел, чтобы получился массив на 100 мб
./number_generator.o size_10000.test 10000  # рандомный файл для запуска hw_2.out
