#include "modele.h"

void affiche_tuile(TUILE tuile, int numTuiles)
{
    if (tuile.chiffre == -1)
        printf("Tuile n°%d :  JOKER\n", numTuiles);
    else
    {
        switch (tuile.clr)
        {
        case NOIR:
            printf("Tuile n°%d :  %d NOIR\n", numTuiles, tuile.chiffre);
            break;
        case ORANGE:
            printf("Tuile n°%d : " ORA " %d ORANGE" RESET "\n", numTuiles, tuile.chiffre);
            break;
        case ROUGE:
            printf("Tuile n°%d : " ROU " %d ROUGE " RESET "\n", numTuiles, tuile.chiffre);
            break;
        case BLEU:
            printf("Tuile n°%d : " BLE " %d BLEU " RESET "\n", numTuiles, tuile.chiffre);
            break;
        default:
            break;
        }
    }
}

/****************
 * LISTE_TUILE  *
 * *************/

int ajouter_tuile(LISTE_TUILES *liste, TUILE tuile)
{
    liste->pile[liste->nbTuiles] = tuile;
    liste->nbTuiles++;
    return TRUE;
}

int tuile_dans_liste(LISTE_TUILES liste, TUILE tuile) {
    int i;
    TUILE t;
    for(i=0; i < liste.nbTuiles; i++) {
        t = liste.pile[i];
        if(tuile.chiffre == t.chiffre && tuile.clr == t.clr)
            return TRUE;
    }
    return FALSE;
}

/**********
 * Joueur *
 * *******/

void init_joueurs(int nbJoueurs, int nbJoueursH)
{
    joueurs.nbJs = nbJoueurs;
    int i, j;
    for (i = 0; i < nbJoueurs; i++)
    { 
        if (nbJoueursH > 0)
        {/*
            printf("Entrez le pseudonyme du joueur %d : ", tmp);
            scanf(" %s", joueurs.js[i].pseudo);*/
            nbJoueursH--;
        }
        else
        {
            //printf("IA 1\n");
            strcpy(joueurs.js[i].pseudo, "IA");
            joueurs.js[i].chevalet.nbTuiles = 0;
        }
        for (j = 0; j < PIOCHE_DEPART; j++)
        {
            piocher(&joueurs.js[i].chevalet);
            //affiche_tuile(pioche.pile[pioche.nbTuiles], j);
        }
    }
}

void affiche_joueur(JOUEUR joueur)
{
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n", joueur.numJoueur, joueur.pseudo);
    printf("CHEVALET : \n");
    affiche_liste_tuiles(joueur.chevalet);
}

void affiche_joueurs()
{
    int i;
    for (i = 0; i < joueurs.nbJs; i++)
        affiche_joueur(joueurs.js[i]);
}

/**********
 * Pioche *
 * *******/

void init_pioche()
{
    int i, j, k;
    pioche.nbTuiles = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 1; j <= MAX_CHIFFRE; j++)
        {
            for (k = NOIR; k <= BLEU; k++)
            {
                pioche.pile[pioche.nbTuiles].chiffre = j;
                pioche.pile[pioche.nbTuiles].clr = k;
                pioche.nbTuiles++;
            }
        }
        pioche.pile[pioche.nbTuiles].chiffre = -1;
        pioche.pile[pioche.nbTuiles].clr = NOIR;
        pioche.nbTuiles++;
    }
    melanger_pioche();
}

void affiche_liste_tuiles(LISTE_TUILES liste_tuiles)
{
    int i;
    for (i = 0; i < liste_tuiles.nbTuiles; i++)
        affiche_tuile(liste_tuiles.pile[i], i);
}

void melanger_pioche()
{
    srand(time(0));
    int i, nb2, index;
    TUILE tmp;
    nb2 = MAX_TUILES;
    for (i = 0; i < MAX_TUILES; i++)
    {
        index = rand() % nb2;
        tmp = pioche.pile[index];
        pioche.pile[index] = pioche.pile[nb2 - 1];
        pioche.pile[MAX_TUILES - i - 1] = tmp;
        nb2--;
    }
}

