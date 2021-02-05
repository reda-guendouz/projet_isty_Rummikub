#include "Vue/graphics2.h"

int main(int argc, char const *argv[])
{
    // creation des variables du jeu
    POINT rec1,rec2,rec3,rec4,rec5,rec6,rec7,rec8,texteInfo,clic,oldClic,err;
    int i,j,nbJoueursH,nbJoueursIA=0,joueurActuel=0,ligne,colonne;
    BOOL has_ia=false,partie=true,tour=true,tourValide=false,selection=true,modifP=true,modifP2=true;
    LISTE_TUILES selectionnees, combinaisonsTrouve;;
    TUILE copieP[DIM_PLATEAU_H][DIM_PLATEAU_W],tmp;

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
	    err.x = 680; err.y = HEIGHT-30;
        
        texteInfo.x=50; texteInfo.y=350;
        do
        {
            clic = wait_clic();
        } while (!dans_zone(clic, rec1, rec2) && !dans_zone(clic, rec3, rec4) && !dans_zone(clic, rec5, rec6));
        if (dans_zone(clic, rec1, rec2)) // joueur choisit IA
        {
            has_ia = true;
        }
        else if (dans_zone(clic, rec5, rec6)) { // quitter
            quit();
            return 0;
        }
        if(has_ia)
            nbJoueursIA = choix_joueurs(nbJoueursIA,TRUE);
        if(nbJoueursIA<3)
            nbJoueursH = choix_joueurs(nbJoueursIA,FALSE);
        else 
            nbJoueursH = 1;
        init_joueurs(nbJoueursH + nbJoueursIA, nbJoueursH);

        BOOL premieresMains[nbJoueursH+nbJoueursIA];
        for (i = 0; i < joueurs.nbJs; i++)
            premieresMains[i] = true;
        

        for (i = 0; i < nbJoueursH; i++)
            inscription(joueurs.js[i].pseudo, i + 1);

        printf("debug -- test creation joueur %d : %s\n", joueurActuel, joueurs.js[joueurActuel].pseudo);

        affiche_auto_off();
        // bouton valider :
        rec7.x=1360; rec7.y=460;
	    rec8.x=1480; rec8.y=500;
        // ici, rec1 - rec2 : dimensions du plateau
        rec1.x = 294; rec1.y = 34;
        rec2.x = 1294; rec2.y = 506;
        // ici, rec5 - rec6 : bouton piocher
        rec5.x = 1360; rec5.y = 510;
        rec6.x = 1480; rec6.y = 550;
        while (tour)
        {
            fill_screen(noir);
            selection=true;
            modifP=true;
            tourValide=false;
            printf("debug -- IA pseudo : %s || numJoueur\n",joueurs.js[joueurActuel].pseudo,joueurActuel);

            if (joueurActuel + 1 - nbJoueursH  > 0) // tour d'un ia
            {
                /*
                printf("IA IS PLAYING...\n");
                SDL_Delay(500);*/
                combinaisonsTrouve.nbTuiles=0;
                trouver_combinaisons(joueurs.js[joueurActuel].chevalet,&combinaisonsTrouve);
                copie_plateau(copieP[0],plateau[0]);
                if (premieresMains[joueurActuel] && calcul_main(combinaisonsTrouve) < 30) {
                    piocher(&joueurs.js[joueurActuel].chevalet);
                    transition_IA(2);
                }
                else {
                    premieresMains[joueurActuel] = false;
                    if (combinaisonsTrouve.nbTuiles > 0 && placer_combinaisons(combinaisonsTrouve, copieP[0])) 
                    {
                        for(i =0; i<combinaisonsTrouve.nbTuiles; i++){
                            supprime_liste(&joueurs.js[joueurActuel].chevalet,combinaisonsTrouve.pile[i]);
                        }
                        copie_plateau(plateau[0], copieP[0]);
                        transition_IA(1);
                    } 
                    else {
                        piocher(&joueurs.js[joueurActuel].chevalet);
                        transition_IA(2);
                    }
                }
            } else // tour d'un joueur H
            {
                while (selection)
                {
                    fill_screen(noir);
                    // PHASE SELECTION TUILES
                    //// ne pas oublier de supprimer LISTE-TUILES selectionnees et copieP
                    mettre_a_jour(&selectionnees,selectionnees); // vide tuiles selectionnees
                    rec4.x=120; rec4.y=40;
                    rec3.x=50; rec3.y=200;
                    draw_fill_rectangle(rec3,rec4,noir); // supprimer "refaire"

                    copie_plateau(copieP[0],plateau[0]);
                    affiche_plateau_graphique(copieP[0]);
                    affiche_joueur_graphique(joueurActuel);
    
                    affiche_all();
                    affiche_info_tour(1);
                    if(selectionne_tuiles_chevalet(joueurActuel,&selectionnees,&premieresMains[joueurActuel])){
                        selection=false;
                        //// afficher texte : "Ou voulez-vous mettre vos tuiles ?" (sur deux 'lignes' surement)
                        // choix placement tuile :
                        draw_rectangle(rec3,rec4,blanc);
                        rec3.x+=10; rec3.y+=10;
                        affiche_texte("Refaire",20,rec3,blanc);
                        rec3.x-=10; rec3.y-=10;
                        rec4.x+=rec3.x; rec4.y+=rec3.y;
                        affiche_info_tour(2);
                        affiche_all();
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
                                    affiche_plateau_graphique_slow(copieP[0]);
                                    affiche_info_tour(3);
                                    affiche_all();
                                    do
                                    {
                                        clic=wait_clic();
                                    } while (!dans_zone(clic,rec7,rec8) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6)); // valider - refaire - piocher
                                    if (dans_zone(clic,rec7,rec8)) // choix - valider
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
                                    }
                                } else{ // retour a la selection
                                    selection = true;
                                    printf("reda is dommed\n");
                                    affiche_texte("Erreur : votre liste ne peut se mettre ici",25,err,rouge);
                                    SDL_Delay(1200);
                                    //// afficher "erreur: votre liste ne peut se mettre ici"
                                }
                            } else
                                selection=true;
                        } else if (dans_zone(clic,rec5,rec6)) // choix - piocher
                        {
                            piocher(&joueurs.js[joueurActuel].chevalet);
                            selection = false;
                            modifP=false;
                            break;
                        } else if (dans_zone(clic,rec3,rec4)){ // choix - refaire
                            selection=true;
                            modifP=false;
                        }
                    } else // choix - piocher
                    {
                        piocher(&joueurs.js[joueurActuel].chevalet);
                        printf("piocher");
                        selection = false;
                        modifP=false;
                        break;
                    }
                    
                    // PHASE MODIFICATION PLATEAU
                    while(modifP){
                        affiche_joueur_graphique(joueurActuel);
                        affiche_info_tour(4);
                        affiche_all();
                        do
                        {
                            clic = wait_clic();
                            printf("debug -- modifP\n");
                        } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6) && !dans_zone(clic,rec7,rec8));//plateau - refaire - piocher - valider
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
                            break;
                        } else // valider
                        {
                            if(analyse_plateau(copieP[0])){
                                tourValide=true;
                                modifP2=false;
                                modifP=false;
                                selection=false;
                                break;
                            } else
                            {
                                //// afficher : "erreur : placement de tuiles invalides"
                                affiche_texte("Erreur : Votre plateau n'est pas valide",25,err,rouge);

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
                                break;
                            } else // valider
                            {
                                if(analyse_plateau(copieP[0])){
                                    modifP2=false;
                                    modifP=false;
                                    selection=false;
                                    tourValide=true;
                                    continue;
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
                            } while (!dans_zone(clic,rec1,rec2) && !dans_zone(clic,rec3,rec4) && !dans_zone(clic,rec5,rec6) && !dans_zone(clic,rec7,rec8));//plateau - refaire - piocher - valider
                            if (dans_zone(clic,rec1,rec2)) // plateau intervertion 1
                            {
                                choix_case_plateau(clic,&ligne,&colonne);
                                tmp = copieP[ligne][colonne];
                                oldClic.x=ligne;
                                oldClic.y=colonne;
                            } else if (dans_zone(clic,rec3,rec4)) // refaire
                            {
                                printf("refaire\n");
                                modifP2=false;
                                modifP=true;
                                break;
                            } else if (dans_zone(clic,rec5,rec6)) // piocher
                            {
                                piocher(&joueurs.js[joueurActuel].chevalet);
                                selection = false;
                                modifP=false;
                                break;
                            } else // valider
                            {
                                if(analyse_plateau(copieP[0])){
                                    modifP2=false;
                                    modifP=false;
                                    selection=false;
                                    tourValide=true;
                                    break;
                                } else
                                {
                                    //// afficher : "erreur : placement de tuiles invalides"
                                    return 0;
                                }
                            }
                        } // end modifP2
                    } // end modifP
                } // end selection
            } // end else tour joueur H
                        
            affiche_all();
            if (tourValide){
                copie_plateau(plateau[0],copieP[0]);
                if (est_victorieux(joueurs.js[joueurActuel])){
                    affiche_victoire_graphique(joueurActuel);
                    score_fin_partie(joueurActuel);
                }
                mettre_a_jour(&joueurs.js[joueurActuel].chevalet,selectionnees);
            }
            joueurActuel = (joueurActuel+1)%joueurs.nbJs;
            if (joueurActuel + 1 - nbJoueursH  <= 0)
                transition(joueurActuel+1);
        } // end tour
        

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
    quit();
    return 0;
}
