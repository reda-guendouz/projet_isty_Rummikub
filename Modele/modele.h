#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_CHIFFRE 13
#define MAX_TUILES 106

/**********************
 * Couleur des Tuiles *
 * *******************/

typedef enum{
    NOIR,ORANGE,ROUGE,BLEU
}COULT;

/**********
 * TUILE  *
 * *******/

typedef struct TUILE
{
	COULT clr;
	int chiffre;
}TUILE;

void affiche_tuile(TUILE tuile);

/*********************************
 * Structure des chevalet/pioche *
 * ******************************/

typedef struct CHEVALET
{
    TUILE pile[106];
    int nbTuiles;
}CHEVALET;


/*************************
 * Structure des joueurs *
 * **********************/

typedef struct JOUEUR
{
	int numJoueur;
	int score;
    CHEVALET chevalet;
}JOUEUR;

/******************
 * Plateau de jeu *
 * ***************/

TUILE plateau[8][22];

/**********
 * Pioche *
 * *******/

CHEVALET pioche[106];

void affiche_pioche();

void init_pioche();

void melanger_pioche();

TUILE piocher();