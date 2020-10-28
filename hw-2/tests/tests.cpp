#include <gtest/gtest.h>
#include <string>
#include <sys/mman.h>
#include <cmath>

#define STD_TEST_FILE "tests/test1.test\0"
/*
В этом файле созданы кортежи соответственно:
{(1 1) (2 2)}
{(3 3) (4 4)}
{(5 5) (6 6)}
{(7 7) (8 8)}
*/
#define BIG_FILE "tests/size_100mb_1.test"
// Файл с числами для массива на 100МБ
#define STD_PROCS_NUMBER 2
#define STD_TEST_ANSWER 9.8994949366116671  // Ответ из файла STD_TEST_FILE
#define STD_TEST_TUPLES_NUMBER 4
#define MASTER_PROC_NUMBER -10

extern "C" {
#include "tuple.h"  // NOLINT
#include "single-process.h"  // NOLINT
#include "multi-process.h"  // NOLINT
}

int compare_tuples(tuple const &lhs, tuple const &rhs) {
    if ((lhs.x1 == rhs.x1)
    && (lhs.y1 == rhs.y1)
    && (lhs.x2 == rhs.x2)
    && (lhs.y2 == rhs.y2)) {
        return 0;
    }
    return 1;
}

TEST(wrong_params, make_tuple) {  // NOLINT
    int32_t *source = nullptr;
    tuple expected = {0, 0, 0, 0};
    tuple received = make_tuple(source);
    EXPECT_EQ(0, compare_tuples(expected, received));
}

TEST(wrong_params, make_tuple_from_file) {  // NOLINT
    char *file_name = nullptr;
    EXPECT_EQ(nullptr, make_tuples_from_file(file_name));
}

TEST(wrong_params, calculate_edge) {  // NOLINT
    tuple *single_tuple = nullptr;
    EXPECT_EQ(-1, calculate_edge(single_tuple));
}

TEST(wrong_params, tuple_is_wrong) {  // NOLINT
    tuple *source = nullptr;
    EXPECT_EQ(1, tuple_is_wrong(source));
}

TEST(wrong_params, calc_result_single_proc_value) {  // NOLINT
    char file_name[] = "not_exists";
    EXPECT_EQ(nullptr, calc_result_single_proc(file_name));
}

TEST(wrong_params, calc_result_single_proc_pointer) {  // NOLINT
    char *file_name = nullptr;
    EXPECT_EQ(nullptr, calc_result_single_proc(file_name));
}

TEST(wrong_params, calculate_root_len_single_pointer) {  // NOLINT
    tuple *tuples = nullptr;
    size_t tuples_number = 1;
    EXPECT_EQ(-1, calculate_root_len_single(tuples, tuples_number));
}

TEST(wrong_params, calculate_root_len_single_tuples_number) {  // NOLINT
    char file_name[] = "not_exists";
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = 0;
    EXPECT_EQ(-1, calculate_root_len_single(tuples, tuples_number));
    free(tuples);
}

TEST(wrong_params, print_result_single_proc) {  // NOLINT
    single_result * res = nullptr;
    EXPECT_NE(0, print_result_single_proc(res));
}

TEST(wrong_params, create_procs_number_value) {  // NOLINT
    size_t procs_number = 0;
    int pids[STD_PROCS_NUMBER];
    EXPECT_EQ(-1, create_procs(procs_number, pids));
}

TEST(wrong_params, create_procs_number_pointer) {  // NOLINT
    size_t procs_number = STD_PROCS_NUMBER;
    int *pids = nullptr;
    EXPECT_EQ(-1, create_procs(procs_number, pids));
}

TEST(wrong_params, calc_result_multi_proc_value) {  // NOLINT
    char file_name[] = "not_exists";
    EXPECT_EQ(nullptr, calc_result_multi_proc(file_name));
}

TEST(wrong_params, calc_result_multi_proc_pointer) {  // NOLINT
    char *file_name = nullptr;
    EXPECT_EQ(nullptr, calc_result_multi_proc(file_name));
}

TEST(wrong_params, print_results_multi_proc) {  // NOLINT
    multi_result *res = nullptr;
    EXPECT_EQ(1, print_results_multi_proc(res));
}

TEST(wrong_params, calculate_root_len_multi_pointer) {  // NOLINT
    tuple *tuples = nullptr;
    size_t tuples_number = 10;
    int beg_pos = 0;
    int end_pos = 1;
    EXPECT_EQ(-1, calculate_root_len_multi(tuples,
                                           tuples_number,
                                           beg_pos, end_pos));
}

TEST(wrong_params, calculate_root_len_multi_tuples_number) {  // NOLINT
    char file_name[] = STD_TEST_FILE;
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = 0;
    int beg_pos = 0;
    int end_pos = 1;
    EXPECT_EQ(-1, calculate_root_len_multi(tuples,
                                           tuples_number,
                                           beg_pos, end_pos));
    free(tuples);
}

TEST(wrong_params, calculate_root_len_multi_beg_pos) {  // NOLINT
    char file_name[] = STD_TEST_FILE;
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = 10;
    int beg_pos = -1;
    int end_pos = 1;
    EXPECT_EQ(-1,
              calculate_root_len_multi(tuples,
                                           tuples_number,
                                           beg_pos, end_pos));
    free(tuples);
}

