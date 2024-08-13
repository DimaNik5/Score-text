
#pragma once

#include "draw.h"
#include <math.h>
#include <wchar.h>

typedef struct{
    int sh, sw, h, w;
    SDL_Texture* texture;
    SDL_Texture* selectTexture;
}Simbol;

typedef struct{
    wchar_t *first, *last;
}Text;

typedef struct{
    int x, y, w, h, wscroll, toffset;
    Text *text;
    int pos, posSelect;
    Uint8 moveCur;
}EditText;

void addText(EditText *t, wchar_t v, int p);

void delText(EditText *t, int p, Uint8 back);

Uint32 RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

Uint32 RGB(Uint8 r, Uint8 g, Uint8 b);

void setColor(struct Surface* sf, Uint32 c);

void putPix(struct Surface* sf, int x, int y);

void putRect(struct Surface* sf, int x, int y, int w, int h);

Simbol* createFont(struct ViewPort* v, Uint32 color, wchar_t *name, Uint8 select);

void lineText(struct Surface* sf, Simbol *simbol, int x, int y, wchar_t *text);

int setHeightLineText(Simbol *simbol, int h);

void setCursorByMouse(int w, int h, EditText *t, int x, int y);

Uint32 havePlace(int start, int width, int ws, wchar_t *t);

void drawEditText(struct Surface* sf, Simbol *simbol, EditText *t);

void addLineCursor(int w, EditText *t, Uint8 down);

void addPosCursor(EditText *t, Uint8 right);

void deleteFont(Simbol *simbol);