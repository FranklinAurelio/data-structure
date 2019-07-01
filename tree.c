    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #define MAX 1024

    typedef struct Tno{
        struct Tno *esq;
        struct Tno *dir;
        int freq;
        char info;
    } Tno;

    Tno *create_node(int numb, char caracter){
        Tno *no = (Tno *) malloc(sizeof (Tno));
        no->freq = numb;
        no->info = caracter;
        no->esq = NULL;
        no->dir = NULL;
        //printf("here");
        return no;
    }

    Tno *insere_node(Tno *node_aux, int numb, char caracter){
        Tno *novo = create_node(numb, caracter), *aux = node_aux;
        if(node_aux == NULL)
            return novo;

        while(1){
            if(aux->freq > numb && aux->esq == NULL)
            {
                aux->esq = novo;
                return node_aux;
            }

            else
                if(aux->freq > numb && aux->esq != NULL)
                aux = aux->esq;
            else
                if(aux->freq <= numb && aux->dir == NULL){
                aux->dir = novo;
                return node_aux;
            }
            else
                if(aux->freq <= numb && aux->dir != NULL)
                aux = aux->dir;
        }
    }

    void print_out(Tno *node_aux)
    {
        if(node_aux == NULL)
            return ;
            //exit(-1);
        //printf("chegou aqui");
        print_out(node_aux->esq);
        printf("%c", node_aux->info);
        print_out(node_aux->dir);
    }

    Tno *remove_node(Tno *node_aux, int freq, char caracter)
    {
        Tno *filho;
        Tno *antecessor;

        if(node_aux == NULL)
            return NULL;

        if(freq < node_aux->freq)
            node_aux->esq = remove_node(node_aux->esq, freq, caracter);

        else
            if(freq > node_aux->freq)
            node_aux->dir = remove_node(node_aux->dir, freq, caracter);

        else
            if(freq == node_aux->freq && node_aux->info != caracter)
            node_aux->dir = remove_node(node_aux->dir, freq, caracter);

        else
        {
            if(node_aux->esq == NULL && node_aux->dir == NULL)
            {
                free(node_aux);
                return NULL;
            }
            if(node_aux->esq != NULL && node_aux->dir == NULL)
            {
                filho = node_aux->esq;
                free(node_aux);
                return filho;
            }
            if(node_aux->dir != NULL && node_aux->esq == NULL)
            {
                filho = node_aux->dir;
                free(node_aux);
                return filho;
            }

            antecessor = node_aux;
            for(filho = node_aux->esq; filho->dir != NULL; filho = filho->dir)
                antecessor = filho;

            node_aux->info = filho->info;
            node_aux->freq  = filho->freq;

            if(antecessor == node_aux)
                antecessor->esq = filho->esq;

            else
                antecessor->dir = filho->esq;

            free(filho);
        }
        return node_aux;
    }

    Tno *release_tree(Tno *node_aux)
    {
        if(node_aux != NULL)
        {
            node_aux->esq = release_tree(node_aux->esq);
            node_aux->dir = release_tree(node_aux->dir);
            free(node_aux);
        }
        return NULL;
    }

    int main()
    {
        Tno *arvore = NULL;
        int  i, cont[26] = {0};
        char data_input[MAX];
        char caracter, caracter_02;

        scanf("%c %c", &caracter, &caracter_02);
        scanf("%s", &data_input);

        //tam = strlen(data_input);
        for(i = 0; i < strlen(data_input); i++)
            cont[data_input[i]-65]++;
        //printf("%d",cont);
        for(i = 0; i < 26; i++)
            if(cont[i] != 0)

                arvore = insere_node(arvore, cont[i], i+65);

        arvore = remove_node(arvore, cont[caracter-65], caracter);
        arvore = remove_node(arvore, cont[caracter_02-65], caracter_02);

        print_out(arvore);
        arvore = release_tree(arvore);

        return 0;
    }


