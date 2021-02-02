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
	WIDTH  = 1500;
	HEIGHT = 700;

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
	/// Couleur hexadecimal en uint32 "C" to Couleur rgb "color"
	int rrr = ((C >> 16) & 0xFF);
	int ggg = ((C >> 8) & 0xFF);
	int bbb = ((C) & 0xFF);
	SDL_Color color = {rrr,ggg,bbb};
	//SDL_SetRenderDrawColor(renderer,255,255,255,0);
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
	printf("%cClic en  %4d %4d\n",13,P.x,P.y);
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

void draw_line(POINT debutLigne, POINT finLigne, COULEUR color)
	{
	int rrr = ((color >> 16) & 0xFF);
	int ggg = ((color >> 8) & 0xFF);
	int bbb = ((color) & 0xFF);
	SDL_SetRenderDrawColor(renderer,rrr,ggg,bbb,0);
	SDL_RenderDrawLine(renderer,debutLigne.x,debutLigne.y,finLigne.x,finLigne.y);
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

void load_img(char *fic,POINT emplacement){
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
	if (SDL_AFFICHE_AUTO) SDL_RenderPresent(renderer);	
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

void affiche_inscription(int numJoueur){
	SDL_RenderClear(renderer);
    POINT textP,rec1,rec2,rec3,l;

	// fond d'ecran :
	l.x=0;l.y=0;
	load_img("assets/images/bg.png",l);

	// titre :
    textP.y=25; textP.x=350;
	char inscrive[29];
	strcpy(inscrive,"Inscrivez le nom du joueur ");
	inscrive[27]= numJoueur + '0';
	inscrive[28]= '\0';
    affiche_texte(inscrive,25,textP,noir);

	// premiere selection :
	rec1.x=100; rec1.y=400;
	rec2.x=170; rec2.y=70;
	draw_rectangle(rec1,rec2,blanc);
	rec1.x+=10; rec1.y+=10;
	affiche_texte("Validez",40,rec1,blanc);
	
	// deuxieme selection :
	rec3.x=100; rec3.y=490;
	draw_rectangle(rec3,rec2,blanc);
	rec3.x+=10; rec3.y+=10;
	affiche_texte("Refaire",40,rec3,blanc);
}

void inscription(char *pseudoJoueur, int numJoueur){
	BOOL done=false;
	BOOL empty=true;
    SDL_Event event;
	char text[80]="";
    POINT clic,rec1,rec2,rec3,rec4,textP,err;
	textP.y=400; textP.x=400;
	err.x=30; err.y=HEIGHT-50;
	rec1.x=100; rec1.y=400;
	rec2.x=270; rec2.y=470;
	rec3.x=100; rec3.y=490;
	rec4.x=270; rec4.y=560;
	affiche_inscription(numJoueur);
	SDL_StartTextInput();
    while (!done) {
        if (SDL_PollEvent(&event)) {
			// case a faire pour plus tard : case SDL_DELETE
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						clic.x = event.button.x;
						clic.y = event.button.y;
						if (dans_zone(clic,rec1,rec2)) // Valider
						{
							if (empty)
							{
								affiche_texte("Erreur : nom entré vide !",30,err,rouge);
								SDL_Delay(1300);
								affiche_inscription(numJoueur);
							}
							else							
								done = true;
						}
						else if(dans_zone(clic,rec3,rec4)) // Refaire
						{
							strcpy(text,"");
							empty=true;
							affiche_inscription(numJoueur);
						}	
					}
                    break;
                case SDL_TEXTINPUT:
					if (strlen(text) > MAX_PSEUDONYME-1)
    					affiche_texte("Limite de caractères atteinte !",30,err,rouge);
					else{
						if(empty) empty = false;
                    	strcat(text, event.text.text);
    					affiche_texte(text,50,textP,blanc);
					}
                    break;
				case SDL_QUIT:
					exit(EXIT_SUCCESS);
            }
        }
    }
	SDL_StopTextInput();
	strcpy(pseudoJoueur,text);
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
	if(t.chiffre==-1)
		strcat(p,"jo");
    else{
		if(t.chiffre<10)
			taille=2;
		else
			taille = 3;
		char numero[taille];
		converti_int_en_str(t.chiffre,numero);
		strcat(p,numero);
	} 
    strcat(p,".png\0");
    strcpy(p2,p);
}

void affiche_plateau_graphique() {
	POINT l1,fond1,fond2,fond3,fond4;
	int i,j,espace=45,espace2=65;
    l1.x = 300; l1.y = 40;
	fond1.x = l1.x - 6; fond1.y = l1.y - 6;
	fond2.x = l1.x + DIM_PLATEAU_W*espace - 4; fond2.y=fond1.y;
	fond3.x = fond1.x; fond3.y = fond1.y;
	fond4.x = fond3.x; fond4.y = DIM_PLATEAU_H*espace2 + espace2/2 + 2;
	draw_line(fond1,fond2,blanc);
	draw_line(fond3,fond4,blanc);
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
			fond3.x = espace + l1.x - 4; fond4.x = fond3.x ;
			draw_line(fond3,fond4,blanc);
			affiche_tuile_graphique(plateau[i][j],l1);
			l1.x+=espace;
    	}
		l1.x=300;
        l1.y+=espace2;
		fond1.y = l1.y - 6;
		fond2.y=fond1.y;
		draw_line(fond1,fond2,blanc);
	}
	if (SDL_AFFICHE_AUTO) SDL_RenderPresent(renderer);
}


