#include "modele.h"

int main(void) {
    srand(time(NULL));
    init_pioche();
    //affiche_pioche();
    //melanger_pioche();
    affiche_pioche();
    printf("%d\n",pioche->nbTuiles);
    printf("=========\n");
    /*
    printf("=========\n");
    TUILE tuile = piocher(2);
    affiche_tuile(tuile);
    tuile = piocher(2);
    affiche_tuile(tuile);
    tuile = piocher(2);
    affiche_tuile(tuile);
    tuile = piocher(2);
    affiche_tuile(tuile);
    tuile = piocher(2);
    affiche_tuile(tuile);*/

    
    init_joueurs(1);
    //affiche_joueur(joueurs[0]);
    int choix;
    printf("Piochez : 1 or 2 \n");
    scanf("%d",&choix);
    piocher(2);
    affiche_joueur(joueurs[0]);
    printf("=========\n");
    affiche_pioche();
    printf("%d\n",pioche->nbTuiles);
    return 0;
}