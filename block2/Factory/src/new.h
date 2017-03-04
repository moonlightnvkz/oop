#ifndef __new_h
#define __new_h

#include <stddef.h>
#include <stdarg.h>

struct Class {
    size_t size;
    void *(*ctor)(void *self, va_list *app);
    void *(*dtor)(void *self);
    void (*draw)(const void *self);
};

void *new_2(const void *_class, ...);
void delete_2(void *item);
void draw(const void *self);

#endif
