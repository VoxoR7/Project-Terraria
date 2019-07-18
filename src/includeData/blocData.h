SDL_Surface *surface = NULL;

strcpy( (bloc + B_AIR)->blocName, "Air" );
(bloc + B_AIR)->blocTexture = NULL;

strcpy( (bloc + B_ROCHE)->blocName, "Roche" );
surface = IMG_Load("data/texturePack/base/Roche.png");
if ( surface == NULL ) {
    printf("chargement de l'image impossible\n");
    (bloc + B_ROCHE)->blocTexture = NULL;
} else {
    (bloc + B_ROCHE)->blocTexture = NULL;
    (bloc + B_ROCHE)->blocTexture = SDL_CreateTextureFromSurface( renderer, surface );
    if ( (bloc + B_ROCHE)->blocTexture == NULL )
        printf("Chargement de la texture impossible\n");
    SDL_FreeSurface( surface );
}
