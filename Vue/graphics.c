// ###############################################
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
// 0. AFFICHAGE DE TEXTE AVEC SDL_ttf ... ligne  30
// 1. VARIABLES, CONSTANTES ............. ligne  47
// 2. AFFICHAGE ......................... ligne  67
// 3. GESTION D'�V�NEMENTS .............. ligne 152
// 4. DESSIN D'OBJETS ................... ligne 375
// 5. �CRITURE DE TEXTE ................. ligne 749
// 6. LECTURE D'ENTIER .................. ligne 862
// 7. GESTION DU TEMPS .................. ligne 879
// 8. VALEUR AL�ATOIRES ................. ligne 939
// 9. DIVERS ............................ ligne 957
// ################################################






// ##################################
// 0. AFFICHAGE DE TEXTE AVEC SDL_ttf
// ##################################

// D�finit SDL_TTF_OK ou non
#include "police.h"
#include "graphics.h"

#ifdef SDL_TTF_OK
	#include <SDL_ttf.h>
	#include <SDL/SDL_ttf.h>
	#define POLICE_NAME "verdana.ttf"
	TTF_Font *police[256];
	int verdana_ok = FALSE;
#endif



// ########################
// 1. VARIABLES, CONSTANTES
// ########################

	// 1.1 La variable dans laquelle
	// l'image finale est �crite
	SDL_Surface * SDL_screen;

	// 1.2 Pour ne pas oublier l'appel � init_graphics()
	int __init_graphics_est_deja_appele = FALSE;

	// 1.3 Si SDL_AFFICHE_AUTO vaut 1, l'affichage
	// est automatiquement fait pour chaque objet
	// Sinon il faut le fait � la main
	int SDL_AFFICHE_AUTO = 1;

	// 1.5
	POINT ___MOUSE_POSITION = {0,0};

// ############
// 2. AFFICHAGE
// ############

	// 2.1 Initialisation de la fen�tre sur laquelle on dessine
	// W et H sont la largeur et la hauteur d�sir�e.
	// La variable globale SDL_screen est initialis�e