void piocher(LISTE_TUILES *liste)
{
    if (pioche.nbTuiles > 0){
        pioche.nbTuiles--;
        TUILE tuile = pioche.pile[pioche.nbTuiles];
        ajouter_tuile(liste, tuile);
    }
    else {
        printf("PLUS DE TUILES DANS LA PIOCHE");
        sleep(3);
    }
}

/***********
 * Plateau *
 * ********/
void affiche_plateau(TUILE *plateau_a_afficher)
{
    int i, j, k;
    printf("\nPlateau:\n  ");
    for (k = 0; k < 22; k++)
    {
        if (k < 10)
            printf("  %d ", k);
        else
            printf(" %d ", k);
    }
    printf("\n  ");
    for (k = 0; k < 88; k++)
        printf("-");
    printf("\n");
    char lettre = 'a';
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        printf("%c|", lettre);
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            // TEST AFFICHAGE
            TUILE t;
            t.chiffre = 10;
            t.clr = NOIR;
            plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)] = t;
            //
            if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == 0 && plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].clr == NOIR)
                printf("    ");
            else if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == -1)
                printf(" JK ");
            else
            {
                if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre < 10)
                    printf(" ");
                switch (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].clr)
                {
                case NOIR:
                    printf(" %d ", plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case ORANGE:
                    printf(ORA " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case ROUGE:
                    printf(ROU " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case BLEU:
                    printf(BLE " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                }
            }
        }
        printf("|\n");
        lettre += 1;
    }
    printf("  ");
    for (k = 0; k < 88; k++)
        printf("-");
    printf("\n");
}

void copie_plateau(TUILE *dest, TUILE *src)
{
    int i, j;
    for (i = 0; i < DIM_PLATEAU_H; i++)
        for (j = 0; j < DIM_PLATEAU_W; j++)
            dest[(int unsigned)(i * DIM_PLATEAU_W + j)] = src[(int unsigned)(i * DIM_PLATEAU_W + j)];
}

void placer_tuiles(LISTE_TUILES selection, TUILE *copie_plateau, int l, int c)
{
    int i;
    for (i = 0; i < selection.nbTuiles; i++)
        copie_plateau[(int unsigned)(l * DIM_PLATEAU_W + c + i)] = selection.pile[i];
}

int suite(LISTE_TUILES *l)
{
    if (l->nbTuiles > 2) {
        int i,j, nbJoker = 0, val = 0, clr = NOIR, new = 0,compteur = 0,cmptPlacementJoker = 0 ;
        int placementJoker[l->nbTuiles];
        TUILE remplacantJoker;
        LISTE_TUILES copie;
        copie.nbTuiles = 0;
     
        tri_liste(l);
        for (i = 0; i < l->nbTuiles; i++){
            if (l->pile[i].chiffre == -1)
                nbJoker++;
            else {
                if (!new){
                    val = l->pile[i].chiffre;
                    clr = l->pile[i].clr;
                    for (j = i; j < l->nbTuiles; j++){
                        if (clr != l->pile[j].clr)
                            return 0;
                    }
                    if (nbJoker)
                        new = i;
                    else
                        new = -6;
                    ajouter_tuile(&copie,l->pile[i]);
                    placementJoker[cmptPlacementJoker] = val;
                    cmptPlacementJoker++;
                }
                else {
                    if (val + 1 == l->pile[i].chiffre){
                        //printf("BONNE COULEUR BONNE SUITE +1 sans joker  %d  --- %d \n",val,l->pile[i].chiffre);
                        val++;
                        ajouter_tuile(&copie,l->pile[i]);
                        placementJoker[cmptPlacementJoker] = val;
                        cmptPlacementJoker++;
                    }
                    else if (val + 1 != l->pile[i].chiffre && nbJoker){
                        //printf("JOKER CONSOME\n");
                        remplacantJoker.clr = clr;
                        remplacantJoker.chiffre = val + 1;
                        val++;
                        ajouter_tuile(&copie,remplacantJoker);
                        nbJoker--;
                        i--;
                    }
                    else 
                        return 0;
                }
            }
        }
        //affiche_liste_tuiles(copie);
        compteur = l->pile[new].chiffre;
        remplacantJoker.clr = clr;
        while (l->pile[l->nbTuiles - 1].chiffre + nbJoker > 13){
            remplacantJoker.chiffre = compteur - 1;
            ajouter_tuile(&copie,remplacantJoker);
            tri_liste(&copie);
            nbJoker--; compteur--;
        }
        val++;
        for (i = 0; i<nbJoker;i++){
            remplacantJoker.chiffre = val;
            remplacantJoker.clr = clr;
            ajouter_tuile(&copie,remplacantJoker);
            val++;
        }
        if (!new) {
            compteur = 0;
            for (i = 0; i<l->nbTuiles;i++)
                compteur += 13 - i;
            return compteur;
        }
        else {
            for (i = 0; i < copie.nbTuiles; i++)
                compteur += copie.pile[i].chiffre;
            permutationJoker(&copie,placementJoker,cmptPlacementJoker);
            copie_liste(&copie,l);
            //printf("COMPTEUR : %d \n",compteur);
            return compteur;
        }
    }
    return 0;
}


void permutationJoker(LISTE_TUILES* l, int* chiffres, int taille){
    int i,j,trouve = 0;
    for (i = 0; i< l->nbTuiles;i++){
        trouve = 0;
        for (j = 0; j < taille; j++){
            if (l->pile[i].chiffre == chiffres[j]){
                trouve = 1;
            }
        }
        if (!trouve){
            l->pile[i].chiffre = -1;
            l->pile[i].clr = NOIR;
        }
    }
}

int triplon_quadruplon(LISTE_TUILES *l)
{
    if (l->nbTuiles > 2 && l->nbTuiles < 5) {
        int i, nbJoker = 0, compteur = 0, clr = NOIR, new = 0;
        int  couleur[4];
        for (i = 0; i <4; i++)
            couleur[i] = 1;
        
        tri_liste(l);
        for (i = 0; i < l->nbTuiles; i++){
            if (l->pile[i].chiffre == -1)
                nbJoker++;
            else {
                if (!new){
                    compteur = l->pile[i].chiffre;
                    clr = l->pile[i].clr;
                    couleur[clr]=0;
                    new = 1;
                }
                else {
                    if (compteur == l->pile[i].chiffre && couleur[l->pile[i].clr]){
                        couleur[l->pile[i].clr] = 0;
                    }
                    else
                        return 0;
                }
            }
        }
        if (!new)
            return 13*l->nbTuiles;
        else 
            return compteur*l->nbTuiles;
    }
    return 0;
}

void tri_liste(LISTE_TUILES *l)
{
    TUILE memo = l->pile[0];
    int i, j;
    for (i = 0; i < l->nbTuiles - 1; i++)
    {
        for (j = 0; j < l->nbTuiles - i - 1; j++)
        {
            if (l->pile[j].chiffre > l->pile[j + 1].chiffre)
            {
                memo = l->pile[j];
                l->pile[j] = l->pile[j + 1];
                l->pile[j + 1] = memo;
            }
        }
    }
}

void supprime_liste(LISTE_TUILES *l, TUILE tuile)
{
    int i,j;
    for (i = 0; i < l->nbTuiles; i++)
    {
        if (l->pile[i].chiffre == tuile.chiffre && l->pile[i].clr == tuile.clr){
            for(j = i+1; j<l->nbTuiles;j++){
                l->pile[i].chiffre = l->pile[j].chiffre;
                l->pile[i].clr = l->pile[j].clr;
            }
            l->nbTuiles--;
            return;
        }

    }
}

int test_combinaison(LISTE_TUILES *l)
{
    return triplon_quadruplon(l) + suite(l);
}

int est_victorieux(JOUEUR j)
{
    if (j.chevalet.nbTuiles == 0)
        return TRUE;
    return FALSE;
}

void affiche_victoire(JOUEUR j, int indiceJoueurGagnant)
{
    int i;
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n                                 ");
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n", j.numJoueur, j.pseudo);
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    printf("\n");
    printf("TABLE DES SCORES\n");
    score_fin_partie(indiceJoueurGagnant);
    for (i = 0; i < joueurs.nbJs; i++)
    {
        printf("%s : %d\n", joueurs.js[i].pseudo, joueurs.scores[i]);
    }
}

int est_placable(int taille_liste, int ligne, int colonne)
{
    int i, j, taille_dispo = 0, depart = FALSE;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (i == ligne && j == colonne)
                depart = TRUE;
            if (depart)
            {
                if (plateau[i][j].chiffre == 0)
                    taille_dispo++;
                if (taille_dispo == taille_liste)
                    return TRUE;
                if (plateau[i][j].chiffre != 0)
                    return FALSE;
            }
        }
    }

    return FALSE;
}

