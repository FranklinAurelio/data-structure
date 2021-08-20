//
//  main.c
//  BubbleSortGame
//
//  Created by Franklin Carvalho on 07/05/21.
//
#include <stdio.h>
#include <stdlib.h>
#define max 1000

void Troca(int *vetor,int i,int j){
    int aux;
    aux=vetor[j];
    vetor[j]=vetor[i];
    vetor[i]=aux;
}
void ord_Bolha(int *vetor,int n, int *winner){
    int i,j,cont,cont2;
    cont2 = 0;
    for(i=0;i<n-1;i++){
        cont=0;
        for(j=0;j<n-i-1;j++){
            if(vetor[j]>vetor[j+1]){
                Troca(vetor,j,j+1);
                cont++;
                cont2 ++;
                //printf("%d ",cont2);
            }
        }
        //cont2 ++;
        //printf("%d ",cont2);
        if(cont==0)
            break;
    }
    //printf("here");
    //printf("%d ", cont2);
    if(cont2 % 2 != 0){
        *winner = 1;
    }
    else{
        *winner = 0;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int i, sizeVet, numb, winner;
    scanf("%d", &sizeVet);
    while (sizeVet>1000) {
        scanf("%d", &sizeVet);
    }
    int vet[sizeVet];
    for (i=0; i<sizeVet; i++) {
        vet[i] = 0;
    }
    for (i=0; i<sizeVet; i++) {
        scanf("%d",&numb);
        vet[i] = numb;
    }
    ord_Bolha(vet, sizeVet, &winner);
    for (i=0; i<sizeVet; i ++){
        printf("%d ", vet[i]);
    }
    if(winner == 1){
        printf("\nMarcelo");
    }
    else{
        printf("\nCarlos");
    }
    return 0;
}
