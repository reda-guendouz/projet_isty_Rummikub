#include "modele.h"

int main(void) {
    srand(time(NULL));
    init_pioche();
    //affiche_pioche();
    melanger_pioche();
    //affiche_pioche();
    TUILE tuile = piocher();
    affiche_tuile(tuile);
    return 0;
}