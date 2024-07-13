#include "display.h"

void call(struct Surface *sf, void *data){
    struct dat *d = (struct dat*)(data);
    setColor(sf, RGBA(100, 0, 255, 255));
    putPix(sf, d->x, d->y);
    double step = (d->h - 2 * d->y)/d->l;
    double offset = step;
    for(int i = d->x + 1; i < d->l; i++){
        putPix(sf, i, (int)(d->y + offset));
        offset += step;
    }
}

void keyBind(struct Surface* sf, int code, void *data){
    printf("%C - %d\n", code, code);
}