void init_graphics()
	{
	// Initialisation d'une taille voulu
	WIDTH  = 1700;
	HEIGHT = 900;

	/// Initialisation de la SDL_surface (variable 1.1)
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			printf("Impossible de charger la librairie SDL: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}

	/// met en place le mode video avec la longueur, la largeur et le nombre de pixel donnée
	/// SDL_HWSURFACE permet d'utiliser la carte graphique
	/// SDL_DOUBLEBUF permet d'optimiser l'utilisation de la carte graphique
	/// SDL_RESIZABLE permet au joueur de modifier la resolution de la fenetre
	/// ( avec la souris en cliquant sur les cotes par exemple ) 
	SDL_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	if ( SDL_screen == NULL )
		{
		fprintf(stderr, "Impossible de passer en %dx%d en 32 bits: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(EXIT_FAILURE);
		}

	/// a voir avec les pseudos des joueurs
	// Autorise la prise en compte de repetition lors d'un appui
	// long sur une touche
	///////SDL_EnableKeyRepeat(1,0);

	// Le titre de la fenetre
	SDL_WM_SetCaption("Rummikub",NULL);

	__init_graphics_est_deja_appele = TRUE;
	///printf("Fenetre de %d x %d\n",WIDTH,HEIGHT);
	#ifdef SDL_TTF_OK
		printf("SDL_ttf OK, ");
		/// Initialise la police (fichier police.h)
		TTF_Init();
        police[50] = TTF_OpenFont(POLICE_NAME, 10);
		if (police[50])  {
			verdana_ok=TRUE;
			printf("police %s OK : affichage graphique OK.\n",POLICE_NAME);
		}
		else {
			verdana_ok = 0;
			printf("police %s absente : affichage dans la console.\n",POLICE_NAME);
		}
	#else
		printf("SDL_ttf absent : affichage dans la console.\n");
	#endif

	// Remplit la fen�tre de noir
	fill_screen(noir);
	affiche_auto_on();
	affiche_all();
	}

	// 2.2 Affichage automatique ou manuel
void affiche_auto_on () { SDL_AFFICHE_AUTO = 1; }
void affiche_auto_off() { SDL_AFFICHE_AUTO = 0; }
	// Affiche tous les objets et v�rifie que la fonction init_graphics
	// a �t� appel�e pr�c�demment et affiche un message d'erreur sinon.
void affiche_all()
	{
	SDL_Event event;
	if (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) exit(0);
	if (__init_graphics_est_deja_appele) SDL_Flip(SDL_screen);
		else {
		     init_graphics(380,80);
		     write_text("init_graphics() n'a pas �t� appel�e.");
		     write_text("");
		     write_text("           Cliquer pour terminer.");
		     fprintf(stderr,"init_graphics() n'a pas �t� appel�e.\n");
		     fprintf(stderr,"Cliquer pour terminer.\n");
		     wait_clic();
		     exit(1);
		     }
	}

	// La fonction synchro est la fonction historique
void synchro() { affiche_all(); }

	// 2.3 Cr�ation de couleur
COULEUR couleur_RGB(int r, int g, int b)
	{
	COULEUR C;
	return ((r%256)<<16) + ((g%256)<<8) + (b%256);
	return C;
	}

void souris_visible()  {SDL_ShowCursor(SDL_ENABLE);}
void souris_invisible(){SDL_ShowCursor(SDL_DISABLE);}

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
POINT get_arrow()
	{
	POINT dep;
	dep.x = dep.y = 0;
	SDL_Event event;
	while (SDL_WaitEvent(&event))
		{
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(EXIT_SUCCESS);

		/* Si l'utilisateur a appuy� sur une touche */
		if (event.type == SDL_KEYDOWN)
			{
			switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE : exit(EXIT_SUCCESS);
						case SDLK_LEFT   : (dep.x) -= MINDEP; printf("fleche gauche\n"); break;
						case SDLK_RIGHT  : (dep.x) += MINDEP; printf("fleche droite\n"); break;
						case SDLK_UP     : (dep.y) += MINDEP; printf("fleche haut\n"); break;
						case SDLK_DOWN   : (dep.y) -= MINDEP; printf("fleche du bas\n"); break;
						default          : break;
					}
			break;
			}
		}
	return dep;
	}

	// 3.2 Renvoie d�placement de souris
	// Meme s�mantique que get_arrow()
	// Instruction non bloquante, si la souris n'a pas boug�,
	// les champs x et y vaudront 0.
POINT get_mouse()
	{
	POINT P = ___MOUSE_POSITION;
	SDL_Event event;
	while (SDL_PollEvent(&event))
		{
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(0);

		/* Si l'utilisateur a appuy� sur une touche */
		if (event.type == SDL_KEYDOWN)
			{
			switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE : exit(0);
						default :	break;
					}
			}
		/* Si l'utilisateur a boug� la souris */
		if (event.type == SDL_MOUSEMOTION)
			{
			P.x = event.motion.x;
			P.y = HEIGHT-event.motion.y;
			}
		}
	___MOUSE_POSITION = P;
	return P;
	}

	// 3.3 Attend que l'on tape Echap et quitte
	// Instruction bloquante
void wait_escape()
	{
	int display = 1;
	SDL_Event event;
	POINT p;
	p.x = WIDTH/2 - 170;
	p.y = 25;
	aff_pol("Appuyer sur Echap pour terminer",20,p,gris);
	affiche_all();
	while (SDL_WaitEvent(&event) && display)
		{
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(EXIT_SUCCESS);

		/* Si l'utilisateur a appuy� sur une touche */
		if (event.type == SDL_KEYDOWN)
			{
			switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE : display=0;	break;
						default :	break;
					}
			}
		}
	/* Fermeture de la police */
	#ifdef SDL_TTF_OK
		int i;
		if (verdana_ok) for (i=0;i<256;i++) if (police[i]) TTF_CloseFont(police[i]);
		TTF_Quit();
	#endif
	SDL_Quit();
	}

	// 3.4 Attend que l'utilisateur clique sur le bouton gauche
	// Renvoie les coordonn�es du point cliqu�
	// Instruction bloquante
