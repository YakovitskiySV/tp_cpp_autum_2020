#include "multi-process.h"
#include "tuple.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define STD_PROC_NUM 2
#define MASTER_PROC_NUMBER -10

double calculate_root_len_multi(tuple *tuples,
                                size_t tuples_number,
                                int beg_pos,
                                int end_pos) {
    if (!tuples) {
        return -1;
    }
    double result = 0;
    if (beg_pos == 0) {
        result += calculate_edge(&tuples[beg_pos]);
    }
    if (tuples_number == 1) {
        return result;
    }
    if (end_pos == tuples_number) {
        end_pos--;
    }
    for (size_t i = beg_pos + 1 ; i <= end_pos ; ++i) {
        tuple buf = {tuples[i - 1].x2,  // Чтобы не пропустить ребро
                     tuples[i - 1].y2,  // между двумя кортежами
                     tuples[i].x1,
                     tuples[i].y1};
        result += calculate_edge(&buf);
        result += calculate_edge(&tuples[i]);
    }
    return result;
}

multi_result *create_shared_multi_result() {
    size_t page_size = getpagesize();
    multi_result *res = mmap(NULL,
                        page_size,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS,
                        -1,
                        0);
    if (!res) {
        return NULL;
    }
    res->time_spent = 0;
    res->root_len = 0;
    return res;
}

int create_procs(size_t procs_number, int* pids) {
    int pid = 1;
    for (size_t i = 0 ; i < procs_number ; ++i) {
        pid = fork();
        if (pid == -1) {
            return -1;
        } else if (pid == 0) {
            return i;
        }
        pids[i] = pid;
    }
    return MASTER_PROC_NUMBER;
}

multi_result *calc_result_multi_proc(char * file_name) {
    multi_result* res = NULL;
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return NULL;
    }
    size_t tuples_number = 0;
    fscanf(file,"%zu", &tuples_number);
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
    res = create_shared_multi_result();
    if (res == NULL) {
        free(tuples);
        return NULL;
    }
    size_t procs_number = STD_PROC_NUM;
    int pids[procs_number];
    for (size_t i = 0 ; i < procs_number ; ++i) {
        pids[i] = 0;
    }
    int proc_number = create_procs(procs_number, pids);
    if (proc_number == -1) {
        munmap(res, getpagesize());
        free(tuples);
    }
    if (proc_number > MASTER_PROC_NUMBER) {
       size_t chunk_size = tuples_number / procs_number;
       int beg_pos = proc_number * chunk_size;
       int end_pos = beg_pos + chunk_size;
       double buf = calculate_root_len_multi(tuples, tuples_number, beg_pos, end_pos);
       res->root_len += buf;
       exit(0);
    }
    for (size_t i = 0 ; i < procs_number ; ++i) {
        while (waitpid(pids[i], NULL, 0) > 0) {}
    }
    clock_t end_time = clock();
    res->time_spent = (double) (end_time - begin_time) / CLOCKS_PER_SEC;
    res->procs_amount = procs_number;
    free(tuples);
    return res;
}

int print_results_multi_proc(multi_result *res) {
    if (!res) {
        return 1;
    }
    printf("%s%lf%c", "multi-process result: ",
           res->root_len, '\n');
    printf("%s%lf%c", "multi-process time: ",
           res->time_spent, '\n');
    printf("%s%d%c", "processes amount: ",
           res->procs_amount, '\n');
    return 0;
}
