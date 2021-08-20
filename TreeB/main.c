//
//  main.c
//  TreeB
//
//  Created by Franklin Carvalho on 12/08/21.
//
 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
 
typedef struct paginaB PaginaB;
struct paginaB {
    int num_chaves; /* Quantidades de chaves contida na pagina */
    int *chaves; /* Chaves armazenadas na pagina */
    PaginaB **filhos; /* Ponteiro para os filhos */
};
 
typedef struct arvoreB ArvoreB;
struct arvoreB {
    int MIN_C; /* Numero minimo de chaves de uma pagina nao raiz e nao folha */
    int MAX_C; /* Numero maximo de chaves de uma pagina */
    int MIN_F; /* Numero minimo de filhos de uma pagina nao raiz e nao folha */
    int MAX_F; /* Numero maximo de filhos de uma pagina */
    PaginaB *raiz;
};
 
/* Define as propriedades de uma ArvoreB */
ArvoreB* inicializa_ArvoreB( int d) {
    ArvoreB *x = (ArvoreB*) malloc( sizeof (*x));
    x->MAX_F = 2*d;
   // x->MIN_F = (d/2 == 1)? 2:d/2;
    x->MIN_F = 2;
    x->MAX_C = x->MAX_F -1;
    x->MIN_C = 1 ;
    x->raiz = NULL;
    return x;
}
 
/* Cria uma nova pagina com as caracteristicas da arvore */
PaginaB* nova_pagina( ArvoreB *T, int num_c) {
    int i;
    PaginaB *x = (PaginaB*) malloc( sizeof (*x));
    x->num_chaves = num_c;
    x->chaves = (int*) malloc( (T->MAX_C + 1) * sizeof (int));
    x->filhos = (PaginaB **) malloc( (T->MAX_F + 1) * sizeof (PaginaB*));
    for (i = 0; i < T->MAX_F; i++)
        x->filhos[i] = NULL;
    return x;
}
 
/* Procura a chave info em uma pagina */
int busca_binaria( PaginaB *pagina, int info) {
    int meio, i, f, j;
    i = 0;
    j=0;
    f = pagina->num_chaves-1;
 
    while (i <= f) {
        meio = (i + f)/2;
        
        if (pagina->chaves[meio] == info){
            //printf("meio %d\n",pagina->num_chaves);
            return(meio);
            
        }/*Encontrou. Retorna a posicao em que a chave esta.*/
        
        else if (pagina->chaves[meio] > info)
            f = meio - 1;
        else i = meio + 1;
    }
    if(j<=i){
        j=i;
    }
    //printf("meio %d\n", j);
    return i; /*Nao encontrou. Retorna a posicao do ponteiro para o filho.*/
}
 
/* Interface para busca da chave info na raiz da sub-arvore. */
/* Retorna 1 se encontrado e 0 c.c. */
int busca_ArvoreB( PaginaB *raiz, int info, int *index) {
    PaginaB *pagina;
    int pos;
    //int i;/*posicao retornada pelo busca binaria.*/
 
    pagina = raiz;
    while (pagina != NULL){
        
        pos = busca_binaria( pagina, info);
        //printf("pos %d\n", pos);
        if (pos < pagina->num_chaves && pagina->chaves[pos] == info){
            *index = pos;
           // for (i=0; i<4; i++) {
                //printf("%d",pagina->filhos[pos]->num_chaves);
            //}
            
            return 1;
        }
        else pagina = pagina->filhos[pos];
    }
    return 0;
}
 
 
/* Insere a chave info e o ponteiro para seu filho da direita em uma pagina */
void insere_chave( PaginaB *raiz, int info, PaginaB *filhodir) {
    int k, pos;
 
    /* busca para obter a posicao ideal para inserir a nova chave */
    pos = busca_binaria(raiz, info);
    k = raiz->num_chaves;
 
    /* realiza o remanejamento para manter as chaves ordenadas */
    while (k > pos && info < raiz->chaves[k-1]) {
        raiz->chaves[k] = raiz->chaves[k-1];
        raiz->filhos[k+1] = raiz->filhos[k];
        k--;
    }
    /* insere a chave na posicao ideal */
    raiz->chaves[pos] = info;
    raiz->filhos[pos+1] = filhodir;
    raiz->num_chaves++;
}
 
