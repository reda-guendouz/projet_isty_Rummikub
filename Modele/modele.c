#include "modele.h"

/**********
 * TUILE  *
 * *******/

void affiche_tuile(TUILE tuile, int numTuiles) {
    if(tuile.chiffre==-1)
         printf("Tuile n°%d : JOKER\n",numTuiles);
    else {
        switch (tuile.clr) 
        {
        case NOIR:
            printf("Tuile n°%d : %d NOIR\n",numTuiles,tuile.chiffre);
            break;
        case ORANGE:
            printf("Tuile n°%d : %d ORANGE\n",numTuiles,tuile.chiffre);
            break;
        case ROUGE:
            printf("Tuile n°%d : %d ROUGE \n",numTuiles,tuile.chiffre);
            break;
        case BLEU:
            printf("Tuile n°%d : %d BLEU\n",numTuiles,tuile.chiffre);
            break;
        default:
            break;
        }
    }
    
}

/**********
 * Joueur *
 * *******/

void init_joueurs(int nbJoueurs) {
    joueurs.nbJs = nbJoueurs;
    int i,j,tmp;
    for(i = 0;i<nbJoueurs;i++) 
    {
        tmp=i+1;
        joueurs.js[i].numJoueur = tmp;
        joueurs.js[i].score = 0;
        printf("Entrez le pseudonyme du joueur %d : ",tmp);
        scanf("%s",joueurs.js[i].pseudo);
        joueurs.js[i].chevalet.nbTuiles = 0;
        for (j = 0; j < PIOCHE_DEPART; j++)
            joueurs.js[i].chevalet.pile[j] = piocher(i);
    }
    for (i = 0; i < nbJoueurs; i++)
        printf("Le joueur %d est %s !\n",tmp,joueurs.js[i].pseudo);
    
}

void affiche_joueur(JOUEUR joueur) {
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n - Score : %d \n",joueur.numJoueur,joueur.pseudo,joueur.score);
    printf("CHEVALET : \n");
    //affiche_liste_tuiles(joueur.chevalet);
}

void affiche_joueurs() {
    int i;
    for (i = 0; i<joueurs.nbJs;i++)
        affiche_joueur(joueurs.js[i]);
}

/**********
 * Pioche *
 * *******/

void init_pioche() {
    int i,j,k;
    pioche.nbTuiles=0;
    for (i=0;i<2;i++) {
        for (j = 1; j <= MAX_CHIFFRE; j++) 
        {
            for (k = NOIR; k <= BLEU; k++) 
            {
                pioche.pile[pioche.nbTuiles].chiffre=j;
                pioche.pile[pioche.nbTuiles].clr=k;
                pioche.nbTuiles++;
            }
        }
        pioche.pile[pioche.nbTuiles].chiffre=-1;
        pioche.pile[pioche.nbTuiles].clr=NOIR;
        pioche.nbTuiles++;
    }
    melanger_pioche();
}

void affiche_liste_tuiles(LISTE_TUILES liste_tuiles) {
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
        tmp = pioche.pile[index];
        pioche.pile[index] = pioche.pile[nb2-1];
        pioche.pile[MAX_TUILES-i-1] = tmp;
        nb2--;
    }
}

TUILE piocher(int numJoueur) {
    TUILE tuile = pioche.pile[pioche.nbTuiles];
    pioche.nbTuiles--;
    joueurs.js[numJoueur].chevalet.nbTuiles++;
    return tuile;
}


/***********
 * Plateau *
 * ********/

void affiche_plateau () {
    int i,j,k;

    // partie test
    TUILE t1;
    t1.clr=ROUGE;
    t1.chiffre=9;
    TUILE t2;
    t2.clr=BLEU;
    t2.chiffre=11;
    TUILE t3;
    t3.clr=BLEU;
    t3.chiffre=-1;
    TUILE t4;
    t4.clr=ORANGE;
    t4.chiffre=7;

    plateau[0][0]=t1;
    plateau[1][1]=t2;
    plateau[2][2]=t3;
    plateau[0][21]=t2;
    plateau[7][0]=t3;
    plateau[7][21]=t4;
    
    printf("\nPlateau:\n ");
    for(k=0;k<88;k++)
        printf("-");
    printf("\n");
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
       printf("|");
       for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if(plateau[i][j].chiffre==0 && plateau[i][j].clr==NOIR)
                printf("    ");
            else if(plateau[i][j].chiffre==-1)
                printf(" JO ");
            else {
                if(plateau[i][j].chiffre<10)
                    printf(" ");
                switch (plateau[i][j].clr) 
                {
                case NOIR:
                    printf(" %d ",plateau[i][j].chiffre);
                    break;
                case ORANGE:
                    printf(ORA" %d "RESET,plateau[i][j].chiffre);
                    break;
                case ROUGE:
                    printf(ROU" %d "RESET,plateau[i][j].chiffre);
                    break;
                case BLEU:
                    printf(BLE" %d "RESET,plateau[i][j].chiffre);
                    break;
                }
            }
        }
        printf("|\n");
    }
    printf(" ");
    for(k=0;k<88;k++)
        printf("-");
    printf("\n");
}