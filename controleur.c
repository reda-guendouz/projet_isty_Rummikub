#include "Vue/graphics2.h"

int main(int argc, char const *argv[])
{
    // creation des variables du jeu
    POINT rec1,rec2,rec3,rec4,rec5,rec6,rec7,rec8,texteInfo,clic,oldClic;
    int i,j,nbJoueursH,joueurActuel=0,ligne,colonne;
    BOOL has_ia=false,partie=true,tour=true,tourValide=false,selection=true,modifP=true,modifP2=true;
    LISTE_TUILES selectionnees;
    TUILE copieP[DIM_PLATEAU_H][DIM_PLATEAU_W],tmp;

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
        rec7.x=1200; rec7.y=600;
        rec8.x=1320; rec8.y=640;
        texteInfo.x=50; texteInfo.y=350;
        do
        {
            clic = wait_clic();
        } while (!dans_zone(clic, rec1, rec2) && !dans_zone(clic, rec3, rec4));
        if (clic.x < 640) // joueur choisit IA
        {
            printf("debug -- LETS GO WITH OUR AI !\n");
            has_ia = true;
        }
        else
            printf("debug -- WE GO FOR FIGHTOUU !\n");
        nbJoueursH = choix_joueurs();

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
                    fill_screen(noir);
                    printf("debug -- selection\n");
                    // PHASE SELECTION TUILES
                    //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
                    selectionnees.nbTuiles=0; // cense vider la pile, a tester
                    rec4.x=120; rec4.y=40;
                    rec3.x=50; rec3.y=200;
                    draw_fill_rectangle(rec3,rec4,noir);

                    copie_plateau(copieP[0],plateau[0]);
                    affiche_plateau_graphique(copieP[0]);
                    affiche_joueur_graphique(joueurActuel);
                    affiche_all();
                    if(selectionne_tuiles_chevalet(joueurActuel,&selectionnees)){
                        selection=false;
                        //// afficher texte : "Ou voulez-vous mettre vos tuiles ?" (sur deux 'lignes' surement)
                        // choix placement tuile :
                        draw_rectangle(rec3,rec4,blanc);
                        rec3.x+=10; rec3.y+=10;
                        affiche_texte("Refaire",20,rec3,blanc);
                        rec3.x-=10; rec3.y-=10;
                        rec4.x+=rec3.x; rec4.y+=rec3.y;
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
                                    do
                                    {
                                        clic=wait_clic();
                                    } while (!dans_zone(clic,rec7,rec8) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6)); // valider - refaire - piocher
                                    if (dans_zone(clic,rec7,rec8)) // valider
                                    {
                                        modifP=true;
                                    } else if (dans_zone(clic,rec3,rec4)) // refaire
                                    {
                                        selection=true;
                                        modifP=false;
                                    } else if (dans_zone(clic,rec5,rec6)) // piocher
                                    {
                                        piocher(&joueurs.js[joueurActuel].chevalet);
                                        selection = false;
                                        modifP=false;
                                        tourValide=false;
                                    }
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
                        } else if (dans_zone(clic,rec3,rec4)){ // choix - refaire
                            selection=true;
                            modifP=false;
                        }
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
                        printf("debug -- modifP\n");
                        affiche_joueur_graphique(joueurActuel);
                        affiche_all();
                        do
                        {
                            clic = wait_clic();
                            printf("debug -- modifP\n");
                        } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6) && !dans_zone(clic,rec5,rec6));//plateau - refaire - piocher - valider
                        if (dans_zone(clic,rec1,rec2)) // plateau intervertion 1
                        {
                            choix_case_plateau(clic,&ligne,&colonne);
                            tmp = copieP[ligne][colonne];
                            oldClic.x=ligne;
                            oldClic.y=colonne;
                            modifP2=true;
                        } else if (dans_zone(clic,rec3,rec4)) // refaire
                        {
                            modifP2=false;
                            modifP=false;
                            selection=true;
                            break;
                        } else if (dans_zone(clic,rec5,rec6)) // piocher
                        {
                            piocher(&joueurs.js[joueurActuel].chevalet);
                            selection = false;
                            modifP=false;
                            tourValide=false;
                            break;
                        } else // valider
                        {
                            if(analyse_plateau(copieP[0])){
                                copie_plateau(plateau[0],copieP[0]);
                                modifP2=false;
                                modifP=false;
                                selection=false;
                                continue;
                            } else
                            {
                                //// afficher : "erreur : placement de tuiles invalides"
                                return 0;
                            }
                        }
                        while(modifP2){
                            printf("debug -- modifP2\n");
                            do
                            {
                                clic = wait_clic();
                            printf("debug -clic- modifP2\n");
                            } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6) && !dans_zone(clic,rec7,rec8));//plateau - refaire - piocher - valider
                            if (dans_zone(clic,rec1,rec2)) // plateau intervertion 2
                            {
                                choix_case_plateau(clic,&ligne,&colonne);
                                copieP[oldClic.x][oldClic.y] = copieP[ligne][colonne];
                                copieP[ligne][colonne] = tmp;
                                affiche_plateau_graphique(copieP[0]);
                                affiche_all();
                            } else if (dans_zone(clic,rec3,rec4)) // refaire
                            {
                                modifP2=false;
                                modifP=true;
                                printf("refaire\n");
                                continue;
                            } else if (dans_zone(clic,rec5,rec6)) // piocher
                            {
                                piocher(&joueurs.js[joueurActuel].chevalet);
                                selection = false;
                                modifP=false;
                                tourValide=false;
                                break;
                            } else // valider
                            {
                                if(analyse_plateau(copieP[0])){
                                    copie_plateau(plateau[0],copieP[0]);
                                    modifP2=false;
                                    modifP=false;
                                    selection=false;
                                    break;
                                } else
                                {
                                    //// afficher : "erreur : placement de tuiles invalides"
                                    return 0;
                                }
                            }
                            printf("debug -- modifP2 2eme tour\n");
                            do
                            {
                                clic = wait_clic();
                            printf("debug -clic- modifP2 2eme tour\n");
                            } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6) && !dans_zone(clic,rec5,rec6));//plateau - refaire - piocher - valider
                            if (dans_zone(clic,rec1,rec2)) // plateau intervertion 1
                            {
                                choix_case_plateau(clic,&ligne,&colonne);
                                tmp = copieP[ligne][colonne];
                                oldClic.x=ligne;
                                oldClic.y=colonne;
                            } else if (dans_zone(clic,rec3,rec4)) // refaire
                            {
                                modifP2=false;
                                modifP=true;
                                break;
                            } else if (dans_zone(clic,rec5,rec6)) // piocher
                            {
                                piocher(&joueurs.js[joueurActuel].chevalet);
                                selection = false;
                                modifP=false;
                                tourValide=false;
                            } else // valider
                            {
                                if(analyse_plateau(copieP[0])){
                                    copie_plateau(plateau[0],copieP[0]);
                                    modifP2=false;
                                    modifP=false;
                                    selection=false;
                                    break;
                                } else
                                {
                                    //// afficher : "erreur : placement de tuiles invalides"
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }

            //// victoire su joueur X ???
            affiche_all();
            if (tourValide){
                copie_plateau(plateau[0],copieP[0]);
            }
            joueurActuel = (joueurActuel+1)%joueurs.nbJs;
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

        ///// fin de partie
    }
    wait_escape();
    return 0;
}
