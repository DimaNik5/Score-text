#include "drawTools.h"

// Извлекает из кода выбранный цвет
#define RED(C) (C >> 16) & 0xff
#define GREEN(C) (C >> 8) & 0xff
#define BLUE(C) (C & 0xff)
#define ALPHA(C) (C >> 24) & 0xff

// Задает выбранному цвету положение в коде
#define sRED(C) (C << 16)
#define sGREEN(C) (C << 8)
#define sBLUE(C) C
#define sALPHA(C) (C << 24)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Получает символ из структуры текста
#define getSimbol(TEXT, i) *(TEXT->first + i)
// Проверяет, выделен ли данный символ
#define SELECTED(I, S, C) (S > -1 && I >= MIN(S, C) && I < MAX(S, C))


//int hp = 504, hs = 36;
//int wp = 272, ws = 17;

void addText(EditText *t, wchar_t v, int p)
{
    t->moveCur = 1;
    const size_t n = t->text->last - t->text->first + 1;
    if(p >= n || p < 0) return;
    wchar_t *ans = (wchar_t*)malloc(sizeof(wchar_t) * (n + 1));
    if(p) wcsncpy(ans, t->text->first, p);
    ans[p] = v;
    ans[p + 1] = 0;
    wcscat(ans, t->text->first + p);
    free(t->text->first);
    t->text->first = ans;
    t->text->last = ans + n + 1;
    addPosCursor(t, 1);
}

void delText(EditText *t, int p, Uint8 back){
    t->moveCur = 1;
    const size_t n = t->text->last - t->text->first + 1;
    if(p >= n || p < 0) return;
    if (back){
        if(p == 0) return;
        t->pos--;
    }
    else{
        if (p == n - 1) return;
    }
    wchar_t *ans = (wchar_t*)malloc(sizeof(wchar_t) * n);
    wcsncpy(ans, t->text->first, back ? p - 1 : p);
    ans[back ? p - 1 : p] = 0;
    wcscat(ans, t->text->first + (back ? p : p + 1));
    free(t->text->first);
    t->text->first = ans;
    t->text->last = ans + n - 1;
}

void setColor(struct Surface* sf, Uint32 c){
    SDL_SetRenderDrawColor(sf->r, RED(c), GREEN(c), BLUE(c), ALPHA(c));
}

void putPix(struct Surface* sf, int x, int y){
    SDL_RenderDrawPoint(sf->r, x, y);
}

void putRect(struct Surface* sf, int x, int y, int w, int h){
    SDL_Rect r = {x, y, w, h};
    SDL_RenderFillRect(sf->r, &r);
}

Uint32 RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    return (sALPHA(a) | sRED(r) | sGREEN(g) | sBLUE(b));
}

Uint32 RGB(Uint8 r, Uint8 g, Uint8 b){
    return (sRED(r) | sGREEN(g) | sBLUE(b));
}

Simbol* createFont(struct ViewPort* v, Uint32 color, wchar_t *name){
    int pitch, w = 272, h = 504;
    Simbol *simbol = (Simbol*)malloc(sizeof(Simbol));
    simbol->sh = 36;
    simbol->sw = 17;
    simbol->h = 36;
    simbol->w = 17;
    simbol->color = color;
    simbol->texture = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    SDL_SetTextureBlendMode(simbol->texture, SDL_BLENDMODE_BLEND);
    if(!simbol->texture) return NULL;
    Uint32 *pixels;

    if(SDL_LockTexture(simbol->texture, NULL, &pixels, &pitch)){
        return NULL;
    }
    if(SDL_RenderReadPixels(v->ren, NULL, SDL_PIXELFORMAT_ARGB8888, pixels, pitch)){
        return NULL;
    }

    double alphaColor = (ALPHA(color)) / 0xff;

    SDL_Surface *surface = IMG_Load(name);
    Uint8 psize = surface->format->BytesPerPixel;
    Uint8 * ptr = (Uint8*)surface->pixels;

    Uint32 from_pixel = RGB(20, 20, 20);
    Uint32 to_pixel   = RGBA(0, 0, 0, 0);
    
    for (int i = 0; i < w * h; i++) {
        if (ptr[i*psize] <= RED(from_pixel) && ptr[i*psize + 1] <= GREEN(from_pixel) && ptr[i*psize + 2] <= BLUE(from_pixel)) {
            pixels[i] = to_pixel;
        }
        else if(ptr[i*psize] <= 245 && ptr[i*psize + 1] <= 245 && ptr[i*psize + 2] <= 245){
            pixels[i] = ((color & 0xffffff) | sALPHA((int)((ptr[i*psize] + ptr[i*psize + 1] + ptr[i*psize + 2])/3 * alphaColor)));
        }
        else{
            pixels[i] = color;
        }
    }
    SDL_UnlockTexture(simbol->texture);
    SDL_FreeSurface(surface);
    return simbol;
}

