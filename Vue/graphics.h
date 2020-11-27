// ############################################
//       UVSQ -- Licence UFR des Sciences
//
// L1S1 IN100 -- Fondements de l'Informatique 1
// L1S2 IN210 -- Fondements de l'Informatique 2
//
// Franck QUESSETTE -- Franck.Quessette@uvsq.fr
// Version de novembre 2009
//
// SOMMAIRE
//
// 1. TYPES, VARIABLES, CONSTANTES ... ligne  39
// 2. AFFICHAGE ...................... ligne  76
// 3. GESTION D'�V�NEMENTS ........... ligne  99
// 4. DESSIN D'OBJETS ................ ligne 135
// 5. �CRITURE DE TEXTE .............. ligne 180
// 6. LECTURE D'ENTIER ............... ligne 210
// 7. GESTION DU TEMPS ............... ligne 219
// 8. VALEUR AL�ATOIRES .............. ligne 241
// 9. DIVERS ......................... ligne 252
// #############################################


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <SDL.h>

// A decommentr si on fonctionne en local, sinon sur un terminal
// on a des lenteurs
// #define EN_LOCAL

// ###############################
// 1. TYPES, VARIABLES, CONSTANTES
// ###############################

// 1.1 TYPES

	// D�finition du type POINT
	typedef struct point {int x,y;} POINT;

	// D�finition du type COULEUR
	typedef Uint32 COULEUR;

	// Les bool�ens
	typedef int BOOL;

// 1.2 VARIABLES
	// Taille de l'affichage
	int WIDTH;
	int HEIGHT;

// 1.3 CONSTANTES

	// D�placement minimal lorsque l'on utilise les fl�ches.
	#define MINDEP 1

	// Constantes de couleur
	#include "couleur.h"

	// Constantes bool�ennes
	#define TRUE 1
	#define True 1
	#define true 1
	#define FALSE 0
	#define False 0
	#define false 0


// ############
// 2. AFFICHAGE
// ############

	// 2.1 Initialisation de la fen�tre sur laquelle on dessine
	void init_graphics();

	// 2.2 Affichage automatique ou manuel
	// Si l'affichage est automatique, chaque objet dessin�
	// est automatiquement affich�.
	// Sinon, il faut explicitement appeler la fonction
	// affiche_all() pour afficher les objets
	// synchro() est identique � affiche_all()
	void affiche_auto_on();
	void affiche_auto_off();
	void affiche_all();
	void synchro();

	// 2.3 Cr�ation de couleur
	// r g et b dans l'intervalle 0 .. 255
	COULEUR couleur_RGB(int r, int g, int b);

void souris_visible();
void souris_invisible();

// #######################
// 3. GESTION D'�V�NEMENTS
// #######################

	// 3.1 Renvoie le ou les fl�ches appuy�es
	// sous forme d'un d�placement en
	// x n�gatif = nombre d'appuis sur la fl�che gauche
	// x positif = nombre d'appuis sur la fl�che droite
	// y n�gatif = nombre d'appuis sur la fl�che bas
	// y positif = nombre d'appuis sur la fl�che haut
	// Instruction non bloquante, si aucune fl�che n'a �t�
	// appuy�e les champs x et y vaudront 0.
	POINT get_arrow();

	// 3.2 Renvoie d�placement de souris
	// Meme s�mantique que get_arrow()
	// Instruction non bloquante, si la souris n'a pas boug�,
	// les champs x et y vaudront 0.
	POINT get_mouse();

	// 3.3 Attend que l'on tape Echap et quitte
	// Instruction bloquante
	void wait_escape();

	// 3.4 Attend que l'utilisateur clique avec le bouton gauche
	// Renvoie les coordonn�es du point cliqu�
	// Instruction bloquante
	POINT wait_clic();

	// 3.5 Attend que l'on clique et renvoie dans button le bouton cliqu� :
	// *button vaut soit 'G' (pour Gauche), soit 'M' (pour milieu),
	// soit 'D' (pour Droit) en fonction du bouton cliqu�
	// Instruction bloquante
	POINT wait_clic_GMD(char *button);


