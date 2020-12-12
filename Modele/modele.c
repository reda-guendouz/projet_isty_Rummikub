#include "modele.h"

/**********
 * TUILE  *
 * *******/

void affiche_tuile(TUILE tuile) {
    switch (tuile.clr)
    {
    case 0 :
        printf("Tuile : %d NOIR\n",tuile.chiffre);
        break;
    case 1 :
        printf("Tuile : %d ORANGE\n",tuile.chiffre);
        break;
    case 2 :
        printf("Tuile : %d ROUGE \n",tuile.chiffre);
        break;
    case 3 :
        printf("Tuile : %d BLEU\n",tuile.chiffre);
        break;
    default:
        break;
    }
}



/**********
 * Pioche *
 * *******/

void init_pioche() {
    int i,j,k;
    pioche->nbTuiles=-1;
    for (i=0;i<2;i++) {
        for (j = 1; j <= MAX_CHIFFRE; j++) {
            for (k = NOIR; k <= BLEU; k++) {
                pioche->nbTuiles++;
                pioche->pile[pioche->nbTuiles].chiffre=j;
                pioche->pile[pioche->nbTuiles].clr=k;
            }
        }
        pioche->nbTuiles++;
        pioche->pile[pioche->nbTuiles].chiffre=-1;
        pioche->pile[pioche->nbTuiles].clr=NOIR;
    }
}

void affiche_pioche() {
    int i;
    for (i = 0; i < MAX_TUILES; i++) {
        affiche_tuile(pioche->pile[i]);
    }
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

TUILE piocher() {
    TUILE tuile = pioche->pile[pioche->nbTuiles];
    pioche->nbTuiles--;
    return tuile;
}