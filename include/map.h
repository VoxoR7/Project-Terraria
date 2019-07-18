#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>

#include <bloc.h>

#define GENERATION_SIZE 64

/*  ---------------------------------------------------------------------------------------------
    |                                                                                           |
    |                                   GENERATION PHASE 1                                      |
    |                                                                                           |
    ---------------------------------------------------------------------------------------------   */

/*
*   Courbe de la carte
*/

#define GENERATION_1_HAUTEUR_STANDART 300 /* Hauteur standart en nombre de bloc */
#define GENERATION_1_HAUTEUR_VARIATION_STANDART 20 /* Les hauteurs min et max seront determinee selon GENERATION_HAUTEUR_STANDART +- GENERATION_HAUTEUR_VARIATION_STANDART */

#define GENERATION_1_MONTEE_DESCENTE_STANDART 6 /* Apres combien de blocs en moyenne la pente s'inversera */
#define GENERATION_1_VARIATION_MONTEE_DESCENTE_STANDART 3 /* les variations min et max seront determinee selon GENERATION_MONTEE_DESCENTE_STANDART +- GENERATION_VARIATION_MONTEE_DESCENTE_STANDART */

#define GENERATION_1_DIFFERENCE_HAUTEUR_STANDART 1 /* difference max de hauteur entre deux colonnes */
/* non implemente */ #define GENERATION_1_DIFFERENCE_HAUTEUR_VARIATION_STANDART 0 /* les variations min et max seront determinee selon GENERATION_1_DIFFERENCE_HAUTEUR_STANDART +- GENERATION_1_DIFFERENCE_HAUTEUR_VARIATION_STANDART */

typedef struct map_colonne_s{

    uint64_t colonneID;

    blocEnum_t *bloc;

    struct map_colonne_s *colonneSuivante;
    struct map_colonne_s *colonnePrecedente;
} map_colonne_t;

typedef struct {

    uint8_t genmdD, genmdG;
    uint8_t genD, genG;
    map_colonne_t *colonne;
    map_colonne_t *colonneAffichage;
} map_t;

void map_gen_phase_1 ();
void map_quit();

map_t *map;

#endif