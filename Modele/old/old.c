#include "modele.h"

int main(void)
{
    srand(time(NULL));
    int nbJoueurs, choixJoueur;
    int joueurActuel = 0;
    int choix = -3;
    char l,l2;
    int c,c2;
    int choixModifPlateau=-1;
    int choixContinuer;
    unsigned char tour = TRUE;
    unsigned char partie = TRUE;
    LISTE_TUILES tuiles_selectionnes;
    TUILE temp[DIM_PLATEAU_H][DIM_PLATEAU_W];
    TUILE selectionne;
    init_pioche();

    // SELECTION DES JOUEURS
    do
    {
        nbJoueurs = -1;
        printf("Combien de joueurs jouent ?\n");
        scanf(" %d", &nbJoueurs);
    } while (nbJoueurs < 2 || nbJoueurs > 4);
    init_joueurs(nbJoueurs);
    

    /* TEST SCORE
    
    LISTE_TUILES jeu;
    jeu.nbTuiles=0;
    joueurs.js[0].chevalet=jeu;

    affiche_joueurs();
    score_fin_partie(0);

    int i;
    for(i=0;i<3;i++) {
        score_fin_partie(0);
    }
    for(i=0;i<joueurs.nbJs;i++) {
        printf("Joueur %d : score = %d\n",i,joueurs.scores[i]);
    }*/
    
    // PARTIE EN COURS
    while (partie)
    {
        while (tour)
        {
            do
            {
                system("clear");
                choixJoueur = -1;
                affiche_joueur(joueurs.js[joueurActuel]);
                affiche_plateau(plateau[0]);
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("1. Jouer \n");
                printf("2. Piocher \n");
                printf("3. fin de partie\n");
                scanf(" %d", &choixJoueur);
            } while (choixJoueur < 1 || choixJoueur > 3);
            if (choixJoueur == 1)
            {
                printf("JOUEUR %d JOUE\n",joueurActuel);
                choix = -3;
                tuiles_selectionnes.pile[MAX_TUILES]; 
                tuiles_selectionnes.nbTuiles = 0;
                do
                {
                    if (choix==-3) affiche_joueur(joueurs.js[joueurActuel]);
                    
                    printf("Quelle tuile voulez-vous jouez dans votre chevalet ?\n");
                    printf("-1. Finalement, je pioche et je finis mon tour\n");
                    if (choix>=0)
                        printf("-2. Valider les tuiles selectionnees\n");
                    scanf(" %d", &choix);
                    if (choix != -1 && choix != -2)
                     {
                        selectionne = joueurs.js[joueurActuel].chevalet.pile[choix];
                        if (ajouter_tuile(&tuiles_selectionnes,selectionne)) {
                            printf("\nTuile selectionne : \n");
                            affiche_tuile(selectionne,555);
                            printf("\n\n");
                        }
                        else 
                            printf("\nVous avez déjà sélectionné cette tuile\n\n");

                        // creer copie

                         //algo clement
                    }
                    if(choix!=-2) affiche_joueur(joueurs.js[joueurActuel]);
                } while (choix >= 0 && choix < 13);
                if (choix==-2)
                {
                    tri_liste(&tuiles_selectionnes);
                    
                    // choisir place de mes tuiles
                    printf("Tuiles selectionnees : \n");
                    affiche_liste_tuiles(tuiles_selectionnes);  
                    copie_plateau(temp[0],plateau[0]);
                    //memcpy(temp,plateau,DIM_PLATEAU_H*DIM_PLATEAU_H*sizeof(TUILE));
                    affiche_plateau(temp[0]);
                    do
                    {
                        printf("Où voulez-vous placer vos tuiles selectionnes ?\n ligne : ");
                        scanf(" %c", &l);
                        printf("colonne : ");
                        scanf(" %d", &c);
                    } while (!est_placable(tuiles_selectionnes.nbTuiles,char_to_int(l),c));
                    // disposer tuiles dans temp
                    placer_tuiles(tuiles_selectionnes,temp[0],char_to_int(l),c);
                    // modifie plateau oui ou  non ?
                    do
                    {
                        affiche_plateau(temp[0]);
                        printf("Voulez-vous modifier le plateau actuel ?\n");
                        printf("1. oui\n");
                        printf("2. non\n");
                        scanf(" %d",&choixModifPlateau);
                        if (choixModifPlateau==1)
                        {
                            do
                            {
                                printf("Quelles tuiles voulez-vous intervertir ?\ntuile source :\nligne : ");
                                scanf(" %c", &l);
                                printf("colonne : ");
                                scanf(" %d", &c);
                                printf("tuile destination :\nligne : ");
                                scanf(" %c", &l2);
                                printf("colonne : ");
                                scanf(" %d", &c2);
                                if (!intervertion_tuiles(temp[0],char_to_int(l),c,char_to_int(l2),c2))
                                {
                                    printf("Err: mauvaises positions\n");
                                }
                                affiche_plateau(temp[0]);
                                printf("Voulez-vous continuer ?\n0. non\n1. oui\n");
                                scanf(" %d", &choixContinuer);
                                
                            } while (choixContinuer);
                        }
                        
                    } while (choixModifPlateau!=2); // le while n'est pas bon "2" ne fonctionne pas 
                    
                }
                
            }
            if (choixJoueur == 2 || choix == -1)
            {
                piocher(&joueurs.js[joueurActuel].chevalet);
                affiche_joueur(joueurs.js[joueurActuel]);
            }
            
            copie_plateau(plateau[0],temp[0]);
            // tour valide uniquement
            joueurActuel = (joueurActuel + 1) % (joueurs.nbJs);
            printf("fin de tour\n");
            // fin tour valide uniquement
            if (choixJoueur == 3)
                tour = FALSE;
        }
        partie = FALSE;
    }

    return 0;
}