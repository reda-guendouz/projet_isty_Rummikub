#include "modele.h"

int main(void) {
    srand(time(NULL));
    init_pioche();
    affiche_liste_tuiles(pioche);
    init_joueurs(2);
    affiche_joueurs();
    affiche_plateau();

    // TOUR DE LA PARTIE
    unsigned char partie=TRUE;
    unsigned char tour=TRUE;
    while (partie)
    {
        while (tour)
        {
            tour=FALSE;
        }
        partie=FALSE;
    }
    
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