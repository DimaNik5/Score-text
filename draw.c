#include "draw.h"

#define XOR(A, B) (A != B)
#define TO_BOOL(X) X ? 1 : 0

int getCode(int code){
    short shift = TO_BOOL(GetKeyState(16) & 0x8000);
    short caps =  TO_BOOL(GetKeyState(20));
    short numLock = TO_BOOL(GetKeyState(144));
    short ctrl = TO_BOOL(GetKeyState(17) & 0x8000);
    short alt = TO_BOOL(GetKeyState(18) & 0x8000);
    short en = 1;

    char KBLayout[64];
    GetKeyboardLayoutNameA(KBLayout);
    if (strcmp(KBLayout,"00000419") == 0) en = 0;

    if( code <= 127 && !(shift | caps | ctrl | alt) && en){
        return code;
    }
    switch(code){
        case '`':{
            if(en){
                if(shift){
                    return '~';
                }
                return code;
            }
            if(shift){
                return 240;
            }
            return 241;
        }
        case '1':{
            if(shift){
                return '!';
            }
            return code;
        }
        case '2':{
            if(en){
                if(shift){
                    return '@';
                }
            }
            if(shift){
                return '"';
            }
            return code;
        }
        case '3':{
            if(en){
                if(shift){
                    return '#';
                }
            }
            if(shift){
                return 252;
            }
            return code;
        }
        case '4':{
            if(en){
                if(shift){
                    return '$';
                }
                return code;
            }
            if(shift){
                return ';';
            }
            return code;
        }
        case '5':{
            if(shift){
                return '%';
            }
            return code;
        }
        case '6':{
            if(en){
                if(shift){
                    return '^';
                }
            }
            if(shift){
                return ':';
            }
            return code;
        }
        case '7':{
            if(en){
                if(shift){
                    return '&';
                }
            }
            if(shift){
                return '?';
            }
            return code;
        }
        case '8':{
            if(shift){
                return '*';
            }
            return code;
        }
        case '9':{
            if(shift){
                return '(';
            }
            return code;
        }
        case '0':{
            if(shift){
                return ')';
            }
            return code;
        }
        case '-':{
            if(shift){
                return '_';
            }
            return code;
        }
        case '=':{
            if(shift){
                return '+';
            }
            return code;
        }
        case 13:
        case 27:
        case 32:
        case 9:
        case 127:
        case 8:{
            return code;
        }
        case 0x4000004A:{
            return HOME;
        }
        case 0x4000004D:{
            return END;
        }
        case 0x4000004F:{
            return RIGHT;
        }
        case 0x40000050:{
            return LEFT;
        }
        case 0x40000051:{
            return BOTTOM;
        }
        case 0x40000052:{
            return TOP;
        }
        case 0x40000054:{
            return '/';
        }
        case 0x40000055:{
            return '*';
        }
        case 0x40000056:{
            return '-';
        }
        case 0x40000057:{
            return '+';
        }
        case 0x40000058:{
            return 13;
        }
        case 0x40000059:{
            if(!numLock){
                return END;
            }
            return '1';
        }
        case 0x4000005A:{
            if(!numLock){
                return BOTTOM;
            }
            return '2';
        }
        case 0x4000005B:{
            if(!numLock){
                return NF;
            }
            return '3';
        }
        case 0x4000005C:{
            if(!numLock){
                return LEFT;
            }
            return '4';
        }
        case 0x4000005D:{
            if(!numLock){
                return NF;
            }
            return '5';
        }
        case 0x4000005E:{
            if(!numLock){
                return RIGHT;
            }
            return '6';
        }
        case 0x4000005F:{
            if(!numLock){
                return HOME;
            }
            return '7';
        }
        case 0x40000060:{
            if(!numLock){
                return TOP;
            }
            return '8';
        }
        case 0x40000061:{
            if(!numLock){
                return NF;
            }
            return '9';
        }
        case 0x40000062:{
            if(!numLock){
                return NF;
            }
            return '0';
        }
        case 'q':{
            if(en){
                if(XOR(shift, caps)){
                    return 'Q';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 137;
            }
            return 169;
        }
        case 'w':{
            if(en){
                if(XOR(shift, caps)){
                    return 'W';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 150;
            }
            return 230;
        }
        case 'e':{
            if(en){
                if(XOR(shift, caps)){
                    return 'E';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 147;
            }
            return 227;
        }
        case 'r':{
            if(en){
                if(XOR(shift, caps)){
                    return 'R';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 138;
            }
            return 170;
        }
        case 't':{
            if(en){
                if(XOR(shift, caps)){
                    return 'T';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 133;
            }
            return 165;
        }
        case 'y':{
            if(en){
                if(XOR(shift, caps)){
                    return 'Y';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 141;
            }
            return 173;
        }
        case 'u':{
            if(en){
                if(XOR(shift, caps)){
                    return 'U';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 131;
            }
            return 163;
        }
        case 'i':{
            if(en){
                if(XOR(shift, caps)){
                    return 'I';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 152;
            }
            return 232;
        }
        case 'o':{
            if(en){
                if(XOR(shift, caps)){
                    return 'O';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 153;
            }
            return 233;
        }
        case 'p':{
            if(en){
                if(XOR(shift, caps)){
                    return 'P';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 135;
            }
            return 167;
        }
        case '[':{
            if(en){
                if(shift){
                    return '{';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 149;
            }
            return 229;
        }
        case ']':{
            if(en){
                if(shift){
                    return '}';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 154;
            }
            return 234;
        }
        case 'a':{
            if(en){
                if(XOR(shift, caps)){
                    return 'A';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 148;
            }
            return 228;
        }
        case 's':{
            if(en){
                if(XOR(shift, caps)){
                    return 'S';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 155;
            }
            return 235;
        }
        case 'd':{
            if(en){
                if(XOR(shift, caps)){
                    return 'D';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 130;
            }
            return 162;
        }
        case 'f':{
            if(en){
                if(XOR(shift, caps)){
                    return 'F';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 128;
            }
            return 160;
        }
        case 'g':{
            if(en){
                if(XOR(shift, caps)){
                    return 'G';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 143;
            }
            return 175;
        }
        case 'h':{
            if(en){
                if(XOR(shift, caps)){
                    return 'H';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 144;
            }
            return 224;
        }
        case 'j':{
            if(en){
                if(XOR(shift, caps)){
                    return 'J';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 142;
            }
            return 174;
        }
        case 'k':{
            if(en){
                if(XOR(shift, caps)){
                    return 'K';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 139;
            }
            return 171;
        }
        case 'l':{
            if(en){
                if(XOR(shift, caps)){
                    return 'L';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 132;
            }
            return 164;
        }
        case ';':{
            if(en){
                if(shift){
                    return ':';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 134;
            }
            return 166;
        }
        case '\'':{
            if(en){
                if(shift){
                    return '"';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 157;
            }
            return 237;
        }
        case '\\':{
            if(en){
                if(shift){
                    return '|';
                }
                return code;
            }
            if(shift){
                return '/';
            }
            return code;
        }
        case 'z':{
            if(en){
                if(XOR(shift, caps)){
                    return 'Z';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 159;
            }
            return 239;
        }
        case 'x':{
            if(en){
                if(XOR(shift, caps)){
                    return 'X';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 151;
            }
            return 231;
        }
        case 'c':{
            if(en){
                if(XOR(shift, caps)){
                    return 'C';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 145;
            }
            return 225;
        }
        case 'v':{
            if(en){
                if(XOR(shift, caps)){
                    return 'V';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 140;
            }
            return 172;
        }
        case 'b':{
            if(en){
                if(XOR(shift, caps)){
                    return 'B';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 136;
            }
            return 168;
        }
        case 'n':{
            if(en){
                if(XOR(shift, caps)){
                    return 'N';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 146;
            }
            return 226;
        }
        case 'm':{
            if(en){
                if(XOR(shift, caps)){
                    return 'M';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 156;
            }
            return 236;
        }
        case ',':{
            if(en){
                if(shift){
                    return '<';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return 129;
            }
            return 161;
        }
        case '.':{
            if(en){
                if(shift){
                    return '>';
                }
                return code;
            }
            if(XOR(shift, caps)){
                return ',';
            }
            return '.';           
        }
        case '/':{
            if(en){
                if(shift){
                    return '?';
                }
                return code;
            }
            if(shift){
                return ',';
            }
            return '.';
        }
        case 1105:{
            if(!en){
                if(XOR(shift, caps)){
                    return 240;
                }
                return 241;
            }
        }
        case 1093:{
            if(!en){
                if(XOR(shift, caps)){
                    return 149;
                }
                return 229;
            }
        }
        case 1098:{
            if(!en){
                if(XOR(shift, caps)){
                    return 154;
                }
                return 234;
            }
        }
        case 1078:{
            if(!en){
                if(XOR(shift, caps)){
                    return 134;
                }
                return 166;
            }
        }
        case 1101:{
            if(!en){
                if(XOR(shift, caps)){
                    return 157;
                }
                return 237;
            }
        }
        case 1073:{
            if(!en){
                if(XOR(shift, caps)){
                    return 129;
                }
                return 161;
            }
        }
        case 1102:{
            if(!en){
                if(XOR(shift, caps)){
                    return 158;
                }
                return 238;
            }
        }
    }
    return NF;
}

struct ViewPort* ViewPort_query(int width, int height, const char name[32], short alpha, void *data, callback fun, keyBindCall kbc, mouseBindCall mbc){
    struct ViewPort* vp = (struct ViewPort*)malloc(sizeof(struct ViewPort));
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        ERR(SDL_Init, 1);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        ERR(SDL_Init, 1);
    
    vp->width = width;
    vp->height = height;
    vp->fun = fun;
    vp->keybind = kbc;
    vp->mousebind = mbc;
    vp->data = data;

    vp->screen = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, vp->width, vp->height,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if(!vp->screen)
        ERR(SDL_CreateWindow, 1);
    
    vp->ren = SDL_CreateRenderer(vp->screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!vp->ren)
        ERR(SDL_CreateRenderer, 1);
    if(SDL_SetRenderDrawBlendMode(vp->ren, alpha))
        ERR(SDL_GetError(), 0);

    return vp;
}

int ViewPort_poll(struct ViewPort *v){
    SDL_Event event;
    short type = 0;
    Uint32 start, elapsed, estimated = msec_in_sec / estfps;
    start = SDL_GetTicks();

    struct Surface s = {v->ren};
    
    while(SDL_PollEvent(&event)){
        if(!type) type = 1;
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;

        case SDL_KEYDOWN:
            if(v->keybind)
                v->keybind(&s, getCode(event.key.keysym.sym), v->data);
            break;

        case SDL_MOUSEMOTION:
            v->mousebind(&s, MOTION, event.motion.x, event.motion.y, v->data);
            break;
        case SDL_MOUSEWHEEL:
            v->mousebind(&s, WHEEL, event.wheel.x, event.wheel.y, v->data);
            break;

        case SDL_MOUSEBUTTONDOWN:
            type = event.button.button == SDL_BUTTON_LEFT? LEFTDOWN : event.button.button == SDL_BUTTON_RIGHT? RIGHTDOWN : WHEELDOWN;
            v->mousebind(&s, type, event.button.x, event.button.y, v->data);
            break;
        case SDL_MOUSEBUTTONUP:
            type = event.button.button == SDL_BUTTON_LEFT? LEFTUP : event.button.button == SDL_BUTTON_RIGHT? RIGHTUP : WHEELUP;
            v->mousebind(&s, type, event.button.x, event.button.y, v->data);
            break;
        
        case 8192: // изменение размеров окна
            SDL_GetWindowSize(v->screen, &v->width, &v->height);
            break;
        default:
            break;
        }
    }
    if(type){
        SDL_SetRenderDrawColor(v->ren, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(v->ren);
        v->fun(&s, v->data);
        SDL_RenderPresent(v->ren);
    }

    elapsed = SDL_GetTicks() - start;
    if(elapsed < estimated)
        SDL_Delay(estimated - elapsed);
    return 1;

}

void destroyViewPort(struct ViewPort *vp){
    SDL_DestroyRenderer(vp->ren);
    SDL_DestroyWindow(vp->screen);
    free(vp);
    SDL_Quit();
}