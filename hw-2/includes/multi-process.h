//
// Created by yakovitskiy on 27.10.2020.
//

#ifndef HW_2_MULTI_PROCESS_H
#define HW_2_MULTI_PROCESS_H

#include <stdio.h>
#include "tuple.h"

typedef struct multi_result {
    double root_len;
    double time_spent;
    int procs_amount;
} multi_result;

double calculate_root_len_multi(tuple *tuples,
                                size_t tuples_number,
                                int beg_pos,
                                int end_pos);
multi_result *calc_result_multi_proc(char * file_name);
multi_result *create_shared_multi_result();

int print_results_multi_proc(multi_result *res);
int create_procs(size_t procs_number, int *pids);

#endif //HW_2_MULTI_PROCESS_H
