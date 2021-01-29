#include "Vue/graphics2.h"

int main(int argc, char const *argv[])
{
    init_pioche();
    init_joueurs(2,2);
    init_graphics();

    affiche_auto_off();

    affiche_plateau(plateau);
    affiche_plateau_graphique();
    

    affiche_all();

    wait_escape();
    return 0;
}
