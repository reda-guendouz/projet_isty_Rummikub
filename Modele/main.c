#include "modele.h"
#include <unistd.h>

int main(void)
{

    srand(time(NULL));
    unsigned char jeu = TRUE;
    unsigned char partie, tour, selectionTuiles, placerTuile, modifPlateau, victoire;
    int jouer, nbJoueurs,nbJoueursH, nbJoueursIA, choixJoueur, joueurActuel, numTuileChoisis, choixPlacement, choixModifPlateau,
         colonneSource,  colonneDestination;
    char ligneSource, ligneDestination;
    LISTE_TUILES tuilesSelectionnes;
    tuilesSelectionnes.pile[MAX_TUILES];
    tuilesSelectionnes.nbTuiles = 0;
    TUILE copiePlateau[DIM_PLATEAU_H][DIM_PLATEAU_W];
    TUILE selectionne;

    while (jeu)
    {

        //LANCEMENT DU JEU
        partie = FALSE;
        system("clear");
        do
        {
            printf("Groupe : 8 Rummikub \n");
            printf("1. Lancer un partie \n");
            printf("2. Voir Tableau Score \n");
            printf("3. Quitter le jeu\n");
            scanf(" %d", &jouer);
        } while (jouer < 1 && jouer > 3);
        system("clear");
        //SORTIR DU JEU
        if (jouer == 3)
            jeu = FALSE;
        else if (jouer == 2){
            do
            {
                affiche_score();
                printf("\n");
                printf("1. Lancer un partie \n");
                printf("2. Quitter le jeu\n");
                scanf(" %d", &jouer);
            } while (jouer != 1 && jouer != 2);
            if (jouer == 2)
                jeu = FALSE;
        }
        //LANCEMENT D'UNE PARTIE
        if(jouer == 1)
        {
            joueurActuel = 0;
            partie = TRUE;
            victoire = FALSE;
            init_pioche();
            // SELECTION DES JOUEURS
            nbJoueurs = -1;
            do
            {
                printf("Combien de joueurs jouent ?\n");
                scanf(" %d", &nbJoueurs);
            } while (nbJoueurs < 2 || nbJoueurs > 4);
            do
            {
                printf("Combien de humains jouent ?\n");
                scanf(" %d", &nbJoueursH);
            } while (nbJoueursH < 1 || nbJoueursH > nbJoueurs);
            nbJoueursIA = nbJoueurs - nbJoueursH;
            init_joueurs(nbJoueurs,nbJoueursH);
            system("clear");
        }

        //DANS UNE PARTIE
        while (partie && !victoire)
        {
            //DANS UN TOUR
            affiche_joueur(joueurs.js[joueurActuel]);
            affiche_plateau(plateau[0]);
            printf("JOUEUR %d JOUE\n", joueurActuel+1);
            if (joueurActuel + 1 - nbJoueursH  <= 0 ){
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
                    selectionTuiles = TRUE;
                    while (tour)
                    {
                        //SELECTION DE TUILE A METTRE SUR LE PLATEAU
                        while (selectionTuiles)
                        {
                            placerTuile = FALSE;
                            do
                            {
                                numTuileChoisis = -3;
                                system("clear");
                                affiche_liste_tuiles(joueurs.js[joueurActuel].chevalet);
                                affiche_plateau(plateau[0]);
                                printf("\nTuile selectionne : \n");
                                affiche_liste_tuiles(tuilesSelectionnes);
                                printf("\n\n");
                                printf("Quelle tuile voulez-vous jouez dans votre chevalet ? (Donnez le numéro de la tuile)\n");
                                printf("-1. Valider la selection\n");
                                printf("-2. Piochez et passer son tour\n");
                                scanf(" %d", &numTuileChoisis);
                            } while (numTuileChoisis < -2 || numTuileChoisis > joueurs.js[joueurActuel].chevalet.nbTuiles - 1);
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
                                ajouter_tuile(&tuilesSelectionnes, selectionne);
                            }
                        }
                        //PLACER LES TUILES SELECTIONNEES
                        while (placerTuile)
                        {
                            system("clear");
                            affiche_plateau(plateau[0]);
                            tri_liste(&tuilesSelectionnes);
                            printf("Tuiles selectionnees : \n");
                            affiche_liste_tuiles(tuilesSelectionnes);
                            do
                            {
                                choixPlacement = -3;
                                printf("\nQue voulez-vous faire ?\n");
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
                                tuilesSelectionnes.pile[MAX_TUILES];
                                tuilesSelectionnes.nbTuiles = 0;
                            }
                            //PLACER LES TUILES DANS LE PLATEAU
                            else
                            {
                                copie_plateau(copiePlateau[0], plateau[0]);
                                affiche_plateau(copiePlateau[0]);
                                do
                                {
                                    system("clear");
                                    affiche_plateau(plateau[0]);
                                    printf("Tuiles selectionnees : \n");
                                    affiche_liste_tuiles(tuilesSelectionnes);
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
                                tuilesSelectionnes.pile[MAX_TUILES];
                                tuilesSelectionnes.nbTuiles = 0;
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
                                if (analyse_plateau(copiePlateau[0]))
                                {
                                    copie_plateau(plateau[0], copiePlateau[0]);
                                    printf("Copie bien passé\n\n");
                                    mettre_a_jour(&joueurs.js[joueurActuel].chevalet, tuilesSelectionnes);
                                    printf("Mise a jour du chevalet bien passé\n\n");
                                    modifPlateau = FALSE;
                                    tour = FALSE;
                                }
                                else
                                {
                                    system("clear");
                                    printf("le plateau n'est pas valide\n");
                                }
                            }
                            //MODIFIER LE PLATEAU
                            else if (choixModifPlateau == 4)
                            {
                                do
                                {
                                    system("clear");
                                    affiche_plateau(copiePlateau[0]);
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
            }
            else {
                system("clear");
                printf("TOUR DE l'IA\n");
                affiche_joueur(joueurs.js[joueurActuel]);
                affiche_plateau(plateau[0]);
                choixJoueur = action_tour_ia(joueurs.js[joueurActuel]);
                sleep(5);
            }
            //PIOCHER
            if (choixJoueur == 2)
            {
                piocher(&joueurs.js[joueurActuel].chevalet);
                system("clear");
            }
            //TOUR AU PROCHAIN JOUEUR
            if (!est_victorieux(joueurs.js[joueurActuel]))
            {
                joueurActuel = (joueurActuel + 1) % (joueurs.nbJs);
                tuilesSelectionnes.pile[MAX_TUILES];
                tuilesSelectionnes.nbTuiles = 0;
            }
            else
            {
                system("clear");
                affiche_victoire(joueurs.js[joueurActuel], joueurActuel);
                do
                {
                    printf("Appuyer sur 0 pour revenir au menu\n");
                    scanf(" %d", &choixJoueur);
                } while (choixJoueur != 0);
                victoire = FALSE;
            }
        }
    }
    return 0;
}