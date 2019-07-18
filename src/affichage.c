#include <main.h>
#include <SDL2/SDL.h>

#include <map.h>
#include <personnage.h>

#include <affichage.h>

SDL_Rect rectbloc, rectblocPers;

void affichage_init () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    atexit( affichage_quit );

    SDL_Init( SDL_INIT_AUDIO /*|| SDL_INIT_TIMER*/ );

    window = SDL_CreateWindow( "Project Terraria", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    affichage_ajust();
}

void affichage_ajust () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    rectbloc.w = WIDTH / NB_BLOC_WIDTH;
    rectbloc.h = HEIGHT / NB_BLOC_HEIGHT;

    rectblocPers.w = rectbloc.w;
    rectblocPers.h = rectbloc.h * 2;
    rectblocPers.x = WIDTH / 2 - rectblocPers.w / 2;
    rectblocPers.y = HEIGHT / 2 - rectblocPers.h / 2;
}

void affichage_map () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    map_colonne_t *colonneAff = map->colonneAffichage;

    rectbloc.x = -(rectbloc.w / 2) - (int)personnage.x;
    rectbloc.y = HEIGHT - rectbloc.h;

    for ( uint16_t i = 0 ; i < NB_BLOC_WIDTH + 2 ; i++ ) {
        for ( uint16_t j = 0 ; j < NB_BLOC_HEIGHT ; j++ ) {

            SDL_RenderCopy( renderer, (bloc +  *( colonneAff->bloc + j + (int)personnage.y - NB_BLOC_HEIGHT / 2 + 1 ))->blocTexture, NULL, &rectbloc);

            rectbloc.y -= rectbloc.h;
        }
        colonneAff = colonneAff->colonneSuivante;
        rectbloc.y = HEIGHT - rectbloc.h;
        rectbloc.x += rectbloc.w;
    }

    SDL_Rect rtest;
    rtest.x = WIDTH / 2;
    rtest.y = HEIGHT / 2;
    rtest.w = 10;
    rtest.h = 10;

    ;

    SDL_RenderCopy( renderer, personnage.texture, NULL, &rectblocPers);

    SDL_RenderCopy( renderer, (bloc + B_ROCHE)->blocTexture, NULL, &rtest);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void affichage_quit () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    SDL_DestroyRenderer( renderer );

    SDL_DestroyWindow( window );

    SDL_Quit();
}