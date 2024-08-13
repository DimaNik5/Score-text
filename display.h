#pragma once

#include <stdio.h>

#include "drawTools.h"
#include "draw.h"

struct dat{
    int h, w;
    struct mouse *mouse;
    EditText *etext;
    Simbol *s;
};

struct mouse{
    int x, y;
    char leftPressed;
};

struct dat* createDat(int h, int w);

char loadFont(struct ViewPort* v, struct dat* d, wchar_t *name);

void deleteDat(struct dat *d);

void display(struct Surface *sf, void *data);

void keyBind(struct Surface* sf, int code, void *data);

void mouseBind(struct Surface *sf, enum mouseType type, int x, int y, void *data);