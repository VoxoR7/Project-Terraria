#include <main.h>
#include <SDL2/SDL.h>

#include <fps.h>

#include <time.h>

double tempsImage;

void fps_init () {
    /* la premiere fois, fps retourne une valeur aleatoire. permet d eviter cela*/

    fps();

    tempsImage = ( 1.0 / FPS ) * 1000.0;
}

double fps () {
    /*  doit être appeler en fin de boucle lorsque le controle du temps doit etre effectuer.
        retourne une valeur double en fonction des fps effectifs de l utilisateur. ( moins il a de fps, plus cette valeur sera elever et vice versa ) --> ex pour 25 fps cette fonction renveras 2 puisque les fps de base sont 50*/

    static uint32_t debutImage = 0;
    uint32_t temp;

    struct timespec tdelay;

    tdelay.tv_sec = 0;
    
    if (  SDL_GetTicks() - debutImage < tempsImage ) {

        tdelay.tv_nsec = ( tempsImage - ( SDL_GetTicks() - debutImage ) ) - 1 ;

        //nanosleep(&tdelay, NULL); // attention : doit etre mis en nanosecondes
        SDL_Delay(tdelay.tv_nsec);
    }

    while ( SDL_GetTicks() - debutImage < tempsImage );

    temp = debutImage;
    debutImage = SDL_GetTicks();

    return FPS_BASE / ( ( 1.0 / ( SDL_GetTicks() - temp ) ) * 1000 );
}