void lineText(struct Surface* sf, Simbol *simbol, int x, int y, wchar_t *text){
    SDL_Rect place, simb;
    place.x = x;
    place.y = y;
    place.h = simbol->h;
    place.w = simbol->w;
    simb.h = simbol->sh;
    simb.w = simbol->sw;
    int i = 0;
    while (text[i])
    {
        simb.x = ((text[i] - 32) & 0xf) * simbol->sw;
        simb.y = ((text[i] - 32) / 0x10) * simbol->sh;
        SDL_RenderCopy(sf->r, simbol->texture, &simb, &place);
        place.x += simbol->w;
        i++;
    }
}

void addLineCursor(int w, EditText *t, Uint8 down){
    t->moveCur = 1;
    int placeX = t->x;
    int i = 0, sbefor = 0, sdown = -1, s = 0, stoent = -1;
    while (getSimbol(t->text, i))
    {
        if(sdown == s){
            t->pos = i;
            return;
        }
        if(t->pos == i){
            if(down){
                sdown = s;
                down = 2;
            }
            else{
                if(sbefor == 0) return;
                if(sbefor > s) t->pos -= sbefor;
                else t->pos -= s + 1;
                return;
            }
        }
        if(stoent == -1) stoent = havePlace(placeX - t->x, t->w - t->wscroll, w, t->text->first + i);
        if(stoent-- == 0){
            if(down == 3){
                t->pos += sbefor - sdown + s;
                return;
            }
            if(down == 2) down = 3;
            placeX = t->x;
            stoent = havePlace(placeX - t->x, t->w - t->wscroll, w, t->text->first + i) - ((t->text->first + i + 1) ? 1 : 0);
            sbefor = s;
            s = 0;
        }

        if(getSimbol(t->text, i) == 10){
            if(down == 3){
                t->pos += sbefor - sdown + s;
                return;
            }
            if(down == 2) down = 3;
            placeX = t->x;
            sbefor = s + 1;
            s = 0;
            stoent = -1;
            i++;
            continue;
        }
        placeX += w;
        s++;
        i++;
    }
    if(sdown == s){
        t->pos = i;
        return;
    }
    if(t->pos == i){
        if(!down){
            if(sbefor == 0) return;
            if(sbefor > s) t->pos -= sbefor;
            else t->pos -= s + 1;
            return;
        }
    }
    if(down == 3){
        t->pos += sbefor - sdown + s;
        return;
    }

}

void setCursorByMouse(int w, int h, EditText *t, int x, int y){
    
    int placeX = t->x;
    int i = 0, l = 0, s = 0, stoent = -1;
    while (getSimbol(t->text, i))
    {
        if((l * h + t->y <= y + t->toffset) && ((l + 1) * h + t->y >= y + t->toffset)){
            if(placeX <= x && placeX + w >= x){
                t->pos = i + ((placeX + w / 2 < x && getSimbol(t->text, i) != 10) ? 1 : 0);
                return;
            }
        }
        if(stoent == -1) stoent = havePlace(placeX - t->x, t->w - t->wscroll, w, t->text->first + i);
        if(stoent-- == 0){
            if((l * h + t->y <= y + t->toffset) && ((l + 1) * h + t->y >= y + t->toffset)){
                t->pos = i;
                return;
            }
            l++;
            placeX = t->x;
            stoent = havePlace(placeX - t->x, t->w - t->wscroll, w, t->text->first + i) - ((t->text->first + i + 1) ? 1 : 0);
            s = 0;
        }

        if(getSimbol(t->text, i) == 10){
            if((l * h + t->y <= y + t->toffset) && ((l + 1) * h + t->y >= y + t->toffset)){
                t->pos = i;
                return;
            }
            l++;
            placeX = t->x;
            stoent = -1;
            s = 0;
            i++;
            continue;
        }
        placeX += w;
        s++;
        i++;
    }
    
    if((l * h + t->y <= y + t->toffset) && ((l + 1) * h + t->y >= y + t->toffset)){
        t->pos = i;
        return;
    }

}

void addPosCursor(EditText *t, Uint8 right){
    t->moveCur = 1;
    if(right){
        if(getSimbol(t->text, t->pos)) t->pos++;
    }
    else if(t->pos > 0){
        t->pos--;
    }
}

