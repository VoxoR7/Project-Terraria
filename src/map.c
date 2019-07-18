#include <main.h>

#include <map.h>
#include <affichage.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef DEBUG
    #include <stdio.h>
    #include <inttypes.h>
#endif

void map_gen_phase_1 () {

    /* Creation du premier chunk */

    atexit( map_quit );

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    map = malloc(sizeof(map_t));

    map->colonne = malloc(sizeof(map_colonne_t));

    map->colonne->colonneID = pow(2, 63);
    map->colonne->colonnePrecedente = NULL;
    map->colonne->colonneSuivante = NULL;

    map->colonne->bloc = malloc( sizeof(blocEnum_t) * HAUTEUR_MAX );

    srand(time(NULL));

    uint16_t genCol1Hauteur = ( rand() % (GENERATION_1_HAUTEUR_VARIATION_STANDART * 2) - GENERATION_1_HAUTEUR_VARIATION_STANDART ) + GENERATION_1_HAUTEUR_STANDART;

    #ifdef DEBUG1
        printf("[spawn] Hauteur gen [ID] [hauteur]: %"PRIu64"\t\t%"PRIu16"\n", map->colonne->colonneID,genCol1Hauteur);
    #endif

    for ( uint16_t i = 0 ; i < genCol1Hauteur ; i++ )
        *(map->colonne->bloc + i) = B_ROCHE;

    for ( uint16_t i = genCol1Hauteur ; i < HAUTEUR_MAX ; i++ )
        *(map->colonne->bloc + i) = B_AIR;

    uint16_t genColD = genCol1Hauteur, genColG = genCol1Hauteur;
    map_t *mapD = malloc(sizeof(map_t)), *mapG = malloc(sizeof(map_t)), *mapDp = malloc(sizeof(map_t)), *mapGp = malloc(sizeof(map_t));
    mapDp->colonne = map->colonne;
    mapGp->colonne = map->colonne;
    uint8_t monteeD, monteeG /* montee = 1, descente = 0 */, nbD = 0, nbG = 0, nbmdD, nbmdG;

    if ( rand() % 2 ) {

        monteeD = 1;
        monteeG = 0;
    } else {

        monteeD = 0;
        monteeG = 1;
    }

    nbmdD = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;
    nbmdG = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;

    /* Generation du chunk droit */
 
    for ( uint16_t i = 0 ; i < GENERATION_SIZE ; i++ ) {

        mapD->colonne = malloc(sizeof(map_colonne_t)); /* /!\ FREE /!\ */
        mapD->colonne->bloc = malloc(sizeof(blocEnum_t) * HAUTEUR_MAX ); /* /!\ FREE /!\ */
        mapD->colonne->colonneSuivante = NULL;
        mapDp->colonne->colonneSuivante = mapD->colonne;
        mapD->colonne->colonnePrecedente = mapDp->colonne;
        mapD->colonne->colonneID = (mapDp->colonne->colonneID) + 1;

        mapDp->colonne = mapD->colonne;

        /* Generation de la hauteur de la colonne suivante */

        if ( genColD > GENERATION_1_HAUTEUR_STANDART + GENERATION_1_HAUTEUR_VARIATION_STANDART ) {

            genColD -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
            monteeD = 0;
            nbD = 0;
            nbmdD = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;
        } else if ( genColD < GENERATION_1_HAUTEUR_STANDART - GENERATION_1_HAUTEUR_VARIATION_STANDART ) {

            genColD += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
            monteeD = 1;
            nbD = 0;
            nbmdD = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;
        } else {
            
            if ( nbD < nbmdD ) {

                if ( monteeD )
                    genColD += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                else
                    genColD -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                nbD++;
            } else {

                if ( monteeD )
                    monteeD = 0;
                else
                    monteeD = 1;

                nbmdD = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;

                if ( monteeD )
                    genColD += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                else
                    genColD -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                nbD = 1;
            }
        }

        /* remplissage de la colonne selon la hauteur determinee precedament */

        for ( uint16_t i = 0 ; i < genColD ; i++ )
            *(mapD->colonne->bloc + i) = B_ROCHE;

        for ( uint16_t i = genColD ; i < HAUTEUR_MAX ; i++ )
            *(mapD->colonne->bloc + i) = B_AIR;

        #ifdef DEBUG1
            printf("Hauteur gen [ID] [hauteur]: %"PRIu64"\t\t%"PRIu16"\n", mapD->colonne->colonneID,genColD);
        #endif
    }

    /* Generation du chunk gauche */
 
    for ( uint16_t i = 0 ; i < GENERATION_SIZE ; i++ ) {

        mapG->colonne = malloc(sizeof(map_colonne_t)); /* /!\ FREE /!\ */
        mapG->colonne->bloc = malloc(sizeof(blocEnum_t) * HAUTEUR_MAX ); /* /!\ FREE /!\ */
        mapG->colonne->colonnePrecedente = NULL;
        mapGp->colonne->colonnePrecedente = mapG->colonne;
        mapG->colonne->colonneSuivante = mapGp->colonne;
        mapG->colonne->colonneID = (mapGp->colonne->colonneID) - 1;

        mapGp->colonne = mapG->colonne;

        /* Generation de la hauteur de la colonne suivante */

        if ( genColG > GENERATION_1_HAUTEUR_STANDART + GENERATION_1_HAUTEUR_VARIATION_STANDART ) {

            genColG -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
            monteeG = 0;
            nbG = 0;
            nbmdG = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;
        } else if ( genColG < GENERATION_1_HAUTEUR_STANDART - GENERATION_1_HAUTEUR_VARIATION_STANDART ) {

            genColG += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
            monteeG = 1;
            nbG = 0;
            nbmdG = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;
        } else {
            
            if ( nbG < nbmdG ) {

                if ( monteeG )
                    genColG += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                else
                    genColG -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                nbG++;
            } else {

                if ( monteeG )
                    monteeG = 0;
                else
                    monteeG = 1;

                nbmdG = ( rand() % (( GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART * 2 ) + 1 )) + GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART;

                if ( monteeG )
                    genColG += GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                else
                    genColG -= GENERATION_1_DIFFERENCE_HAUTEUR_STANDART;
                nbG = 1;
            }
        }

        /* remplissage de la colonne selon la hauteur determinee precedament */

        for ( uint16_t i = 0 ; i < genColG ; i++ )
            *(mapG->colonne->bloc + i) = B_ROCHE;

        for ( uint16_t i = genColG ; i < HAUTEUR_MAX ; i++ )
            *(mapG->colonne->bloc + i) = B_AIR;

        #ifdef DEBUG1
            printf("Hauteur gen [ID] [hauteur]: %"PRIu64"\t\t%"PRIu16"\n", mapG->colonne->colonneID,genColG);
        #endif
    }

    free(mapD);
    free(mapG);
    free(mapDp);
    free(mapGp);

    map->colonneAffichage = map->colonne;

    for ( uint16_t i = 0 ; i < NB_BLOC_WIDTH / 2 ; i++ )
        map->colonneAffichage = map->colonneAffichage->colonnePrecedente;
}

void map_quit () {

    #ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

    map_t *delD = malloc(sizeof(map_t)), *delG = malloc(sizeof(map_t)), *temp = malloc(sizeof(map_t));
    delD->colonne = map->colonne->colonneSuivante;
    delG->colonne = map->colonne->colonnePrecedente;

    while ( delD->colonne->colonneSuivante != NULL ) {

        free( delD->colonne->bloc );
        temp->colonne = delD->colonne;
        delD->colonne = delD->colonne->colonneSuivante;
        free( temp->colonne );
    }

    free( delD->colonne->bloc );
    free( delD->colonne );

    while ( delG->colonne->colonnePrecedente != NULL ) {

        free( delG->colonne->bloc );
        temp->colonne = delG->colonne;
        delG->colonne = delG->colonne->colonnePrecedente;
        free( temp->colonne );
    }

    free( delG->colonne->bloc );
    free( delG->colonne );

    free( delD );
    free( delG );
    free( temp );

    free( map->colonne->bloc );
    free( map->colonne );
    free( map );
}