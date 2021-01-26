#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "couleur.h" // Constantes de couleur

	//  type POINT
	typedef struct point {int x,y;} POINT;

	//  type COULEUR
	typedef Uint32 COULEUR;

	// type booleen
	typedef int BOOL;

	// Taille de la fenetre principal
	int WIDTH;
	int HEIGHT;


	// Constantes booleennes
	#define TRUE 1
	#define True 1
	#define true 1
	#define FALSE 0
	#define False 0
	#define false 0

	/// Initialisation de la fenetre principal
	void init_graphics();

//// Jsais pas quoi en faire l'instant
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
//// Fin de "Jsais pas quoi en faire l'instant"

	/// Creation de couleur (0 .. 255)
	COULEUR couleur_RGB(int r, int g, int b);

	/// ttend que l'on tape Echap et quitte
	// Instruction bloquante
	void wait_escape();

	/// fonction obligatoire :
	// Instruction bloquante
	POINT wait_clic();

	/// J'aime bien ça, c'est interessant pour avoir des points bonus :
	POINT wait_clic_GMD(char *button);

	/// Dessine un pixel
	void draw_pixel(POINT p, COULEUR color);

	/// Dessine un segment
	void draw_line(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle non rempli
	void draw_rectangle(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle rempli
	void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color);