POINT wait_clic()
	{
	int encore = 1;
	POINT P;
	SDL_Event event;
	P.x = 0;
	P.y = 0;
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des �tudiants, c'est trop lent
	#ifdef SDL_TTF_OK
		POINT E,F;
		char S[16];
		E.x = WIDTH - 55; E.y = 15;
		F.x = WIDTH; F.y = 0;
	#endif
#endif
	while (SDL_WaitEvent(&event) && encore)
		{
		/* Si l'utilisateur clique avec la souris */
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
			encore=0;
			P.x = event.button.x;
			P.y = HEIGHT-event.button.y;
			}
		/* Si l'utilisateur d�place la souris */
		if (event.type == SDL_MOUSEMOTION)
			{
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des �tudiants, c'est trop lent
			#ifdef SDL_TTF_OK
				if (police[10])
					{
					draw_fill_rectangle(E,F,noir);
					sprintf(S,"%4d %4d",event.motion.x,HEIGHT - event.motion.y);
					aff_pol(S,10,E,gris);
					affiche_all();
					}
			#endif
#endif
			printf("%cEn attente de clic ... %4d %4d           %c",13,event.motion.x,HEIGHT - event.motion.y,13);
			fflush(stdout);
			}
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(EXIT_SUCCESS);

		}
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des �tudiants, c'est trop lent
	#ifdef SDL_TTF_OK
		aff_pol(S,10,E,noir);
		//draw_fill_rectangle(E,F,jaune);
		affiche_all();
	#endif
#endif
	printf("%cClic en %4d %4d                                           \n",13,P.x,P.y);
	___MOUSE_POSITION = P;
	return P;
	}

	// 3.5 Attend que l'on clique et renvoie dans button le bouton cliqu� :
	// *button vaut soit 'G' (pour Gauche), soit 'M' (pour milieu),
	// soit 'D' (pour Droit) en fonction du bouton cliqu�
	// Instruction bloquante
POINT wait_clic_GMD(char *button)
	{
	int encore = 1;
	POINT P;
	SDL_Event event;
	P.x = 0;
	P.y = 0;
	#ifdef SDL_TTF_OK
		POINT E,F;
		char S[16];
		E.x = WIDTH - 55; E.y = 15;
		F.x = WIDTH; F.y = 0;
	#endif
	affiche_all();
	printf("Cliquer dans la fen�tre...");
	while (SDL_WaitEvent(&event) && encore)
		{
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(0);

		/* Si l'utilisateur a cliqu� avec la souris */
		if ((event.type == SDL_MOUSEBUTTONDOWN))
			{
			#ifdef SDL_TTF_OK
				if (!police[10])
					{
					draw_fill_rectangle(E,F,noir);
					sprintf(S,"%4d %4d",event.motion.x,HEIGHT - event.motion.y);
					aff_pol(S,10,E,gris);
					affiche_all();
					}
			#endif
			printf("%cCliquer dans la fen�tre ... %4d %4d           %c",13,event.motion.x,HEIGHT - event.motion.y,13);
			fflush(stdout);
			encore=0;
			P.x = event.button.x;
			P.y = HEIGHT-event.button.y;
			if (event.button.button == SDL_BUTTON_LEFT)   *button = 'G';
			if (event.button.button == SDL_BUTTON_MIDDLE) *button = 'M';
			if (event.button.button == SDL_BUTTON_RIGHT)  *button = 'D';
			}
		}
	#ifdef SDL_TTF_OK
		draw_fill_rectangle(E,F,noir);
	#endif
	printf("Clic '%c' en %4d %4d                                           \n",*button,P.x,P.y);
	return P;
	}


// ##################
// 4. DESSIN D'OBJETS
// ##################

	// 4.1 Remplissage de tout l'�cran
