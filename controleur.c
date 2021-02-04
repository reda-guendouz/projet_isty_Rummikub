#include "Vue/graphics2.h"

int main(int argc, char const *argv[])
{
    // creation des variables du jeu
    POINT rec1,rec2,rec3,rec4,rec5,rec6,texteInfo,clic;
    int i,j,nbJoueursH,nbJoueursIA=0,joueurActuel=0,ligne,colonne;
    BOOL has_ia=false,partie=true,tour=true,tourValide=false,selection=true,modifP=true;
    LISTE_TUILES selectionnees;
    TUILE copieP[DIM_PLATEAU_H][DIM_PLATEAU_W];

    init_pioche();
    init_graphics();
    while (partie)
    {
        // menu_debut selection pvp/ia
        affiche_menu_debut();
        rec1.x = 250; rec1.y = 320;
        rec2.x = 620; rec2.y = 400;
        rec3.x = 850; rec3.y = 420;
        rec4.x = 1375; rec4.y = 500;
        rec5.x = 730; rec5.y = 600;
        rec6.x = 800; rec6.y = 630;
        texteInfo.x=50; texteInfo.y=350;
        do
        {
            clic = wait_clic();
        } while (!dans_zone(clic, rec1, rec2) && !dans_zone(clic, rec3, rec4) && !dans_zone(clic, rec5, rec6));
        if (dans_zone(clic, rec1, rec2)) // joueur choisit IA
        {
            has_ia = true;
        }
        else if (dans_zone(clic, rec5, rec6)) {
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return 0;
        }
        if(has_ia)
            nbJoueursIA = choix_joueurs(nbJoueursIA,TRUE);
        if(nbJoueursIA<3)
            nbJoueursH = choix_joueurs(nbJoueursIA,FALSE);
        else 
            nbJoueursH = 1;

        init_joueurs(nbJoueursH + has_ia, nbJoueursH);

        for (i = 0; i < nbJoueursH; i++)
            if ((!has_ia || i != 3)/* && (has_ia || i!=0)*/) // 4 jrs + ia = impossible && 1 jr sans ia = impossible
                inscription(joueurs.js[i].pseudo, i + 1);

        printf("debug -- test creation joueur %d : %s\n", joueurActuel, joueurs.js[joueurActuel].pseudo);

        affiche_auto_off();

        while (tour)
        {
            fill_screen(noir);
            selection=true;
            modifP=true;
            printf("debug -- IA pseudo : %s || numJoueur\n",joueurs.js[joueurActuel].pseudo,joueurActuel);

            if (has_ia && !strcmp(joueurs.js[joueurActuel].pseudo,"IA")) // tour d'un ia
            {
                printf("IA IS PLAYING...\n");
                SDL_Delay(500);
            } else // tour d'un joueur H
            {
                while (selection)
                {

                    // PHASE SELECTION TUILES
                    //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
                    selectionnees.nbTuiles=0; // cense vider la pile, a tester

                    copie_plateau(copieP[0],plateau[0]);
                    affiche_plateau_graphique(copieP[0]);
                    affiche_joueur_graphique(joueurActuel);
                    affiche_all();
                    if(selectionne_tuiles_chevalet(joueurActuel,&selectionnees)){
                        selection=false;
                        printf("debug -- selection tuiles\n");
                        //// afficher texte : "Ou voulez-vous mettre vos tuiles ?" (sur deux 'lignes' surement)
                        // choix placement tuile :
                        rec4.x=120; rec4.y=40;
                        rec3.x=50; rec3.y=200;
                        draw_rectangle(rec3,rec4,blanc);
                        rec3.x+=10; rec3.y+=10;
                        affiche_texte("Refaire",20,rec3,blanc);
                        rec3.x-=10; rec3.y-=10;
                        affiche_all();
                        // ici, rec1 - rec2 : dimensions du plateau
                        rec1.x = 294; rec1.y = 34;
                        rec2.x = 1294; rec2.y = 506;
                        // ici, rec5 - rec6 : bouton piocher
                        rec5.x = 1190; rec5.y = 640;
                        rec6.x = 1310; rec6.y = 680;
                        do
                        {
                            clic=wait_clic();
                        } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6));//plateau - refaire - piocher
                        if (dans_zone(clic,rec1,rec2)) // choix - placement tuiles
                        {
                            if (selectionnees.nbTuiles!=0)
                            {
                                choix_case_plateau(clic,&ligne,&colonne);
                                if (est_placable(selectionnees.nbTuiles,ligne,colonne)) // placement tuile :
                                {
                                    placer_tuiles(selectionnees,copieP[0],ligne,colonne);
                                    affiche_plateau_graphique(copieP[0]);
                                    affiche_all();
                                    modifP=true;
                                } else{ // retour a la selection
                                    selection = true;
                                    //// afficher "erreur: votre liste ne peut se mettre ici"
                                }
                            } else
                                selection=true;
                        } else if (dans_zone(clic,rec5,rec6)) // choix - piocher
                        {
                            piocher(&joueurs.js[joueurActuel].chevalet);
                            selection = false;
                            modifP=false;
                            tourValide=false;
                        } else  // choix - refaire
                            selection=true;
                        
                    } else // choix - piocher
                    {
                        piocher(&joueurs.js[joueurActuel].chevalet);
                        selection = false;
                        modifP=false;
                        tourValide=false;
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
            }
            joueurActuel= (joueurActuel+1)%joueurs.nbJs;
        }
        

        // PHASE SELECTION TUILES
        //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
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

        affiche_all();
        if (tourValide)
            copie_plateau(plateau[0], copieP[0]);
    }
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
