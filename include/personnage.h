#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <map.h>

#include <SDL2/SDL.h>

#define PERSONNAGE_VITESSE_X_BASE 10.0

#define TAILLE_PERSONNAGE_HEIGHT 1.8
#define TAILLE_PERSONNAGE_WIDTH 0.9

#define PERSONNAGE_VITESSE_SAUT 10

typedef struct {

    map_colonne_t *colonnePers;
    map_colonne_t *colonneAff;

    double x;

    double y;

    double vitesse;
    double accel;

    SDL_Texture *texture;

    float hitBoxW;
    float hitBoxH;
} personnage_t;

void personnage_init ();
void personnage_collision ();

personnage_t personnage;

#endif