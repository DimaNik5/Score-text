#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

enum mouseType{
    MOTION,
    WHEEL,
    LEFTDOWN,
    LEFTUP,
    RIGHTDOWN,
    RIGHTUP,
    WHEELDOWN,
    WHEELUP
};

static const int estfps = 30;
static const int msec_in_sec = 1000;

typedef void (*callback)(struct Surface *sf, void *data);

typedef void (*keyBindCall)(struct Surface *sf, int code, void *data);

typedef void (*mouseBindCall)(struct Surface *sf, enum mouseType type, int x, int y, void *data);

struct ViewPort {
    int width, height;
    SDL_Window *screen;
    SDL_Renderer *ren;
    callback fun;
    keyBindCall keybind;
    mouseBindCall mousebind;
    void* data;
};

int getCode(int code);

struct ViewPort* ViewPort_query(int width, int height, const char name[32], short alpha, void *data, callback fun, keyBindCall kbc, mouseBindCall mbc);

int ViewPort_poll(struct ViewPort *v);

void destroyViewPort(struct ViewPort *vp);
