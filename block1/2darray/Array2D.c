//
// Created by moonlightnvkz on 13.02.17.
//

#include <stdio.h>
#include "Array2D.h"

Array2D *array_create(int m, int n) {
    if (m < 0 || n < 0) {
        return NULL;
    }
    Array2D *array2D = malloc(sizeof(Array2D));
    if (!array2D) {
        fprintf(stderr, "Failed to allocate memory for Array2D. In function %s", __FUNCTION__);
        return NULL;
    }
    array2D->i = (size_t)m;
    array2D->j = (size_t)n;
    array2D->data = calloc((size_t) n * m, sizeof(int));
    if (!array2D->data) {
        fprintf(stderr, "Failed to allocate memory for Array2D. In function %s", __FUNCTION__);
        return NULL;
    }
    return array2D;
}

void array_delete(Array2D *arr) {
    if (!arr) {
        return;
    }
    free(arr->data);
    free(arr);
}

void array_fill(Array2D *arr, int value) {
    if (!arr) {
        return;
    }
    for (size_t idx = 0; idx < arr->i * arr->j; ++idx) {
        arr->data[idx] = value;
    }
}

int array_get(Array2D *arr, int i, int j) {
    if (!arr) {
        return 0;
    }
    if (i < 0 || i >= arr->i || j < 0 || j >= arr->j) {
        return 0;
    }
    return arr->data[i * arr->j + j];
}

void array_set(Array2D *arr, int i, int j, int value) {
    if (!arr) {
        return;
    }
    if (i < 0 || i >= arr->i || j < 0 || j >= arr->j) {
        return;
    }
    arr->data[i * arr->j + j] = value;
}