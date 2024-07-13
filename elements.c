#include "elements.h"

enum offsets{
    OFF_B,
    OFF_G = 8,
    OFF_R = 16,
    OFF_A = 24
};

void setColor(struct Surface* sf, unsigned c){
    SDL_SetRenderDrawColor(sf->r, c >> OFF_A, (c >> OFF_R) % 256, (c >> OFF_G) % 256, (c >> OFF_B) % 256);
}

void putPix(struct Surface* sf, int x, int y){
    SDL_RenderDrawPoint(sf->r, x, y);
}

void putColorPix(struct Surface* sf, int x, int y, unsigned c){
    SDL_SetRenderDrawColor(sf->r, c >> OFF_A, (c >> OFF_R) % 256, (c >> OFF_G) % 256, (c >> OFF_B) % 256);
    SDL_RenderDrawPoint(sf->r, x, y);
}

unsigned RGBA(int r, int g, int b, int a){
    return (a << OFF_A | r << OFF_G | g << OFF_G | b << OFF_B);
}