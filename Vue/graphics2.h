#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "couleur.h" // Constantes de couleur
#include "../Terminal/modele.h"


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

	/// bah tout est dans le titre ^^
	void affiche_texte(char *texte_affichable, int taille, POINT p, COULEUR C);

	/// ttend que l'on tape Echap et quitte
	// Instruction bloquante
	void wait_escape();

	/// fonction obligatoire :
	// Instruction bloquante
	POINT wait_clic();

	/// Dessine un pixel
	void draw_pixel(POINT p, COULEUR color);

	/// Dessine un segment
	void draw_line(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle non rempli
	void draw_rectangle(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle rempli
	void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color);

	/// charge une image sans l'afficher (besoin d'un affiche_all() pour la voir)
	void load_img(char *fic,POINT emplacement);

	void affiche_menu_debut();

	void converti_int_en_str(int nb, char *p);
	void transforme_tuile_en_path(TUILE t, char *p);
	void affiche_plateau_graphique(TUILE *plateau_a_afficher);

	void affiche_joueur_graphique(int num_joueur);

	void affiche_tuile_graphique(TUILE t,POINT p);

	/*
	* Affiche le premier menu du jeu !
	* dimensions premier rectangle  : 90x320 - 640x450
	* dimensions deuxieme rectangle : 790x420 - 1410x550
	*/
	void affiche_menu_debut();

	void fill_screen(COULEUR clr);

	void affiche_texte_special(char *texte_affichable, int taille, POINT p, COULEUR C, char *ttf_file);

	int dans_zone(POINT clic, POINT p1, POINT p2);

	void inscription(char *pseudoJoueur,int numJoueur);

	void affiche_inscription();

	void choix_case_plateau(POINT clic,int *ligne,int *colonne);
	int choix_joueurs(int nbIA, BOOL demandeIA);
	BOOL selectionne_tuiles_chevalet(int num_joueur, LISTE_TUILES *selectionnees, BOOL *premiereMain) ;
	void choix_case_plateau(POINT clic,int *ligne,int *colonne);
	void affiche_modif_plateau(TUILE *plateau_a_afficher, int joueur);


	void tuile_selectionne(int ligne,int colonne,BOOL selec);

	
	void transition(int joueurSuivant);
	
	void affiche_info_tour(int val);
	void transition_IA(int val);

	void quit();
