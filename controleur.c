#include "Vue/graphics2.h"


int main(int argc, char const *argv[])
{
    // creation des champs
    POINT rec1,rec2,rec3,rec4,clic;
    int i,j,nbJoueursH,joueurActuel=0,ligne,colonne;
    BOOL has_ia=false,partie=true,tour=true,tourValide=false,selection=true,modifP=true;
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

        affiche_auto_off();

        while (tour)
        {
            fill_screen(noir);
            selection=true;
            if (has_ia && strcmp(joueurs.js[joueurActuel].pseudo,"IA"))
            {
                printf("IA IS PLAYING...\n");
                SDL_Delay(500);
            } else
            {
                while (selection)
                {
                    // PHASE SELECTION TUILES
                    //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
                    selectionnees.pile[MAX_TUILES]; // cense vider la pile, a tester

                    copie_plateau(copieP[0],plateau[0]);
                    affiche_plateau_graphique(copieP[0]);
                    affiche_joueur_graphique(joueurActuel);
                    affiche_all();
                    if(selectionne_tuiles_chevalet(joueurActuel,&selectionnees)){
                        selection=false;
                        //// afficher texte : "Ou voulez-vous mettre vos tuiles ?" (sur deux 'lignes' surement)
                        // choix placement tuile :
                        rec3.x=50; rec3.y=200;
                        rec4.x=120; rec4.y=40;
                        draw_rectangle(rec3,rec4,blanc);
                        rec1.x+=10; rec1.y+=10;
                        affiche_texte("Refaire",20,rec1,blanc);
                        affiche_all();
                        // rec1 - rec2 : dimensions du plateau
                        rec1.x = 294; rec1.y = 34;
                        rec2.x = 1294; rec2.y = 506;
                        do
                        {
                            clic=wait_clic();
                        } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4));
                        if (dans_zone(clic,rec1,rec2)) // choix - placement tuiles
                        {
                            choix_case_plateau(clic,&ligne,&colonne);

                            if (est_placable(selectionnees.nbTuiles,ligne,colonne)) // placement tuile :
                            {
                                placer_tuiles(selectionnees,copieP[0],ligne,colonne);
                                affiche_plateau_graphique(copieP[0]);
                                affiche_all();
                            } else{ // retour a la selection
                                selection = true;
                                //// afficher "erreur: votre liste ne peut se mettre ici"
                            }
                        } else // choix - refaire
                            selection=true;
                        
                    } else // choix - piocher
                    {
                        piocher(&joueurs.js[joueurActuel].chevalet);
                        selection = false;
                    }
                    
                    /// bouton refaire => continue;
                    // PHASE SELECTION/MODIFICATION PLATEAU
                    while(modifP){
                        affiche_modif_plateau(copieP[0],joueurActuel);
                        rec3.x = 294; rec3.y = 34;
                        rec4.x = 1294; rec4.y = 506;
                        do
                        {
                            clic=wait_clic();
                        } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4));
                        choix_case_plateau(clic,&ligne,&colonne);
                        /// bouton refaire plateau => continue;
                        /// bouton retour selection => break;
                        // VALIDATION DU JOUEUR
                        // PHASE VERIFICATION (implicite/caché)
                        /// if (toutEstBon) selection = false; plateau = false;
                        /// else break; // retour a la selection
                    }
                }
            }

            
            affiche_all();
            if (tourValide){
                copie_plateau(plateau[0],copieP[0]);
                joueurActuel++;
            }
        }

    }
    wait_escape();
    return 0;
}
