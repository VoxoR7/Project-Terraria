#include <main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <personnage.h>
#include <affichage.h>
#include <bloc.h>

void personnage_init () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    personnage.colonnePers = map->colonne;
    personnage.colonneAff = map->colonneAffichage;

    uint16_t i;

    for ( i = 0 ; i < NB_BLOC_WIDTH / 2 ; i++ )
        personnage.colonneAff = personnage.colonneAff->colonnePrecedente;

    i = 0;

    while ( *((personnage.colonnePers)->bloc + i) != B_AIR )
        i++;

    personnage.y = i;
    personnage.x = 0;

    personnage.hitBoxW = 0.8 * ( WIDTH / NB_BLOC_WIDTH);
    personnage.hitBoxH = 1.8 * ( HEIGHT / NB_BLOC_HEIGHT);

    printf("W/NB_W H : %d\t\t%d\n", WIDTH / NB_BLOC_WIDTH, HEIGHT / NB_BLOC_HEIGHT);
    printf("HB[W][H] : %f\t\t%f\n", personnage.hitBoxW, personnage.hitBoxH);

    SDL_Surface *surface;

    surface = IMG_Load("data/texturePack/base/personnage.png");
    if ( surface == NULL ) {
        printf("chargement de l'image impossible\n");
        personnage.texture = NULL;
    } else {
        personnage.texture = NULL;
        personnage.texture = SDL_CreateTextureFromSurface( renderer, surface );
        if ( personnage.texture == NULL )
            printf("Chargement de la texture impossible\n");
        SDL_FreeSurface( surface );
    }

}

void personnage_collision () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    map_colonne_t *colonneHitBoxRight, *colonneHitBoxLeft;

    double hitBoxLeft = ( NB_BLOC_WIDTH - personnage.hitBoxW ) / 2; /* possiblement a refaire */

    if ( personnage.x + personnage.hitBoxW > WIDTH / NB_BLOC_WIDTH )
        colonneHitBoxRight = personnage.colonnePers->colonneSuivante;
    else
        colonneHitBoxRight = personnage.colonnePers;

    if (  *(personnage.colonnePers->bloc + (int)personnage.y - 1) == B_AIR && *(colonneHitBoxRight->bloc + (int)personnage.y - 1) == B_AIR )
        personnage.y --;

    if ( *(personnage.colonnePers->bloc + (int)personnage.y ) != B_AIR )
        personnage.y ++;
}