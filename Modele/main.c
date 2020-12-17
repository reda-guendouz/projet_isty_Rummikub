#include "modele.h"

int main(void)
{
    srand(time(NULL));
    int nbJoueurs, choixJoueur;
    int joueurActuel = 0;
    int choix = -2;
    int l,c,l2,c2;
    int choixModifPlateau=-1;
    unsigned char tour = TRUE;
    unsigned char partie = TRUE;
    LISTE_TUILES tuiles_selectionnes;
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
    affiche_joueur(joueurs.js[joueurActuel]);

    // PARTIE EN COURS
    while (partie)
    {
        while (tour)
        {
            do
            {
                choixJoueur = -1;
                affiche_plateau();
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

                        /* algo clement */
                    }
                    if(choix!=-2) affiche_joueur(joueurs.js[joueurActuel]);
                } while (choix >= 0 && choix < 13);
                if (choix==-2)
                {
                    tri_liste(&tuiles_selectionnes);
                    
                    // choisir place de mes tuiles
                    printf("Tuiles selectionnees : \n");
                    affiche_liste_tuiles(tuiles_selectionnes);
                    affiche_plateau();
                    do
                    {
                        printf("Où voulez-vous placer vos tuiles selectionnes ?\n ligne : ");
                        scanf(" %d", &l);
                        printf("colonne : ");
                        scanf(" %d", &c);
                    } while (!est_placable(tuiles_selectionnes.nbTuiles,l,c));

                    // modifie plateau oui ou  non ?
                    do
                    {
                        affiche_plateau();
                        printf("Voulez-vous modifier le plateau actuel ?\n");
                        printf("1. oui\n");
                        printf("2. non\n");
                        scanf(" %d",&choixModifPlateau);
                        if (choixModifPlateau==1)
                        {

                            do
                            {
                                printf("Quelles tuiles voulez-vous intervertir ?\ntuile source :\nligne : ");
                                scanf(" %d", &l);
                                printf("colonne : ");
                                scanf(" %d", &c);
                                printf("tuile destination :\nligne : ");
                                scanf(" %d", &l2);
                                printf("colonne : ");
                                scanf(" %d", &c2);
                            } while (intervertion_tuiles(l,c,l2,c2));
                        }
                        
                    } while (choixModifPlateau!=2 || choixModifPlateau!=1); // le while n'est pas bon "2" ne fonctionne pas 
                    
                }
                
            }
            if (choixJoueur == 2 || choix == -1)
            {
                piocher(&joueurs.js[joueurActuel].chevalet);
                affiche_joueur(joueurs.js[joueurActuel]);
            }
            joueurActuel = (joueurActuel + 1) % (joueurs.nbJs);
            if (choixJoueur == 3)
                tour = FALSE;
            printf("fin de tour\n");
        }
        partie = FALSE;
    }

    return 0;
}