int intervertion_tuiles(TUILE *copie_plateau, int ligneSource, int colonneSource, int ligneDestination, int colonneDestination)
{
    // verifier ici d'abord que les lignes et colonnes sont bonnes
    // sinon retourner false
    printf(" SOURCE : %d %d  ---- DESTINATION %d %d \n",ligneSource,colonneSource,ligneDestination,colonneDestination);
    if (ligneSource < 0 || ligneSource >= DIM_PLATEAU_H || colonneSource < 0 || colonneSource >= DIM_PLATEAU_W ||
        ligneDestination < 0 || ligneDestination >= DIM_PLATEAU_H || colonneDestination < 0 || colonneDestination >= DIM_PLATEAU_W)
        return FALSE;
    TUILE temp;
    temp.chiffre = copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].chiffre;
    temp.clr = copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].clr;
    copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].chiffre = copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].chiffre;
    copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].clr = copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].clr;
    copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].chiffre = temp.chiffre;
    copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].clr = temp.clr;
    return TRUE;
}

void score_fin_partie(int indiceJoueurGagnant)
{
    int score[JOUEURS_MAX];
    int i, j;
    for (i = 0; i < joueurs.nbJs; i++)
    {
        if (i != indiceJoueurGagnant)
        {
            for (j = 0; j < joueurs.js[i].chevalet.nbTuiles; j++)
            {
                score[indiceJoueurGagnant] += joueurs.js[i].chevalet.pile[j].chiffre;
                score[i] -= joueurs.js[i].chevalet.pile[j].chiffre;
            }
        }
    }
    for (i = 0; i < joueurs.nbJs; i++)
    {
        joueurs.scores[i] += score[i];
        ecrire_score(joueurs.js[i].pseudo,score[i]);
    }
}

