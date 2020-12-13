#include "modele.h"


int main(void) {
    srand(time(NULL));
    int nbJoueurs ;
    int choixJoueur;
    int joueurActuel = 1;
    int choix = -2;
    unsigned char tour=TRUE;
    unsigned char partie=TRUE;
    init_pioche();

    // SELECTION DES JOUEURS
    do{
        nbJoueurs = -1;
        printf("Combien de joueurs jouent ?\n");
        scanf(" %d",&nbJoueurs);
    }while(nbJoueurs < 2 && nbJoueurs > 4);
    init_joueurs(nbJoueurs);
    affiche_liste_tuiles(joueurs.js[0].chevalet);
    
    // PARTIE EN COURS
    while (partie)
    {
        while (tour)
        {
            do{
                choixJoueur = -1;
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("1. Jouer \n");
                printf("2. Piocher \n");
                scanf(" %d",&choixJoueur);
            }while(choixJoueur!= 1 && choixJoueur != 2);
            if (choixJoueur == 1) {
                printf("JOUEUR JOUE\n");
                LISTE_TUILES combinaisons;
                combinaisons.nbTuiles = 0;
                choix = -2;
                do{
                    affiche_liste_tuiles(joueurs.js[joueurActuel].chevalet);
                    printf("Quelle tuile voulez-vous jouez dans votre chevalet ?\n");
                    scanf(" %d",&choix);
                }while(choix < -2 && choix > 13);
            }
            if (choixJoueur == 2 || choix == -1) {
                piocher(joueurs.js[joueurActuel-1].chevalet);
                affiche_joueur(joueurs.js[joueurActuel-1]);
            }
            tour=FALSE;
        }
        partie=FALSE;
    }
    
    return 0;
}