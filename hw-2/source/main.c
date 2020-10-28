#include "multi-process.h"  // NOLINT
#include "single-process.h"  // NOLINT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define STD_STRING_SIZE 64

int main(int argc, char **argv) {
    char file_name[STD_STRING_SIZE] = {};
    if (argc > 1) {
        snprintf(file_name, STD_STRING_SIZE - 1, "%s", argv[1]);
    } else {
        if (!scanf("%1s", file_name)) {
            perror("wrong file name");
            return 1;
        }
    }
    single_result *single_proc_res = calc_result_single_proc(file_name);
    if (!single_proc_res) {
        perror("single-process error");
        return 1;
    }
    if (print_result_single_proc(single_proc_res) != 0) {
        perror("pointer error");
        return 1;
    }
    printf("%c", '\n');
    free(single_proc_res);
    multi_result *multi_proc_results = calc_result_multi_proc(file_name);
    if (!multi_proc_results) {
        perror("multi-process error");
    }
    if (print_results_multi_proc(multi_proc_results) != 0) {
        perror("pointer error");
    }
    munmap(multi_proc_results, getpagesize());
    return 0;
}
