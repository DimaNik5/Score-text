#pragma once

#include "draw.h"
#include <math.h>

Uint32 RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

Uint32 RGB(Uint8 r, Uint8 g, Uint8 b);

void setColor(struct Surface* sf, Uint32 c);

void putPix(struct Surface* sf, int x, int y);

void putColorPix(struct Surface* sf, int x, int y, Uint32 c);

Uint32 addAlpha(Uint8 *ptr, int i);

short loadFont(struct ViewPort* v);

void lineText(struct Surface* sf, int x, int y, wchar_t *text);

int setHeightLineText(int h);

void deleteFont();