// ##################
// 4. DESSIN D'OBJETS
// ##################

	// 4.1 Remplissage de tout l'�cran
	void fill_screen(COULEUR color);

	// 4.2 Dessine un pixel
	void draw_pixel(POINT p, COULEUR color);

	// 4.3 Dessine un segment
	void draw_line(POINT p1, POINT p2, COULEUR color);

	// 4.4 Dessine un rectangle non rempli
	// Les deux points sont deux points quelconques
	// non adjacents du rectangle
	void draw_rectangle(POINT p1, POINT p2, COULEUR color);

	// 4.5 Dessine un rectangle rempli
	// Les deux point sont deux points quelconques
	// non adjacents du rectangle
	void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color);

	// 4.6 Dessine un cercle non rempli
	void draw_circle(POINT centre, int rayon, COULEUR color);

	// 4.7 Dessine un cercle rempli
	void draw_fill_circle(POINT centre, int rayon, COULEUR color);

	// 4.8 Dessine des quarts de cercle
	void draw_circle_HD(POINT centre, int rayon, COULEUR color);
	void draw_circle_BD(POINT centre, int rayon, COULEUR color);
	void draw_circle_HG(POINT centre, int rayon, COULEUR color);
	void draw_circle_BG(POINT centre, int rayon, COULEUR color);

	// 4.9 Dessine une ellipse remplie
	void draw_fill_ellipse(POINT F1, POINT F2, int r, COULEUR color);

	// 4.10 Dessine un triangle
	void draw_triangle(POINT p1, POINT p2, POINT p3, COULEUR color);

	// 4.11 Dessine un triangle rempli
	void draw_fill_triangle(POINT p1, POINT p2, POINT p3, COULEUR color);


// ####################
// 5. �CRITURE DE TEXTE
// ####################

// L'affichage se fait dans la fen�tre graphique si SDL_ttf est install�.
// Sinon il se fait dans dans la fen�tre shell

	// 5.1 Affiche du texte avec
	// Le texte est pass� dans l'argument "a_ecrire"
	// la police est celle d�finie par la constante POLICE_NAME
	//           dans graphics.c
	// la taille est pass�e en argument
	// l'argument p de type POINT est le point en haut � gauche
	// � partir duquel le texte s'affiche
	// la COULEUR C pass�e en argument est la couleur d'affichage
	void aff_pol(char *a_ecrire, int taille, POINT p, COULEUR C);

	// 5.2 Affiche un entier
	// Meme s�mantique que aff_pol()
	void aff_int(int n, int taille, POINT p, COULEUR C);

	// 5.3 Affiche dans la fen�tre graphique comme dans une fen�tre
	// shell mais sans d�roulement. Commence en haut et
	// se termine en bas.
	void write_text(char *a_ecrire);
	void write_int(int n);
	void write_bool(BOOL b);
	void writeln() ;


// ###################
// 6. LECTURE D'ENTIER
// ###################

	// 6.1 Renvoie l'entier tap� au clavier.
	// Cette fonction est bloquante
	int lire_entier_clavier();


// ###################
// 7. GESTION DU TEMPS
// ###################

	// 7.1 Chronom�tre �l�mentaire
	// D�clenchement du chrono
	// Le remet � z�ro s'il �tait d�j� lanc�
	void chrono_start();
	// Renvoie la valeur du chrono et ne l'arr�te pas
	float chrono_val();

	// 7.2 Attend le nombre de millisecondes pass� en argument
	void attendre(int millisecondes);

	// 7.3.1 Renvoie l'heure de l'heure courante
	int heure();
	// 7.3.2 Renvoie le nombre de minutes de l'heure courante
	int minute();
	// 7.3.3 Renvoie le nombre de secondes de l'heure courante
	int seconde();


// ####################
// 8. VALEUR AL�ATOIRES
// ####################

	// 8.1 Renvoie un float dans l'intervalle [0;1[
	float alea_float();
	// 8.2 Renvoie un int dans l'intervalle [0..N[
	// soit N valeurs diff�rentes de 0 � N-1
	int alea_int(int N);


// #########
// 9. DIVERS
// #########

	// 9.1 Renvoie la distance entre deux points
	int distance(POINT P1, POINT P2);
