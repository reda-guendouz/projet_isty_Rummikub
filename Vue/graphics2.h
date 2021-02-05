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

	/// affiche le texte 
	void affiche_texte(char *texte_affichable, int taille, POINT p, COULEUR C);

	
	/// Instruction bloquante : attend que l'on tape Echap et quitte
	void wait_escape();

	/// Instruction bloquante : attend que l'on clique
	POINT wait_clic();

	/// Dessine un pixel
	void draw_pixel(POINT p, COULEUR color);

	/// Dessine un segment
	void draw_line(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle non rempli
	void draw_rectangle(POINT p1, POINT p2, COULEUR color);

	/// Dessine un rectangle rempli
	void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color);

	/// Dessin tout l'ecran d'une couleur
	void fill_screen(COULEUR clr);

	/// charge une image sans l'afficher (besoin d'un affiche_all() pour la voir)
	void load_img(char *fic,POINT emplacement);

	/// Affiche le menu d'accueil
	void affiche_menu_debut();

	/// Affiche le plateau de jeu
	void affiche_plateau_graphique(TUILE *plateau_a_afficher);
	void affiche_plateau_graphique_slow(TUILE *plateau_a_afficher);

	/// Affiche le chevalet d'un joueur
	void affiche_joueur_graphique(int num_joueur);

	/// Affiche une tuile
	void affiche_tuile_graphique(TUILE t,POINT p);

	/// Affiche le tableau des scores
	void affiche_score_graphique(POINT p);

	/// Affiche le texte avec la police voulu
	void affiche_texte_special(char *texte_affichable, int taille, POINT p, COULEUR C, char *ttf_file);

	/// Renvoie vrai si le point est dans le rectangle forme par les deux autres points,renvoie faux sinon
	int dans_zone(POINT clic, POINT p1, POINT p2);

	/// Affiche le menu de saisi de pseudo
	void inscription(char *pseudoJoueur,int numJoueur);
	void affiche_inscription();

	/// transforme un clic en coordonnee d'un plateau
	void choix_case_plateau(POINT clic,int *ligne,int *colonne);

	/// Affiche le menu de choix des joueurs / IA
	int choix_joueurs(int nbIA, BOOL demandeIA);

	/// Selectionne une liste de tuile dans le chevalet
	BOOL selectionne_tuiles_chevalet(int num_joueur, LISTE_TUILES *selectionnees, BOOL *premiereMain) ;
	
	/// Affiche la selection ou non d'une tuile selon son positionnement dans le plateau
	void tuile_selectionne(int ligne,int colonne,BOOL selec);

	// Affiche la victoire d'un joueur
	void affiche_victoire_graphique(int indiceJoueurGagnant);
	
	// Affiche une transition entre deux joueurs
	void transition(int joueurSuivant);
	
	// Affiche ce que le joueur peut faire pendant son tour
	void affiche_info_tour(int val);

	//Affiche une transition de l'IA
	void transition_IA(int val);

	// Ferme la fenetre
	void quit();

	