void ecrire_score(char * nomjoueur,int score){

    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    FILE* fichier = NULL;

    char chaine[500] = "";
    char chaine_score[500] = "";

    fichier = fopen("score.txt", "a");

    if (fichier != NULL){
        // On peut lire et écrire dans le fichier
        strcat(chaine,"Date de la partie : ");
        strcat(chaine,c_time_string);

        strcat(chaine,"Joueur : ");

        sprintf(chaine_score,"Score : %d",score);

        strcat(chaine,nomjoueur);
        strcat(chaine,"\n");

        strcat(chaine,chaine_score);
        strcat(chaine,"\n");

        fputs(chaine,fichier);
        
        fclose(fichier);
    }
    else{
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier score.txt en ecriture \n");
    }
}

void affiche_score(){

    FILE* fichier = NULL;
    char chaine[500] = "";
    fichier = fopen("score.txt", "r");

    if (fichier != NULL){
        // On peut lire et écrire dans le fichier
        while (fgets(chaine,500,fichier) != NULL){ // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            printf("%s",chaine);
        }
        fclose(fichier);
    }
    else{
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier score.txt en lecture \n");
    }
}

int char_to_int(char l)
{
    switch (l)
    {
    case 'a':
        return 0;
        break;
    case 'b':
        return 1;
        break;
    case 'c':
        return 2;
        break;
    case 'd':
        return 3;
        break;
    case 'e':
        return 4;
        break;
    case 'f':
        return 5;
        break;
    case 'g':
        return 6;
        break;
    case 'h':
        return 7;
        break;
    default:
        break;
    }
    return -1;
}

