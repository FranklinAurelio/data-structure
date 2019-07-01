    #include <stdio.h>
    #include <stdlib.h>

    typedef struct celula{
        int numb;
        int time;
        struct celula *prox;
    } celula;

    typedef struct{
        celula *inicio;
    } Tfila;

    typedef struct celula_atend{
        int numb;
        Tfila fila;
        struct celula_atend *prox;
    } celula_atend;

    typedef struct{
        celula_atend *inicio;
    } Tlista;

    void inicializa(Tfila *fila){
        fila->inicio = NULL;
    }

    void ini_lista(Tlista *lista){
        lista->inicio = NULL;
    }

    void insere_lista(Tlista *lista, int i){
        //printf("chegou");
        celula_atend *aux, *novo = malloc(sizeof(celula_atend));
        novo->numb = i;
        novo->prox = NULL;
        novo->fila.inicio = NULL;
        if(lista->inicio == NULL){
            lista->inicio = novo;
        }
        else{
            for(aux = lista->inicio; aux->prox != NULL; aux = aux->prox);
            aux->prox = novo;
        }
    }


    void insere_na_fila(Tfila *fila, int i, int tmp){
        celula *aux, *novo = malloc(sizeof(celula));
        novo->time = tmp;
        novo->numb = i;
        novo->prox = NULL;

        if(fila->inicio == NULL){
            fila->inicio = novo;
        }
        else{
            for(aux = fila->inicio; aux->prox != NULL; aux = aux->prox);
            aux->prox = novo;
        }
    }

    celula *attended(Tfila *fila){
        celula *aux;
        aux = fila->inicio;

        if(aux != NULL){
            fila->inicio = fila->inicio->prox;
            aux->prox = NULL;
        }
        return aux;
    }

    void withdraw(Tfila *fila){
        celula *aux;

        if(fila->inicio != NULL){
            aux = fila->inicio;
            fila->inicio = fila->inicio->prox;
            //printf("%d",aux);
            free(aux);
        }
    }

    int row_search(Tfila fila, int info){
        celula *aux;

        //printf("here");
        for(aux = fila.inicio; aux != NULL; aux = aux->prox)
            if(aux->numb == info)
                return 1;
        //printf("%d", info);
        return 0;
    }

    int verification(Tlista lista){
        celula_atend *aux;
        //printf("aqui");
        for(aux = lista.inicio; aux != NULL; aux = aux->prox)
            if(aux->fila.inicio == NULL)
                return 0;

        return 1;
    }

    celula *MIN(Tlista *lista){
        celula_atend *aux;
        celula *aux2;
        celula *smaller_row;
        int Aux;
        aux = lista->inicio;

        for(smaller_row = aux->fila.inicio; smaller_row->prox != NULL; smaller_row = smaller_row->prox);

        for(; aux != NULL; aux = aux->prox){

            for(aux2 = aux->fila.inicio; aux2->prox != NULL; aux2 = aux2->prox);

            if(smaller_row->time > aux2->time)
                smaller_row = aux2;
        }
        Aux = smaller_row->time;
        //printf("%d",Aux);

        for(aux = lista->inicio; aux != NULL; aux = aux->prox){

            for(aux2 = aux->fila.inicio; aux2->prox != NULL; aux2 = aux2->prox);
            aux2->time -= Aux;
        }

        return smaller_row;
    }

    void copy_row(Tlista *lista, Tfila *fila){
        int cond1 , i ;
         i= 1;
        cond1 = 0;
        celula_atend *aux;
        celula *aux2;

        while(row_search(*fila, i++)){
            if(cond1 != 1){

                for(aux = lista->inicio; aux->fila.inicio != NULL; aux = aux->prox);
                aux2 = attended(fila);
                aux->fila.inicio = aux2;
                cond1 = verification(*lista);
            }
            else{
                aux2 = MIN(lista);
                aux2->prox = attended(fila);
            }
        }
    }

    void imprime(Tlista lista){
        celula_atend *aux;
        celula *aux2;
        //printf("here");
        for(aux = lista.inicio; aux != NULL; aux = aux->prox){
            printf("%d:", aux->numb);
            for(aux2 = aux->fila.inicio; aux2 != NULL; aux2 = aux2->prox)
                printf(" %d", aux2->numb, aux2->time);
            printf("\n");
        }
    }

    void free_list(Tlista *lista){
        celula_atend *aux;
        celula *aux2;

        for(aux = lista->inicio; aux != NULL; aux = lista->inicio){
            for(aux2 = aux->fila.inicio; aux2 != NULL; aux2 = aux->fila.inicio)
                withdraw(&(aux->fila));
            lista->inicio = lista->inicio->prox;
            free(aux);
        }
    }

    int main(){
        int numb_C, numb_caixas, i, time;
        Tfila fila;
        Tlista lista;

        inicializa(&fila);
        ini_lista(&lista);

        scanf("%d %d", &numb_C, &numb_caixas);
        for(i = 1; i <= numb_caixas; i++)
            insere_lista(&lista, i);
        for(i = 1; i <= numb_C; i++){
            scanf("%d", &time);
           // printf("%d",time);
            insere_na_fila(&fila, i, time);
        }
        copy_row(&lista, &fila);
        imprime(lista);
        free_list(&lista);
        return 0;
    }
