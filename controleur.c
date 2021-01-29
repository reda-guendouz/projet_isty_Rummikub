#include "Vue/graphics2.h"
#include "Modele/modele.h"

int main(int argc, char const *argv[])
{
    init_pioche();
    init_joueurs(2);
    init_graphics();



    wait_escape();
    return 0;
}
