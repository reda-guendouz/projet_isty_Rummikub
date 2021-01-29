#include "Vue/graphics2.h"
#include "Modele/modele.h"

int main(int argc, char const *argv[])
{
    init_graphics();

    POINT welcomeText,RecEmplacement,RecDimesions;
    welcomeText.y=25; welcomeText.x=500;
    affiche_texte_special("RUMMIKUB",130,welcomeText,blanc,"assets/Cartoon.ttf");
    welcomeText.y=400; welcomeText.x=790;
    affiche_texte("OR",50,welcomeText,blanc);
    RecEmplacement.x = 200; RecEmplacement.y = 320;
    RecDimesions.x = 550; RecDimesions.y = 130;
    draw_rectangle(RecEmplacement,RecDimesions,blanc);
    RecEmplacement.x += 30; RecEmplacement.y += 15;
    affiche_texte_special("Player(s) VS IA",70,RecEmplacement,blanc,"assets/Poppins.ttf");
    RecEmplacement.x = 900; RecEmplacement.y = 420;
    RecDimesions.x = 620; RecDimesions.y = 130;
    draw_rectangle(RecEmplacement,RecDimesions,blanc);
    RecEmplacement.x += 30; RecEmplacement.y += 15;
    affiche_texte_special("PVP FIGHTOUUU !",70,RecEmplacement,blanc,"assets/Poppins.ttf");



    wait_escape();
    return 0;
}
