#include "single-process.h"
#include "tuple.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "math.h"

single_result *calc_result_single_proc(char *file_name) {
    if (file_name == NULL) {
        return NULL;
    }
    FILE* file = fopen(file_name, "r+");
    if (!file) {
        return NULL;
    }
    size_t tuples_number = 0;
    if (!fscanf(file,"%zu", &tuples_number)) {
        return NULL;
    }
    clock_t begin_time = clock();
    tuple* tuples = make_tuples_from_file(file_name);
    if (!tuples) {
        fclose(file);
        return NULL;
    }
    if (fclose(file) == EOF) {
        free(tuples);
        return NULL;
    }
    single_result *res = (single_result*) malloc(1 * sizeof(single_result));
    res->root_len = calculate_root_len_single(tuples, tuples_number);
    if (res->root_len == -1) {
        fclose(file);
        free(tuples);
        return NULL;
    }
    clock_t end_time = clock();
    res->time_spent = (double) (end_time - begin_time) / CLOCKS_PER_SEC;
    free(tuples);
    return res;
}

double calculate_root_len_single(tuple *tuples, size_t tuples_number) {
    if (!tuples || tuples_number == 0) {
        return -1;
    }
    double result = 0;
    double buf_res = calculate_edge(&tuples[0]);
    if (buf_res == -1) {
        return -1;
    }
    result += buf_res;
    if (tuples_number == 1) {
        return result;
    }
    for (size_t i = 1 ; i < tuples_number ; ++i) {
        tuple buf_tuple = {tuples[i - 1].x2,  // Чтобы не пропустить ребро
                     tuples[i - 1].y2,  // между двумя кортежами
                     tuples[i].x1,
                     tuples[i].y1};
        if ((buf_res = calculate_edge(&buf_tuple)) != -1)
            result += buf_res;
        else return -1;
        if ((buf_res = calculate_edge(&tuples[i])) != -1)
            result += buf_res;
        else return -1;
    }
    return result;
}

int print_result_single_proc(single_result *res) {
    if (!res) {
        return 1;
    }
    printf("%s%lf%c", "single process result: ",
           res->root_len, '\n');
    printf("%s%lf%c", "single process time: ",
           res->time_spent, '\n');
    return 0;
}
