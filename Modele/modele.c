#include "modele.h"

/**********
 * TUILE  *
 * *******/

void affiche_tuile(TUILE tuile, int numTuiles)
{
    if (tuile.chiffre == -1)
        printf("Tuile n°%d :  JOKER\n", numTuiles);
    else
    {
        switch (tuile.clr)
        {
        case NOIR:
            printf("Tuile n°%d : %d NOIR\n", numTuiles, tuile.chiffre);
            break;
        case ORANGE:
            printf("Tuile n°%d : " ORA " %d ORANGE" RESET "\n", numTuiles, tuile.chiffre);
            break;
        case ROUGE:
            printf("Tuile n°%d : " ROU " %d ROUGE " RESET "\n", numTuiles, tuile.chiffre);
            break;
        case BLEU:
            printf("Tuile n°%d : " BLE " %d BLEU " RESET "\n", numTuiles, tuile.chiffre);
            break;
        default:
            break;
        }
    }
}

/****************
 * LISTE_TUILE  *
 * *************/

int ajouter_tuile(LISTE_TUILES *liste, TUILE tuile)
{
    int i;
    for (i = 0; i < liste->nbTuiles; i++)
        if (tuile.chiffre == liste->pile[i].chiffre && tuile.clr == liste->pile[i].clr)
            return FALSE;
    liste->pile[liste->nbTuiles] = tuile;
    liste->nbTuiles++;
    return TRUE;
}

/**********
 * Joueur *
 * *******/

void init_joueurs(int nbJoueurs)
{
    joueurs.nbJs = nbJoueurs;
    int i, j, tmp;
    for (i = 0; i < nbJoueurs; i++)
    {
        tmp = i + 1;
        joueurs.js[i].numJoueur = tmp;
        printf("Entrez le pseudonyme du joueur %d : ", tmp);
        scanf("%s", joueurs.js[i].pseudo);
        joueurs.js[i].chevalet.nbTuiles = 0;
        for (j = 0; j < PIOCHE_DEPART; j++)
            piocher(&joueurs.js[i].chevalet);
    }
    for (i = 0; i < nbJoueurs; i++)
        printf("Le joueur %d est %s !\n", i + 1, joueurs.js[i].pseudo);
}

void affiche_joueur(JOUEUR joueur)
{
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n", joueur.numJoueur, joueur.pseudo);
    printf("CHEVALET : \n");
    affiche_liste_tuiles(joueur.chevalet);
}

void affiche_joueurs()
{
    int i;
    for (i = 0; i < joueurs.nbJs; i++)
        affiche_joueur(joueurs.js[i]);
}

/**********
 * Pioche *
 * *******/

void init_pioche()
{
    int i, j, k;
    pioche.nbTuiles = 0;
    for (i = 0; i < 2; i++)
    {
        for (j = 1; j <= MAX_CHIFFRE; j++)
        {
            for (k = NOIR; k <= BLEU; k++)
            {
                pioche.pile[pioche.nbTuiles].chiffre = j;
                pioche.pile[pioche.nbTuiles].clr = k;
                pioche.nbTuiles++;
            }
        }
        pioche.pile[pioche.nbTuiles].chiffre = -1;
        pioche.pile[pioche.nbTuiles].clr = NOIR;
        pioche.nbTuiles++;
    }
    melanger_pioche();
}

void affiche_liste_tuiles(LISTE_TUILES liste_tuiles)
{
    int i;
    for (i = 0; i < liste_tuiles.nbTuiles; i++)
        affiche_tuile(liste_tuiles.pile[i], i);
}

void melanger_pioche()
{
    int i, nb2;
    nb2 = MAX_TUILES;
    for (i = 0; i < MAX_TUILES; i++)
    {
        TUILE tmp;
        int index = rand() % nb2;
        tmp = pioche.pile[index];
        pioche.pile[index] = pioche.pile[nb2 - 1];
        pioche.pile[MAX_TUILES - i - 1] = tmp;
        nb2--;
    }
}

void piocher(LISTE_TUILES *liste)
{
    pioche.nbTuiles--;
    TUILE tuile = pioche.pile[pioche.nbTuiles];
    ajouter_tuile(liste, tuile);
    /*joueurs.js[numJoueur].chevalet.pile[joueurs.js[numJoueur].chevalet.nbTuiles] = tuile;
    joueurs.js[numJoueur].chevalet.nbTuiles++;*/
}

/***********
 * Plateau *
 * ********/
void affiche_plateau()
{
    int i, j, k;

    // partie test
    /*
    TUILE t1;
    t1.clr = ROUGE;
    t1.chiffre = 9;
    TUILE t2;
    t2.clr = BLEU;
    t2.chiffre = 11;
    TUILE t3;
    t3.clr = BLEU;
    t3.chiffre = -1;
    TUILE t4;
    t4.clr = ORANGE;
    t4.chiffre = 7;

    plateau[0][0] = t1;
    plateau[1][1] = t2;
    plateau[2][2] = t3;
    plateau[0][21] = t2;
    plateau[7][0] = t3;
    plateau[7][21] = t4;*/

    printf("\nPlateau:\n  ");
    for (k = 0; k < 22; k++)
    {
        if (k < 10)
            printf("  %d ", k);
        else
            printf(" %d ", k);
    }
    printf("\n  ");
    for (k = 0; k < 88; k++)
        printf("-");
    printf("\n");
    char lettre = 'a';
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        printf("%c|", lettre);
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (plateau[i][j].chiffre == 0 && plateau[i][j].clr == NOIR)
                printf("    ");
            else if (plateau[i][j].chiffre == -1)
                printf(" JO ");
            else
            {
                if (plateau[i][j].chiffre < 10)
                    printf(" ");
                switch (plateau[i][j].clr)
                {
                case NOIR:
                    printf(" %d ", plateau[i][j].chiffre);
                    break;
                case ORANGE:
                    printf(ORA " %d " RESET, plateau[i][j].chiffre);
                    break;
                case ROUGE:
                    printf(ROU " %d " RESET, plateau[i][j].chiffre);
                    break;
                case BLEU:
                    printf(BLE " %d " RESET, plateau[i][j].chiffre);
                    break;
                }
            }
        }
        printf("|\n");
        lettre += 1;
    }
    printf("  ");
    for (k = 0; k < 88; k++)
        printf("-");
    printf("\n");
}

