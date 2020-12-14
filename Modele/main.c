#include "modele.h"

int main(void) {
    srand(time(NULL));
    init_pioche();
    /*affiche_liste_tuiles(pioche);
    init_joueurs(2);
    affiche_joueurs();
    affiche_plateau();*/

    LISTE_TUILES liste;
    liste.nbTuiles=4;
    TUILE t1;
    t1.clr=ROUGE;
    t1.chiffre=10;
    TUILE t2;
    t2.clr=ROUGE;
    t2.chiffre=10;
    TUILE t3;
    t3.clr=ROUGE;
    t3.chiffre=10;
    TUILE t4;
    t4.clr=ROUGE;
    t4.chiffre=10;

    liste.pile[0]=t1;
    liste.pile[1]=t2;
    liste.pile[2]=t3;
    liste.pile[3]=t4;
    
    printf("%d\n",triplon_quadruplon(&liste));
    //printf("%d\n",pioche->nbTuiles);
    //printf("=========\n");
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

    
    //init_joueurs(1);
    //affiche_joueur(joueurs[0]);
    //printf("%d\n",joueurs[0].chevalet.nbTuiles);
    //piocher(0);
    //affiche_joueur(joueurs[0]);
    //printf("%d\n",joueurs[0].chevalet.nbTuiles);
    //printf("=========\n");*/
    //affiche_pioche();
    //printf("%d\n",pioche->nbTuiles);

    return 0;
}