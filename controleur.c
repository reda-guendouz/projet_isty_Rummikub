#include "Vue/graphics2.h"


int main(int argc, char const *argv[])
{
    // creation des champs
    POINT rec1,rec2,rec3,rec4,clic;
    int i,j,nbJoueursH;
    BOOL has_ia=false;

    init_pioche();
    init_graphics();

    // menu_debut selection pvp/ia
    affiche_menu_debut();
    rec1.x = 90; rec1.y = 320;
    rec2.x = 640; rec2.y = 450;
    rec3.x = 790; rec3.y = 420;
    rec4.x = 1410; rec4.y = 550;
    do
    {
        clic = wait_clic();
    } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4));
    if (clic.x < 640){
        printf("LETS GO WITH OUR AI !\n");
        has_ia=true;
    }
    else
        printf("WE GO FOR FIGHTOUU !\n");
    nbJoueursH = choix_joueurs();

    init_joueurs(nbJoueursH,nbJoueursH-has_ia);

    for (i = 0; i < nbJoueursH; i++)
        if (!has_ia || i!=3)
            inscription(joueurs.js[i].pseudo,i+1);

    printf("debug -- test creation joueur 1 : %s\n",joueurs.js[0].pseudo);

    fill_screen(noir);

    affiche_auto_off();

    // TEST AFFICHAGE
    TUILE t;
    t.chiffre = 10;
    t.clr = NOIR;
    //affiche_plateau(plateau[0]);
    for (i = 0; i < DIM_PLATEAU_H; i++)
        for (j = 0; j < DIM_PLATEAU_W; j++)
            plateau[i][j] = t;
    // FIN TEST AFFICHAGE
    affiche_plateau_graphique();
    POINT p;
    p.x= 1288; p.y = 540;
    affiche_texte("TESTAS",30,p,blanc);

    affiche_joueur_graphique(1);
    selectionne_tuiles_chevalet(1);
    
    affiche_all();

    wait_escape();
    return 0;
}
