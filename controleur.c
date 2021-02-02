#include "Vue/graphics2.h"


int main(int argc, char const *argv[])
{
    // creation des champs
    POINT rec1,rec2,rec3,rec4,clic;
    int i,j,nbJoueursH,joueurActuel=0;
    BOOL has_ia=false,partie=true,tour=true,tourValide=false,selection;
    LISTE_TUILES selectionnees;
    TUILE copieP[DIM_PLATEAU_H][DIM_PLATEAU_W];

    init_pioche();
    init_graphics();
    while (partie)
    {
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

        printf("debug -- test creation joueur %d : %s\n",joueurActuel,joueurs.js[joueurActuel].pseudo);

        fill_screen(noir);

        affiche_auto_off();

        while (tour)
        {
            fill_screen(noir);

            copie_plateau(copieP[0],plateau[0]);

            affiche_plateau_graphique(copieP[0]);
            affiche_joueur_graphique(joueurActuel);
            affiche_all();
            while (selection)
            {
                // PHASE SELECTION TUILES
                //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
                selectionne_tuiles_chevalet(joueurActuel,&selectionnees);
                /// bouton refaire => continue;
                // PHASE SELECTION/MODIFICATION PLATEAU
                /// while(plateau){
                    //// ne pas oublier de supprimer copieP
                    /// bouton refaire plateau => continue;
                    /// bouton retour selection => break;
                    // VALIDATION DU JOUEUR
                    // PHASE VERIFICATION (implicite/caché)
                    /// if (toutEstBon) selection = false; plateau = false;
                    /// else break; // retour a la selection
                /// }
            }

            
            affiche_all();
            if (tourValide)
                copie_plateau(plateau[0],copieP[0]);
        }

    }
    wait_escape();
    return 0;
}
