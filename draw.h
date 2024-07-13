#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

#include "defErr.h"

struct Surface {
    SDL_Renderer *r;
};

enum commands{
    NF = 256,
    HOME,
    END,
    TOP,
    LEFT,
    BOTTOM,
    RIGHT};

struct ViewPort;

static const int estfps = 50;
static const int msec_in_sec = 1000;

typedef void (*callback)(struct Surface *sf, void *data);

typedef void (*keyBindCall)(struct Surface *sf, int code, void *data);

int getCode(int code);

struct ViewPort* ViewPort_query(int width, int height, const char name[32], callback fun, void *data, keyBindCall kbc);

int ViewPort_poll(struct ViewPort *v);

void destroyViewPort(struct ViewPort *vp);
