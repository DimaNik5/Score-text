
#pragma once

#include "draw.h"
#include <math.h>
#include <wchar.h>

/*
*   Файл с описанием функций для рисования в окне
*/

// Структура, хранящая в себе загруженный шрифт и его характеристики
typedef struct{
    int sh, sw, h, w;
    Uint32 color;
    SDL_Texture* texture;
}Simbol;

// Структура с указателями на начало и конец текста
typedef struct{
    wchar_t *first, *last;
}Text;

// Структура описывающая сам редактируемый текст
typedef struct{
    int x, y, w, h, wscroll, toffset;
    Text *text;
    int pos, posSelect;
    Uint8 moveCur;
}EditText;

// Добавляет символ по индексу
void addText(EditText *t, wchar_t v, int p);

// Удаляет символ по индексу
void delText(EditText *t, int p, Uint8 back);

// Возвращает код цвета с прозрачностью
Uint32 RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Возвращает код цвета без прозрачности
Uint32 RGB(Uint8 r, Uint8 g, Uint8 b);

// Устанавливает цвет для рисования
void setColor(struct Surface* sf, Uint32 c);

// Закрашивает пиксель по координатам выбранным цветом
void putPix(struct Surface* sf, int x, int y);

// Закрашивает прямоугольник по координатам выбранным цветом
void putRect(struct Surface* sf, int x, int y, int w, int h);

// Загружает выбранный шрифт и закрашивает его в выбранный цвет
Simbol* createFont(struct ViewPort* v, Uint32 color, wchar_t *name);

// Выводит текст в строчку
void lineText(struct Surface* sf, Simbol *simbol, int x, int y, wchar_t *text);

// Устанавливает высоту выбранного шрифта и возвращает полученную ширину
int setHeightLineText(Simbol *simbol, int h);

// Устанавливает курсор в редактируемом тексте на указанном месте
void setCursorByMouse(int w, int h, EditText *t, int x, int y);

// Проверяет наличие места на строке и возвращет количество символов до принуждённого переноса строки или -1 если неопределено
int havePlace(int start, int width, int ws, wchar_t *t);

// Рисует редактируемый текст
void drawEditText(struct Surface* sf, Simbol *simbol, EditText *t);

// Добавляет/вычитает строчку курсору в редактируемом тесте
void addLineCursor(int w, EditText *t, Uint8 down);

// Добавляет/вычитает позицию курсора в редактируемом тесте
void addPosCursor(EditText *t, Uint8 right);

// Очищает память из под шрифта
void deleteFont(Simbol *simbol);

// Рисует инструменты сверху
void drawTopTools(struct Surface* sf, int w, int h);