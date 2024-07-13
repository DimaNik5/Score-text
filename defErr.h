#pragma once

#define ERR1(S)                    \
    fprintf(stderr, "[%s:%d] %s error: %s\n", __FILE__, __LINE__, #S, SDL_GetError());

#define ERR2(S, CRIT)   \
    do{                 \
        ERR1(S)         \
        if(CRIT)        \
            abort();    \
    } while (0)

#define GET_3RD_ARG(A1, A2, A3, ...) A3
#define ERR_MACRO_CHOOSER(...) GET_3RD_ARG(__VA_ARGS__, ERR2, ERR1)
#define ERR(...)                                    \
  do {                                              \
    ERR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__);    \
  } while (0)
    