#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "defErr.h"

/*
*   Файл с описанием функций по созданию окна и его обновлению
*/

// Структура для рисования в окне
struct Surface {
    SDL_Renderer *r;
};

// Перечисление с кодами клавиш
enum commands{
    NF = 256,
    HOME,
    END,
    TOP,
    LEFT,
    BOTTOM,
    RIGHT};

// Перечисление с действиями мышью
enum mouseType{
    MOTION,
    WHEEL,
    LEFTDOWN,
    LEFTUP,
    RIGHTDOWN,
    RIGHTUP,
    WHEELDOWN,
    WHEELUP
};

// Константа - количество кадров в секунду
static const int estfps = 30;
// Константа - количество милисекунд в секунде
static const int msec_in_sec = 1000;

// Определеня функторов как типов
typedef void (*callback)(struct Surface *sf, void *data);

typedef void (*keyBindCall)(struct Surface *sf, int code, void *data);

typedef void (*mouseBindCall)(struct Surface *sf, enum mouseType type, int x, int y, void *data);

// Структура, описывающая окно и хранящая callback функции и указатель на данные
struct ViewPort {
    int width, height;
    SDL_Window *screen;
    SDL_Renderer *ren;
    callback fun;
    keyBindCall keybind;
    mouseBindCall mousebind;
    void* data;
};

// Функция для получения кода в нужной кодировке
int getCode(int code);

// Функция для создания окна
struct ViewPort* ViewPort_query(int width, int height, const char name[32], short alpha, void *data, callback fun, keyBindCall kbc, mouseBindCall mbc);

// Функция для обновления окна и проверки событий
int ViewPort_poll(struct ViewPort *v);

// Функция для освобождения памяти из под структуры
void destroyViewPort(struct ViewPort *vp);
