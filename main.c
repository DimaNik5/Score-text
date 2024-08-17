/*
*   Программа - текстовый редактор.
*   Написана на языке "C" с использованием Simple DirectMedia Layer (SDL) версии 2.0 для создания оконного приложения.
*   Проект создан 13 июля 2024 года.
*   Автор: Никифоров Дмитрий.
*   Последние изменения: 17.08.2024.
*
*
*   Для компиляции через gcc с терминалом:
*   gcc -O2 -o test main.c draw.c drawTools.c display.c -lSDL2 -lSDL2_image
*
*   Без терминала:
*   gcc -O2 -mwindows -o test main.c draw.c drawTools.c display.c -lSDL2 -lSDL2_image
*/


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
    if(!loadFont(v, d, "bitfont.png")){
        abort();
    }
    while(ViewPort_poll(v)){
    }
    destroyViewPort(v);
    deleteDat(d);
    return 0;
}    
