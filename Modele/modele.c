#include "modele.h"

void init_pioche() {
    int i,j,k;
    pioche->nbTuiles=0;
    for (i=0;i<2;i++) {
        for (j = 1; j <= MAX_CHIFFRE; j++) {
            for (k = NOIR; k <= BLEU; k++) {
                pioche->pile[pioche->nbTuiles].chiffre=j;
                pioche->pile[pioche->nbTuiles].clr=k;
                pioche->nbTuiles++;
            }
        }
        pioche->pile[pioche->nbTuiles].chiffre=-1;
        pioche->pile[pioche->nbTuiles].clr=NOIR;
        pioche->nbTuiles++;
    }
}

void affiche_pioche() {
    int i;
    int c;
    COULT clr;
    for (i = 0; i < MAX_TUILES; i++) {
        c = pioche->pile[i].chiffre;
        clr = pioche->pile[i].clr;
        printf("%d -- %d\n",c,clr);
    }
}