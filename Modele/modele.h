#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_CHIFFRE 13
#define MAX_TUILES 106
#define PIOCHE_DEPART 14

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
    TUILE pile[MAX_TUILES];
    int nbTuiles;
}CHEVALET;


/***********
 * Joueurs *
 * ********/

typedef struct JOUEUR
{
	int numJoueur;
	int score;
    CHEVALET chevalet;
}JOUEUR;

JOUEUR joueurs[4];

void init_joueurs(int nbJoueur);

void affiche_joueur(JOUEUR joueur);

void affiche_joueurs(int nbJoueur);

/******************
 * Plateau de jeu *
 * ***************/

TUILE plateau[8][22];

/**********
 * Pioche *
 * *******/

CHEVALET pioche[MAX_TUILES];

void affiche_pioche();

void init_pioche();

void melanger_pioche();

TUILE piocher(int numJoueur);
