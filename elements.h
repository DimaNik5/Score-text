#pragma once

#include "draw.h"

enum offsets;

unsigned RGBA(int r, int g, int b, int a);

void setColor(struct Surface* sf, unsigned c);

void putPix(struct Surface* sf, int x, int y);

void putColorPix(struct Surface* sf, int x, int y, unsigned c);