//
//  main.c
//  K-esimo elemento
//
//  Created by Franklin Carvalho on 26/05/21.
//

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef int TChave;

typedef struct {
    TChave Chave;
      
} TItem;

TItem *Aloca(int n){
    return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
}

int Carrega(TItem **A){
    int i, n;
    scanf("%d", &n);

    (*A) = Aloca(n);
    for (i = 0; i < n ; i++)
        scanf("%d", &(*A)[i].Chave);

    return n;
}

void Libera(TItem **A){
    if ((*A) != NULL) {
        free(*A);
        (*A) = NULL;
    }
}

void Imprime(TItem *A, int n){
    int i;
    if (n > 0) {
        printf("%d", A[0].Chave);
        for (i = 1; i < n; i++)
            printf(" %d", A[i].Chave);
        //printf("\n");
    }
}

int quickSort_particao(TItem *A, int p, int r){
    int j, i = -1;
    TItem troca;

    for (j = 0; j < r; j++) {
        if (A[r].Chave >= A[j].Chave) {
            i++;
            troca = A[i];
            A[i] = A[j];
            A[j] = troca;

        }

    }
    troca = A[i+1];
    A[i+1] = A[r];
    A[r] = troca;
    return(i+1);
}
    
int cont;

bool verification(TItem *A, int indice, int p){
    int i;
    bool reult = true;
    for (i=indice; i<p; i++) {
        if (A[indice].Chave > A[i].Chave) {
            reult = false;
            return reult;
        }
        else reult = true;
        
    }
    
    return reult;

}

void quickSort_ordena(TItem *A, int p, int r, int k, int size){
    //int i;
    int pivo ;
    bool verifica =true;
    verifica = verification(A,cont,size);
    
    //printf("cont %d\n", cont);
    if (p <= r && cont != k-1 && verifica == true) {
        pivo = quickSort_particao(A, p, r);
        //printf("%d\n", pivo);
        cont ++;
        quickSort_ordena(A, p, pivo-1, k, size);
        quickSort_ordena(A, pivo+1, r, k, size);
        /*if (6 > 0) {
            printf("%d", A[0].Chave);
            for (i = 1; i < 6; i++)
                printf(" %d", A[i].Chave);
            printf("\n");
        }*/
    }

}



void quickSort(TItem *A, int n, int k){
    quickSort_ordena(A, 0, n-1, k , n);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    TItem *A;
    int n,k;
    
    scanf("%d", &k);
    
    
    n = Carrega(&A);
    quickSort_particao(A, 0, n-1);
    //Imprime(A, n);
    quickSort(A, n, k);
    printf("%do menor elemento eh o %d\n", k, A[k-1].Chave);
    Imprime(A, n);
    Libera(&A);
    
    return 0;
}
