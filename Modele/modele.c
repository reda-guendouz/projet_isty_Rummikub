#include "modele.h"

/**********
 * TUILE  *
 * *******/

void affiche_tuile(TUILE tuile, int numTuiles) {
    switch (tuile.clr) 
    {
    case 0 :
        printf("Tuile n°%d : %d NOIR\n",numTuiles,tuile.chiffre);
        break;
    case 1 :
        printf("Tuile n°%d : %d ORANGE\n",numTuiles,tuile.chiffre);
        break;
    case 2 :
        printf("Tuile n°%d : %d ROUGE \n",numTuiles,tuile.chiffre);
        break;
    case 3 :
        printf("Tuile n°%d : %d BLEU\n",numTuiles,tuile.chiffre);
        break;
    default:
        break;
    }
}

/**********
 * Joueur *
 * *******/

void init_joueurs(int nbJoueurs) {
    int i,j;
    for(i = 0;i<nbJoueurs;i++) 
    {
        joueurs[i].numJoueur = i+1;
        joueurs[i].score = 0;
        joueurs[i].chevalet.nbTuiles = 0;
        for (j = 0; j < PIOCHE_DEPART; j++)
            joueurs[i].chevalet.pile[j] = piocher(i);
    }
}

void affiche_joueur(JOUEUR joueur) {
    int i;
    printf("Joueur n°%d, Score : %d \n",joueur.numJoueur,joueur.score);
    printf("CHEVALET : \n");
    affiche_liste_tuiles(joueur.chevalet);
}

void affiche_joueurs() {
    int i = 0;
    for (i = 0; i<4;i++) {
        affiche_joueur(joueurs[i]);
    }
}

/**********
 * Pioche *
 * *******/

void init_pioche() {
    int i,j,k;
    pioche->nbTuiles=0;
    for (i=0;i<2;i++) {
        for (j = 1; j <= MAX_CHIFFRE; j++) 
        {
            for (k = NOIR; k <= BLEU; k++) 
            {
                pioche->pile[pioche->nbTuiles].chiffre=j;
                pioche->pile[pioche->nbTuiles].clr=k;
                pioche->nbTuiles++;
            }
        }
        pioche->pile[pioche->nbTuiles].chiffre=-1;
        pioche->pile[pioche->nbTuiles].clr=NOIR;
        pioche->nbTuiles++;
    }
    melanger_pioche();
}

void affiche_liste_tuiles(CHEVALET liste_tuiles) {
    int i;
    for (i = 0; i <= liste_tuiles.nbTuiles; i++) 
        affiche_tuile(liste_tuiles.pile[i], i);
}

void melanger_pioche() {
    int i,nb2;
    nb2 = MAX_TUILES;
    for(i=0;i<MAX_TUILES;i++)
    {
        TUILE tmp;
        int index = rand()%nb2;
        tmp = pioche->pile[index];
        pioche->pile[index] = pioche->pile[nb2-1];
        pioche->pile[MAX_TUILES-i-1] = tmp;
        nb2--;
    }
}

TUILE piocher(int numJoueur) {
    TUILE tuile = pioche->pile[pioche->nbTuiles];
    pioche->nbTuiles--;
    joueurs[numJoueur].chevalet.nbTuiles++;
    return tuile;
}


/***********
 * Plateau *
 * ********/

void affiche_plateau () {
    int i,j;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
       for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            printf("%d  ",plateau[i][j].chiffre);
        }
        printf("\n");
    }
}