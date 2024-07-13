#pragma once

#include <stdio.h>

#include "elements.h"
#include "draw.h"

struct dat{
    int h, w;
    int x, y;
    int l;
};

void call(struct Surface *sf, void *data);

void keyBind(struct Surface* sf, int code, void *data);