void drawEditText(struct Surface* sf, Simbol *simbol, EditText *t){
    
    int i = 0, s = 0, l = 0, offset = t->toffset, stoent = -1;
    SDL_Rect place, simb;
    place.x = t->x;
    place.y = t->y - offset;
    place.h = simbol->h;
    place.w = simbol->w;
    simb.h = simbol->sh;
    simb.w = simbol->sw;
    Uint8 visable = t->toffset < simbol->h, someVis = 0;
    if(visable) someVis = 1;
    while (getSimbol(t->text, i))
    {
        if(t->pos == i){
            if(t->moveCur){
                t->moveCur = 0;
                if(t->toffset > l * simbol->h) t->toffset = l * simbol->h;
                else if(t->toffset + t->h < l * simbol->h + simbol->h) t->toffset = l * simbol->h + simbol->h - t->h;
            }
            setColor(sf, simbol->color);
            SDL_RenderDrawLine(sf->r, place.x, place.y, place.x, place.y + place.h);
        }
        if(stoent == -1) stoent = havePlace(place.x - t->x, t->w - t->wscroll , simbol->w, t->text->first + i);
        if(stoent-- == 0){
            l++;
            if(offset <= simbol->h * l) visable = 1;
            if(l * simbol->h > t->h + offset) visable = 0;
            if(visable) someVis = 1;
            place.y += simbol->h;
            place.x = t->x;
            stoent = havePlace(place.x - t->x, t->w - t->wscroll, simbol->w, t->text->first + i) - ((t->text->first + i + 1) ? 1 : 0);
            s = 0;
        }

        if(getSimbol(t->text, i) == 10){
            l++;
            if(offset <= simbol->h * l) visable = 1;
            if(l * simbol->h > t->h + offset) visable = 0;
            if(visable) someVis = 1;
            place.y += simbol->h;
            place.x = t->x;
            s = 0;
            stoent = -1;
            i++;
            continue;
        }

        simb.x = ((getSimbol(t->text, i) - 32) & 0xf) * simbol->sw;
        simb.y = ((getSimbol(t->text, i) - 32) / 0x10) * simbol->sh;

        if(visable){
            if(SELECTED(i, t->posSelect, t->pos)){
                setColor(sf, RGBA(66, 170, 255, 180));
                putRect(sf, place.x, place.y, place.w, place.h);
            }
            SDL_RenderCopy(sf->r, simbol->texture, &simb, &place);
        }
        place.x += simbol->w;
        s++;
        i++;
    }
    if(t->pos == i){
        if(t->moveCur){
            t->moveCur = 0;
            if(t->toffset > l * simbol->h) t->toffset = l * simbol->h;
            else if(t->toffset + t->h < l * simbol->h + simbol->h) t->toffset = l * simbol->h + simbol->h - t->h;
        }
        setColor(sf, simbol->color);
        if(visable) SDL_RenderDrawLine(sf->r, place.x, place.y, place.x, place.y + place.h);
    }
    if(!someVis){
        t->toffset = l * simbol->h + simbol->h - t->h;
    }
    if((l + 1) * simbol->h < t->toffset + t->h){
        t->toffset = (l + 1) * simbol->h - t->h;
        if(t->toffset < 0) t->toffset = 0;
    }

    setColor(sf, 0xfff0f0f0);
    putRect(sf, t->x + t->w - t->wscroll, t->y, t->wscroll, t->h);
    setColor(sf, 0xffe0e0e0);
    if(l * simbol->h <= t->h){
        putRect(sf, t->x + t->w - t->wscroll + 1, t->y + 1, t->wscroll - 2, t->h - 2);
    }else{
        putRect(sf, t->x + t->w - t->wscroll + 1, t->y + 1 + offset * t->h / (l * simbol->h), t->wscroll - 2, t->h * t->h / (l * simbol->h) - 2);
    }
    
}

int havePlace(int start, int width, int ws, wchar_t *t){
    //if(start == 0) return 1;
    width -= start;
    int i = 0;
    while(t[i] && t[i] != 9 && t[i] != 10 && t[i] != 32){
        width -= ws;
        if(width <= 0) {
            if(start){
                return 0;
            }
            else {
                return i;
            }
        }
        i++;
    }
    return -1;
}

int setHeightLineText(Simbol *simbol, int h){
    simbol->w = round((double)simbol->sw / (simbol->sh / h));
    simbol->h = h;
    return simbol->w;
}

void deleteFont(Simbol *simbol){
    free(simbol->texture);
    free(simbol);
}

void drawTopTools(struct Surface* sf, int w, int h){
    setColor(sf, 0xfff0f0f0);
    putRect(sf, 0, 0, w, h);
}
