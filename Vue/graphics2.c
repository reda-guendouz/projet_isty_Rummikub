#include "police.h"
#include "graphics2.h"
/// previously here : #ifdef SDL_ttf_OK
#include <SDL/SDL_ttf.h>
#define POLICE_NAME "verdana.ttf"
TTF_Font *police[256];
int verdana_ok = FALSE;
/// fin de "previously"

	// 1.1 La variable dans laquelle
	// l'image finale est �crite
	SDL_Window *screen;

	// 1.2 Pour ne pas oublier l'appel � init_graphics()
	int __init_graphics_est_deja_appele = FALSE;

	// 1.3 Si SDL_AFFICHE_AUTO vaut 1, l'affichage
	// est automatiquement fait pour chaque objet
	// Sinon il faut le fait � la main
	int SDL_AFFICHE_AUTO = 1;

	// 1.5
	POINT ___MOUSE_POSITION = {0,0};

void init_graphics()
	{
	/// Initialisation d'une taille voulu
	WIDTH  = 1700;
	HEIGHT = 900;

	/// Initialisation de la SDL_surface (variable 1.1)
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			printf("Impossible de charger la librairie SDL: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}

	screen = SDL_CreateWindow("Ceci est un titre quelconque mais pas vraiment parce qu'il n'y a vraiment rien de quelconque dans la vie",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH, HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_MOUSE_FOCUS|SDL_WINDOW_SHOWN);
	if ( screen == NULL )
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
    printf("SDL_ttf OK, ");
    /// Initialise la police (fichier police.h)
    TTF_Init();
    police[50] = TTF_OpenFont(POLICE_NAME, 10);
    if (police[50]) {
        verdana_ok=TRUE;
        printf("police %s OK : affichage graphique OK.\n",POLICE_NAME);
    }
    else {
        verdana_ok = 0;
        printf("police %s absente : affichage dans la console.\n",POLICE_NAME);
    }
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

COULEUR couleur_RGB(int r, int g, int b)
	{
	COULEUR C;
	return ((r%256)<<16) + ((g%256)<<8) + (b%256);
	return C;
	}

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

	/// Instruction bloquante
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

void fill_screen(COULEUR color)
	{
	int i,j;
	for (i=0;i<WIDTH;i++)
		for (j=0;j<HEIGHT;j++) *((COULEUR *)SDL_screen->pixels + (HEIGHT-j-1) * WIDTH + i) = color;
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

/// obligatoire pour le dessin (a comprendre, ainsi que le define "add_pix")
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

void draw_pixel(POINT p, COULEUR color)
	{
	add_pix(p.x,p.y,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

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