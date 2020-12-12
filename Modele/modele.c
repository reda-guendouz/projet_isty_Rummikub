#include "modele.h"

void init_pioche() {
    int i,j,compt;
    compt=0;
    for (i = 1; i <= MAX_CHIFFRE; i++) {
        pioche[compt].chiffre=i;
        for (j = NOIR; j <= BLEU; j++) {
            pioche[compt].clr=j;
            compt++;
        }
    }

}

void affiche_pioche() {
    int i;
    int c;
    COULT clr;
    for (i = 0; i <= MAX_TUILES; i++) {
        c = pioche[i].chiffre;
        clr = pioche[i].clr;
        printf("%d -- %d\n",c,clr);
    }
}