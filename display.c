#include "display.h"

// Проверка на нахождение точки внутри прямоугольника
#define COLISION(RECT, X, Y) (RECT->x <= X && RECT->y <= Y && RECT->x + RECT->w >= X && RECT->y + RECT->h >= Y)

struct dat* createDat(int h, int w){
    struct dat *d = (struct dat*)malloc(sizeof(struct dat));
    d->h = h;
    d->w = w;
    d->mouse = (struct mouse*)malloc(sizeof(struct mouse));
    d->mouse->leftPressed = 0;
    d->mouse->x = 0;
    d->mouse->y = 0;
    d->etext = (EditText*)malloc(sizeof(EditText));
    d->etext->x = 10;
    d->etext->y = 30;
    d->etext->w = w - d->etext->x;
    d->etext->h = h - d->etext->y;
    d->etext->wscroll = 20;
    d->etext->pos = 0;
    d->etext->posSelect = -1;
    d->etext->toffset = 0;
    d->etext->moveCur = 0;
    d->etext->text = (Text*)malloc(sizeof(Text));
    d->etext->text->first = (wchar_t*)malloc(sizeof(wchar_t));
    *d->etext->text->first = 0;
    d->etext->text->last = d->etext->text->first;
    
    return d;
}

char loadFont(struct ViewPort* v, struct dat* d, wchar_t *name){
    d->s = createFont(v, RGBA(0x00, 0x00, 0x00, 0xff), name);
    return d->s ? 1 : 0;
}

void deleteDat(struct dat *d){
    if(!d) return;
    if(d->s) deleteFont(d->s);
    free(d->mouse);
    free(d);
}

void display(struct Surface *sf, void *data){
    struct dat *d = (struct dat*)(data);
    if(d->h != d->etext->h + d->etext->y || d->w != d->etext->w + d->etext->x){
        d->etext->h = d->h - d->etext->y;
        d->etext->w = d->w - d->etext->x;
    }

    setColor(sf, RGBA(250, 250, 250, 255));
    putRect(sf, 0, 0, d->w, d->h);

    drawEditText(sf, d->s, d->etext);

    drawTopTools(sf, d->w, 30);

}

void keyBind(struct Surface* sf, int code, void *data){
    struct dat *d = (struct dat*)(data);
    printf("%C - %d\n", code, code);
    if(code > 31 && code < 256 && code != 127){
        addText(d->etext, code, d->etext->pos);
    }
    else{
        switch(code){
            case 13:
                addText(d->etext, 10, d->etext->pos); // переход строки
                break;
            case 9:
                addText(d->etext, 32, d->etext->pos);
                addText(d->etext, 32, d->etext->pos);
                addText(d->etext, 32, d->etext->pos);
                addText(d->etext, 32, d->etext->pos);
                break;
            case 8:
                delText(d->etext, d->etext->pos, 1);
                break;
            case 127:
                delText(d->etext, d->etext->pos, 0);
                break;
            case 259: // up
                addLineCursor(d->s->w, d->etext, 0);
                break;
            case 260: // left
                addPosCursor(d->etext, 0);
                break;
            case 261: // down
                addLineCursor(d->s->w, d->etext, 1);
                break;
            case 262: // right
                addPosCursor(d->etext, 1);
                break;

        }
    }
}

void mouseBind(struct Surface *sf, enum mouseType type, int x, int y, void *data){
    struct dat *d = (struct dat*)(data);
    switch (type)
    {
    case MOTION:
        d->mouse->x = x;
        d->mouse->y = y;
        if(COLISION(d->etext, x, y) && d->mouse->leftPressed){
            if(d->etext->w - d->etext->wscroll > x){
                if(d->etext->posSelect < 0){
                    d->etext->posSelect = d->etext->pos;
                }
                else{
                    setCursorByMouse(d->s->w, d->s->h, d->etext, x, y);
                }
            }
            else{

            }
        }
        break;
    case WHEEL:
        d->etext->toffset -= 10 * y;
        if(d->etext->toffset < 0) d->etext->toffset = 0;
        //d->etext->moveCur = 1;
        break;
    case LEFTDOWN:{
        d->mouse->leftPressed = 1;
        if(COLISION(d->etext, x, y)) {
            if(d->etext->w - d->etext->wscroll > x){
                if(d->etext->posSelect > -1) d->etext->posSelect = -1;
                setCursorByMouse(d->s->w, d->s->h, d->etext, x, y);
            }
            else{

            }
        }
        break;
    }
    case LEFTUP:
        d->mouse->leftPressed = 0;
        break;
    case RIGHTDOWN:
        
        break;
    case RIGHTUP:
        
        break;
    
    }
}