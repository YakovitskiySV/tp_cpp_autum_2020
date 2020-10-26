#!/usr/bin/env bash

g++ -std=c++11 number-generator.cpp -o number_generator.o

./number_generator.o size_100mb_1.test 26214400
./number_generator.o size_100mb_2.test 26214400
./number_generator.o size_100mb_3.test 26214400
./number_generator.o size_10.test 10
./number_generator.o size_200.test 200
./number_generator.o size_5000.test 5000
./number_generator.o size_10000.test 10000
./number_generator.o size_20.test 20
./number_generator.o size_30.test 30
./number_generator.o size_40.test 40
./number_generator.o size_50.test 50
./number_generator.o size_60.test 60
