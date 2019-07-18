#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <map.h>

#include <SDL2/SDL.h>

#define PERSONNAGE_VITESSE_X_BASE 10.0

typedef struct {

    map_colonne_t *colonnePers;
    map_colonne_t *colonneAff;

    double x;

    double y;

    SDL_Texture *texture;

    float hitBoxW;
    float hitBoxH;
} personnage_t;

void personnage_init ();
void personnage_collision ();

personnage_t personnage;

#endif