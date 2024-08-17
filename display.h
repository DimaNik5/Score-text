#pragma once

#include <stdio.h>

#include "drawTools.h"
#include "draw.h"

/*
*   Файл с описанием callback функций и структур данных
*/

// Структура данных, указатель на которую передаются в callback функции
struct dat{
    int h, w;
    struct mouse *mouse;
    EditText *etext;
    Simbol *s;
};

// Структура с информацией о положении мышки и состоянии кнопок
struct mouse{
    int x, y;
    char leftPressed;
};

// Функция для создания структуры данных
struct dat* createDat(int h, int w);

// Функция для загрузки шрифта из картинки; возвращает 1, если загрузка удалась
char loadFont(struct ViewPort* v, struct dat* d, wchar_t *name);

// Функция для освобождения памяти из под структуры данных
void deleteDat(struct dat *d);

// Callback функция отображения содержимого на экране 
void display(struct Surface *sf, void *data);

// Callback функция обработки нажатия клавиши
void keyBind(struct Surface* sf, int code, void *data);

// Callback функция обработки действий мышью
void mouseBind(struct Surface *sf, enum mouseType type, int x, int y, void *data);