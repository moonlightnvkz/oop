#include <stdio.h>
#include "tests_Array2D.h"

int main() {
    printf("Test array_create: %d\n",  test_array_create());
    printf("Test array_fill: %d\n",  test_array_fill());
    printf("Test array_get: %d\n",  test_array_get());
    printf("Test array_set: %d\n",  test_array_set());
    return 0;
}