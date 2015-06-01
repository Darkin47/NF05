#include "generateur.h"

/// G�n�rateur de grille de sudoku
void generateur(int grille[9][9][10], int *niveauRequis)
{
    srand(time(NULL));
    int niveauTeste=0;
    do
    {
        int ligne=0, colonne=0;
        // On initialise la grille
        for(ligne=0; ligne<9; ligne++)
        {
            for(colonne=0; colonne<9; colonne++)
            {
                grille[ligne][colonne][0]=0;
            }
        }
        // On envoi la grille au backtracking qui va la remplir en entier de mani�re al�atoire
        backtracking(grille, 0);
        niveauTeste=(*niveauRequis);
        // On retire des cases � la grille
        vidage(grille, &niveauTeste);
    }
    while(niveauTeste!=(*niveauRequis)); // Tant que la grille n'a pas le niveau d�sir� on recommence
}

/// Proc�dure qui permet de retirer des cases � la grille en fonction du niveau requis
void vidage(int grille[9][9][10], int *niveauRequis)
{
    int nombreDeCases=0, indice2=0, *position=NULL, indice=0, niveauMax=0, grille2[9][9][10] = {{{0}}}, sauvegarde[9][9][10] = {{{0}}}, niveauTeste=0, compteur=0, ligne=0, colonne=0;
    // On choisit le nombre de cases de d�part de mani�re al�atoire en fonction du niveau d�sir�
    if(*niveauRequis<3)
    {
        nombreDeCases=chiffreAleatoire(30,40);
    }
    else
    {
        nombreDeCases=chiffreAleatoire(24,35);
    }
    // On cr�e un tableau avec les positions des cases de mani�re al�atoire
    position = malloc(81*sizeof(int));
    while(indice<81)
    {
        position[indice]=chiffreAleatoire(0,81);
        indice2 = 0;
        while(indice2!=indice&&position[indice]!=position[indice2])
        {
            indice2++;
        }
        if(indice==indice2)
        {
            indice++;
        }
    }
    indice=0;
    // On retire le nombre de cases d�sir�es de la grille
    for(compteur=nombreDeCases; compteur<81; compteur++)
    {
        copierTableau(grille, sauvegarde);
        do
        {
            copierTableau(sauvegarde, grille);
            ligne = position[indice]/9;
            colonne = position[indice]%9;
            grille[ligne][colonne][0]=0;
            copierTableau(grille, grille2);
            niveauTeste=1;
            resolveur(grille2, &niveauTeste);
            indice++;
        }
        while(niveauTeste>(*niveauRequis)&&indice<81);
        /* Tant qu'on a pas une case qui se r�sout avec un niveau de difficult� inf�rieur ou �gal � celui d�sir�
         alors on passe � la case suivante du tableau des positions jusqu'� la fin de ce dernier */
        // On enregistre le niveau maximum rencontr� lors de la r�solution de la grille
        if(niveauTeste>niveauMax)
        {
            niveauMax=niveauTeste;
        }
        // Si on a fini de parcourir toutes les cases on arr�te de retirer des cases
        if(indice==81)
        {
            break;
        }
    }
    free(position);
    *niveauRequis=niveauMax;
}

/// Proc�dure d'exportation de la grille par �criture dans une fichier
void exportationGrille(FILE* fichier, int grille[9][9][10])
{
    int ligne=0, colonne=0;
    for(ligne=0; ligne<9; ligne++)
    {
        for(colonne=0; colonne<9; colonne++)
        {
            fprintf(fichier, "%d,", grille[ligne][colonne][0]);
        }
        fprintf(fichier, "\n");
    }
}

/// Proc�dure d'affichage de la grille de Sudoku
void affichageGrille2(int grille[9][9])
{
    int ligne=0, colonne=0;
    printf("-------------------\n");
    for(ligne=0; ligne<9; ligne++)
    {
        for(colonne=0; colonne<9; colonne++)
        {
            if(colonne==0)
            {
                printf("|%d ", grille[ligne][colonne]);
            }
            else if(((colonne+1)%3))
            {
                printf("%d ", grille[ligne][colonne]);
            }
            else
            {
                printf("%d|", grille[ligne][colonne]);
            }
        }
        putchar('\n');
        if (!((ligne+1)%3))
        {
            printf("-------------------\n");
        }
    }
}
