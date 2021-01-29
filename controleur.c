#include "Vue/graphics2.h"
#include "Modele/modele.h"

int main(int argc, char const *argv[])
{
    init_graphics();

    POINT welcomeText,IA1,IA2,PVP1,PVP2;
    welcomeText.y=25; welcomeText.x=800;
    IA1.x = IA1.y = 100;
    IA2.x = 600;
    IA2.y = 500;
    draw_rectangle(IA1,IA2,blanc);
    IA1.x += 30; IA1.y += 190;
    affiche_texte_special("Player(s) VS IA",70,IA1,rouge,"assets/verdana.ttf");



    wait_escape();
    return 0;
}