int analyse_plateau(TUILE *plateau)
{
    int i, j;
    unsigned char test = FALSE;
    LISTE_TUILES analyse;
    analyse.nbTuiles = 0;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (plateau[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre != 0)
            {
                ajouter_tuile(&analyse, plateau[(int unsigned)(i * DIM_PLATEAU_W + j)]);
                test = TRUE;
            }
            else if (plateau[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == 0 && test)
            {
                if (!test_combinaison(&analyse))
                    return FALSE;
                test = FALSE;
                analyse.nbTuiles=0;
            }
        }
    }
    return TRUE;
}

void mettre_a_jour(LISTE_TUILES *chevalet, LISTE_TUILES tuilesSelectionnees)
{
    int i;
    for (i = 0; i < tuilesSelectionnees.nbTuiles; i++)
        supprime_liste(chevalet, tuilesSelectionnees.pile[i]);
}

void trouver_combinaisons(LISTE_TUILES chevaletIa, LISTE_TUILES* combinaisonsTrouve)
{
    int i;
    int taille = chevaletIa.nbTuiles;
    int tab[taille];
    combinaisonsTrouve->nbTuiles = 0;
    for (i = 0; i<taille;i++)
        tab[i]= i;
    for (i=3;i<6;i++) {
        int data[i];
        combinationUtil(tab, data, 0, taille,0, i, chevaletIa, combinaisonsTrouve);
    }
    return;
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r, LISTE_TUILES chevalet, LISTE_TUILES* bestListe) 
{ 
    LISTE_TUILES newListe;
    int i,j;
    newListe.nbTuiles = 0;
	if (index == r) 
	{ 
		for (j=0; j<r; j++) 
            ajouter_tuile(&newListe,chevalet.pile[data[j]]);
		if (test_combinaison(&newListe)){
            //affiche_liste_tuiles(newListe);
            //printf("\n");
            if (calcul_main(&newListe) > calcul_main(bestListe)){
                copie_liste(&newListe,bestListe);
            }
        }
		return; 
	} 
    printf("milieu -- \n");
	for (i=start; i<=end && end-i+1 >= r-index; i++) 
	{ 
        printf("boucle 2 -- \n");
		data[index] = arr[i];
        printf("boucle 2.2 -- \n");
		combinationUtil(arr, data, i+1, end, index+1, r, chevalet, bestListe); 
        
        printf("boucle 2.3 -- \n");
	} 
}

void copie_liste(LISTE_TUILES* src, LISTE_TUILES* dst){
    dst->nbTuiles = 0;
    int i = 0;
    for (i = 0; i < src->nbTuiles; i++){
        ajouter_tuile(dst,src->pile[i]);
    }
}

int placer_combinaisons(LISTE_TUILES combinaisonTrouve, TUILE* copiePlateau) {
    int i,j, tailleCombinaisons = combinaisonTrouve.nbTuiles;
    for (i = 0; i<DIM_PLATEAU_H;i++){
        for (j=0; j<DIM_PLATEAU_W;j++){
            if (est_placable(tailleCombinaisons,i,j) && plateau[i][j-1].chiffre == 0){
                placer_tuiles(combinaisonTrouve,copiePlateau,i,j);
                return TRUE;
            }
        }
    }
    return FALSE;   
}

int readInt( int limMin, int limMax ) {
   for (;;) { // tant que la saisie n'est pas valide
      // lire
      char str[12];
      if ( !fgets( str , sizeof str/sizeof*str , stdin ) )
         printf( "Incident lors de la saisie\n" );
      else {
         // convertir
         char *end;
         long  res;
         int errno = 0;
         res = strtol( str, &end, 0 );
         if ( errno == 0 && end != str  && res >= limMin  &&  res <= limMax )
            return (int)res;
      }
   }
}

int calcul_main(LISTE_TUILES* listeTuiles){ 
    int valTriplonQuadruplon = triplon_quadruplon(listeTuiles), valSuite = suite(listeTuiles);
    //printf("TRIPLON : %d -------- SUITE : %d \n",valTriplonQuadruplon,valSuite);
    if (valTriplonQuadruplon > valSuite)
        return valTriplonQuadruplon;
    return valSuite;
}

int est_dans_selection(int selection,int taille,int *tabSelection){
    int i;
    for (i = 0; i<taille;i++){
        if (tabSelection[i] == selection)
            return 1;
    }
    return 0;
}