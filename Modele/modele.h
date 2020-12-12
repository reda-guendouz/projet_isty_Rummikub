#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_CHIFFRE 13
#define MAX_TUILES 106
#define PIOCHE_DEPART 14
#define DIM_PLATEAU_W 22
#define DIM_PLATEAU_H 8

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

void affiche_tuile(TUILE tuile, int numTuiles);

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

void affiche_joueurs();

/******************
 * Plateau de jeu *
 * ***************/

TUILE plateau[DIM_PLATEAU_H][DIM_PLATEAU_W];

void affiche_plateau();

/**********
 * Pioche *
 * *******/

CHEVALET pioche[MAX_TUILES];

void affiche_pioche();

void init_pioche();

void melanger_pioche();

TUILE piocher(int numJoueur);
