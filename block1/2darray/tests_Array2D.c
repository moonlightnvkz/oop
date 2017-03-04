//
// Created by moonlightnvkz on 13.02.17.
//

#include <stdlib.h>
#include "tests_Array2D.h"
#include "Array2D.h"

bool _test_array_create(int m, int n) {
    Array2D *arr = array_create(m, n);
    bool ret = arr->i == m && arr->j == n;
    array_delete(arr);
    return ret;
}

bool test_array_create() {

    return (
            _test_array_create(1, 1) &&
            _test_array_create(2, 1) &&
            _test_array_create(2, 2) &&
            _test_array_create(21, 32) &&
            _test_array_create(0, 0)
    );
}

bool _test_array_fill(int m, int n, int value) {
    Array2D *arr = array_create(m, n);
    array_fill(arr, value);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (array_get(arr, i, j) != value) {
                return false;
            }
        }
    }
    array_delete(arr);
    return true;
}

bool test_array_fill() {
    array_fill(NULL, 0);
    return (_test_array_fill(1, 1, -2) &&
            _test_array_fill(2, 1, 0) &&
            _test_array_fill(31, 9, 101));
}

bool _test_array_get(int m, int n) {
    Array2D *arr = array_create(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            arr->data[i * arr->j + j] = i * j;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (array_get(arr, i, j) != i * j) {
                return false;
            };
        }
    }

    array_get(arr, -2,  0);
    array_get(arr, 0,  -1);
    array_get(arr, -3,  -1);
    array_get(arr, m,  2);
    array_get(arr, 1,  n);
    array_delete(arr);
    return true;
}

bool _test_array_set(int m, int n) {
    Array2D *arr = array_create(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            array_set(arr, i, j, i * j);
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr->data[i * arr->j + j] != i * j) {
                return false;
            };
        }
    }

    array_set(arr, -2,  0, 0);
    array_set(arr, 0,  -1, 0);
    array_set(arr, -3,  -1, 0);
    array_set(arr, m,  2, 0);
    array_set(arr, 1,  n, 0);
    array_delete(arr);
    return true;
}

bool test_array_get() {
    array_get(NULL, 1, 1);
    return (_test_array_get(1, 1) &&
            _test_array_get(3, 1) &&
            _test_array_get(4, 21));
}

bool test_array_set() {
    array_set(NULL, 1, 1, 0);
    return (_test_array_set(1, 1) &&
            _test_array_set(3, 1) &&
            _test_array_set(4, 21));
}