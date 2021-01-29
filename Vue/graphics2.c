#include "police.h"
#include "graphics2.h"




/// previously here : #ifdef SDL_ttf_OK

#define POLICE_NAME "assets/verdana.ttf"
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
    //"Ceci est un titre quelconque mais pas vraiment parce qu'il n'y a vraiment rien de quelconque dans la vie"
	screen=SDL_CreateWindow("TITLE",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
	if ( screen == NULL )
		{
		fprintf(stderr, "Impossible de passer en %dx%d: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(EXIT_FAILURE);
		}
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
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
	IMG_Init(IMG_INIT_PNG);
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
	int texteW = 0;   int texteH = 0;
	int texteX = p.x; int texteY = HEIGHT - p.y;
	/// Couleur hexadecimal en uint32 "C" to Couleur rgb "color"
	SDL_Color color = {255,255,255};
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
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
			SDL_Rect position = {texteX, texteY, texteW, texteH};
			SDL_RenderCopy(renderer, texture, NULL, &position);
			SDL_RenderPresent(renderer);
			if (SDL_AFFICHE_AUTO) affiche_all();
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(texte);
			}
	else printf("%s\n",texte_affichable);
	TTF_CloseFont(police);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
}

void wait_escape()
	{
	int display = 1;
	SDL_Event event;
	POINT p;
	p.x = WIDTH/2 - 170;
	p.y = 25;
	affiche_texte("Appuyer sur Echap pour terminer",20,p,blanc);
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
	IMG_Quit();
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
#define add_pix(x,y,color)  if (dans_ecran((x),(y))) { SDL_RenderDrawPoint(renderer, x, y); }

void draw_pixel(POINT p, COULEUR color)
	{
	add_pix(p.x,p.y,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void draw_line(POINT p1, POINT p2, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF) / 255.0;
	int ggg = ((color >> 8) & 0xFF) / 255.0;
	int bbb = ((color) & 0xFF) / 255.0;
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_RenderDrawLine(renderer,p1.x,p1.y,p2.x,p2.y);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void draw_rectangle(POINT p1, POINT p2, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF);
	int ggg = ((color >> 8) & 0xFF);
	int bbb = ((color) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_Rect testas= {p1.x,p1.y,p2.x,p2.y};
	SDL_RenderDrawRect(renderer, &testas);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void draw_fill_rectangle(POINT p1, POINT p2, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF);
	int ggg = ((color >> 8) & 0xFF);
	int bbb = ((color) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_Rect testas= {p1.x,p1.y,p2.x,p2.y};
	SDL_RenderFillRect(renderer, &testas);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void load_img(char *fic,POINT emplacement, POINT dimensions){
	int png1 = 5; int png2 = 5;
	SDL_Surface *image = IMG_Load(fic);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_QueryTexture(texture,NULL,NULL,&png1,&png2);		
	SDL_Rect position = {emplacement.x, emplacement.y, png1, png2};
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
}

void affiche_menu_debut(){
	SDL_RenderClear(renderer);
	//POINT rect1,rect2;
}

void converti_int_en_str(int nb, char *p)
{
	int unite = nb%10;
	if(nb<10) {
		p[0] = unite+'0';
		p[1] = '\0';
	}
	else {
		p[0] = 1 + '0';
		p[1] = unite+'0';
		p[2] = '\0';
	}
}

void transforme_tuile_en_path(TUILE t,char *p2) {
    char p[23];
    strcpy(p,"assets/Tuiles/");
    switch (t.clr)
        {
        case NOIR:
            strcat(p,"N/");
            break;
        case ORANGE:
            strcat(p,"O/");
            break;
        case ROUGE:
            strcat(p,"R/");
            break;
        case BLEU:
            strcat(p,"B/");
            break;
        }
    int taille;
    if(t.chiffre<10)
		taille=2;
	else
		taille = 3;
	char numero[taille];
	converti_int_en_str(t.chiffre,numero);
    strcat(p,numero);
    strcat(p,".png\0");
    strcpy(p2,p);
}

void affiche_plateau_graphique() {
	POINT l1,l2;
    l1.x = 75; l2.x = 0;
    l1.y = 75; l2.y = 0;
	int i,j;
	TUILE t;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
			if (plateau[i][j].chiffre == -1)
                printf(" JK ");
            else
            {
				t = plateau[i][j];
				char chaine[23];
    			transforme_tuile_en_path(t,chaine);
				printf("%s\n",chaine);
				load_img(chaine,l1,l2);
				l1.x+=50;
			}
    	}
		l1.x=75;
        l1.y+=75;
	}
}