void fill_screen(COULEUR color)
	{
	int i,j;
	for (i=0;i<WIDTH;i++)
		for (j=0;j<HEIGHT;j++) *((COULEUR *)SDL_screen->pixels + (HEIGHT-j-1) * WIDTH + i) = color;
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.x.1 Fonction de clipping (v�rification que le point est
	// dans la fen�tre)
	// Cette fonction n'est pas visible en dehors de ce fichier
int dans_ecran(int x, int y)
	{
	if (x<0) return 0;
	if (x>=WIDTH) return 0;
	if (y<0) return 0;
	if (y>=HEIGHT) return 0;
	return 1;
	}

	// 4.x.2 Macro qui permet d'ajouter un pixel � la SDL_surface
	// Inverse l'ordonn�e entre haut et bas
#define add_pix(x,y,color)  if (dans_ecran((x),(y))) *((COULEUR *)SDL_screen->pixels + (HEIGHT-(y)-1) * WIDTH + (x)) = (color)

	// 4.2 Affichage un pixel
void draw_pixel(POINT p, COULEUR color)
	{
	add_pix(p.x,p.y,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.3 Dessine un segment
void draw_line(POINT p1, POINT p2, COULEUR color)
	{
	int xmin, xmax;
	int ymin, ymax;
	int i,j;
	float a,b,ii,jj;

	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}

	if (xmin==xmax) for (j=ymin;j<=ymax;j++) add_pix(xmin,j,color);
	if (ymin==ymax) for (i=xmin;i<=xmax;i++) add_pix(i,ymin,color);


	// La variation la plus grande est en x
	if ((xmax-xmin >= ymax-ymin) && (ymax-ymin>0))
		{
		a = (float)(p1.y-p2.y) / ((float)(p1.x-p2.x));
		b = p1.y - a*p1.x;
		for (i=xmin;i<=xmax;i++)
			{
			jj = a*i+b;
			j = jj;
			if (((jj-j) > 0.5) && (j < HEIGHT-1)) j++;
			add_pix(i,j,color);
			}
		}

	// La variation la plus grande est en y
	if ((ymax-ymin > xmax-xmin) && (xmax-xmin>0))
		{
		a = (float)(p1.y-p2.y) / ((float)(p1.x-p2.x));
		b = p1.y - a*p1.x;
		for (j=ymin;j<=ymax;j++)
			{
			ii = (j-b)/a;
			i = ii;
			if (((ii-i) > 0.5) && (i < WIDTH-1)) i++;
			add_pix(i,j,color);
			}
		}
		if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.4 Dessine un rectangle non rempli
	// Les deux points sont deux points quelconques
	// non adjacents du rectangle
void draw_rectangle(POINT p1, POINT p2, COULEUR color)
	{
	int xmin, xmax;
	int ymin, ymax;
	int i,j;

	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}

	for (i=xmin;i<=xmax;i++) add_pix(i,ymin,color);
	for (i=xmin;i<=xmax;i++) add_pix(i,ymax,color);

	for (j=ymin;j<=ymax;j++) add_pix(xmin,j,color);
	for (j=ymin;j<=ymax;j++) add_pix(xmax,j,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.5 Dessine un rectangle rempli
	// Les deux points sont deux points quelconques
	// non adjacents du rectangle
void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color)
	{
	int xmin, xmax;
	int ymin, ymax;
	int i,j;

	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}

	for (i=xmin;i<=xmax;i++) for (j=ymin;j<=ymax;j++) add_pix(i,j,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.6 Dessine un cercle non rempli
void draw_circle(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x - rayon;  max.x = centre.x + rayon;
	min.y = centre.y - rayon;  max.y = centre.y + rayon;
	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y + dy;
		add_pix(i,j,color);
		j = centre.y - dy;
		add_pix(i,j,color);
		}
	for (j=min.y;j<=max.y;j++)
		{
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x + dx;
		add_pix(i,j,color);
		i = centre.x - dx;
		add_pix(i,j,color);
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.7 Dessine un cercle rempli
void draw_fill_circle(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x - rayon; max.x = centre.x + rayon;
	min.y = centre.y - rayon; max.y = centre.y + rayon;

	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		for (j=min.y;j<=max.y;j++)
			{
			dy = j - centre.y;
			if (dx*dx + dy*dy <= rr) add_pix(i,j,color);
			}
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.8.1 Dessine un quart de cercle en haut � droite
void draw_circle_HD(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x;  max.x = centre.x + rayon;
	min.y = centre.y;  max.y = centre.y + rayon;
	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y + dy;
		add_pix(i,j,color);
		}
	for (j=min.y;j<=max.y;j++)
		{
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x + dx;
		add_pix(i,j,color);
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.8.2 Dessine un quart de cercle en bas � droite
void draw_circle_BD(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x; max.x = centre.x + rayon;
	min.y = centre.y - rayon; max.y = centre.y;
	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y - dy;
		add_pix(i,j,color);
		}
	for (j=min.y;j<=max.y;j++)
		{
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x + dx;
		add_pix(i,j,color);
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.8.3 Dessine un quart de cercle en haut � gauche
void draw_circle_HG(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x - rayon; max.x = centre.x;
	min.y = centre.y; max.y = centre.y + rayon;
	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y + dy;
		add_pix(i,j,color);
		}
	for (j=min.y;j<=max.y;j++)
		{
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x - dx;
		add_pix(i,j,color);
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}


	// 4.8.4 Dessine un quart de cercle en bas � gauche
void draw_circle_BG(POINT centre, int rayon, COULEUR color)
	{
	POINT min, max;
	int i,j;
	float dx, dy, rr;

	min.x = centre.x - rayon; max.x = centre.x;
	min.y = centre.y - rayon; max.y = centre.y;
	rr = rayon*rayon;

	for (i=min.x;i<=max.x;i++)
		{
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y - dy;
		add_pix(i,j,color);
		}
	for (j=min.y;j<=max.y;j++)
		{
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x - dx;
		add_pix(i,j,color);
		}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}


	// 4.9 Dessine une ellipse remplie
	// Les arguments F1 et F2 sont les focales et r est
	// la somme des distances � chacun des points focaux
void draw_fill_ellipse(POINT F1, POINT F2, int r, COULEUR color)
	{
	int i,j;
	int dx, fx;
	int dy, fy;
	float d, d1, d2;

	d = (F1.x-F2.x)*(F1.x-F2.x) + (F1.y-F2.y)*(F1.y-F2.y);
	d = sqrt(d);

	if (F1.x<F2.x) {dx = F1.x - d - r; fx = F2.x + d + r;} else {dx = F2.x - d - r; fx = F1.x + d + r;}
	if (F1.y<F2.y) {dy = F1.y - d - r; fy = F2.y + d + r;} else {dy = F2.y - d - r; fy = F1.y + d + r;}
	for (i=dx;i<=fx;i++)
		for (j=dy;j<=fy;j++)
			if (dans_ecran(i,j))
				{
				d1 = (i-F1.x)*(i-F1.x) + (j-F1.y)*(j-F1.y);
				d1 = sqrt(d1);
				d2 = (i-F2.x)*(i-F2.x) + (j-F2.y)*(j-F2.y);
				d2 = sqrt(d2);
				if (d1+d2 < d+r) add_pix(i,j,color);
				}
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

	// 4.10 Dessine un triangle
void draw_triangle(POINT p1, POINT p2, POINT p3, COULEUR color)
	{
	draw_line(p1,p2,color);
	draw_line(p2,p3,color);
	draw_line(p3,p1,color);
	}

	// 4.11 Dessine un triangle rempli
	// Fonction annexe qui calcule le min de 3 valeurs
int min3(int a, int b, int c)
	{
	if ( (a<b) && (a<c) ) return a;
	if ( (b<a) && (b<c) ) return b;
	return c;
	}

	// Fonction annexe qui calcule le max de 3 valeurs
int max3(int a, int b, int c)
	{
	if ( (a>b) && (a>c) ) return a;
	if ( (b>a) && (b>c) ) return b;
	return c;
	}

void draw_fill_triangle(POINT p1, POINT p2, POINT p3, COULEUR color)
	{
	float a12, b12, a23, b23, a31, b31;
	float s1, s2, s3;
	// La droite passant par les point pi et pj
	// a pour �quation : y = aij x  +  bij
	a12 = (p1.y-p2.y)/(float)(p1.x-p2.x);   b12 = p1.y - a12*p1.x;
	a23 = (p2.y-p3.y)/(float)(p2.x-p3.x);   b23 = p2.y - a23*p2.x;
	a31 = (p3.y-p1.y)/(float)(p3.x-p1.x);   b31 = p3.y - a31*p3.x;
	// Le signe de sk d�termine de quel cot� pk est de la droite [pi,pj]
	s3 = p3.y - (a12*p3.x + b12);
	s1 = p1.y - (a23*p1.x + b23);
	s2 = p2.y - (a31*p2.x + b31);

	int minx, maxx, miny, maxy;
	minx = min3(p1.x,p2.x,p3.x); maxx = max3(p1.x,p2.x,p3.x);
	miny = min3(p1.y,p2.y,p3.y); maxy = max3(p1.y,p2.y,p3.y);

	int i,j;
	int ok;
	for (i=minx;i<maxx;i++)
		for (j=miny;j<maxy;j++)
			{
			ok = 1;
			// On v�rifie que le point (i,j) est du bon cot�
			// des 3 droites du triangle
			if (s3 * (j - (a12*i + b12)) < 0) ok = 0;
			if (s1 * (j - (a23*i + b23)) < 0) ok = 0;
			if (s2 * (j - (a31*i + b31)) < 0) ok = 0;
			if (ok) add_pix(i,j,color);
			}
	}


// ####################
// 5. �CRITURE DE TEXTE
// ####################

	// 5.1 Affiche du texte avec
	// Le texte est pass� dans l'argument "a_ecrire"
	// la police est celle d�finie par la constante POLICE_NAME
	//           dans graphics.c
	// la taille est pass�e en argument
	// l'argument p de type POINT est le point en haut � gauche
	// � partir duquel le texte s'affiche
	// la COULEUR C pass�e en argument est la couleur d'affichage
	// N�cessite l'installation  de SDL_ttf.h
void aff_pol(char *a_ecrire, int taille, POINT p, COULEUR C)
	{
	#ifdef SDL_TTF_OK
	    int i;
	    SDL_Color color;
	    SDL_Surface *texte = NULL;
	    SDL_Rect position;
	    static int premiere_fois = 1;
	    static TTF_Font *police[256];
	    TTF_Font *pol;

	    // Initialisation de la police (n'est fait qu'une seule fois pour les tailles < 256)
	    if (premiere_fois)  { TTF_Init(); for (i=0;i<256;i++) police[i] = NULL; premiere_fois = 0;}
	    if (taille>=256) pol = TTF_OpenFont(POLICE_NAME, taille);
		    else {
			 if (police[taille]==NULL) police[taille] = TTF_OpenFont(POLICE_NAME, taille);
		         pol = police[taille];
			 }
	    SDL_GetRGB(C,SDL_screen->format,&(color.r),&(color.g),&(color.b));

	    /* Ecriture du texte dans la SDL_Surface "texte" en mode Blended (optimal) */
	    if (pol) texte = TTF_RenderText_Blended(pol, a_ecrire, color); else texte = NULL;
	    if (texte)  {
		    	position.x = p.x;
		    	position.y = HEIGHT - p.y;
		    	SDL_BlitSurface(texte, NULL, SDL_screen, &position); /* Blit du texte par-dessus */
	            	if (SDL_AFFICHE_AUTO) affiche_all();
			SDL_FreeSurface(texte);
		    	}
		    else printf("%s\n",a_ecrire);
/*
	    if (SDL_AFFICHE_AUTO) affiche_all();
	    if (police) TTF_CloseFont(police);
	    TTF_Quit();
	    if (texte) SDL_FreeSurface(texte);
*/
	#else
		taille = 0; p.x = p.y = 0; C = 0;
		printf("%s\n",a_ecrire);
	#endif
	}

	// 5.2 Affiche un entier
	// Meme s�mantique que aff_pol()
void aff_int(int n,  int taille, POINT p, COULEUR C)
	{
	char s[32];
	sprintf(s,"%d",n);
	aff_pol(s,taille,p,C);
	}

	// 5.3 Affiche dans la fen�tre graphique comme dans une fen�tre
	// shell mais sans d�roulement. Commence en haut et
	// se termine en bas.
void write_text(char *a_ecrire)
	{
	#ifdef SDL_TTF_OK
	    static char s[256];
	    static int fin = 0;
	    static int premier = 1;
	    static POINT position;

	    if (premier) {position.x = 10; position.y = HEIGHT; premier = 0;}

	if (verdana_ok)
		{
//		printf("verd\n");
	    if (a_ecrire)
		    {
		    if (fin+strlen(a_ecrire) > 256) {fprintf(stderr,"Chaine de caract�re trop longue\n"); return;}
	            strcat(s+fin,a_ecrire);
//		printf("a_ecr : #%s#\n",s);
	            aff_pol(s,20,position,blanc);
		    fin += strlen(a_ecrire);
		    s[fin] = '\0';
		    }
		    else
		    {
		    position.y -= 20;
		    fin = 0;
		    s[fin] = '\0';
		    }
		}
		else { if (a_ecrire) {printf("%s",a_ecrire); fflush(stdout);} else printf("\n"); }
	#else
	    if (a_ecrire) {printf("%s",a_ecrire); fflush(stdout);}
		    else  printf("\n");
	#endif
	}

void write_int(int n)
	{
	char s[32];
	sprintf(s,"%d",n);
	write_text(s);
	}

void write_bool(BOOL b) { if (b) write_text("True"); else write_text("False"); }

void writeln() { write_text(NULL); }
// ###################
// 6. LECTURE D'ENTIER
// ###################

	// 6.1 Renvoie l'entier tap� au clavier.
	// Cette fonction est bloquante
int lire_entier_clavier()
	{
	int n;
	int ret;
	printf("Donner un entier : ");
	fflush(stdout);
	ret = scanf("%d",&n);
	return n;
	}


// ###################
// 7. GESTION DU TEMPS
// ###################

	// 7.1 Chronom�tre �l�mentaire, pr�cis � la micro seconde.
	// Fonction non visible en dehors de ce fichier
float chrono(int action)
	{
	static double ch = 0.0;
	double current;
	float delta;
	struct timeval tv;

	gettimeofday(&tv,NULL);
	current = tv.tv_sec + (float)(tv.tv_usec)*1e-6;
	if (action == 0) ch = current;
	delta = (float)(current-ch);
	return delta;
	}

	// D�clenchement du chrono
	// Le remet � z�ro s'il �tait d�j� lanc�
void  chrono_start() { chrono(0); }
float chrono_val()   { return chrono(1); }


	// 7.2 Attend le nombre de millisecondes pass� en argument
void attendre(int millisecondes) { SDL_Delay(millisecondes); }

	// 7.3.1 Renvoie l'heure de l'heure courante
int heure()
	{
	struct tm *stm;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	stm = localtime((time_t *)&(tv.tv_sec));
	return stm->tm_hour;
	}

	// 7.3.2 Renvoie le nombre de minutes de l'heure courante
int minute()
	{
	struct tm *stm;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	stm = localtime((time_t *)&(tv.tv_sec));
	return stm->tm_min;
	}

	// 7.3.3 Renvoie le nombre de secondes de l'heure courante
int seconde()
	{
	struct tm *stm;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	stm = localtime((time_t *)&(tv.tv_sec));
	return stm->tm_sec;
	}


// ####################
// 8. VALEUR AL�ATOIRES
// ####################

	// 8.1 Renvoie un float dans l'intervalle [0;1[
float alea_float()
	{
	static int init_alea = 1;
	if (init_alea) srand(time(NULL));
	init_alea = 0;
	return (float)rand() / (float)RAND_MAX;
	}

	// 8.2 Renvoie un int dans l'intervalle [0..N[
	// soit N valeurs diff�rentes de 0 � N-1
int alea_int(int N) { return (int)(N*alea_float()); }


// #########
// 9. DIVERS
// #########

	// 9.1 Renvoie la distance entre deux points
int distance(POINT P1, POINT P2)
	{
	int d;
	d = (P1.x-P2.x)*(P1.x-P2.x) + (P1.y-P2.y)*(P1.y-P2.y);
	return (int)(sqrt(d));
	}


/// #########
/// 10. DIVERS v2
/// #########

	/// 10.1 Permet d'avoir la hauteur et la largeur de la surface
	void taille(int* h,int* w){
		*h = SDL_screen->h;
		*w = SDL_screen->w;
	}