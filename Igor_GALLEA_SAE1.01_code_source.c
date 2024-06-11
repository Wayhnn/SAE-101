/**
 * @author GALLEA Igor
 * 
 * @date 29/11/2023
 * 
 * @version 1.0
 * 
 * Ce programme incroyable du jeu du Sudoku !
 * Requiert des fichiers binaires pour charger 
 * les grilles.
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define TAILLE 9 /** @def Taille de notre tableau de jeu */
#define N sqrt(TAILLE) /** @def Taille de chaque sous tableau*/

typedef int tabSudoku[TAILLE][TAILLE]; /** @typedef Correspond à notre grille de jeu*/

void chargerGrille(tabSudoku grille);
void afficherGrille(tabSudoku grille);
void saisir(int *val);
bool possible(tabSudoku grille, int indiceLigne, int indiceColonne, int valeur);
bool grilleComplete(tabSudoku grille);


int main()
{
    /**
     * @fn int main()
     * 
     * @brief Fonction principale du programme Sudoku.
     * 
     * @return 0 si l'exécution s'est déroulée avec succès.
     * 
     * Demande à charger une grille depuis un fichier
     * Puis à chaque tour :
     *   - affiche la grille
     *   - Demande au joueur de saisir les indices de la case à modifier
     *   - Si la case est valide alors lui demande la valeur qu'il souhaite insérer
     *   - Insère la valeur dans la case si c'est possible
     *   - Puis recommence
    */

    int numLigne, numCol, valeur;

    tabSudoku grille1;

    chargerGrille(grille1);
    while(!grilleComplete(grille1))
    {
        afficherGrille(grille1);
        printf("Indice de la case ? \n");
        saisir(&numLigne);
        saisir(&numCol);

        /** Permet de réajuster le décalage entre l'indice des ligne/colonnes sur la grille (de 1 à 9) et celui du langage C (de 0 à 8) */
        numCol--;
        numLigne--;
        if (grille1[numLigne][numCol] != 0)
        {
            printf("\nIMPOSSIBLE, la case n'est pas libre.\n\n");
        }
        else
        {
            printf("Valeur a inserer : ");
            saisir(&valeur);
            if (possible(grille1, numLigne, numCol, valeur))
            {
                grille1[numLigne][numCol] = valeur;
            }
        }
    }
    
    return 0;
}



void chargerGrille(tabSudoku g)
{

    /**
     * @fn void chargerGrille(tabSudoku g)
     * 
     * @brief Charge une grille Sudoku à partir d'un fichier binaire.
     * 
     * @param g La grille vide à remplire.
     * 
     * Fonction qui demande à l'utilisateur de 
     * saisir un nom de fichier. Tant que le 
     * nom du fichier n'est pas valide, redemande 
     * la saisie. Puis remplis g en lisant le fichier
    */

    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");

    /* Redemande la saisie jusqu'à ce que le nom du fichier soit valide */
    while (f==NULL)
    {
        printf("\nERREUR sur le fichier %s\n\n", nomFichier);
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
    }
    fread(g, sizeof(int), TAILLE*TAILLE, f);
    fclose(f);
}

void afficherGrille(tabSudoku grille)
{

    /**
     * @fn void afficherGrille(tabSudoku grille)
     * 
     * @brief Affiche la grille Sudoku.
     * 
     * @param grille La grille Sudoku à afficher.
     * 
     * Fonction qui affiche et met en page la grille de Sudoku. 
     * Permet de bien afficher chaque ligne/colonne mais également 
     * de séparer les carrés de N*N. Ajoute également des indices 
     * en face de chaque ligne et de chaque colonne. 
    */

    int indiceSousTab = N;

    /** affiche les indices des colonnes */
    printf("    ");
    for (int i = 1; i <= TAILLE; i++)
    {
        printf("%3d",i);
        if (i% (int)N == 0)
        {
            printf(" ");
        }
        
    }
    printf("\n");
    
    for(int i = 0; i < TAILLE ; i++)
    {
        if (i%indiceSousTab == 0)
        {
            /** affiche les séparations horizontales*/
            printf("    +");
            for (int k = 1; k <= TAILLE; k++)
            {
                printf("---");
                if (k% (int)N == 0)
                {
                    printf("+");
                }
                
            }
            printf("\n");
        }

        printf("%3d ",i+1); /** affiche les indices des lignes */


        for(int j = 0; j < TAILLE; j++)
        {
            if (j%indiceSousTab == 0)
            {
                printf("|"); /** affiche les séparations verticales */
            }
            
            if(grille[i][j] != 0 )
            {
                printf(" %d ",grille[i][j]);
            }
            else
            {
                printf(" . "); /** Remplace les 0 par des . (pour l'affichage uniquement) */
            }
            }
        
        printf("|\n");
    }

    /** affiche la séparation verticale de fin*/
    printf("    +");
    for (int k = 1; k <= TAILLE; k++)
    {
        printf("---");
        if (k% (int)N == 0)
        {
            printf("+");
        }
                
    }
    printf("\n\n");
}


void saisir(int *nbSaisie)
{

    /**
     * @fn void saisir(int *nbSaisie)
     * 
     * @brief Saisit une valeur entre 1 et TAILLE.
     * 
     * @param nbSaisie Pointeur vers la variable qui stockera la valeur saisie.
     * 
     * Demande à l'utilisateur de saisir un chiffre entier entre 1 et TAILLE.
     * Tant que le valeur saisie ne sera pas un entier compris entre 1 et TAILLE,
     * la saisie et redemandée. 
    */

    char temp[50];
    printf("Donnez une valeur entre 1 et %d : ",TAILLE);
    scanf("%s",temp);

    while(sscanf(temp,"%d",nbSaisie) == 0 || *nbSaisie > TAILLE || *nbSaisie < 1)
    {
        /** Redemande la saisie jusqu'à ce que le nombre soit compris entre 1 et n*n */
        
        printf("\nERREUR : Veuillez saisir un entier compris entre 1 et %d\n\n",TAILLE);
        printf("Donnez une valeur entre 1 et %d : ",TAILLE);
        scanf("%s",temp);
    }
}



bool grilleComplete(tabSudoku grille)
{

    /**
     * @fn bool grilleComplete(tabSudoku grille)
     * 
     * @brief Vérifie si la grille Sudoku est complète (toutes les cases sont remplies).
     * 
     * @param grille La grille Sudoku.
     * 
     * @return true si la grille est complète, false sinon.
     * 
     * Fonction qui parcours le tableau case par case et vérifie si elles sont égale à 0.
     * Si aucune n'est égale à 0, alors la grille est complète et renvoie true
     * Sinon, renvoie false.
    */

    bool complete;
    int indiceLigne, indiceCol;

    complete = true;
    indiceLigne = 0;
    indiceCol = 0;

    while(indiceLigne < TAILLE && complete)
    {
        while (indiceCol < TAILLE && complete)
        {
            if (grille[indiceLigne][indiceCol] == 0)
            {
                complete = false;
            }
            indiceCol ++;
        }
        indiceCol = 0;
        indiceLigne ++;
    }

    return complete;
}