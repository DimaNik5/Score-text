#include "elements.h"

#define RED(C) (C >> 16) & 0xff
#define GREEN(C) (C >> 8) & 0xff
#define BLUE(C) (C & 0xff)
#define ALPHA(C) (C >> 24) & 0xff

#define sRED(C) (C << 16)
#define sGREEN(C) (C << 8)
#define sBLUE(C) C
#define sALPHA(C) (C << 24)

//int hp = 504, hs = 36;
//int wp = 272, ws = 17;

void setColor(struct Surface* sf, Uint32 c){
    SDL_SetRenderDrawColor(sf->r, RED(c), GREEN(c), BLUE(c), ALPHA(c));
}

void putPix(struct Surface* sf, int x, int y){
    SDL_RenderDrawPoint(sf->r, x, y);
}

void putColorPix(struct Surface* sf, int x, int y, Uint32 c){
    SDL_SetRenderDrawColor(sf->r, sRED(c), sGREEN(c), sBLUE(c), sALPHA(c));
    SDL_RenderDrawPoint(sf->r, x, y);
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
    simbol->place = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    simbol->simb = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    simbol->simb->h = 36;
    simbol->simb->w = 17;
    simbol->place->h = 36;
    simbol->place->w = 17;
    simbol->texture = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    SDL_SetTextureBlendMode(simbol->texture, SDL_BLENDMODE_BLEND);
    if(!simbol->texture) return NULL;
    Uint32* pixels;

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
    simbol->place->x = x;
    simbol->place->y = y;
    int i = 0;
    while (text[i])
    {
        simbol->simb->x = ((text[i] - 32) & 0xf) * simbol->simb->w;
        simbol->simb->y = ((text[i] - 32) / 0x10) * simbol->simb->h;
        SDL_RenderCopy(sf->r, simbol->texture, simbol->simb, simbol->place);
        simbol->place->x += simbol->place->w;
        i++;
    }
}

int setHeightLineText(Simbol *simbol, int h){
    simbol->place->w = round((double)simbol->simb->w / (simbol->simb->h / h));
    simbol->place->h = h;
    return simbol->place->w;
}

void deleteFont(Simbol *simbol){
    free(simbol->place);
    free(simbol->simb);
    free(simbol->texture);
}
