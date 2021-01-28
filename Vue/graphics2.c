#include "police.h"
#include "graphics2.h"
/// previously here : #ifdef SDL_ttf_OK

#define POLICE_NAME "verdana.ttf"
int verdana_ok = FALSE;
/// fin de "previously"

	SDL_Window *screen;
    SDL_Renderer *renderer;

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
    //"Ceci est un titre quelconque mais pas vraiment parce qu'il n'y a vraiment rien de quelconque dans la vie",
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &screen, &renderer);
	if ( screen == NULL )
		{
		fprintf(stderr, "Impossible de passer en %dx%d: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(EXIT_FAILURE);
		}
    SDL_SetRenderDrawColor(renderer,0,255,0,0);
    SDL_RenderClear(renderer);
	/// a voir avec les pseudos des joueurs
	// Autorise la prise en compte de repetition lors d'un appui
	// long sur une touche
	///////SDL_EnableKeyRepeat(1,0);

	__init_graphics_est_deja_appele = TRUE;
	///printf("Fenetre de %d x %d\n",WIDTH,HEIGHT);
    printf("SDL_ttf OK, ");
    /// Initialise la police (fichier police.h)
    TTF_Init();
    TTF_Font *test = TTF_OpenFont(POLICE_NAME, 10);
    if (test) {
        verdana_ok=TRUE;
        printf("police %s OK : affichage graphique OK.\n",POLICE_NAME);
		TTF_CloseFont(test);
    }
    else {
        verdana_ok = 0;
        printf("police %s absente.\n",POLICE_NAME);
		exit(EXIT_FAILURE);
    }
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
	if (SDL_PollEvent(&event)) 
		if (event.type == SDL_QUIT) exit(0);
	if (__init_graphics_est_deja_appele) SDL_RenderPresent(renderer);
		else wait_escape();
	}

	// La fonction synchro est la fonction historique
void synchro() { affiche_all(); }

COULEUR couleur_RGB(int r, int g, int b)
	{
	COULEUR C;
	return ((r%256)<<16) + ((g%256)<<8) + (b%256);
	return C;
	}

/// si ne fonctionne pas, mettre position = {0, 0, X, X}
void affiche_texte(char *texte_affichable, int taille, POINT p, COULEUR C){
	int texteW = 0; int texteH = 0;
	/// Couleur hexadecimal en uint32 "C" to Couleur rgb "color"
	SDL_Color color = {((C >> 16) & 0xFF) / 255.0,((C >> 8) & 0xFF) / 255.0,((C) & 0xFF) / 255.0};
	SDL_Surface *texte = NULL;
	TTF_Font *police;

	/// Initialisation de la librairie "TTF" necessitant SDL_ttf.h
	TTF_Init();
	police = TTF_OpenFont(POLICE_NAME, taille);
	/* Ecriture du texte dans la SDL_Surface "texte" en mode Blended (optimal) */
	if (police) texte = TTF_RenderText_Blended(police, texte_affichable, color); else texte = NULL;
	if (texte)  {
			/// old : \\\ SDL_BlitSurface(texte, NULL, SDL_screen, &position); /* Blit du texte par-dessus */
			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, texte);
			SDL_QueryTexture(texture,NULL,NULL,&texteW,&texteH);		
			SDL_Rect position = {0, 0, texteW, texteH};
			SDL_RenderCopy(renderer, texture, NULL, &position);
			SDL_RenderPresent(renderer);
			if (SDL_AFFICHE_AUTO) affiche_all();
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(texte);
			}
	else printf("%s\n",texte_affichable);
	TTF_CloseFont(police);
}

void wait_escape()
	{
	int display = 1;
	SDL_Event event;
	POINT p;
	p.x = WIDTH/2 - 170;
	p.y = 25;
	affiche_texte("Appuyer sur Echap pour terminer",20,p,gris);
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
	
	TTF_Quit();
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
			printf("%cEn attente de clic ... %4d %4d           %c",13,event.motion.x,HEIGHT - event.motion.y,13);
			fflush(stdout);
			}
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(EXIT_SUCCESS);

		}
	printf("%cClic en %4d %4d                                           \n",13,P.x,P.y);
	___MOUSE_POSITION = P;
	return P;
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
#define add_pix(x,y,color)  if (dans_ecran((x),(y))) { SDL_RenderDrawPoint(renderer, x, y); SDL_RenderPresent(renderer); }

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