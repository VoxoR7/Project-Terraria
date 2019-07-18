#include <main.h>
#include <SDL2/SDL.h>

#include <touche.h>

#include <string.h>

uint8_t *keyBoardState;
configTouche_t *configTouche;

void touche_init () {

    keyBoardState = malloc( sizeof(uint8_t) * TOUCHE_NB );
    configTouche = malloc( sizeof(configTouche_t) * TOUCHE_NB );

    for ( uint16_t i = 0 ; i < TOUCHE_NB ; i++ ) {

        (configTouche + i)->descriptif = malloc( sizeof(char) * TOUCHE_DESCR_MAX );
        *(keyBoardState + i) = RELEASED;
    }

    #include "includeData/toucheData.h"

    atexit(touche_quit);
}

void touche_update () {

    SDL_Event event;

    uint16_t i;

    while ( SDL_PollEvent(&event) ) {

        i = 0;

        switch( event.type ) {

            case SDL_QUIT:

                *( keyBoardState + QUITTER ) = PRESSED;
                break;

            case SDL_KEYDOWN:

                while ( event.key.keysym.sym != ( configTouche + i)->keyCode && i < TOUCHE_NB )
					i++;

				*( keyBoardState + i ) = PRESSED;
				break;

            case SDL_KEYUP:

                while ( event.key.keysym.sym != ( configTouche + i)->keyCode && i < TOUCHE_NB )
					i++;

				*( keyBoardState + i ) = RELEASED;
				break;
        }
    }
}

uint8_t touche_appuyer ( const uint16_t touche ) {

    return ( *( keyBoardState + touche) == PRESSED );
}

void touche_quit () {

    for ( uint16_t i = 0 ; i < TOUCHE_NB ; i++ )
        free( (configTouche + i)->descriptif );

    free( keyBoardState );
    free( configTouche );
}