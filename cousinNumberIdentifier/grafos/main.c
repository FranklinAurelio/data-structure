//
//  main.c
//  grafos
//
//  Created by Franklin Aurelio on 01/10/20.
//  RA: 120384
//  Turma: Professora Regina
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

//####TAD matriz de adjacencia ####
typedef struct{
    int **matriz;
    int tam;
}Tadjacencia;
 
void Tadjacencia_inicia(Tadjacencia *adjacencia,int n){
    int i,j;
    //Alocacao da matriz;
    adjacencia->matriz=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++){
        adjacencia->matriz[i]=(int*)malloc(n*sizeof(int));
        for(j=0;j<n;j++)
            adjacencia->matriz[i][j]=0;
    }
    adjacencia->tam=0;
}
void Tadjacencia_insere(Tadjacencia *adjacencia,int i,int j){
    if(i!=j){
        adjacencia->matriz[i][j]++;
        adjacencia->matriz[j][i]++;
    }
    else
        adjacencia->matriz[i][j]++;
    adjacencia->tam++;
}
void Tadjacencia_retira(Tadjacencia *adjacencia,int i,int j){
    if(i!=j){
        adjacencia->matriz[i][j]--;
        adjacencia->matriz[j][i]--;
    }
    else
        adjacencia->matriz[i][j]--;
    adjacencia->tam--;
}
void Tadjacencia_libera(Tadjacencia *adjacencia,int n){
    int i;
    for(i=n;i>=0;i--)
        free(adjacencia->matriz[i]);
    free(adjacencia->matriz);
    adjacencia->tam=0;
}
//#### FIM TAD ####

typedef struct TipoCelula{
        int usuario;
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

int verification(Tgrafo *grafo, int in_user){
    int i;
    for(i = 0; i < grafo->Ni; i++)
        if(grafo->vet_usuarios->usuario == in_user)
            return 0;
           // printf("here");
    return 1;
}

int indice(Tgrafo *grafo, char in_user){

    int i, indice = 0;

    for(i = 0; i < grafo->Ni; i++)
        if(grafo->vet_usuarios->usuario == in_user)
            indice = i;
    return indice;
}

void insere_grafo(Tgrafo *grafo, char user_one, char user_two){

    if(verification(grafo, user_one))
    {
        grafo->vet_usuarios[grafo->Ni].usuario = user_one;
        grafo->Ni++;
    }

    if(verification(grafo, user_two))
    {
        grafo->vet_usuarios[grafo->Ni].usuario = user_two;
        grafo->Ni++;
    }

    grafo->adj[indice(grafo, user_one)][indice(grafo, user_two)] = 1;
    grafo->adj[indice(grafo, user_two)][indice(grafo, user_one)] = 1;

       // printf("%c",user_one);
       // printf("%c",user_two);
}

void printAdj(Tgrafo *grafo){
    int i,j;
    for (i=0; i< grafo->numb_v; i++){
        for(j=0; j< grafo->numb_v; j++){
            printf("%d",grafo->adj[i][j]);
        }
        printf("\n");
    }
}

int search_graph(Tgrafo *grafo){
    int i, j;
    int vert_friends[MAX];
    int cont_friends[MAX] = {0};
    int tam ,cont;
    tam = 0;
    cont = 0;

    for(i = 1; i < grafo->numb_v; i++)

        if(grafo->adj[0][i]){
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
    int input_1, input_2;
    scanf("%d", &input_1);
    scanf("%d %d", &numb_peoples, &conex);

    inicializa_grafo(&grafo, numb_peoples);
    grafo.vet_usuarios->usuario = input_1;
    grafo.Ni++;

    for(i = 0; i < conex; i++)
    {
        scanf("%d %d", &input_1, &input_2);
        insere_grafo(&grafo, input_1, input_2);
    }
        //printf("here");
    printAdj(&grafo);
    printf("%d", search_graph(&grafo));
    free(grafo.vet_usuarios);

    for(i = 0; i < grafo.numb_v; i++)
        free(grafo.adj[i]);
    free(grafo.adj);
        //printf("here");
    return 0;
}
