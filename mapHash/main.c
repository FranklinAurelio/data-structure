//
//  main.c
//  mapHash
//
//  Created by Franklin Carvalho on 31/07/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct SLista *PLista;

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef int TIndice;

typedef struct {
    PLista Lista;
    TIndice m, n;
} THash;

typedef struct SNo *TCelula;

typedef struct SNo {
    TItem Item;
    TCelula Prox;
} TNo;

typedef struct SLista {
    TCelula Primeiro, Ultimo;
} TLista;

void TLista_Inicializa(TLista *L){
    L->Primeiro = (TCelula) malloc(sizeof(TNo));
    L->Ultimo = L->Primeiro;
    L->Primeiro->Prox = NULL;
}

int TLista_EhVazia(TLista *L){
    return (L->Primeiro == L->Ultimo);
}

void TLista_Insere(TLista *L, TItem x){

        L->Ultimo->Prox = (TCelula) malloc(sizeof(TNo));
        L->Ultimo = L->Ultimo->Prox;
        L->Ultimo->Item = x;
        L->Ultimo->Prox = NULL;

}


void TLista_Remove(TLista *L, TCelula No){
    TCelula aux;

    aux = No->Prox;
    No->Prox = aux->Prox;
    if (No->Prox == NULL){
        L->Ultimo = No;
    }
    free(aux);
}

void TLista_Imprime(TLista *L){
    TCelula No;
    No = L->Primeiro->Prox;
    while (No != NULL) {
        printf(" %d", No->Item.Chave);
        No = No->Prox;
    }
}

void TLista_Libera(TLista *L){
    TCelula No;
    while (L->Primeiro->Prox != NULL) {
        No = L->Primeiro->Prox;
        L->Primeiro->Prox = No->Prox;
        free(No);
    }
    free(L->Primeiro);
}

TIndice h(THash *T, TChave k){
    return k % T->m;
}

THash *Inicializa(int m){
    TIndice i;
    THash *T;
    T = (THash *) malloc(sizeof(THash));
    T->n = 0; T->m = m;
    T->Lista = (PLista) malloc(T->m * sizeof(TLista));
    for (i = 0; i < T->m; i++){
        TLista_Inicializa(&T->Lista[i]);
    }
    return T;
}

TCelula Pesquisa(THash *T, TChave x){
    int i = h(T, x);
    TCelula No;
    No = T->Lista[i].Primeiro;
    if(!TLista_EhVazia(&T->Lista[i])) {
        while(No != NULL) {
            if(No->Item.Chave == x) {
                return(No);
            }
        No = No->Prox;
        }
    }
    return NULL;
}

int Insere(THash *T, TItem x){
    int i = h(T, x.Chave);
    //printf("local: %d\n", i);
    TCelula No;
    No = T->Lista[i].Primeiro;
    TLista_Insere((&T->Lista[i]), x);
    return 1;
}

int Remove(THash *T, TChave x){
    //pegar a posição onde vou remover
    int i = h(T, x);
    //printf("local %d",i);
    TCelula No;
    No = T->Lista[i].Primeiro;
    while(No != NULL) {
        if(No->Prox->Item.Chave == x) {
            TLista_Remove((&T->Lista[i]), No);
           // printf("removendo %d",T->Lista[i]);
            return 1;
        }
        No = No->Prox;
    }
    return 0;
}

void InsereHash(THash *T){
    TItem x;
    
    do {
        scanf("%d", &x.Chave);
        if(x.Chave>=0){
            Insere(T, x);
        }
    } while (x.Chave!= -1);

}

void Libera(THash **T){
    THash *aux;
    int i;

    aux = *T;
    if (aux != NULL) {
        for (i = 0; i < aux->m; i++){
            TLista_Libera(&aux->Lista[i]);
        }
        if (aux->Lista != NULL){
            free(aux->Lista);
        }
        free(aux);
        (*T) = NULL;
    }
}

// printar todo o map hash
void ImprimeHash(THash *T){
    int i;
    if (T->m > 0) {
        for (i = 0; i < T->m; i++) {
            printf("[%d]", i);
            TLista_Imprime(&T->Lista[i]);
            printf("\n");
        }
    }
}

//printar o valor especifico
void printHash(THash *T, int i){
    printf("[%d]", i);
    TLista_Imprime(&T->Lista[i]);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    TIndice sizeHash;
    THash *T;
    TItem keySearch;
    int numb;
        //TCelula No;
    scanf("%d", &sizeHash);
    T = Inicializa(sizeHash);
    InsereHash(T);
    scanf("%d", &keySearch.Chave);
    if (Pesquisa(T, keySearch.Chave) == NULL){
        //Insere(T, x);
        printf("Valor não encontrado\n");
    }
    else{
        Remove(T, keySearch.Chave);
    }
    do {
        scanf("%d",&numb);
    } while (numb<0);
    printHash(T, numb);
    //printf("\n");
    //ImprimeHash(T);
    Libera(&T);
    return 0;
}
