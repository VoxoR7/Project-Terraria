#include <main.h>

#include <map.h>
#include <bloc.h>
#include <affichage.h>
#include <touche.h>
#include <personnage.h>
#include <fps.h>

#include <stdio.h>

int main () {

	#ifdef DEBUG
    	printf("WARNING : DEBUG is enabled, it can cause serious lag. disabled it by going into include/main.h and removing #define DEBUG\n");
	#else
		printf("DEBUG is disabled, enable it by going into include/main.h and add the line #define DEBUG\n");
	#endif

	#ifdef TRACE
    	printf("WARNING : TRACE is enabled, it can cause lag. disabled it by going into include/main.h and removing #define TRACE\n");
	#else
		printf("TARCE is disabled, enable it by going into include/main.h and add the line #define TRACE\n");
	#endif

	#ifdef TRACE
        printf("%s, %s, %d\n", __FILE__, __FUNCTION__, __LINE__);
    #endif

	affichage_init();

	map_gen_phase_1();

	bloc_init();

	touche_init();

	personnage_init();

	affichage_map();

	uint16_t tailleBloc = WIDTH / NB_BLOC_WIDTH;

	fps_init();

	double fpsr = 1;

	while ( !touche_appuyer(QUITTER) && !touche_appuyer(ESCAPE) ) {

		touche_update();

		if ( touche_appuyer(DROITE) ) {

			personnage.x += ( tailleBloc / PERSONNAGE_VITESSE_X_BASE ) * fpsr;

			if ( personnage.x > tailleBloc ) {

				personnage.x -= tailleBloc;

				map->colonne = map->colonne->colonneSuivante;
				map->colonneAffichage = map->colonneAffichage->colonneSuivante;

				personnage.colonnePers = personnage.colonnePers->colonneSuivante;
				personnage.colonneAff = personnage.colonneAff->colonneSuivante;
			}
		}

		if ( touche_appuyer(GAUCHE) ) {

			personnage.x -= ( tailleBloc / PERSONNAGE_VITESSE_X_BASE ) * fpsr;

			if ( personnage.x < 0 ) {

				personnage.x += tailleBloc;

				map->colonne = map->colonne->colonnePrecedente;
				map->colonneAffichage = map->colonneAffichage->colonnePrecedente;

				personnage.colonnePers = personnage.colonnePers->colonnePrecedente;
				personnage.colonneAff = personnage.colonneAff->colonnePrecedente;
			}
		}

		personnage_collision ();

		affichage_map();

		fpsr = fps();
	}

	return 0;
}
