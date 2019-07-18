#ifndef __BLOC_H__
#define __BLOC_H__

#include <SDL2/SDL.h>

#define BLOC_NB 2

#define BLOC_DESCR_MAX 30

typedef enum {
    B_AIR = 0,
    B_ROCHE
} blocEnum_t;

typedef struct {

    SDL_Texture *blocTexture;
    char *blocName;

    uint16_t durete;
} bloc_t;

void bloc_init ();
void bloc_quit ();

bloc_t *bloc;

#endif