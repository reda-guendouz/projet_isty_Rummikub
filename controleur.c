#include "Vue/graphics2.h"
#include "Modele/modele.h"

int main(int argc, char const *argv[])
{
    POINT rec1,rec2,rec3,rec4,clic;
    init_graphics();

    affiche_menu_debut();
    rec1.x = 90; rec1.y = 320;
    rec2.x = 640; rec2.y = 450;
    rec3.x = 790; rec3.y = 420;
    rec4.x = 1410; rec4.y = 550;
    do
    {
        clic = wait_clic();
    } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4));
    if (clic.x < 640)
        printf("LETS GO WITH OUR AI !\n");
    else
        printf("WE GO FOR FIGHTOUU !\n");    

    wait_escape();
    return 0;
}
