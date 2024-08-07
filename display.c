#include "display.h"

struct dat* createDat(int h, int w){
    struct dat *d = (struct dat*)malloc(sizeof(struct dat));
    d->h = h;
    d->w = w;
    d->text[0] = 0;
    d->l = 0;
    d->mouse = (struct mouse*)malloc(sizeof(struct mouse));
    d->mouse->leftPressed = 0;
    d->mouse->x = 0;
    d->mouse->y = 0;
    return d;
}

short loadFont(struct ViewPort* v, struct dat* d, wchar_t *name){
    d->s = createFont(v, RGBA(0xf1, 0, 0xf1, 0xff), name);
}

void deleteDat(struct dat *d){
    if(!d) return;
    if(d->s) deleteFont(d->s);
    free(d->mouse);
    free(d);
}

void display(struct Surface *sf, void *data){
    struct dat *d = (struct dat*)(data);
        
    setColor(sf, RGBA(0,0, 0, 255));
    for(int i = 0; i < 640; i++){
        for(int j = 0; j < 480; j++){
            putPix(sf, i, j);
        }
    }
    
    lineText(sf, d->s, 1, 1, d->text);
}

void keyBind(struct Surface* sf, int code, void *data){
    struct dat *d = (struct dat*)(data);
    printf("%C - %d\n", code, code);
    if(code > 31 && code < 256){
        d->text[d->l++] = code;
        d->text[d->l] = 0;
    }
    if(code == 9){
        d->text[d->l++] = 32;
        d->text[d->l++] = 32;
        d->text[d->l++] = 32;
        d->text[d->l++] = 32;
        d->text[d->l] = 0;
    }
    if(code == 8){
        d->text[--d->l] = 0;
    }
}

void mouseBind(struct Surface *sf, enum mouseType type, int x, int y, void *data){
    struct dat *d = (struct dat*)(data);
    switch (type)
    {
    case MOTION:
        d->mouse->x = x;
        d->mouse->y = y;
        break;
    case WHEEL:
        
        break;
    case LEFTDOWN:
        d->mouse->leftPressed = 1;
        break;
    case LEFTUP:
        d->mouse->leftPressed = 0;
        break;
    case RIGHTDOWN:
        
        break;
    case RIGHTUP:
        
        break;
    
    }
}