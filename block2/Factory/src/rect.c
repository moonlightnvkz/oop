//
// Created by moonlightnvkz on 13.02.17.
//

#include <stdio.h>
#include "rect.h"
#include "new.h"

static void  *Rect_ctor(void *_self, va_list *app) {
    struct Rect *self = _self;
    ((const struct Class *)Point)->ctor((void*)&(self)->position, app);
    ((const struct Class *)Point)->ctor((void*)&(self)->dimensions, app);
    return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)
#define w(p) (((const struct Point *)(p) + 1) -> x)
#define h(p) (((const struct Point *)(p) + 1) -> y)

static void Rect_draw(const void * _self)
{
    const struct Rect * self = _self;
    printf("rect at %d,%d width %d height %d\n", x(self), y(self), w(self), h(self));
}

static const struct Class _Rect = {
        sizeof(struct Rect),
        Rect_ctor,
        0,
        Rect_draw
};

const void *Rect = &_Rect;