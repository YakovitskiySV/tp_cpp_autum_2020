#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include "single-process.h"
#include "multi-process.h"

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
