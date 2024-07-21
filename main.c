// gcc -O2 -o test main.c draw.c elements.c display.c -lSDL2 -lSDL2_image
// gcc -O2 -mwindows -o test main.c draw.c elements.c display.c -lSDL2 -lSDL2_image


#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "display.h"


#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

const int height = 480, width = 640;

#if defined(_WIN32) || defined(WIN32)
int WinMain(HINSTANCE h, HINSTANCE g, LPSTR s, int n)
#else
int main(int argc, char *argv[])
#endif
{
    struct dat *d = createDat(height, width);
    struct ViewPort *v = ViewPort_query(width, height, "test", 1, d, display, &keyBind, &mouseBind);
    if(!loadFont(v, d, L"bitfont.png")){
        abort();
    }
    while(ViewPort_poll(v)){
    }
    destroyViewPort(v);
    deleteDat(d);
    return 0;
}    
