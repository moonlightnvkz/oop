#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "new.h"
#include "objects.h"

#define MAX_TYPENAME_LENGTH 6 //The longest type name is "Circle"

bool resize_objects_array(void ***objects, size_t new_size) {
    void **temp = realloc(*objects, sizeof(void*) * new_size);
    if (!temp) {
        return false;
    }
    *objects = temp;
    return true;
}

/*
 * Reallocates array if necessary
 * @return number of objects created
 */
size_t parse_input(FILE *input, void ***objects, size_t objects_alloc) {
    size_t objects_size = 0;
    while (!feof(input)) {
        char type[MAX_TYPENAME_LENGTH + 1];
        fscanf(input, "%s", type);
        if (objects_size == objects_alloc) {
            objects_alloc *= 2;
            resize_objects_array(objects, objects_alloc);
        }
        if (strcmp(type, "point") == 0) {
            int x, y;
            fscanf(input, "%d %d", &x, &y);
            (*objects)[objects_size++] = new_2(Point, x, y);
        }
        if (strcmp(type, "circle") == 0) {
            int x, y, r;
            fscanf(input, "%d %d %d", &x, &y, &r);
            (*objects)[objects_size++] = new_2(Circle, x, y, r);
        }
        if (strcmp(type, "line") == 0) {
            int x1, y1, x2, y2;
            fscanf(input, "%d %d %d %d", &x1, &y1, &x2, &y2);
            (*objects)[objects_size++] = new_2(Line, x1, y1, x2, y2);
        }
        if (strcmp(type, "rect") == 0) {
            int x, y, w, h;
            fscanf(input, "%d %d %d %d", &x, &y, &w, &h);
            (*objects)[objects_size++] = new_2(Rect, x, y, w, h);
        }
    }
    return objects_size;
}

int main() {
    FILE *input = fopen("objects", "rt");
    if (!input) {
        fprintf(stderr, "Input file no found");
        exit(1);
    }

    size_t objects_size = 0;
    size_t objects_alloc = 4;
    void **objects = malloc(sizeof(void *) * objects_alloc);

    objects_size = parse_input(input, &objects, objects_alloc);

    for (size_t i = 0; i < objects_size; ++i) {
        draw(objects[i]);
    }
    for (size_t i = 0; i < objects_size; ++i) {
        delete_2(objects[i]);
    }
    free(objects);
    return 0;
}