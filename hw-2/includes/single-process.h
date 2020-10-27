#ifndef HW_2_SINGLE_PROCESS_H
#define HW_2_SINGLE_PROCESS_H

#include <stdio.h>
#include "tuple.h"

typedef struct {
    double root_len;
    double time_spent;
} single_result;

single_result *calc_result_single_proc(char *file_name);

double calculate_root_len_single(tuple *tuples, size_t tuples_number);

int print_result_single_proc(single_result *res);

#endif //HW_2_SINGLE_PROCESS_H
