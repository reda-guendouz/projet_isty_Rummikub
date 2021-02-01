#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

#define ROU "\x1B[31m"
#define ORA "\x1b[33m"
#define BLE "\x1B[34m"
#define RESET "\x1B[0m"

/**********************
 * Couleur des Tuiles *
 * *******************/

typedef enum
{
    NOIR,
    ORANGE,
    ROUGE,
    BLEU
} COULT;

/**********
 * TUILE  *
 * *******/

typedef struct TUILE
{
    COULT clr;
    int chiffre;
} TUILE;

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
} LISTE_TUILES;

int ajouter_tuile(LISTE_TUILES *liste, TUILE tuile);

int suite(LISTE_TUILES *l);
void tri_liste(LISTE_TUILES *l);
int triplon_quadruplon(LISTE_TUILES *l);
int test_combinaison(LISTE_TUILES *l);
int intervertion_tuiles(TUILE *copie_plateau, int ligneSource, int colonneSource, int ligneDestination, int colonneDestination);

/***********
 * Joueurs *
 * ********/

typedef struct JOUEUR
{
    int numJoueur;
    char pseudo[MAX_PSEUDONYME];
    LISTE_TUILES chevalet;
} JOUEUR;

typedef struct LISTE_JOUEURS
{
    JOUEUR js[JOUEURS_MAX];
    int scores[JOUEURS_MAX];
    int nbJs;
} LISTE_JOUEURS;

LISTE_JOUEURS joueurs;

/*
Initialise le tableau global de type JOUEUR avec "nbJoueurs" joueurs
*/
void init_joueurs(int nbJoueurs, int nbJoueursH);

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
void affiche_plateau(TUILE *plateau_a_afficher);

int est_placable(int taille_liste, int ligne, int colonne);

void placer_tuiles(LISTE_TUILES selection, TUILE *copie_plateau, int l, int c);

void copie_plateau(TUILE *dest, TUILE *src);

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
void affiche_liste_tuiles(LISTE_TUILES liste_tuiles);

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
void piocher(LISTE_TUILES *l);

void supprime_liste(LISTE_TUILES *l, TUILE tuile);
int est_victorieux(JOUEUR j);
void affiche_victoire(JOUEUR j, int indiceJoueurGagnant);
void score_fin_partie(int indiceJoueurGagnant);

int analyse_plateau(TUILE *plateau);



/*
IA
*/
int action_tour_ia(LISTE_TUILES* chevaleurIa);
void combinationUtil(int arr[], int taille, int r, int index, int data[], int i, LISTE_TUILES chevaletIa, LISTE_TUILES* max);
void trouver_combinaisons(LISTE_TUILES chevaletIa, LISTE_TUILES* combinaisonsTrouve);
void placer_combinaisons(LISTE_TUILES combinaisonTrouve, TUILE* copiePlateau);



/******
 * DIVERS
 * *****/
int char_to_int(char l);
void mettre_a_jour(LISTE_TUILES *chevalet, LISTE_TUILES tuilesSelectionnees);
void copie_liste(LISTE_TUILES *src, LISTE_TUILES *dest);
int readInt( int limMin, int limMax );
void ecrire_score(char * chaine,int score);
void affiche_score();
