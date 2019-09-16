#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <SDL2/SDL.h>

#define WIDTH 1664
#define HEIGHT 936

#define NB_BLOC_WIDTH 32
#define NB_BLOC_HEIGHT 18

void affichage_init ();
void affichage_quit ();

void affichage_ajust ();
void affichage_map ();

SDL_Window *window;
SDL_Renderer *renderer;

#endif