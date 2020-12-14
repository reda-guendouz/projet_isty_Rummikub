#include "modele.h"

int main(void)
{
    srand(time(NULL));
    int nbJoueurs;
    int choixJoueur;
    int joueurActuel = 0;
    int choix = -2;
    unsigned char tour = TRUE;
    unsigned char partie = TRUE;
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
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("1. Jouer \n");
                printf("2. Piocher \n");
                printf("3. fin de partie\n");
                scanf(" %d", &choixJoueur);
            } while (choixJoueur < 1 || choixJoueur > 3);
            if (choixJoueur == 1)
            {
                printf("JOUEUR JOUE\n");
                LISTE_TUILES combinaisons;
                combinaisons.nbTuiles = 0;
                choix = -2;
                do
                {
                    affiche_joueur(joueurs.js[joueurActuel]);
                    printf("Quelle tuile voulez-vous jouez dans votre chevalet ?\n");
                    printf("-1. piocher majuscule et finir mon tour\n");
                    scanf(" %d", &choix);
                    if (choix != -1)
                     {
                        TUILE tuile_selectionne = joueurs.js[joueurActuel].chevalet.pile[choix];
                        ajouter_tuile(&combinaisons, tuile_selectionne);

                        /* algo clement */
                    }
                } while (choix < -1 || choix > 13);
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