#include "modele.h"

int main(void) {
    srand(time(NULL));
    init_pioche();
    //affiche_pioche();
    melanger_pioche();
    //affiche_pioche();
    //TUILE tuile = piocher();
    //affiche_tuile(tuile);

    init_joueurs(3);
    affiche_joueurs(3);
    return 0;
}