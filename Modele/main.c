#include "modele.h"

int main(void) {
    srand(time(NULL));
    int nbJoueurs ;
    int choixJoueur;
    int joueurActuel = 1;
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
    
    // PARTIE EN COURS
    while (partie)
    {
        while (tour)
        {
            do{
                choixJoueur = -1;
                printf("Voulez-vous posez une combinaison ou piocher ?\n");
                printf("Jouer : 1 \n");
                printf("Piocher : 2 \n");
                scanf(" %d",&choixJoueur);
            }while(choixJoueur!= 1 && choixJoueur != 2);
            if (choixJoueur == 2) {
                piocher(joueurActuel);
                affiche_joueur(joueurs.js[joueurActuel-1]);
            }
            else {
                printf("JOUEUR JOUE");
            }
            tour=FALSE;
        }
        partie=FALSE;
    }
    
    return 0;
}