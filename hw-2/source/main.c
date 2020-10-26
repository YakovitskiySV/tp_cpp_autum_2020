#include "tuple.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"

int main(int argc, char **argv) {
    char file_name[64] = {};
    if (argc > 1) {
        strcpy(file_name, argv[1]);
    }
    else {
        if (!scanf("%s", file_name)) {
            perror("wrong file name");
            return 1;
        }
    }
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return NULL;
    }
    size_t tuples_number = 0;
    fscanf(file,"%zu", &tuples_number);
    clock_t begin_time = clock();
    tuple* tuples = make_tuples_from_file(file_name);
    if (!tuples) {
        perror("pointer error");
        return 1;
    }
    fclose(file);
    double single_proc_res = calculate_root_len(tuples, tuples_number);
    printf("%lf", single_proc_res);
    clock_t end_time = clock();
    double time_spent = (double) (end_time - begin_time) / CLOCKS_PER_SEC;
    free(tuples);
    return 0;
}
