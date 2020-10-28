#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "tuple.h"  // NOLINT

#define STD_BUF_TUPLE_SIZE 4

tuple make_tuple(int32_t *source) {
    tuple result = {0, 0, 0, 0};
    if (!source) {
        return result;
    }
    int8_t buffer[STD_BUF_TUPLE_SIZE];
    if (!memcpy(buffer, source, sizeof(*source))) {
        return result;
    }
    result.x1 = buffer[0];
    result.y1 = buffer[1];
    result.x2 = buffer[2];
    result.y2 = buffer[3];
    return result;
}

tuple *make_tuples_from_file(char* file_name) {
    if (!file_name) {
        return NULL;
    }
    FILE* file = fopen(file_name, "r");
    if (!file) {
        return NULL;
    }
    size_t tuples_number = 0;
    if (!fscanf(file, "%zu", &tuples_number)) {
        fclose(file);
        return NULL;
    }
    tuple *tuples = NULL;
    if (!(tuples = (tuple*) malloc(sizeof(tuple) * tuples_number))) {
        fclose(file);
        return NULL;
    }
    for (size_t i = 0 ; i < tuples_number ; ++i) {
        int32_t source = 0;
        if (!fscanf(file, "%"PRId32, &source)) {
            free(tuples);
            return NULL;
        }
        tuples[i] = make_tuple(&source);
        if (tuple_is_wrong(&tuples[i])) {
            free(tuples);
            return NULL;
        }
    }
    fclose(file);
    return tuples;
}

double calculate_edge(tuple *single_tuple) {
    if (!single_tuple) {
        return -1;
    }
    double result = 0;
    result = sqrt(pow((single_tuple->x2 - single_tuple->x1), 2)
                  + pow((single_tuple->y2 - single_tuple->y1), 2));
    return result;
}

int tuple_is_wrong(tuple *source) {
    if (!source) {
        return 1;
    }
    if ((source->x1 == 0)
    && (source->y1 == 0)
    && (source->x2 == 0)
    && (source->y2 == 0)) {
        return 1;
    }
    return 0;
}