void affiche_joueur_graphique(int num_joueur) {
	POINT p;
	p.x=75;
	p.y=600;

	affiche_texte(joueurs.js[num_joueur].pseudo,20,p,blanc);

	POINT l1;
    l1.x = 445 + ((14-joueurs.js[num_joueur].chevalet.nbTuiles)*22);
    l1.y = 600;
	int i;

	for (i = 0; i < joueurs.js[num_joueur].chevalet.nbTuiles ; i++)
    {
		affiche_tuile_graphique(joueurs.js[num_joueur].chevalet.pile[i],l1);
		l1.x+=44;
	}
	if (SDL_AFFICHE_AUTO) SDL_RenderPresent(renderer);
}

void affiche_tuile_graphique(TUILE t,POINT p) {
	char chaine[23];
	transforme_tuile_en_path(t,chaine);
	load_img(chaine,p);
}

/*
* affiche un menu
* et renvoie le nombre de joueurs choisi
*/
int choix_joueurs(){
	SDL_RenderClear(renderer);
    POINT textP,rec1,rec2,rec3,rec4,rec5,rec6,rec7,rec8,l,clic;

	// fond d'ecran :
	l.x=0;l.y=0;
	load_img("assets/images/bg.png",l);

	// titre :
    textP.y=25; textP.x=380;
    affiche_texte("Combien de joueurs ?",35,textP,noir);

	// premiere selection :
	rec1.x=100; rec1.y=100;
	rec2.x=130; rec2.y=70;
	draw_rectangle(rec1,rec2,blanc);
	rec1.x+=10; rec1.y+=10;
	affiche_texte("Un",40,rec1,noir);
	
	// deuxieme selection :
	rec3.x=100; rec3.y=490;
	draw_rectangle(rec3,rec2,blanc);
	rec3.x+=10; rec3.y+=10;
	affiche_texte("Deux",40,rec3,noir);

	// Troisieme selection :
	rec4.x=900; rec4.y=100;
	draw_rectangle(rec4,rec2,blanc);
	rec3.x+=10; rec3.y+=10;
	affiche_texte("Trois",40,rec4,noir);

	// Quatrieme selection :
	// attention : quatrieme joueur impossible avec ia
	rec5.x=900; rec5.y=490;
	draw_rectangle(rec5,rec2,blanc);
	rec3.x+=10; rec3.y+=10;
	affiche_texte("Quatre",40,rec5,noir);

	rec6.x = rec3.x + rec2.x; rec6.y = rec3.y + rec2.y;
	rec7.x = rec4.x + rec2.x; rec7.y = rec4.y + rec2.y;
	rec8.x = rec5.x + rec2.x; rec8.y = rec5.y + rec2.y;
	rec2.x += rec1.x; rec2.y += rec1.y;

	do
    {
        clic = wait_clic();
    } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec6) && !dans_zone(clic,rec4,rec7) && !dans_zone(clic,rec5,rec8));

	if (dans_zone(clic,rec1,rec2))
		return 1;
	else if (dans_zone(clic,rec3,rec6))
		return 2;
	else if (dans_zone(clic,rec4,rec7))
		return 3;
	else if (dans_zone(clic,rec5,rec8))
		return 4;
	else
		return -1;
	
	if (SDL_AFFICHE_AUTO) SDL_RenderPresent(renderer);
}

void selectionne_tuiles_chevalet(int num_joueur) {
	POINT rec1,rec2,coin,dim,clic;
	int i,j,xg,xd;
	LISTE_TUILES liste;
	COULEUR c;
	TUILE t;
	liste.nbTuiles=0;

	rec1.x=1200; rec1.y=600;
	rec2.x=170; rec2.y=70;
	draw_rectangle(rec1,rec2,blanc);
	rec1.x+=10; rec1.y+=10;
	affiche_texte("Validez",40,rec1,blanc);
	affiche_all();

	rec1.x-=10; rec1.y-=10;
	rec2.x=rec1.x+170; rec2.y=rec1.y+70;
	clic = wait_clic();
	while (!dans_zone(clic,rec1,rec2))
	{
		if(clic.y>=600 && clic.y<=654){
			xg = 445 + ((14-joueurs.js[num_joueur].chevalet.nbTuiles)*22);
			xd = xg + ((joueurs.js[num_joueur].chevalet.nbTuiles)*44) - 3;
			if(clic.x>=xg && clic.x<=xd){
				for(i=0; i<joueurs.js[num_joueur].chevalet.nbTuiles; i++){
					if(clic.x>=xg+i*44 && clic.x<=xg+(i*44)+38){
						coin.x=xg+(i*44)-1; coin.y=599;
						dim.x=39; dim.y=55;
						t = joueurs.js[num_joueur].chevalet.pile[i];
						if(tuile_dans_liste(liste,t)) {
							c = noir;
							supprime_liste(&liste,t);
						}
						else {
							c = jaune;
							ajouter_tuile(&liste,t);
						}
						for(j=0;j<3;j++){
							draw_rectangle(coin,dim,c);
							coin.x--; coin.y--;
							dim.x+=2; dim.y+=2;
						}
						affiche_all();
					}
				}
			}
		}
		clic = wait_clic();
	}
}
