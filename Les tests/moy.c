/**
*@brief la moyenne des étudiants
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float BREAK = -1;

int main (){
    int nb;
    int somme = 0;
    int cmpt = 0;

    printf("Entrez votre nombre : ");
    scanf("%d",&nb);

    while(nb != -1){
        somme += nb;
        cmpt++;
        printf("Entrez votre nombre : ");
        scanf("%d",&nb);
    }

    if(cmpt == 0){
        printf("Erreur : votre liste de valeurs est vide.");
    }
    else{
        printf("la moyenne de ces valeurs est de : %.2f", 1.0*somme/cmpt);
    }
}