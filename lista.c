    #include <stdio.h>
    #include <stdlib.h>

    typedef struct {
        int coefficient;
        int exp;
    } Lcelula;

    typedef struct {
        Lcelula *polynomial;
        int ultimo;
        int tam;
    } ListaSD;
    int inicializa(ListaSD *lista, int tam) {
        lista->ultimo = 0;
        lista->tam = tam;
        lista->polynomial = (Lcelula *) malloc(tam * sizeof(Lcelula));
        if(lista->polynomial == NULL)
            return -1;
        return 0;
    }

    void print_out(ListaSD aux) {
        int i;
        if(aux.ultimo == 0)
            printf("nulo");
        else
            for(i = 0; i < aux.ultimo; i++)
                printf("%+dx%c%d ", aux.polynomial[i].coefficient, 94, aux.polynomial[i].exp);
        printf("\n%d\n", aux.ultimo);
    }

    int busca(ListaSD aux, int chave) {
        int i;
        for(i = 0; i < aux.ultimo; i++)
            if(aux.polynomial[i].exp == chave)
                return i;
        return -1;
    }

    int remover(ListaSD *aux, int indice) {
        int i;
        if(indice >= aux->ultimo)
            return -1;
        for(i = indice; i < (aux->ultimo - 1); i++)
            aux->polynomial[i] = aux->polynomial[i + 1];
        aux->ultimo--;
        return 0;
    }

    int insere(ListaSD *aux, int indice, Lcelula novo) {
        int i;
        if(indice > aux->ultimo)
            return -1;

        for(i = aux->ultimo; i > indice; i--)
            aux->polynomial[i] = aux->polynomial[i - 1];
        aux->polynomial[i] = novo;
        aux->ultimo++;

        return 0;
    }

    ListaSD ordered(ListaSD lista, Lcelula novo) {
        int i;
        if(lista.ultimo == 0) {
            lista.polynomial[0] = novo;
            lista.ultimo++;
            return lista;
        }
        i = busca(lista, novo.exp);
        if(i != -1) {
            lista.polynomial[i].coefficient += novo.coefficient;
            if(lista.polynomial[i].coefficient == 0)
                remover(&lista, i);
            return lista;
        }

        for(i = 0; i < lista.ultimo; i++)
            if(novo.exp > lista.polynomial[i].exp) {
                insere(&lista, i, novo);
                return lista;
            }

        insere(&lista, i, novo);
        return lista;
    }

    int main() {
        int Numb, i;
        Lcelula celula;
        ListaSD lista;
        scanf("%d", &Numb);
        //printf("%d", Numb);
        inicializa(&lista, Numb);

        for(i = 0; i < Numb; i++) {
            scanf("%d %d", &celula.coefficient, &celula.exp);
            //printf("%d", celula.coefficient);
            //printf("%d",celula.exp);
            lista = ordered(lista, celula);
        }

        print_out(lista);
        free(lista.polynomial);

        return 0;
    }
