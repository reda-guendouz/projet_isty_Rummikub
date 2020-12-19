#include "modele.h"

int main(void)
{
    srand(time(NULL));
    unsigned char jeu = TRUE;
    unsigned char partie, tour, selectionTuiles, placerTuile, modifPlateau;
    int jouer, nbJoueurs, choixJoueur, joueurActuel, numTuileChoisis, choixPlacement, choixModifPlateau,
    ligneSource, colonneSource, ligneDestination, colonneDestination;
    LISTE_TUILES tuilesSelectionnes;
    TUILE copiePlateau[DIM_PLATEAU_H][DIM_PLATEAU_W];
    TUILE selectionne;

    while (jeu)
    {

        //LANCEMENT DU JEU
        partie = FALSE;
        do
        {
            printf("Groupe : 8 Rummikub \n");
            printf("1. Lancer un partie \n");
            printf("2. Quitter le jeu\n");
            scanf(" %d", &jouer);
        } while (jouer != 1 && jouer != 2);
        system("clear");
        //SORTIR DU JEU
        if (jouer == 2)
            jeu = FALSE;

        //LANCEMENT D'UNE PARTIE
        else
        {
            joueurActuel = 0;
            partie = TRUE;
            init_pioche();
            // SELECTION DES JOUEURS
            do
            {
                nbJoueurs = -1;
                printf("Combien de joueurs jouent ?\n");
                scanf(" %d", &nbJoueurs);
            } while (nbJoueurs < 2 || nbJoueurs > 4);
            init_joueurs(nbJoueurs);
        }

        //DANS UNE PARTIE
        while (partie)
        {
            //DANS UN TOUR
            affiche_joueur(joueurs.js[joueurActuel]);
            affiche_plateau(plateau[0]);
            printf("JOUEUR %d JOUE\n", joueurActuel);
            do
            {
                choixJoueur = -1;
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("0. Fin de partie\n");
                printf("1. Jouer \n");
                printf("2. Piocher \n");
                scanf(" %d", &choixJoueur);
            } while (choixJoueur < 0 || choixJoueur > 2);

            //FIN DE PARTIE PREMATURE
            if (choixJoueur == 0)
                partie = FALSE;
            else if (choixJoueur == 1)
            {
                tour = TRUE;
                while (tour)
                {
                    selectionTuiles = TRUE;
                    tuilesSelectionnes.pile[MAX_TUILES];
                    tuilesSelectionnes.nbTuiles = 0;
                    placerTuile = FALSE;
                    //SELECTION DE TUILE A METTRE SUR LE PLATEAU
                    while (selectionTuiles)
                    {
                        do
                        {
                            numTuileChoisis = -3;
                            printf("Quelle tuile voulez-vous jouez dans votre chevalet ?\n");
                            printf("-1. Valider la selection\n");
                            printf("-2. Piochez et passer son tour\n");
                            scanf(" %d", &numTuileChoisis);
                        } while (numTuileChoisis < -2 || numTuileChoisis > joueurs.js[joueurActuel].chevalet.nbTuiles);
                        //ARRETE SON TOUR ET PASSER A LA PIOCHE
                        if (numTuileChoisis == -2)
                        {
                            tour = FALSE;
                            selectionTuiles = FALSE;
                            choixJoueur = 2;
                        }
                        //PLACER LES TUILES SELECTIONNEES
                        else if (numTuileChoisis == -1)
                        {
                            if (tuilesSelectionnes.nbTuiles > 0)
                            {
                                selectionTuiles = FALSE;
                                placerTuile = TRUE;
                            }
                            else
                                printf("Selectionner au moins une tuile avant de valider la selection\n");
                        }
                        //RECUPERER LA TUILE SELECTIONNEE
                        else
                        {
                            selectionne = joueurs.js[joueurActuel].chevalet.pile[numTuileChoisis];
                            if (ajouter_tuile(&tuilesSelectionnes, selectionne))
                            {
                                printf("\nTuile selectionne : \n");
                                affiche_tuile(selectionne, 555);
                                printf("\n\n");
                            }
                            else
                                printf("\nVous avez déjà sélectionné cette tuile\n\n");
                        }
                    }
                    //PLACER LES TUILES SELECTIONNEES
                    while (placerTuile)
                    {
                        tri_liste(&tuilesSelectionnes);
                        printf("Tuiles selectionnees : \n");
                        affiche_liste_tuiles(tuilesSelectionnes);
                        do
                        {
                            choixPlacement = -3;
                            printf("Que voulez-vous faire ?\n");
                            printf("0. Piochez et passer son tour\n");
                            printf("1. Refaire sa selection\n");
                            printf("2. Placer les tuiles sur le plateau\n");
                            scanf(" %d", &choixPlacement);
                        } while (choixPlacement < 0 || choixPlacement > 2);
                        //ARRETE SON TOUR ET PASSER A LA PIOCHE
                        if (choixPlacement == 0)
                        {
                            placerTuile = FALSE;
                            tour = FALSE;
                            choixJoueur = 2;
                        }
                        //RECOMMENCER LA SELECTION DE TUILE
                        else if (choixPlacement == 1)
                        {
                            placerTuile = FALSE;
                            selectionTuiles = TRUE;
                        }
                        //PLACER LES TUILES DANS LE PLATEAU
                        else
                        {
                            copie_plateau(copiePlateau[0], plateau[0]);
                            affiche_plateau(copiePlateau[0]);
                            do
                            {
                                printf("Où voulez-vous placer vos tuiles selectionnes ?\n ligne : ");
                                scanf(" %c", &ligneSource);
                                printf("colonne : ");
                                scanf(" %d", &colonneSource);
                            } while (!est_placable(tuilesSelectionnes.nbTuiles, char_to_int(ligneSource), colonneSource));
                            placer_tuiles(tuilesSelectionnes, copiePlateau[0], char_to_int(ligneSource), colonneSource);
                            placerTuile = FALSE;
                            modifPlateau = TRUE;
                        }
                    }
                    //MODIFIER LE PLATEAU
                    while (modifPlateau)
                    {
                        affiche_plateau(copiePlateau[0]);
                        do
                        {
                            choixModifPlateau = -3;
                            printf("Que voulez-vous faire ?\n");
                            printf("0. Piochez et passer son tour\n");
                            printf("1. Refaire sa selection\n");
                            printf("2. Replacer les tuiles sur le plateau\n");
                            printf("3. Valider le plateau et passer son tour\n");
                            printf("4. Modifier le plateau\n");
                            scanf(" %d", &choixModifPlateau);
                        } while (choixPlacement < 0 || choixPlacement > 4);
                        //ARRETE SON TOUR ET PASSER A LA PIOCHE
                        if (choixModifPlateau == 0)
                        {
                            modifPlateau = FALSE;
                            tour = FALSE;
                            choixJoueur = 2;
                        }
                        //RECOMMENCER LA SELECTION DE TUILE
                        else if (choixModifPlateau == 1)
                        {
                            modifPlateau = FALSE;
                            selectionTuiles = TRUE;
                        }
                        //REFAIRE LE PLACEMENT DES TUILES
                        else if (choixModifPlateau == 2)
                        {
                            modifPlateau = FALSE;
                            selectionTuiles = FALSE;
                            placerTuile = TRUE;
                        }
                        //VALIDER ET TESTER LE PLATEAU
                        else if (choixModifPlateau == 3)
                        {
                            printf("VALIDATION EN COURS\n\n");
                            if (analyse_plateau(copiePlateau[0])){
                                copie_plateau(plateau[0],copiePlateau[0]);
                                printf("copie bien passé\n\n");
                                mettre_a_jour(&joueurs.js[joueurActuel].chevalet,tuilesSelectionnes);
                                printf("mise a jour passée du chevalet\n\n");
                                modifPlateau = FALSE;
                                tour = FALSE;
                            }
                            else 
                                printf("le plateau n'est pas valide\n");
                        }
                        //MODIFIER LE PLATEAU
                        else if (choixModifPlateau == 4)
                        {
                            do
                            {
                                printf("Quelles tuiles voulez-vous intervertir ?\ntuile source :\nligne : ");
                                scanf(" %c", &ligneSource);
                                printf("colonne : ");
                                scanf(" %d", &colonneSource);
                                printf("tuile destination :\nligne : ");
                                scanf(" %c", &ligneDestination);
                                printf("colonne : ");
                                scanf(" %d", &colonneDestination);
                                if (!intervertion_tuiles(copiePlateau[0], char_to_int(ligneSource), colonneSource, char_to_int(ligneDestination), colonneDestination))
                                {
                                    printf("Err: mauvaises positions\n");
                                }
                                affiche_plateau(copiePlateau[0]);
                                printf("Voulez-vous continuer ?\n");
                                printf("0. Non\n");
                                printf("1. Oui\n");
                                scanf(" %d", &choixModifPlateau);
                            } while (choixModifPlateau);
                        }
                    }
                }
            }

            //PIOCHER
            if (choixJoueur == 2)
            {
                system("cls");
                piocher(&joueurs.js[joueurActuel].chevalet);
                affiche_joueur(joueurs.js[joueurActuel]);
            }
            //TOUR AU PROCHAIN JOUEUR
            joueurActuel = (joueurActuel + 1) % (joueurs.nbJs);
        }
    }
    return 0;
}