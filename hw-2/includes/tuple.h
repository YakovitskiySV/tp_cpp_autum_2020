//
// Created by yakovitskiy on 25.10.2020.
//

#ifndef HW_2_TUPLE_H
#define HW_2_TUPLE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int8_t x1;
    int8_t y1;
    int8_t x2;
    int8_t y2;
} tuple;

tuple make_tuple(int32_t *source);
tuple *make_tuples_from_file(char* file_name);

double calculate_edge(tuple *single_tuple);


#endif //HW_2_TUPLE_H
