#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

/*
Cette fonction permet d'ajouter une tuile dans une liste
*/
int ajouter_tuile(LISTE_TUILES *liste, TUILE tuile);

/*!
 * @param       tuile    la tuile @struct{TUILE} a verifier
 * @param       liste    la @struct{LISTE_TUILES} a verifier
 * @result      TRUE si @param{tuile} est dans @param{liste} FALSE sinon
*/
int tuile_dans_liste(LISTE_TUILES liste, TUILE tuile);

/*
Verifie si une combinaison de tuile est une suite potentiellement placable sur le plateau
*/
int suite(LISTE_TUILES *l);

/*
Tri une liste par rapport au nombre inscrit sur les tuiles
*/
void tri_liste(LISTE_TUILES *l);

/*
Verifie si une combinaison de tuile est composé de trois ou quatres tuiles du même chiffre mais de couleur différente
Renvoie VRAI si la combinaison est un triplon ou un quadruplon, FALSE sinon
*/
int triplon_quadruplon(LISTE_TUILES *l);

/*
Test si une combinaisons est une suite, un triplon ou un quadruplon
*/
int test_combinaison(LISTE_TUILES *l);

/*
Supprime une selection de tuiles, d'un chevalet d'un joueur
*/
void mettre_a_jour(LISTE_TUILES *chevalet, LISTE_TUILES tuilesSelectionnees);

/*
Copie une liste src dans une liste dest
*/
void copie_liste(LISTE_TUILES *src, LISTE_TUILES *dest);

/*
Supprime une tuile d'une liste
*/
void supprime_liste(LISTE_TUILES *l, TUILE tuile);

/*
Affiche une liste TUILE
*/
void affiche_liste_tuiles(LISTE_TUILES liste_tuiles);

/*
Renvoie la somme des tuiles d'une liste de tuile.
*/
int calcul_main(LISTE_TUILES liste_tuiles);

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

/*
Verifie si un joueur rempli une condition de victoire
Renvoie TRUE si le joueur a gagné, FALSE sinon
*/
int est_victorieux(JOUEUR j);

/******************
 * Plateau de jeu *
 * ***************/

TUILE plateau[DIM_PLATEAU_H][DIM_PLATEAU_W];

/*
Affiche le plateau sous avec dimensions DIM_PLATEAU_H et DIM_PLATEAU_W
*/
void affiche_plateau(TUILE *plateau_a_afficher);

/*
Regarde si une liste est placable à des coordonnées dans un plateau
*/
int est_placable(int taille_liste, int ligne, int colonne);

/*
Place des tuiles sur une copie du plateau
*/
void placer_tuiles(LISTE_TUILES selection, TUILE *copie_plateau, int l, int c);

/*
Crée une copie du plateau
*/
void copie_plateau(TUILE *dest, TUILE *src);

/*
Regarde si les tuiles sur le plateau sont correctement placé et forme bien des combinaisons
Renvoie TRUE si le plateau est bon, FALSE sinon
*/
int analyse_plateau(TUILE *plateau);

/*
Change de place deux tuiles du plateaux.
Renvoie TRUE si le changement est posible, FALSE sinon.
*/
int intervertion_tuiles(TUILE *copie_plateau, int ligneSource, int colonneSource, int ligneDestination, int colonneDestination);

/**********
 * Pioche *
 * *******/

/*
la pioche est un encemble de tuiles pas un chevalet
(a faire: renommer le nom de la structure chevalet)
*/
LISTE_TUILES pioche;

/*
Initialise la pioche puis la melange
*/
void init_pioche();

/*
Melange la pioche de facon aleatoire
*/
void melanger_pioche();

/*
Tire une carte au hasard de la pioche, met a jour la pioche et ajoute la tuile à une liste de tuile (chevalet)
*/
void piocher(LISTE_TUILES *l);


/******
*  IA *
* ****/
int action_tour_ia(LISTE_TUILES* chevaleurIa);
void combinationUtil(int arr[], int taille, int r, int index, int data[], int i, LISTE_TUILES chevaletIa, LISTE_TUILES* max);
void trouver_combinaisons(LISTE_TUILES chevaletIa, LISTE_TUILES* combinaisonsTrouve);
int placer_combinaisons(LISTE_TUILES combinaisonTrouve, TUILE* copiePlateau);



/******
 * DIVERS
 * *****/
int char_to_int(char l);
int readInt( int limMin, int limMax );
void ecrire_score(char * chaine,int score);
void affiche_score();
void affiche_victoire(JOUEUR j, int indiceJoueurGagnant);
void score_fin_partie(int indiceJoueurGagnant);
