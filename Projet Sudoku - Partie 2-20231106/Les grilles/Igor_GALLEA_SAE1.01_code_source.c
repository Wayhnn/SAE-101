#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define TAILLE 9
#define N sqrt(TAILLE)

typedef int tabSudoku[TAILLE][TAILLE];

void chargerGrille(tabSudoku grille);
void afficherGrille(tabSudoku grille);
void saisir(int *val);
bool possible(tabSudoku grille, int indiceLigne, int indiceColonne, int valeur);
bool grilleComplete(tabSudoku grille);
int nbElementsCol(tabSudoku g, int col);
int nbElementsLigne(tabSudoku g, int lig);

int main()
{
    int numLigne, numCol, valeur;

    tabSudoku grille1;

    chargerGrille(grille1);
    while(!grilleComplete(grille1))
    {
        afficherGrille(grille1);
        printf("Indice de la case ? \n");
        saisir(&numLigne);
        saisir(&numCol);
        //Permet de réajuster le décalage entre l'indice des ligne/colonnes sur la grille (de 1 à 9) et celui du langage C (de 0 à 8)
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
}

void chargerGrille(tabSudoku g)
{
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
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
    int indiceSousTab = N;

    //affiche les indices des colonnes
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
            // affiche les séparations horizontales
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
        // affiche les indices des lignes
        printf("%3d ",i+1);

        for(int j = 0; j < TAILLE; j++)
        {
            if (j%indiceSousTab == 0)
            {
                //affiche les séparations verticales
                printf("|");
            }
            
            if(grille[i][j] != 0 )
            {
                printf(" %d ",grille[i][j]);
            }
            else
            {
                printf(" . ");
            }
            }
        
        printf("|  (%d)\n",nbElementsLigne(grille,i));
    }

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
    printf("     ");
    for (int k = 1; k <= TAILLE; k++)
    {
        printf("(%d)", nbElementsCol(grille,k-1));
        if (k% (int)N == 0)
        {
            printf(" ");
        }
                
    }
    printf("\n\n");
}


void saisir(int *nbSaisie)
{
    char temp[50];
    printf("Donnez une valeur entre 1 et %d : ",TAILLE);
    scanf("%s",temp);

    while(sscanf(temp,"%d",nbSaisie) == 0 || *nbSaisie > TAILLE || *nbSaisie < 1)
    {
        printf("\nERREUR : Veuillez saisir un entier compris entre 1 et %d\n\n",TAILLE);
        printf("Donnez une valeur entre 1 et %d : ",TAILLE);
        scanf("%s",temp);
    }
}

bool possible(tabSudoku grille, int indiceLigne, int indiceColonne, int valeur)
{
    bool estValide;
    int cmptLigne;
    int cmptCol;
    // utile pour verifier si la valeur se trouve dans le carré
    int indiceInitLigne;
    int indiceInitCol;

    //Init
    estValide = true;
    cmptLigne = 0;
    cmptCol = 0;
    indiceInitLigne = N * (int)(indiceLigne/N);
    indiceInitCol = N * (int)(indiceColonne/N);

    // vérification des sous-tableau
    while (estValide && indiceInitLigne < (N * (int)(indiceLigne/N)) + N)
    {
        while (estValide && indiceInitCol <  (N * (int)(indiceColonne/N)) + N)
        {
            if (grille[indiceInitLigne][indiceInitCol] == valeur)
            {
                estValide = false;
                printf("\nIMPOSSIBLE : cette valeur est deja presente dans le carré\n\n");
            }
            indiceInitCol ++;
        }
        indiceInitLigne ++;
    }
    

    // vérification des lignes

    while (estValide && cmptCol < TAILLE){

        if (grille[indiceLigne][cmptCol] == valeur)
        {
            estValide = false;
            printf("\nIMPOSSIBLE : cette valeur est deja presente dans la ligne\n\n");
        }
        cmptCol++;
    }

    // vérification des colonnes

    while(estValide && cmptLigne < TAILLE){

        if (grille[cmptLigne][indiceColonne] == valeur)
        {
            estValide = false;
            printf("\nIMPOSSIBLE : cette valeur est deja presente dans la colonne\n\n");
        }
        cmptLigne++;
    }

    return estValide;
}

bool grilleComplete(tabSudoku grille)
{
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

/*    EXO 1     */
int nbElementsLigne(tabSudoku g, int lig)
{
    int cmpt = 0;
    for (int i = 0; i < TAILLE; i++)
    {
        if (g[lig][i] != 0)
        {
            cmpt++;
        }
        
    }
    return cmpt;
}

int nbElementsCol(tabSudoku g, int col)
{
    int cmpt = 0;
    for (int i = 0; i < TAILLE; i++)
    {
        if (g[i][col] != 0)
        {
            cmpt++;
        }
        
    }
    return cmpt;
}

/*      EXO 2      */
