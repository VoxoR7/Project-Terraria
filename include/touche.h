#ifndef __TOUCHE_H__
#define __TOUCHE_H__

#define TOUCHE_NB 6

#define QUITTER 0
#define ESCAPE 1

#define DROITE 2
#define GAUCHE 3
#define MONTER 4
#define DESCENDRE 5

#define TOUCHE_NULL 4294967295

#define RELEASED 0
#define PRESSED 1

#define TOUCHE_DESCR_MAX 20

typedef struct {

	uint32_t keyCode;
	char *descriptif;
} configTouche_t;

void touche_init ();
void touche_quit ();

void touche_update ();
uint8_t touche_appuyer ( const uint16_t touche );

#endif