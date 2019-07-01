    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAX 1023

    typedef struct TipoItem{
        int numb;
        char caracter;
        struct TipoItem *ant;
        struct TipoItem *prox;
    }TipoItem;

    typedef struct TipoList{
        TipoItem *inicio;
        TipoItem *fim;
        int tam;
    }TipoList;

    void inicializa_lista (TipoList *lista){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tam = 0;
    }

    void print_out (TipoList *list_aux){
        TipoItem *novo = list_aux->inicio;
        while(novo != NULL){
            printf("%d%c",novo->numb, novo->caracter);
        novo = novo->prox;
        }
    }

    void insere(TipoList *list_aux, char *caracter, int i){
        TipoItem *new_item;
        new_item = (TipoItem *) malloc(sizeof (TipoItem));
        //printf("here");

        if(new_item == NULL) exit(1);
           new_item->caracter = caracter[i];

        if(list_aux->inicio == NULL){
            list_aux->inicio = new_item;
            list_aux->fim = new_item;
            new_item->ant = NULL;
            new_item->prox = NULL;
            new_item->numb = 1;
            list_aux->tam = 2;

        }
        else{
            if(list_aux->fim->caracter == caracter[i]){
                free(new_item);
                list_aux->fim->numb++;

                if(list_aux->fim->numb == 10){
                    list_aux->tam++;

                }
                else if(list_aux->fim->numb == 100){
                    list_aux->tam++;
                }
                else if(list_aux->fim->numb == 1000){
                    list_aux->tam++;
                }
            }
            //printf("%d",list_aux->tam);
            else{
                new_item->ant = list_aux->fim;
                new_item->prox = NULL;
                new_item->numb = 1;
                list_aux->fim->prox = new_item;
                list_aux->fim = new_item;
                list_aux->tam++;
                list_aux->tam++;
            }
        }
        //printf("%d",list_aux->tam);
    }



    void compression (TipoList *list_aux){
        TipoItem *aux = list_aux->inicio;

        while(aux != NULL){

            if((aux == list_aux->inicio) && (aux->numb == 1) && (aux->prox != NULL) && (aux->prox->numb > 1)){

                TipoItem *Aux = aux;
                aux = aux->prox;
                aux->numb++;
                if(aux->numb == 10){
                    list_aux -> tam++;
                }
                if(aux->numb == 100){
                    list_aux -> tam++;
                }
                if(aux->numb == 1000){
                    list_aux->tam++;
                }
                list_aux->inicio = aux;
                aux->ant = NULL;
                Aux->prox = NULL;
                free(Aux);
                list_aux->tam = list_aux->tam-2;
            //printf("aqui");
            }
            else if((aux != list_aux->inicio) && (aux->numb == 1) && (aux != list_aux->fim) && (aux->ant->numb > 1) && (aux->prox->numb > 1)){
                TipoItem *Aux = aux;
                if(aux->ant->numb < aux->prox->numb){
                    aux->prox->numb++;
                    if(aux->prox->numb==10){
                        list_aux->tam++;
                    }
                    if(aux->prox->numb==100){
                        list_aux->tam++;
                    }
                    if(aux->prox->numb==1000){
                        list_aux->tam++;
                    }
                }
                else{
                    aux->ant->numb++;
                    if(aux->ant->numb==10){
                        list_aux->tam++;
                    }
                    if(aux->ant->numb==100){
                        list_aux->tam++;
                    }
                    if(aux->ant->numb==1000){
                        list_aux->tam++;
                    }
                }
                aux = aux->prox;
                aux->ant = Aux->ant;
                Aux->ant->prox = Aux->prox;
                Aux->ant = NULL;
                Aux->prox = NULL;
                //printf("%d",Aux);
                free(Aux);
                //printf("%d",Aux);
                list_aux->tam = list_aux->tam-2;
            }
            else if((aux != list_aux->inicio) && (aux->ant->numb > 1) && (aux->numb == 1) && (aux == list_aux->fim)){
                aux->ant->numb++;
                if(aux->ant->numb==10){
                    list_aux->tam++;
                }
                if(aux->ant->numb==100){
                    list_aux->tam++;
                }
                if(aux->ant->numb==1000){
                    list_aux->tam++;
                }
                TipoItem *Aux = aux;
                list_aux->fim = list_aux->fim->ant;
                aux = aux->prox;
                Aux->ant->prox = Aux->prox;
                Aux->ant = NULL;
                free(Aux);
                list_aux->tam = list_aux->tam-2;
            }
            else aux = aux->prox;
        }
    }

    void data_output(TipoList *list_aux){

        TipoItem *novo_item = list_aux->inicio;

        while(novo_item != NULL){

            if(novo_item->numb != 0){
                printf("%d%c", novo_item->numb, novo_item->caracter);
            }
            TipoItem *aux = novo_item;
            novo_item = novo_item->prox;
            list_aux->inicio = novo_item;

            if(list_aux->fim == aux){
                list_aux->fim = NULL;
            }
            if(novo_item != NULL){
                novo_item->ant = NULL;
            }
            aux->prox = NULL;
            free(aux);
        }
    }

    int main(){
        TipoList list;
        char string[MAX];
        int i;
        inicializa_lista(&list);
        scanf("%s", &string);

        for(i = 0; i < strlen(string); i++)
            insere(&list, string, i);

        printf("%d\n", list.tam);
        print_out(&list);
        compression(&list);
        printf("\n%d\n", list.tam);
        data_output(&list);

        return 0;
    }
