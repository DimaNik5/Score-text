#pragma once

#include <stdio.h>

#include "elements.h"
#include "draw.h"

struct dat{
    int h, w;
    struct mouse *mouse;
    wchar_t text[128];
    short l;
};

struct mouse{
    int x, y;
    short leftPressed;
};

struct dat* createDat(int h, int w);

void deleteDat(struct dat *d);

void display(struct Surface *sf, void *data);

void keyBind(struct Surface* sf, int code, void *data);

void mouseBind(struct Surface *sf, enum mouseType type, int x, int y, void *data);