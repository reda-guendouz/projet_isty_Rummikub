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
	WIDTH  = 1450;
	HEIGHT = 750;

	/// Initialisation de la SDL_surface (variable 1.1)
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			printf("Impossible de charger la librairie SDL: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
    //"Ceci est un titre quelconque mais pas vraiment parce qu'il n'y a vraiment rien de quelconque dans la vie"
	screen=SDL_CreateWindow("Rummikub",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
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
	int texteX = p.x; int texteY = p.y;
	/// Couleur hexadecimal en uint32 "C" to Couleur rgb "color".
	int rrr = ((C >> 16) & 0xFF);
	int ggg = ((C >> 8) & 0xFF);
	int bbb = ((C ) & 0xFF);
	SDL_Color color = {rrr,ggg,bbb};
	//SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_Surface *texte = NULL;
	TTF_Font *police;

	police = TTF_OpenFont(POLICE_NAME, taille);
	/* Ecriture du texte dans la SDL_Surface "texte" en mode Blended (optimal) */
	if (police) texte = TTF_RenderUTF8_Blended(police, texte_affichable, color);
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

/// si ne fonctionne pas, mettre position = {0, 0, X, X}
void affiche_texte_special(char *texte_affichable, int taille, POINT p, COULEUR C, char *ttf_file){
	int texteW = 0;   int texteH = 0;
	int texteX = p.x; int texteY = p.y;
	/// Couleur hexadecimal en uint32 "C" to Couleur rgb "color".
	int rrr = ((C >> 16) & 0xFF);
	int ggg = ((C >> 8) & 0xFF);
	int bbb = ((C ) & 0xFF);
	SDL_Color color = {rrr,ggg,bbb};
	//SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_Surface *texte = NULL;
	TTF_Font *police;

	police = TTF_OpenFont(ttf_file, taille);
	/* Ecriture du texte dans la SDL_Surface "texte" en mode Blended (optimal) */
	if (police) texte = TTF_RenderUTF8_Blended(police, texte_affichable, color);
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
	p.y = HEIGHT - 25;
	affiche_texte("Appuyer sur Echap pour terminer",20,p,blanc);
	//affiche_all();
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
			P.y = event.button.y;
			}
		/* Si l'utilisateur deplace la souris */
		if (event.type == SDL_MOUSEMOTION)
			{
			printf("%cEn attente de clic ... %4d %4d           %c",13,event.motion.x,event.motion.y,13);
			fflush(stdout);
			}
		/* Si l'utilisateur a demand� � fermer la fen�tre, on quitte */
		if (event.type == SDL_QUIT) exit(EXIT_SUCCESS);

		}
	printf("%cClic en %4d %4d\n",13,P.x,P.y);
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

	// 4.x.2 Macro qui permet d'ajouter un pixel
	// Inverse l'ordonn�e entre haut et bas
#define add_pix(x,y,color)  if (dans_ecran((x),(y))) { SDL_SetRenderDrawColor(renderer,((color >> 16) & 0xFF),((color >> 8) & 0xFF),((color) & 0xFF),0);SDL_RenderDrawPoint(renderer, x, y);SDL_SetRenderDrawColor(renderer,255,255,255,0); }

void draw_pixel(POINT p, COULEUR color)
	{
	add_pix(p.x,p.y,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void draw_line(POINT p1, POINT p2, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF);
	int ggg = ((color >> 8) & 0xFF);
	int bbb = ((color) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_RenderDrawLine(renderer,p1.x,p1.y,p2.x,p2.y);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
	if (SDL_AFFICHE_AUTO) affiche_all();
	}

void draw_rectangle(POINT emplacement, POINT dimensions, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF);
	int ggg = ((color >> 8) & 0xFF);
	int bbb = ((color) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_Rect testas= {emplacement.x,emplacement.y,dimensions.x,dimensions.y};
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

void fill_screen(COULEUR clr){
	int rrr = ((clr >> 16) & 0xFF);
	int ggg = ((clr >> 8) & 0xFF);
	int bbb = ((clr) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,255,255,255,0);
}

void affiche_menu_debut(){
	fill_screen(cyan);

    POINT welcomeText,RecEmplacement,RecDimesions;
    welcomeText.y=25; welcomeText.x=400;
    affiche_texte_special("RUMMIKUB",130,welcomeText,vertolive,"assets/Cartoon.ttf");
    welcomeText.y=400; welcomeText.x=680;
    affiche_texte("OR",50,welcomeText,noir);
    RecEmplacement.x = 90; RecEmplacement.y = 320;
    RecDimesions.x = 550; RecDimesions.y = 130;
    draw_fill_rectangle(RecEmplacement,RecDimesions,jaune);
    RecEmplacement.x += 30; RecEmplacement.y += 15;
    affiche_texte_special("Player(s) VS IA",70,RecEmplacement,noir,"assets/Poppins.ttf");
    RecEmplacement.x = 790; RecEmplacement.y = 420;
    RecDimesions.x = 620; RecDimesions.y = 130;
	draw_fill_rectangle(RecEmplacement,RecDimesions,jaune);
    RecEmplacement.x += 30; RecEmplacement.y += 15;
    affiche_texte_special("PVP FIGHTOUUU !",70,RecEmplacement,noir,"assets/Poppins.ttf");
}

int dans_zone(POINT clic, POINT p1, POINT p2){
	if (clic.x > p2.x || clic.x < p1.x || clic.y > p2.y || clic.y < p1.y )
		return false;
	return true;
}


void affiche_inscription(char *pseudoJoueur){
	POINT l;
	l.x=0;l.y=0;
	load_img("assets/images/bg.png",l,l);

	BOOL done=false;
    SDL_Event event;
	char text[80]="";
    POINT textP,rec1,rec2,rec3,rec4,err,clic;

	err.x=30; err.y=HEIGHT-50;
    textP.y=25; textP.x=350;
    affiche_texte("Inscrivez le nom du joueur X",25,textP,noir);
	rec1.x=100; rec1.y=400;
	rec2.x=170; rec2.y=70;
	draw_rectangle(rec1,rec2,blanc);
	rec1.x+=10; rec1.y+=10;
	affiche_texte("Validez",40,rec1,blanc);

	rec3.x=100; rec3.y=490;
	draw_rectangle(rec3,rec2,blanc);
	rec3.x+=10; rec3.y+=10;
	affiche_texte("Refaire",40,rec3,blanc);

	// reajustement pour les "dans_zone"
	rec1.x-=10; rec1.y-=10;
	rec4.x=rec2.x+rec3.x; rec4.y=rec2.y+rec3.y;
	rec2.x+=rec1.x; rec2.y+=rec1.y;

	textP.y=400; textP.x=400;
	SDL_StartTextInput();
    while (!done) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						clic.x = event.button.x;
						clic.y = event.button.y;
						if (dans_zone(clic,rec1,rec2))
							done = true;
						else if(dans_zone(clic,rec3,rec4))
						{
							strcpy(text,"");
							load_img("assets/images/bg.png",l,l);
							textP.y=25; textP.x=300;
							affiche_texte("Inscrivez le nom du joueur X",25,textP,noir);
							textP.y=400; textP.x=400;
							rec1.x=100; rec1.y=400;
							rec2.x=170; rec2.y=70;
							draw_rectangle(rec1,rec2,blanc);
							rec1.x+=10; rec1.y+=10;
							affiche_texte("Validez",40,rec1,blanc);

							rec3.x=100; rec3.y=490;
							draw_rectangle(rec3,rec2,blanc);
							rec3.x+=10; rec3.y+=10;
							affiche_texte("Refaire",40,rec3,blanc);

							// reajustement pour les "dans_zone"
							rec1.x-=10; rec1.y-=10;
							rec4.x=rec2.x+rec3.x; rec4.y=rec2.y+rec3.y;
							rec2.x+=rec1.x; rec2.y+=rec1.y;
						}
						
					}
                    break;
                case SDL_TEXTINPUT:
                    /* Add new text onto the end of our text */
					if (strlen(text) > MAX_PSEUDONYME-1)
    					affiche_texte("Limite de caractères atteinte !",30,err,rouge);
					else					
                    	strcat(text, event.text.text);
    				affiche_texte(text,50,textP,blanc);
                    break;
				case SDL_QUIT:
					exit(EXIT_SUCCESS);
            }
        }
    }
	SDL_StopTextInput();
	strcpy(pseudoJoueur,text);
}