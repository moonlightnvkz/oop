//
// Created by moonlightnvkz on 13.02.17.
//

#pragma once

#include <stdlib.h>

typedef struct _Array2D {
    size_t i;
    size_t j;
    int * data;
} Array2D;

// Создать новый массив с размерностью mxn
Array2D *array_create(int m, int n);

// Уничтожить массив
void array_delete(Array2D *arr);

// Заполнить весь массив значением value
void array_fill(Array2D *arr, int value);

// Получить значение из массива
int array_get(Array2D *arr, int i, int j);

// Установить значение в массиве
void array_set(Array2D *arr, int i, int j, int value);