#include "Vue/graphics2.h"

int main(int argc, char const *argv[])
{
    POINT rec1,rec2,rec3,rec4,clic;
    char pseudo[MAX_PSEUDONYME];
    int i,j;


    init_pioche();
    init_joueurs(2,2);
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
    
    inscription(pseudo);
    fill_screen(noir);

    affiche_auto_off();

    // TEST AFFICHAGE
    TUILE t;
    t.chiffre = 10;
    t.clr = NOIR;
    //affiche_plateau(plateau[0]);
    for (i = 0; i < DIM_PLATEAU_H; i++)
        for (j = 0; j < DIM_PLATEAU_W; j++)
            plateau[0][(int unsigned)(i * DIM_PLATEAU_W + j)] = t;
    // FIN TEST AFFICHAGE
    affiche_plateau_graphique();
    

    affiche_joueur_graphique(1);
    

    affiche_all();

    wait_escape();
    return 0;
}
