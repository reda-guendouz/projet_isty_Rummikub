#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_CHIFFRE 13
#define JOUEURS_MAX 4
#define MAX_TUILES 106
#define PIOCHE_DEPART 14
#define DIM_PLATEAU_W 22
#define DIM_PLATEAU_H 8
#define MAX_PSEUDONYME 25

#define TRUE 1
#define FALSE 0

#define ROU   "\x1B[31m"
#define ORA   "\x1b[33m"
#define BLE   "\x1B[34m"
#define RESET "\x1B[0m"

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

/*
Cette fonction permet d'afficher une tuile dans un terminal
exemple pour la tuile 5 rouge dans la liste à l'indice X : 
Tuile n°<X> : 5 ROUGE
*/
void affiche_tuile(TUILE tuile, int numTuiles);

/*********************************
 * Structure des chevalet/pioche *
 * ******************************/

typedef struct LISTE_TUILES
{
    TUILE pile[MAX_TUILES];
    int nbTuiles;
}LISTE_TUILES;


/***********
 * Joueurs *
 * ********/

typedef struct JOUEUR
{
	int numJoueur;
	int score;
    char pseudo[MAX_PSEUDONYME];
    LISTE_TUILES chevalet;
}JOUEUR;

typedef struct LISTE_JOUEURS
{
	JOUEUR js[JOUEURS_MAX];
    int nbJs;
}LISTE_JOUEURS;

LISTE_JOUEURS joueurs;

/*
Initialise le tableau global de type JOUEUR avec "nbJoueurs" joueurs
*/
void init_joueurs(int nbJoueurs);


/*
affiche le numero du joueur, son score ainsi que son chevalet
*/
void affiche_joueur(JOUEUR joueur);

/*
affiche l'ensemble des joueurs
ERREUR POTENTIEL (non testé): l'affichage d'un joueur non existant
*/
void affiche_joueurs();

/******************
 * Plateau de jeu *
 * ***************/

TUILE plateau[DIM_PLATEAU_H][DIM_PLATEAU_W];

/*
affiche le plateau sous avec dimensions DIM_PLATEAU_H et DIM_PLATEAU_W
*/
void affiche_plateau();

/**********
 * Pioche *
 * *******/

/*
la pioche est un encemble de tuiles pas un chevalet
(a faire: renommer le nom de la structure chevalet)
*/
LISTE_TUILES pioche;

/*
afficher
*/
void affiche_liste_tuiles();

/*
initialise la pioche puis la melange
*/
void init_pioche();

/*
melange la pioche de facon aleatoire
*/
void melanger_pioche();

/*
tire une carte au hasard dans la pioche et met a jour la pioche
*/
TUILE piocher(int numJoueur);
