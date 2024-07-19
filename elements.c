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

typedef struct{
    int hs;
    int ws;
    SDL_Texture* texture;
    SDL_Rect *simb, *place;
}Simbol;

static Simbol simbol = {36, 17, NULL, NULL, NULL};

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

Uint32 addAlpha(Uint8 *ptr, int i){
    return  (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? 
            (sALPHA(0xff) | sRED(ptr[i]) | sGREEN(ptr[i+1]) | sBLUE(ptr[i+2])) :
            (sALPHA(0xff) | sRED(ptr[i+2]) | sGREEN(ptr[i]) | sBLUE(ptr[i+1])); // более похож на оригинал 
}

short loadFont(struct ViewPort* v){
    int pitch, w = 272, h = 504;
    simbol.place = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    simbol.simb = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    simbol.simb->h = simbol.hs;
    simbol.simb->w = simbol.ws;
    simbol.place->h = simbol.hs;
    simbol.place->w = simbol.ws;
    simbol.texture = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    SDL_SetTextureBlendMode(simbol.texture, SDL_BLENDMODE_BLEND);
    if(!simbol.texture) return 0;
    Uint32* pixels;

    if(SDL_LockTexture(simbol.texture, NULL, &pixels, &pitch)){
        return 0;
    }
    if(SDL_RenderReadPixels(v->ren, NULL, SDL_PIXELFORMAT_RGBA8888, pixels, pitch)){
        return 0;
    }

    SDL_Surface *surface = IMG_Load("bitfont.png");
    Uint8 psize = surface->format->BytesPerPixel;
    Uint8 * ptr = (Uint8*)surface->pixels;

    Uint32 from_pixel = RGB(20, 20, 20);
    Uint32 to_pixel   = RGBA(0, 0, 0, 0);

    for (int i = 0; i < w * h; i++) {
        if (ptr[i*psize] <= RED(from_pixel) && ptr[i*psize + 1] <= GREEN(from_pixel) && ptr[i*psize + 2] <= BLUE(from_pixel)) {
            pixels[i] = to_pixel;
        }
        else{
            pixels[i] = addAlpha(ptr, i*psize);
        }
    }
    SDL_UnlockTexture(simbol.texture);
    SDL_FreeSurface(surface);
    return 1;
}

void lineText(struct Surface* sf, int x, int y, wchar_t *text){
    simbol.place->x = x;
    simbol.place->y = y;
    int i = 0;
    while (text[i])
    {
        simbol.simb->x = ((text[i] - 32) & 0xf) * simbol.ws;
        simbol.simb->y = ((text[i] - 32) / 0x10) * simbol.hs;
        SDL_RenderCopy(sf->r, simbol.texture, simbol.simb, simbol.place);
        simbol.place->x += simbol.place->w;
        i++;
    }
}

int setHeightLineText(int h){
    simbol.place->w = round((double)simbol.place->w / (simbol.place->h / h));
    simbol.place->h = h;
    return simbol.place->w;
}

void deleteFont(){
    free(simbol.place);
    free(simbol.simb);
    free(simbol.texture);
}
