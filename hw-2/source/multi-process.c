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
    if (!tuples
    || (beg_pos >= end_pos)
    || (beg_pos < 0)
    || (end_pos < 0)
    || (end_pos > (int)tuples_number)) {
        return -1;
    }
    double result = 0;
    double buf_res = 0;
    if (beg_pos == 0) {
        buf_res = calculate_edge(&tuples[beg_pos]);
        if (buf_res != -1) {
            result += buf_res;
        }
    }
    if (tuples_number == 1) {
        return result;
    }
    if (end_pos == (int)tuples_number) {
        end_pos--;
    }
    for (size_t i = beg_pos + 1 ; i <= (size_t)end_pos ; ++i) {
        tuple buf = {tuples[i - 1].x2,  // Чтобы не пропустить ребро
                     tuples[i - 1].y2,  // между двумя кортежами
                     tuples[i].x1,
                     tuples[i].y1};
        buf_res = calculate_edge(&buf);
        if (buf_res != -1)
            result +=buf_res;
        else return -1;
        buf_res = calculate_edge(&tuples[i]);
        if (buf_res != -1)
            result += buf_res;
        else return -1;
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
    if (res == MAP_FAILED) {
        return NULL;
    }
    res->time_spent = 0;
    res->root_len = 0;
    return res;
}

int create_procs(size_t procs_number, int* pids) {
    if (!pids || procs_number == 0) {
        return -1;
    }
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
    if (file_name == NULL) {
        return NULL;
    }
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return NULL;
    }
    size_t tuples_number = 0;
    if (!fscanf(file,"%zu", &tuples_number)) {
        fclose(file);
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
    multi_result* res = create_shared_multi_result();
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
       int beg_pos = proc_number * (int)chunk_size;
       int end_pos = beg_pos + (int)chunk_size;
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
