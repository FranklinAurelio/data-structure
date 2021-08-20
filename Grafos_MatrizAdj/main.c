
//
//  main.c
//  Grafos_MatrizAdj
//
//  Created by Franklin Aurelio on 18/02/21.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

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

//####TAD Grafo ####
typedef struct TipoCelula{
        int packege;
    } TipoCelula;

typedef struct Tgrafo{
    int numb_v, Ni, **adj;
    TipoCelula *vetVertice;
} Tgrafo;

void inicializa_grafo(Tgrafo *grafo, int N){
    int i;
    grafo->numb_v = N;
    grafo->Ni = 0;
    grafo->vetVertice = malloc(N * sizeof(TipoCelula));
    grafo->adj = malloc(N * sizeof(int *));

    for(i = 0; i < N; i++)
        grafo->adj[i] = calloc(N, sizeof(int));
}
/*
int verification(Tgrafo *grafo, int indexNumber){
    int i;
    for(i = 0; i < grafo->Ni; i++)
        if(grafo->vetVertice->packege == indexNumber)
            return 0;
           // printf("here");
    return 1;
}

int indice(Tgrafo *grafo, char indexNumber){

    int i, indice = 0;

    for(i = 0; i < grafo->Ni; i++)
        if(grafo->vetVertice->packege == indexNumber)
            indice = i;
    return indice;
}
 */

void insere_grafo(Tgrafo *grafo, int number_one, int number_two, Tgrafo *headquarters){
   // printf("\n here");
    if (number_one != number_two && grafo->adj[number_one][number_two] == 0){
        grafo->adj[number_one][number_two] = 1;
        headquarters->adj[number_one][number_two] = number_two+1;
        //grafo->adj[number_two][number_one] = 1;
        grafo->Ni ++;
        
    }
    //printf("here %d\n", grafo->adj[number_one][number_two]);

    /*if(verification(grafo, number_one)){
        grafo->vetVertice[grafo->Ni].packege = number_one;
        grafo->Ni++;
    }

    if(verification(grafo, number_two)){
        grafo->vetVertice[grafo->Ni].packege = number_two;
        grafo->Ni++;
    }

    grafo->adj[indice(grafo, number_one)][indice(grafo, number_two)] = 1;
    grafo->adj[indice(grafo, number_two)][indice(grafo, number_one)] = 1;
*/
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

/*int search_graph(Tgrafo *grafo){
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

    for(i = 0; i < tam; i++){
        for(j = 1; j < grafo->numb_v; j++)
            if(grafo->adj[i][j] == 1){
                cont++;
                //cont_friends[j]++;
            }
    }
        //printf("%d",cont);
    return cont;
}
*/
int dependents(Tgrafo *graph, int indice){
    int numbOfDependents;
    numbOfDependents = 0;
    int j;
    j = 0;
    
    for (j = 0; j<graph->numb_v; j++){
        if (graph->adj[j][indice] == 1){
            numbOfDependents++;
        }
    }
    return numbOfDependents;
}

int dependencyOfGraph(Tgrafo *graph, int indice){
    int numbOfDependencies;
    numbOfDependencies = 0;
    int j;
    j = 0;
    
    for (j = 0; j<graph->numb_v; j++){
        if (graph->adj[indice][j] == 1){
            numbOfDependencies++;
        }
    }
    return numbOfDependencies;
}


void vetOfDependencies( Tgrafo *graph, int indice, int tamVet){
    int j;
    //int vet[tamVet];
    j = 0;
    for(j= 0; j<graph->numb_v; j++){
        if(graph->adj[indice][j]!= 0){
            printf("%d ", graph->adj[indice][j]);
        }
    }
    printf("\n");
   
}
//#### FIM TAD ####

int main(int argc, const char * argv[]) {
    // insert code here...
    Tgrafo grafo;
    Tgrafo headquarters;
    
    int numb1, rDependency, i, pack, dependency;
    i = 0;
    scanf("%d %d", &numb1, &rDependency);
    //int vet[numb1];
    //verificando se os inputs se encaixam no padrao requerido
    while (numb1< 1 || numb1> 100 || rDependency< 0 || rDependency> 10000) {
        scanf("%d %d", &numb1, &rDependency);
    }
    inicializa_grafo(&grafo, numb1);
    inicializa_grafo(&headquarters, numb1);
    for(i=0; i<rDependency; i++){
        scanf("%d %d", &pack, &dependency);
        //printf("%d %d", pack, dependency);
        insere_grafo(&grafo, pack-1, dependency-1, &headquarters);
    }
    for (i=0; i<numb1; i++) {
        //inserir dependencias e dependentes agora
        printf("%d %d %d ", i+1, dependents(&grafo, i), dependencyOfGraph(&grafo, i));
        vetOfDependencies(&headquarters, i, numb1);
        
    }
    
    //printAdj(&grafo);
    //printAdj(&headquarters);
  
    //printf("%d", search_graph(&grafo));
        
    for(i = 0; i < grafo.numb_v; i++)
        free(grafo.adj[i]);
    free(grafo.adj);
    
    return 0;
}
