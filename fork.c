    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAX 1024

    typedef struct TipoCelula{
        char usuario[17];
    } TipoCelula;

    typedef struct Tgrafo{
        int numb_v, Ni, **adj;
        TipoCelula *vet_usuarios;
    } Tgrafo;

    void inicializa_grafo(Tgrafo *grafo, int N){
        int i;
        grafo->numb_v = N;
        grafo->Ni = 0;
        grafo->vet_usuarios = malloc(N * sizeof(TipoCelula));
        grafo->adj = malloc(N * sizeof(int *));

        for(i = 0; i < N; i++)
            grafo->adj[i] = calloc(N, sizeof(int));
    }

    int verification(Tgrafo *grafo, char in_user[])
    {
        int i;
        for(i = 0; i < grafo->Ni; i++)
            if(strcmp(grafo->vet_usuarios[i].usuario, in_user) == 0)
                return 0;
           // printf("here");
        return 1;
    }

    int indice(Tgrafo *grafo, char in_user[]){

        int i;

        for(i = 0; i < grafo->Ni; i++)
            if(strcmp(grafo->vet_usuarios[i].usuario, in_user) == 0)
                return i;
    }

    void insere_grafo(Tgrafo *grafo, char user_one[], char user_two[]){

        if(verification(grafo, user_one))
        {
            strcpy(grafo->vet_usuarios[grafo->Ni].usuario, user_one);
            grafo->Ni++;
        }

        if(verification(grafo, user_two))
        {
            strcpy(grafo->vet_usuarios[grafo->Ni].usuario, user_two);
            grafo->Ni++;
        }

        grafo->adj[indice(grafo, user_one)][indice(grafo, user_two)] = 1;
        grafo->adj[indice(grafo, user_two)][indice(grafo, user_one)] = 1;

       // printf("%c",user_one);
       // printf("%c",user_two);
    }

    int search_graph(Tgrafo *grafo)
    {
        int i, j;
        int vert_friends[MAX];
        int cont_friends[MAX] = {0};
        int tam ,cont;
        tam = 0;
        cont = 0;

        for(i = 1; i < grafo->numb_v; i++)

            if(grafo->adj[0][i])
            {
                vert_friends[tam] = i;
                tam++;
            }

        for(i = 0; i < tam; i++)
            for(j = 1; j < grafo->numb_v; j++)
                if(grafo->adj[vert_friends[i]][j] == 1 && grafo->adj[0][j] == 0 && cont_friends[j] == 0){
                    cont++;
                    cont_friends[j]++;
                }
        //printf("%d",cont);
        return cont;
    }

    int main(){
        Tgrafo grafo;
        int numb_peoples, conex, i;
        char peoples_1[17], people_2[17];
        scanf("%s", peoples_1);
        getchar();
        scanf("%d %d", &numb_peoples, &conex);
        getchar();
        inicializa_grafo(&grafo, numb_peoples);
        strcpy(grafo.vet_usuarios[0].usuario, peoples_1);
        grafo.Ni++;

        for(i = 0; i < conex; i++)
        {
            scanf("%s %s", peoples_1, people_2);
            getchar();
            insere_grafo(&grafo, peoples_1, people_2);
        }
        //printf("here");
        printf("%d", search_graph(&grafo));
        free(grafo.vet_usuarios);

        for(i = 0; i < grafo.numb_v; i++)
            free(grafo.adj[i]);
        free(grafo.adj);
        //printf("here");
        return 0;
    }
