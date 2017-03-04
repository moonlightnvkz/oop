//
// Created by moonlightnvkz on 13.02.17.
//

#include <stdio.h>
#include "line.h"
#include "new.h"

static void  *Line_ctor(void *_self, va_list *app) {
    struct Line *self = _self;
    ((const struct Class *)Point)->ctor((void*)&self->from, app);
    ((const struct Class *)Point)->ctor((void*)&self->to, app);
    return self;
}

#define x1(p) (((const struct Point *)(p)) -> x)
#define y1(p) (((const struct Point *)(p)) -> y)
#define x2(p) (((const struct Point *)(p) + 1) -> x)
#define y2(p) (((const struct Point *)(p) + 1) -> y)

static void Line_draw(const void * _self)
{
    const struct Line * self = _self;
    printf("line from %d,%d to %d,%d\n", x1(self), y1(self), x2(self), y2(self));
}

static const struct Class _Line = {
        sizeof(struct Line),
        Line_ctor,
        0,
        Line_draw
};

const void *Line = &_Line;