int suite(LISTE_TUILES *l)
{
    if (l->nbTuiles > 2)
    {
        tri_liste(l);
        affiche_liste_tuiles(*l);
        int i, compteur = l->pile[0].chiffre;
        for (i = 0; i < l->nbTuiles - 1; i++)
        {
            if (l->pile[i].clr == l->pile[i + 1].clr && l->pile[i].chiffre + 1 == l->pile[i + 1].chiffre)
                compteur += l->pile[i + 1].chiffre;
            else
                return 0;
        }
        return compteur;
    }
    return 0;
}

int triplon_quadruplon(LISTE_TUILES *l)
{
    if (l->nbTuiles > 2 && l->nbTuiles < 5)
    {
        int i, j;
        for (i = 0; i < l->nbTuiles - 1; i++)
        {
            if (l->pile[i].chiffre == l->pile[i + 1].chiffre)
            {
                for (j = i + 1; j < l->nbTuiles; j++)
                {
                    if (l->pile[i].clr == l->pile[j].clr)
                    {
                        return 0;
                    }
                }
            }
            else
                return 0;
        }
        return l->pile[0].chiffre * l->nbTuiles;
    }
    else
        return 0;
}

void tri_liste(LISTE_TUILES *l)
{
    TUILE memo = l->pile[0];
    int i, j;
    for (i = 0; i < l->nbTuiles - 1; i++)
    {
        for (j = 0; j < l->nbTuiles - i - 1; j++)
        {
            if (l->pile[j].chiffre > l->pile[j + 1].chiffre)
            {
                memo = l->pile[j];
                l->pile[j] = l->pile[j + 1];
                l->pile[j + 1] = memo;
            }
        }
    }
}

LISTE_TUILES supprime_liste(LISTE_TUILES l, int indice)
{
    int i;
    LISTE_TUILES reponse;
    reponse.nbTuiles = 0;
    if (indice < l.nbTuiles)
    {
        for (i = 0; i < indice + 1; i++)
            reponse.pile[i] = l.pile[i];
        for (i = indice + 1; i < l.nbTuiles; i++)
            reponse.pile[i - 1] = l.pile[i];
        reponse.nbTuiles = l.nbTuiles - 1;
    }
    return reponse;
}

LISTE_TUILES copie_liste(LISTE_TUILES l)
{
    int i;
    LISTE_TUILES reponse;
    reponse.nbTuiles = 0;
    if (l.nbTuiles > 0)
    {
        for (i = 0; i < l.nbTuiles + 1; i++)
            reponse.pile[i] = l.pile[i];
        reponse.nbTuiles = l.nbTuiles;
    }
    return reponse;
}

int test_combinaison(LISTE_TUILES *l)
{
    return triplon_quadruplon(l) + suite(l);
}

int est_victorieux(JOUEUR j)
{
    if (j.chevalet.nbTuiles == 0)
        return TRUE;
    return FALSE;
}

void affiche_victoire(JOUEUR j)
{
    int k;
    for (k = 0; k < 44; k++)
        printf("/\\");
    printf("\n");
    for (k = 0; k < 44; k++)
        printf("/\\");
    printf("\n                                 ");
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n", j.numJoueur, j.pseudo);
    for (k = 0; k < 44; k++)
        printf("/\\");
    printf("\n");
    for (k = 0; k < 44; k++)
        printf("/\\");
    printf("\n");
}

int est_placable(int taille_liste, int ligne, int colonne)
{
    int i, j, taille_dispo = 0, depart = FALSE;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (i == ligne && j == colonne)
                depart = TRUE;
            if (depart)
            {
                if (plateau[i][j].chiffre == 0)
                    taille_dispo++;
                if (taille_dispo == taille_liste)
                    return TRUE;
                if (plateau[i][j].chiffre != 0)
                    return FALSE;
            }
        }
    }

    return FALSE;
}

int intervertion_tuiles(int ligneSource, int colonneSource, int ligneDestination, int colonneDestination)
{
    // verifier ici d'abord que les lignes et colonnes sont bonnes
    // sinon retourner false
    if (ligneSource > DIM_PLATEAU_H || ligneSource < 0 || colonneDestination > DIM_PLATEAU_W || colonneDestination < 0)
        return FALSE;
    TUILE temp;
    temp = plateau[ligneSource][colonneSource];
    plateau[ligneSource][colonneSource] = plateau[ligneDestination][colonneDestination];
    plateau[ligneDestination][colonneDestination] = temp;
    return TRUE;
}

void score_fin_partie(int indice)
{

    int score[JOUEURS_MAX];
    int i, j;
    for (i = 0; i < joueurs.nbJs; i++)
    {
        if (i != indice)
        {
            for (j = 0; j < joueurs.js[i].chevalet.nbTuiles; j++)
            {
                score[indice] += joueurs.js[i].chevalet.pile[j].chiffre;
                score[i] -= joueurs.js[i].chevalet.pile[j].chiffre;
            }
        }
    }
    for (i = 0; i < joueurs.nbJs; i++)
    {
        joueurs.scores[i] += score[i];
    }
}