#pragma once

#include "draw.h"
#include <math.h>

typedef struct{
    SDL_Texture* texture;
    SDL_Rect *simb, *place;
}Simbol;

Uint32 RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

Uint32 RGB(Uint8 r, Uint8 g, Uint8 b);

void setColor(struct Surface* sf, Uint32 c);

void putPix(struct Surface* sf, int x, int y);

void putColorPix(struct Surface* sf, int x, int y, Uint32 c);

short createFont(struct ViewPort* v, Uint32 color, wchar_t *name);

void lineText(struct Surface* sf, Simbol *simbol, int x, int y, wchar_t *text);

int setHeightLineText(Simbol *simbol, int h);

void deleteFont(Simbol *simbol);