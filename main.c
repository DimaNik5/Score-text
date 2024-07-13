// gcc -O2 -o test main.c draw.c elements.c display.c -lSDL2

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
    struct dat d = {height, width, 100, 100, 500};
    struct ViewPort *v = ViewPort_query(width, height, "test", &call, &d, &keyBind);
    while(ViewPort_poll(v)){
        if(d.y < d.h - 100) d.y++;
        else d.y--;
    }
    destroyViewPort(v);
    return 0;
}    
