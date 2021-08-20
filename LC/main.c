//
//  main.c
//  listCircular
//
//  Created by Franklin Aurelio on 03/02/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 50000

//TAD LISTA//
typedef struct Scelula *Tapontador;
typedef struct Scelula{
    char info;
    Tapontador ant;
    Tapontador prox;
}Tcelula;
typedef struct{
    int tamanho;
    Tapontador inicio;
    Tapontador fim;
    Tapontador prox;
}Tlista;

void Tlista_inicia(Tlista *lista){
    Tapontador sentinela;
    sentinela=(Tapontador)malloc(sizeof(Tcelula));
    if(sentinela==NULL)
        exit(-1);
    sentinela->prox=NULL;
    sentinela->info='0';
    lista->prox = sentinela;
    lista->inicio = sentinela;
    lista->fim = sentinela;
    lista->tamanho = 0;
    sentinela = NULL;
}
void Tlista_insere(Tlista *lista,Tapontador anterior,char x){
    //printf("indo inserir %c depois de %c\n", x, anterior->info);fflush(stdout);
    Tapontador novo;
    novo=(Tapontador)malloc(sizeof(Tcelula));
    if(novo==NULL){
        exit (-1);
    }
    else
        if(lista->tamanho == 0){
            novo->info = x;
            novo->prox = anterior->prox;
            novo->ant = anterior;
            lista->fim = novo;
            lista->inicio = novo;
            anterior->prox = novo;
            lista->tamanho++;
        }
    else{
        novo->info = x;
        novo->prox = anterior->prox;
        novo->ant = anterior;
        if(anterior==lista->fim)
            lista->fim = novo;
        anterior->prox = novo;
        lista->tamanho++;
    }
}
void Tlista_retira(Tlista *lista,Tapontador anterior,char *x){
   // printf("indo retirar %c\n", anterior->prox->info);
    Tapontador retirar;
    retirar=anterior->prox;
    anterior->prox=retirar->prox;
    *x=retirar->info;
    lista->tamanho--;
    free(retirar);
}


void printList(Tlista *list){
    Tapontador aux;
    int i;
    i = 0;
    aux = list->inicio->prox;//Pular o sentinela
    for(i=0;i<list->tamanho;i++){
        printf("%c", aux->info);
        aux = aux->prox;
    }
}
//FIM TAD LISTA//

int main(int argc, const char * argv[]) {
    // insert code here...
    Tlista list;
    char inputText[Max];
    long sized;
    int i;
    Tlista_inicia(&list);
    Tapontador anteriorList = list.fim;
    //Tlista_inicia(&listAux);
    scanf("%[^\n]", inputText);
    sized = strlen(inputText);
    char retirada;
    //printf("Tamanho da entrada %d\n", sized);
    for (i = 0; i<sized; i++) {
        if(inputText[i] == '[')
                anteriorList = list.inicio;
        else if (inputText[i] == ']')
                anteriorList = list.fim;
        else if (inputText[i] == '-'){
            if(list.inicio!=anteriorList){
                anteriorList = anteriorList->ant;
                Tlista_retira(&list, anteriorList, &retirada);
            }
        }
        else if (inputText[i] == '<'){
                if(anteriorList != list.inicio)
                    anteriorList = anteriorList->ant;
        }
        else if (inputText[i] =='>'){
                if(anteriorList != list.fim)
                    anteriorList = anteriorList->prox;
                
        }
        else{
            Tlista_insere(&list, anteriorList, inputText[i]);
            anteriorList = anteriorList->prox;
        }
    }
    
    //Tlista_localiza(&list, &listAux);
    printList(&list);
    //free(&list);

    return 0;
}
