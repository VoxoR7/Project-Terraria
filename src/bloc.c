#include <main.h>
#include <SDL2/SDL_image.h>

#include <affichage.h>
#include <bloc.h>

#include <stdlib.h>

#ifdef DEBUG
    #include <stdio.h>
    #include <string.h>
#endif

static void bloc_data () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    #include "includeData/blocData.h"
}

void bloc_init () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    bloc = malloc( sizeof(bloc_t) * BLOC_NB );

    for ( uint32_t i = 0 ; i < BLOC_NB ; i++ )
        (bloc + i)->blocName = malloc( sizeof(char) * BLOC_DESCR_MAX );

    bloc_data();

    atexit( bloc_quit );
}

void bloc_quit () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    for ( uint32_t i = 0 ; i < BLOC_NB ; i++ ) {

        if ( (bloc + i)->blocTexture != NULL )
            SDL_DestroyTexture((bloc + i)->blocTexture);

        free( (bloc + i)->blocName );
    }

    free( bloc );
}