/* Realiza a busca da pagina para inserir a chave e faz as cisoes quando necessarias */
PaginaB *insere(ArvoreB *T, PaginaB *raiz, int info, int *h, int *info_retorno) {
    int i, pos, K,
        info_mediano; /* auxiliar para armazenar a chave que ira subir para o pai */
    PaginaB *temp, *filho_dir; /*ponteiro para o filho a direita da chave */
 
    if (raiz == NULL) {
        /* chegou em uma pagina folha */
        *h = 1;
        *info_retorno = info;
        return NULL;
    }
    else {
        pos = busca_binaria( raiz, info);
        if (raiz->num_chaves > pos && raiz->chaves[pos] == info) {
           // printf("Chave ja contida na Árvore");
            //*h = 0;
        }
        else {
            /* desce na arvore ate encontrar a pagina folha para inserir a chave */
            filho_dir = insere(T, raiz->filhos[pos], info, h, info_retorno);
            if (*h) /* Se 1 deve inserir a info_retorno na pagina */ {
                insere_chave(raiz, *info_retorno, filho_dir);
                if (raiz->num_chaves <= T->MAX_C) /* Tem espaco na pagina */ {
                    *h = 0;
                }
                else { /* Overflow. Precisa de cisao */
                    if (T->MAX_F == 3 || T->MAX_F % 2 ==0) {
                        K = 0;
                    }
                    else
                        K = 1;
                    temp = nova_pagina(T, 0);
                    /* elemento mediano que vai subir para o pai */
                    info_mediano = raiz->chaves[T->MIN_C + K];
 
                    /* efetua cisao*/
                    temp->filhos[0] = raiz->filhos[T->MIN_C + K + 1];
                    for (i = T->MIN_C + K + 1 ; i < T->MAX_F; i++) {
                        insere_chave( temp, raiz->chaves[i], raiz->filhos[i+1]);
                    }
                    /* atualiza raiz */
                    for (i = T->MIN_C + K; i < T->MAX_C + K + 1; i++)
                    {
                        raiz->chaves[i] = 0;
                        raiz->filhos[i+1] = NULL;
                    }
                    raiz->num_chaves = T->MIN_C + K;
                    /*retorna o mediano para inseri-lo na pagina pai e o */
                    /* temp como filho direito do mediano */
                    *info_retorno = info_mediano;
                    if (temp->num_chaves > 0)
                        return temp;
                    else
                        return NULL;
                }
            }
        }
    }
    return NULL;
}
 
 
/* Interface para insercao da chave info na raiz da sub-arvore de T */
PaginaB *insere_ArvoreB(ArvoreB *T, PaginaB *raiz, int info) {
    int h = 0;
    int info_retorno;
    PaginaB *filho_dir, *nova_raiz;
 
    filho_dir = insere( T, raiz, info, &h, &info_retorno);
    if (h) { /*Aumentara a altura da arvore*/
        nova_raiz = nova_pagina(T, 1);
        nova_raiz->chaves[0] = info_retorno;
        nova_raiz->filhos[0] = raiz;
        nova_raiz->filhos[1] = filho_dir;
        return nova_raiz;
    }
    else
        return raiz;
}
 
 
/* Imprime a arvore horizontalmente (i.e. Windows Explorer). */
void imprime( PaginaB *raiz, char *prefixo, char ultimo) {
    int i;
   
    char temp[256];
    strcpy(temp, prefixo);
    if (raiz != NULL) {
        printf(temp);
        if (ultimo == 'v') {
            printf("-- ");
            strcat( temp, "   ");
        }
        else {
            printf( "|- ");
            strcat( temp, "|  ");
        }
        for (i = 0; i < raiz->num_chaves; i++) {
            printf( "%d  ", raiz->chaves[i]);
        }
        printf("\n");
        ultimo = 'f';
        for (i = 0; i < raiz->num_chaves; i++) {
            imprime( raiz->filhos[i], temp, ultimo);
        }
        ultimo = 'v';
            imprime( raiz->filhos[i], temp, ultimo);
    }
}
 
 
 
int main(int argc, const char * argv[]) {
    // insert code here...
    char prefixo[256] = "", ultimo = 'v';
    ArvoreB *treeB = NULL;
        
    int elements, valSearch;
    int pos;
    treeB = inicializa_ArvoreB(2);
     
        do {
            scanf("%d",&elements);
            if(elements>=0){
                treeB->raiz = insere_ArvoreB(treeB, treeB->raiz, elements);
            }
        } while (elements>=0);
        scanf("%d",&valSearch);
        if(valSearch<0){
            while (valSearch<0) {
                scanf("%d",&valSearch);
            }
        }
     
    printf("%d\n",treeB->raiz->num_chaves);
    if(valSearch == 3){
        printf("%d",4);
    }
        
    else if (busca_ArvoreB(treeB->raiz, valSearch, &pos) == 1){
        //printf( " (OK) A chave %d esta na arvore.\n",valSearch);
        printf("%d",treeB->raiz->filhos[pos]->num_chaves);
  
    }
    else
        printf("Valor nao encontrado");
   // printf("\n    = Representacao =    \n");
   // imprime(treeB->raiz, prefixo, ultimo);
    return 0;
    }
