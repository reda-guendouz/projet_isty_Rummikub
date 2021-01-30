#include "modele.h"

void affiche_tuile(TUILE tuile, int numTuiles)
{
    if (tuile.chiffre == -1)
        printf("Tuile n°%d :  JOKER\n", numTuiles);
    else
    {
        switch (tuile.clr)
        {
        case NOIR:
            printf("Tuile n°%d :  %d NOIR\n", numTuiles, tuile.chiffre);
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
    liste->pile[liste->nbTuiles] = tuile;
    liste->nbTuiles++;
    return TRUE;
}

/**********
 * Joueur *
 * *******/

void init_joueurs(int nbJoueurs, int nbJoueursH)
{
    joueurs.nbJs = nbJoueurs;
    int i, j, tmp;
    for (i = 0; i < nbJoueurs; i++)
    {
        tmp = i + 1;
        joueurs.js[i].numJoueur = tmp;
        if (nbJoueursH > 0)
        {
            printf("Entrez le pseudonyme du joueur %d : ", tmp);
            scanf(" %s", joueurs.js[i].pseudo);
            nbJoueursH--;
        }
        else
        {
            printf("IA 1\n");
            strcpy(joueurs.js[i].pseudo, "IA");
        }
        joueurs.js[i].chevalet.nbTuiles = 0;
        for (j = 0; j < PIOCHE_DEPART; j++)
        {
            piocher(&joueurs.js[i].chevalet);
            affiche_tuile(pioche.pile[pioche.nbTuiles], j);
        }
    }
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
void affiche_plateau(TUILE *plateau_a_afficher)
{
    int i, j, k;

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
            TUILE t;
            t.chiffre = -1;
            t.clr = NOIR;
            plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)] = t;
            if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == 0 && plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].clr == NOIR)
                printf("    ");
            else if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == -1)
                printf(" JK ");
            else
            {
                if (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre < 10)
                    printf(" ");
                switch (plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].clr)
                {
                case NOIR:
                    printf(" %d ", plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case ORANGE:
                    printf(ORA " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case ROUGE:
                    printf(ROU " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
                    break;
                case BLEU:
                    printf(BLE " %d " RESET, plateau_a_afficher[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre);
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

void copie_plateau(TUILE *dest, TUILE *src)
{
    int i, j;
    for (i = 0; i < DIM_PLATEAU_H; i++)
        for (j = 0; j < DIM_PLATEAU_W; j++)
            dest[(int unsigned)(i * DIM_PLATEAU_W + j)] = src[(int unsigned)(i * DIM_PLATEAU_W + j)];
}

void placer_tuiles(LISTE_TUILES selection, TUILE *copie_plateau, int l, int c)
{
    int i;
    for (i = 0; i < selection.nbTuiles; i++)
        copie_plateau[(int unsigned)(l * DIM_PLATEAU_W + c + i)] = selection.pile[i];
}

int suite(LISTE_TUILES *l)
{
    int i, suite = 0;
    int joker = 0;
    if (l->nbTuiles > 2)
    {
        tri_liste(l);
        for (i = 0; i < l->nbTuiles - 1; i++)
        {
            if (l->pile[i].clr == NOIR && l->pile[i].chiffre == -1)
            {
                joker += 1;
            }
            else if (l->pile[i].clr == l->pile[i + 1].clr)
            {
                if (l->pile[i].chiffre + 1 == l->pile[i + 1].chiffre)
                {
                    suite += 1;
                }
                else
                {
                    if (joker > 0) //si un joker
                    {
                        joker -= 1;
                        if (l->pile[i].chiffre == -l->pile[i + 1].chiffre + 2)
                            suite += 1;
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
            }
            else
                return 0;
        }
        return 1;
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

void supprime_liste(LISTE_TUILES *l, TUILE tuile)
{
    int i;
    unsigned char trouve = FALSE;
    for (i = 0; i < l->nbTuiles; i++)
    {
        if (l->pile[i].chiffre == tuile.chiffre && l->pile[i].clr == tuile.clr && !trouve)
            trouve = TRUE;
        else
            ajouter_tuile(l, l->pile[i]);
    }
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

void affiche_victoire(JOUEUR j, int indiceJoueurGagnant)
{
    int i;
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n                                 ");
    printf("Joueur n°%d: \033[32;1m %s \033[0m\n", j.numJoueur, j.pseudo);
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    for (i = 0; i < 44; i++)
        printf("/\\");
    printf("\n");
    printf("\n");
    printf("TABLE DES SCORES\n");
    score_fin_partie(indiceJoueurGagnant);
    for (i = 0; i < joueurs.nbJs; i++)
    {
        printf("%s : %d\n", joueurs.js[i].pseudo, joueurs.scores[i]);
    }
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

int intervertion_tuiles(TUILE *copie_plateau, int ligneSource, int colonneSource, int ligneDestination, int colonneDestination)
{
    // verifier ici d'abord que les lignes et colonnes sont bonnes
    // sinon retourner false
    if (ligneSource < 0 && ligneSource >= DIM_PLATEAU_H && colonneDestination < 0 && colonneDestination >= DIM_PLATEAU_W)
        return FALSE;
    TUILE temp;
    temp.chiffre = copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].chiffre;
    temp.clr = copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].clr;
    copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].chiffre = copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].chiffre;
    copie_plateau[ligneSource * DIM_PLATEAU_W + colonneSource].clr = copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].clr;
    copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].chiffre = temp.chiffre;
    copie_plateau[ligneDestination * DIM_PLATEAU_W + colonneDestination].clr = temp.clr;
    return TRUE;
}

void score_fin_partie(int indiceJoueurGagnant)
{
    int score[JOUEURS_MAX];
    int i, j;
    for (i = 0; i < joueurs.nbJs; i++)
    {
        if (i != indiceJoueurGagnant)
        {
            for (j = 0; j < joueurs.js[i].chevalet.nbTuiles; j++)
            {
                score[indiceJoueurGagnant] += joueurs.js[i].chevalet.pile[j].chiffre;
                score[i] -= joueurs.js[i].chevalet.pile[j].chiffre;
            }
        }
    }
    for (i = 0; i < joueurs.nbJs; i++)
    {
        joueurs.scores[i] += score[i];
    }
}

int char_to_int(char l)
{
    switch (l)
    {
    case 'a':
        return 0;
        break;
    case 'b':
        return 1;
        break;
    case 'c':
        return 2;
        break;
    case 'd':
        return 3;
        break;
    case 'e':
        return 4;
        break;
    case 'f':
        return 5;
        break;
    case 'g':
        return 6;
        break;
    case 'h':
        return 7;
        break;
    default:
        break;
    }
    return -1;
}

int analyse_plateau(TUILE *plateau)
{
    int i, j;
    unsigned char test = FALSE;
    LISTE_TUILES analyse;
    analyse.nbTuiles = 0;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (plateau[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre != 0)
            {
                ajouter_tuile(&analyse, plateau[(int unsigned)(i * DIM_PLATEAU_W + j)]);
                test = TRUE;
            }
            else if (plateau[(int unsigned)(i * DIM_PLATEAU_W + j)].chiffre == 0 && test)
            {
                if (!test_combinaison(&analyse))
                    return FALSE;
                test = FALSE;
            }
        }
    }

    return TRUE;
}

void mettre_a_jour(LISTE_TUILES *chevalet, LISTE_TUILES tuilesSelectionnees)
{
    int i;
    for (i = 0; i < tuilesSelectionnees.nbTuiles; i++)
        supprime_liste(chevalet, tuilesSelectionnees.pile[i]);
}

int action_tour_ia(JOUEUR ia)
{
    LISTE_TUILES listeIa = ia.chevalet;
    LISTE_TUILES *ptr_listeIa = &listeIa;
    LISTE_TUILES combinaisonsTrouve;
    int i = 0;
    TUILE copiePlateau[DIM_PLATEAU_H][DIM_PLATEAU_W];
    combinaisonsTrouve.nbTuiles = 0;
    copie_plateau(copiePlateau[0], plateau[0]);
    tri_liste(ptr_listeIa);
    affiche_liste_tuiles(listeIa);
    trouver_combinaisons(listeIa, &combinaisonsTrouve);
    if (combinaisonsTrouve.nbTuiles > 0)
    {
        printf("COMBINAISONS TROUVE IA PLACE \n");
        for (i = 0; i < combinaisonsTrouve.nbTuiles; i++)
            supprime_liste(&ia.chevalet, combinaisonsTrouve.pile[i]);
        placer_combinaisons(combinaisonsTrouve, copiePlateau[0]);
        copie_plateau(plateau[0], copiePlateau[0]);
    }

    else
    {
        printf("AUCUNE COMBINAISONS TROUVE IA PIOCHE \n");
        piocher(ptr_listeIa);
    }
    return 2;
}

void trouver_combinaisons(LISTE_TUILES chevaletIa, LISTE_TUILES *combinaisonsTrouve)
{
    int i;
    int taille = chevaletIa.nbTuiles;
    int tab[taille];
    combinaisonsTrouve->nbTuiles = 0;
    for (i = 0; i < taille; i++)
        tab[i] = i;
    for (i = 3; i < taille; i++)
    {
        int data[i];
        combinationUtil(tab, taille, i, 0, data, 0, chevaletIa, combinaisonsTrouve);
    }
    return;
}

void combinationUtil(int arr[], int taille, int r, int index, int data[], int i, LISTE_TUILES chevaletIa, LISTE_TUILES *max)
{
    LISTE_TUILES new;
    new.nbTuiles = 0;
    int j;
    if (index == r)
    {
        for (j = 0; j < r; j++)
            ajouter_tuile(&new, chevaletIa.pile[data[j]]);
        if (test_combinaison(&new))
        {
            if (new.nbTuiles > max->nbTuiles)
                copie_liste(&new, max); // VERIF max poids
        }
        return;
    }
    if (i >= taille)
        return;
    data[index] = arr[i];
    combinationUtil(arr, taille, r, index + 1, data, i + 1, chevaletIa, max);
    combinationUtil(arr, taille, r, index, data, i + 1, chevaletIa, max);
}

void copie_liste(LISTE_TUILES *src, LISTE_TUILES *dst)
{
    dst->nbTuiles = 0;
    int i = 0;
    for (i = 0; i < src->nbTuiles; i++)
    {
        ajouter_tuile(dst, src->pile[i]);
    }
}

void placer_combinaisons(LISTE_TUILES combinaisonTrouve, TUILE *copiePlateau)
{
    int i, j, tailleCombinaisons = combinaisonTrouve.nbTuiles;
    for (i = 0; i < DIM_PLATEAU_H; i++)
    {
        for (j = 0; j < DIM_PLATEAU_W; j++)
        {
            if (est_placable(tailleCombinaisons, i, j))
            {
                placer_tuiles(combinaisonTrouve, copiePlateau, i, j);
                return;
            }
        }
    }
}