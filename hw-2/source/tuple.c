#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "tuple.h"

tuple make_tuple(int32_t *source) {
    tuple result = {0, 0, 0, 0};
    if (!source) {
        return result;
    }
    int8_t buffer[4];
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
    fscanf(file,"%zu", &tuples_number);
    tuple *tuples = NULL;
    if (!(tuples = (tuple*) malloc(sizeof(tuple) * tuples_number))) {
        return NULL;
    }
    for (size_t i = 0 ; i < tuples_number ; ++i) {
        int32_t source = 0;
        fscanf(file,"%"PRId32, &source);
        tuples[i] = make_tuple(&source);
    }
    fclose(file);
    return tuples;
}

double calculate_edge(tuple *single_tuple) {
    double result = 0;
    result = sqrt(pow((single_tuple->x2 -single_tuple->x1), 2)
                  + pow((single_tuple->y2 - single_tuple->y1), 2));
    return result;
}
