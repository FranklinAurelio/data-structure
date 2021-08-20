//
//  main.c
//  contando Parres_mergeSort
//
//  Created by Franklin Carvalho on 18/05/21.
//

#include <stdio.h>
#include <stdlib.h>

/*void merge(int vetor[],int *left,int *right,int nl,int nr, int cont, int constant){
    int i,j,k;
    i=0;j=0;k=0;
    //printf("cont: %d \n", cont);
    while(i<nl && j<nr){
        printf("nl nr: %d %d\n", nl, nr);
        printf("indices: %d  %d\n", i, j);
        printf("valores indices: %d  %d\n", left[i], right[j]);
        if(left[i] > right[j]*constant){
            cont ++;
            printf("cont: %d \n", cont);
            printf("indices cont: %d  %d\n", left[i], left[j]);
        }
        if(left[i] < right[j]){
            vetor[k++] = left[i++];
        }
        else{
            vetor[k++] = right[j++];
        }
    }
    while(i<nl){
        vetor[k++] = left[i++];
    }
    while(j<nr){
        vetor[k++] = right[j++];
    }

}

void sort(int vetor[],int n, int  cont, int k){
    int mid,*left,*right,i;
    if(n<4) return ;
    mid = n/2;
    left = (int *)malloc(sizeof(int)*mid);
    right = (int *)malloc(sizeof(int)*(n-mid));
    printf("vetor l: ");
    for(i=0;i<mid;i++){
        left[i] = vetor[i];
        printf("%d ", left[i]);
    }
    printf("\n");
    printf("vetor r: ");
    for(i=mid;i<n;i++){
        right[i-mid] = vetor[i];
        printf("%d ", right[i-mid]);
    }
    printf("\n");
    sort(left,mid, cont, k);
    sort(right,n-mid,cont, k);
    merge(vetor,left,right,mid,n-mid, cont, k);
    free(left);
    free(right);

}
*/
int vet;
void contador(int cont, int tam){
    //int vet[tam];
    //int *list;
    //list = (int *)malloc(sizeof(int)*tam);
    
    //int i;
    cont = cont+cont;
    vet = cont;
    //for (i=0; i<tam; i++) {
        //printf("tam: %d\n", vet[i]);
    //}
    //printf("%d\n", vet[0]);
    //printf("cont1: %d\n", cont);
}
void Concatena (int vet[], int inicio, int meio, int fim, int cont, int constant) {

   int aux[fim-inicio];
   int i, j, k;
   i = 0;
   for (k = inicio; k <= meio; k++) {
        aux[i] = vet[k];
        i++;
   }
   j = ((fim-inicio)/2)+1;
   for (k = fim; k > meio; k--) {
        aux[j] = vet[k];
        j++;
   }

   i = 0;
   j = fim-inicio;

   for (k = inicio; k <= fim; k++) {
       //printf("indices ini: %d %d\n", i, j);
       //printf("valores indices ini: %d %d\n", aux[i],aux[j]);
       if(i < j && aux[i]>aux[j]*constant){
           //printf("indices: %d %d\n", i, j);
           //printf("valores indices: %d %d\n", aux[i],aux[j]);
           cont ++;
           //contador(cont);
           //printf("cont: %d\n", cont+1);
       }
      
       if(aux[i] <= aux[j]) {
           vet[k] = aux[i];
           i++;
       }
       else {
           vet[k] = aux[j];
           j--;
       }
       //printf("cont: %d\n", cont);
   }
    
   // if (cont > 0) {
        //printf("cont: %d\n", cont);
    //}
    //else
        //printf("cont: 0");
    contador(cont, fim);
    //printf("fim: %d\n",fim);
}
void Mergesort (int inicio, int fim, int vet[], int cont, int k) {
    int meio;
    if (inicio < fim) {
        meio = (inicio+fim)/ 2;
        Mergesort(inicio, meio, vet,cont, k);
        Mergesort(meio+1, fim, vet,cont, k);
        Concatena(vet, inicio, meio, fim, cont, k);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int cont, sizeN, k, numb, i;
    cont = 0;

    scanf("%d", &sizeN);
    while (sizeN > 100000) {
        scanf("%d", &sizeN);
    }
    int vetor[sizeN];
    scanf("%d", &k);
    
    for (i=0; i<sizeN; i++) {
        vetor[i] = 0;
    }
    
    for (i=0; i<sizeN; i++) {
        scanf("%d", &numb);
        vetor[i] = numb;
    }

    //for(i=0;i<sizeN;i++){
    //        printf("%d ",vetor[i]);
    //}
    //    printf("\n");
    
        //sort(vetor,sizeN, cont, k);
    Mergesort(0, sizeN-1, vetor, cont, k);

    //for(i=0;i<sizeN;i++){
    //        printf("%d ",vetor[i]);
    //}
    printf("%d", vet);
     
    return 0;
}
