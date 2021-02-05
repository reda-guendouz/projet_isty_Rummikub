#include "modele.h"

int main(void)
{

    srand(time(NULL));
    unsigned char jeu = TRUE;
    unsigned char partie, tour, selectionTuiles, placerTuile, modifPlateau, victoire;
    int jouer,nbJoueursH, choixJoueur, joueurActuel, numTuileChoisis, choixPlacement, choixModifPlateau,
    colonneSource,  colonneDestination;
    char ligneSource, ligneDestination;
    int selection = 0;
    int estSelectionne[50];
    int nbJoueurs = 4;
    LISTE_TUILES tuilesSelectionnes;
    int premiereMain[nbJoueurs];
    tuilesSelectionnes.nbTuiles = 0;
    TUILE copiePlateau[DIM_PLATEAU_H][DIM_PLATEAU_W];
    TUILE selectionne;

    while (jeu)
    {
        //LANCEMENT DU JEU
        partie = FALSE;
        system("clear");
        printf("Groupe : 8 Rummikub \n");
        printf("1. Lancer un partie \n");
        printf("2. Voir Tableau Score \n");
        printf("3. Quitter le jeu\n");
        jouer = readInt(1,3);
        system("clear");
        //SORTIR DU JEU
        if (jouer == 3)
            jeu = FALSE;
        else if (jouer == 2){
            affiche_score();
            printf("\n");
            printf("1. Lancer un partie \n");
            printf("2. Quitter le jeu\n");
            jouer = readInt(1,2);
            if (jouer == 2)
                jeu = FALSE;
            system("clear");
        }
        //LANCEMENT D'UNE PARTIE
        if(jouer == 1)
        {
            int i = 0;
            for (i = 0; i < 4; i++){
                premiereMain[i]= 1;
            }
            joueurActuel = 0;
            partie = TRUE;
            victoire = FALSE;
            init_pioche();
            // SELECTION DES JOUEURS
            nbJoueurs = -1;
            printf("Combien de joueurs jouent (2 à 4)?\n");
            nbJoueurs = readInt(2,4);
            printf("Combien de humains jouent (1 à %d)?\n",nbJoueurs);
            nbJoueursH = readInt(1,nbJoueurs);
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
                choixJoueur = -1;
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("0. Fin de partie\n");
                printf("1. Jouer \n");
                printf("2. Piocher \n");
                choixJoueur = readInt(0,2);

                //FIN DE PARTIE PREMATURE
                if (choixJoueur == 0)
                    partie = FALSE;
                else if (choixJoueur == 1)
                {
                    tour = TRUE;
                    selectionTuiles = TRUE;
                    while (tour)
                    {
                        int i;
                        for (i=0;i<selection;i++){
                             estSelectionne[i] = -3;
                        }
                        selection = 0;
                        //SELECTION DE TUILE A METTRE SUR LE PLATEAU
                        while (selectionTuiles)
                        {
                            placerTuile = FALSE;
                            numTuileChoisis = -3;
                            
                            do {
                                system("clear");
                                affiche_liste_tuiles(joueurs.js[joueurActuel].chevalet);
                                affiche_plateau(plateau[0]);
                                printf("\nTuile selectionne : \n");
                                affiche_liste_tuiles(tuilesSelectionnes);
                                printf("\n\n");
                                printf("Quelle tuile voulez-vous jouez dans votre chevalet ? (Donnez le numéro de la tuile)\n");
                                printf("(-1). Valider la selection\n");
                                printf("(-2). Piochez et passer son tour\n");
                                numTuileChoisis = readInt(-2,joueurs.js[joueurActuel].chevalet.nbTuiles - 1);
                            }
                            while(est_dans_selection(numTuileChoisis,selection+1,estSelectionne));
                            estSelectionne[selection] = numTuileChoisis;
                            selection++;
                            //ARRETE SON TOUR ET PASSER A LA PIOCHE
                            if (numTuileChoisis == -2)
                            {   
                                tour = FALSE;
                                selectionTuiles = FALSE;
                                modifPlateau = FALSE;
                                choixJoueur = 2;
                            }
                            //PLACER LES TUILES SELECTIONNEES
                            else if (numTuileChoisis == -1)
                            {
                                if (tuilesSelectionnes.nbTuiles > 0)
                                {
                                    if (premiereMain[joueurActuel] && calcul_main(&tuilesSelectionnes) < 30) {
                                        int i;
                                        for (i=0;i<selection;i++){
                                            estSelectionne[i] = -3;
                                        }
                                        selection = 0;
                                        tuilesSelectionnes.nbTuiles = 0;
                                        printf("/************************************************************************\\\n");
                                        printf("Pour votre premiere main, la valeur de celle-ci doit etre suépérieur à 30\n");
                                        printf("\\************************************************************************/\n");
                                        sleep(2);
                                        system("clear");
                                    }
                                    else {
                                        selectionTuiles = FALSE;
                                        placerTuile = TRUE;
                                    }                                    
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
                            suite(&tuilesSelectionnes);
                            printf("Tuiles selectionnees : \n");
                            affiche_liste_tuiles(tuilesSelectionnes);
                            choixPlacement = -3;
                            printf("\nQue voulez-vous faire ?\n");
                            printf("0. Piochez et passer son tour\n");
                            printf("1. Refaire sa selection\n");
                            printf("2. Placer les tuiles sur le plateau\n");
                            choixPlacement = readInt(0,2);
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
                                    colonneSource = readInt(0,DIM_PLATEAU_W);
                                } while (!est_placable(tuilesSelectionnes.nbTuiles, char_to_int(ligneSource), colonneSource));
                                placer_tuiles(tuilesSelectionnes, copiePlateau[0], char_to_int(ligneSource), colonneSource);
                                placerTuile = FALSE;
                                modifPlateau = TRUE;
                                system("clear");
                            }
                        }
                        //MODIFIER LE PLATEAU
                        while (modifPlateau)
                        {
                            affiche_plateau(copiePlateau[0]);
                            choixModifPlateau = -3;
                            printf("Que voulez-vous faire ?\n");
                            printf("0. Piochez et passer son tour\n");
                            printf("1. Refaire sa selection\n");
                            printf("2. Replacer les tuiles sur le plateau\n");
                            printf("3. Valider le plateau et passer son tour\n");
                            printf("4. Modifier le plateau\n");
                            choixModifPlateau = readInt(0,4);
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
                                    if (premiereMain[joueurActuel])
                                        premiereMain[joueurActuel] = 0;
                                    copie_plateau(plateau[0], copiePlateau[0]);
                                    printf("Copie bien passé\n\n");
                                    mettre_a_jour(&joueurs.js[joueurActuel].chevalet, tuilesSelectionnes);
                                    printf("Mise a jour du chevalet bien passé\n\n");
                                    modifPlateau = FALSE;
                                    tour = FALSE;
                                }
                                else
                                {
                                    //system("clear");
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
                                    colonneSource = readInt(0,DIM_PLATEAU_W);
                                    printf("tuile destination :\nligne : ");
                                    scanf(" %c", &ligneDestination);
                                    printf("colonne : ");
                                    colonneDestination = readInt(0,DIM_PLATEAU_W);
                                    if (!intervertion_tuiles(copiePlateau[0], char_to_int(ligneSource), colonneSource, char_to_int(ligneDestination), colonneDestination))
                                    {
                                        printf("Err: mauvaises positions\n");
                                    }
                                    else {
                                        affiche_plateau(copiePlateau[0]);
                                        printf("Voulez-vous continuer ?\n");
                                        printf("0. Non\n");
                                        printf("1. Oui\n");
                                        choixModifPlateau = readInt(0,1);
                                    }
                                } while (choixModifPlateau);
                            }
                        }
                    }
                }
            }
            //TOUR DE L'IA
            else {
                system("clear");
                printf("TOUR DE l'IA\n");
                affiche_joueur(joueurs.js[joueurActuel]);
                affiche_plateau(plateau[0]);
                LISTE_TUILES combinaisonsTrouve;
                combinaisonsTrouve.nbTuiles = 0;
                int i = 0;
                trouver_combinaisons(joueurs.js[joueurActuel].chevalet,&combinaisonsTrouve);
                copie_plateau(copiePlateau[0],plateau[0]);
                if (premiereMain[joueurActuel] && calcul_main(&combinaisonsTrouve) < 30) {
                    printf("AUCUNE COMBINAISONS TROUVE IA PIOCHE \n");
                    piocher(&joueurs.js[joueurActuel].chevalet);
                }
                else {
                    if (combinaisonsTrouve.nbTuiles > 0 && placer_combinaisons(combinaisonsTrouve, copiePlateau[0])) 
                    {
                        printf("COMBINAISONS TROUVE PAR L'IA \n");
                        for(i =0; i<combinaisonsTrouve.nbTuiles; i++){
                            supprime_liste(&joueurs.js[joueurActuel].chevalet,combinaisonsTrouve.pile[i]);
                        }
                        copie_plateau(plateau[0], copiePlateau[0]);  
                        premiereMain[joueurActuel] = 0;
                    } 
                    else {
                        printf("AUCUNE COMBINAISONS TROUVE IA PIOCHE \n");
                        piocher(&joueurs.js[joueurActuel].chevalet);
                    }
                }
                sleep(1);
                choixJoueur = -1;
                system("clear");
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
                tuilesSelectionnes.nbTuiles = 0;
            }
            //FIN DE PARTIE VICTOIRE
            else
            {
                system("clear");
                affiche_victoire(joueurs.js[joueurActuel], joueurActuel);
                printf("Appuyer sur 0 pour revenir au menu\n");
                choixJoueur = readInt(0,0);
                victoire = FALSE;
            }
        }
    }
    return 0;
}