TEST(wrong_params, calculate_root_len_multi_end_pos) {  // NOLINT
    char file_name[] = STD_TEST_FILE;
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = 10;
    int beg_pos = 0;
    int end_pos = -1;
    EXPECT_EQ(-1, calculate_root_len_multi(tuples,
                                           tuples_number,
                                           beg_pos, end_pos));
    free(tuples);
}

TEST(correct_params, make_tuple) {  // NOLINT
    int32_t source = 33685761;  // разбивается как 1 1 2 2
    tuple expected = {1, 1, 2, 2};
    tuple received = make_tuple(&source);
    EXPECT_EQ(0, compare_tuples(expected, received));
}

TEST(correct_params, tuple_is_wrong) {  // NOLINT
    tuple source = {0, 0, 0, 0};
    EXPECT_EQ(1, tuple_is_wrong(&source));
}

TEST(correct_params, tuple_is_not_wrong) {  // NOLINT
    tuple source = {1, 1, 2, 2};
    EXPECT_EQ(0, tuple_is_wrong(&source));
}

TEST(correct_params, calculate_edge) {  // NOLINT
    tuple single_tuple = {1, 1, 2, 2};  // Длина ребра = корень из 2
    EXPECT_EQ(sqrt(2), calculate_edge(&single_tuple));
}

TEST(correct_params, make_tuples_from_file) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = 4;
    for (size_t i = 0 ; i <  tuples_number ; ++i) {
        tuple expected = {int8_t(2 * i + 1),  // Запонение кортежей
                          int8_t(2 * i + 1),  // как в файле
                          int8_t(2 * i + 2),
                          int8_t(2 * i + 2)};
        EXPECT_EQ(0, compare_tuples(expected, tuples[i]));
    }
    free(tuples);
}

TEST(correct_params, calculate_root_len_single) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    tuple *tuples = make_tuples_from_file(file_name);
    size_t tuples_number = STD_TEST_TUPLES_NUMBER;
    double received = calculate_root_len_single(tuples, tuples_number);
    double expected = STD_TEST_ANSWER;
    EXPECT_DOUBLE_EQ(expected, received);
    free(tuples);
}

TEST(correct_params, calc_result_single_proc) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    single_result *result = calc_result_single_proc(file_name);
    double expected = STD_TEST_ANSWER;
    EXPECT_DOUBLE_EQ(result->root_len, expected);
    free(result);
}

TEST(correct_params, print_result_single_proc) {  // NOLINT
    single_result res = {0, 0};
    EXPECT_EQ(0 , print_result_single_proc(&res));
}

TEST(correct_params, create_procs) {  // NOLINT
    size_t procs_number = STD_PROCS_NUMBER;
    int pids[STD_PROCS_NUMBER];
    int process_number = create_procs(procs_number, pids);
    if (process_number != MASTER_PROC_NUMBER) {
        exit(0);  // Убиваем процессы созданные входе теста
    }
    EXPECT_EQ(MASTER_PROC_NUMBER, process_number);
}

TEST(correct_params, calculate_root_len_multi) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    tuple *tuples = make_tuples_from_file(file_name);
    double res = calculate_root_len_multi(tuples,
                                          STD_TEST_TUPLES_NUMBER,
                                          0,
                                          STD_TEST_TUPLES_NUMBER);
    free(tuples);
    double expected = STD_TEST_ANSWER;
    EXPECT_DOUBLE_EQ(expected, res);
}

TEST(correct_params, calc_result_multi_proc) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    multi_result *res = calc_result_multi_proc(file_name);
    double expected = STD_TEST_ANSWER;
    EXPECT_DOUBLE_EQ(expected, res->root_len);
    munmap(res, getpagesize());
}

TEST(correct_params, print_results_multi_proc) {  // NOLINT
    multi_result res = {0, 0, 0};
    EXPECT_EQ(0, print_results_multi_proc(&res));
}

TEST(correct_params, multi_and_single_compare) {  // NOLINT
    std::string buf = STD_TEST_FILE;
    char *file_name = (char*) buf.c_str();
    multi_result *multi_res = calc_result_multi_proc(file_name);
    single_result *single_res = calc_result_single_proc(file_name);
    EXPECT_DOUBLE_EQ(STD_TEST_ANSWER, single_res->root_len);
    EXPECT_DOUBLE_EQ(multi_res->root_len, single_res->root_len);
    munmap(multi_res, getpagesize());
    free(single_res);
}

TEST(correct_params, multi_and_single_compare_del_grande) {  // NOLINT
    std::string buf = BIG_FILE;
    char *file_name = (char*) buf.c_str();
    multi_result *multi_res = calc_result_multi_proc(file_name);
    single_result *single_res = calc_result_single_proc(file_name);
    EXPECT_LT(abs(multi_res->root_len - single_res->root_len), 1);
    // отсекли дробные чатсти
    // тк они не будут совпадать тк чисел слишком много
    munmap(multi_res, getpagesize());
    free(single_res);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
