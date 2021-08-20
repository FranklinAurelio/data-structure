//
//  main.c
//  Graph_ListAdj
//
//  Created by Franklin Aurelio on 21/02/21.
//

#include <stdio.h>
#include <stdlib.h>

// TAD LIST ADJ
struct AdjListNode{
    int dest;
    struct AdjListNode* next;
    struct AdjListNode* ant;
};

struct Queue{
    int data;
    struct Queue* next;
    struct Queue* ant;
};
struct Queue *front,*rear = NULL;

struct AdjList{
    struct AdjListNode *head;
    struct AdjListNode *tail;
};

struct Graph{
    int v;
    struct AdjList* array;
    
};

struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* new = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    new->dest = dest;
    new->next = NULL;

    return new;
}


struct Graph* createGrpah(int v){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->array = (struct AdjList*)malloc(sizeof(struct AdjList)*v);

    int i;
    for(i=0;i<v;i++){
        graph->array[i].head = NULL;
    }
    return graph;

}

void addEdge(struct Graph* graph, int src, int dest)
{
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    //newNode->next = graph->array[dest].head;
    //graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph, int indice, int numVert, int cont){
    int  i;
    i = 0;

    int vet[numVert] , vet2[numVert];
    for(i = 0; i<numVert; i++){
        vet[i] = 0;
        vet2[i] = 0;
    }
    struct AdjListNode* crawl = graph->array[indice].head;
    //printf("%d ",indice+1);
    while(crawl){
        //printf("%d ",crawl->dest+1);
        //printf("s%lu", sizeof(crawl));
        //i = cont;
        vet[i] = crawl->dest+1;
        printf("%d ", vet[i]);
        crawl = crawl->next;
        i++;
    }
    //for(i=4; i<sizeof(crawl); i++){
       // printf("aa%d ", vet[i]);
        //vet2[i-numVert] = vet[i];
    //}
    //for(i=0; i<4;i++){
        //printf("bb%d ", vet2[i]);
    //}
 
    printf("\n");
}

int printOfTheDependentsOfGraph(struct Graph* graph, int indice, int numVert){
    int cont = 0, i;
    i = 0;
    int contVet[numVert];
    for(i = 0; i<numVert; i++){
        contVet[i] = 0;
    }
    //for (i=0; i<numVert; i++) {
        //printf("%d\n", contVet[i]);
    //}
    for(i=0; i<numVert; i++){
        struct AdjListNode* crawl = graph->array[i].head;
        while(crawl){
            contVet[crawl->dest] ++;
            crawl = crawl->next;
            //i++;
            cont ++;
        }
    }
   
    return contVet[indice];
    //printf("%d ",cont);
}

int printNumDependencies(struct Graph* graph, int indice, int numVert){
    int cont = 0, i;
    i = 0;
    int vet[numVert] ;
    for(i = 0; i<numVert; i++){
        vet[i] = 0;
    }
    struct AdjListNode* crawl = graph->array[indice].head;
    while(crawl){
        vet[i] = crawl->dest+1;
        crawl = crawl->next;
        i++;
        cont ++;
    }
    //printf("%d ",cont);
    return cont;;
}


//FIM TAD

int main(int argc, const char * argv[]) {
    // insert code here...
    //ADD ESSA BOSTA NO FINAL
    int numb1, rDependency, i, pack, dependency, cont, j;
    i = 0;
    j = 0;
    scanf("%d %d", &numb1, &rDependency);
    while (numb1< 1 || numb1> 100 || rDependency< 0 || rDependency> 10000) {
        scanf("%d %d", &numb1, &rDependency);
    }
    struct Graph* graph = createGrpah(numb1);
    for(i=0; i<rDependency; i++){
        scanf("%d %d", &pack, &dependency);
        addEdge(graph, pack-1, dependency-1);
    }
    for (i=0; i<numb1; i++) {
        printf("%d ", i+1);
        printf("%d ",printOfTheDependentsOfGraph(graph, i ,numb1));
        printf("%d ", printNumDependencies(graph, i, numb1));
        cont = printNumDependencies(graph, i, numb1);
        //printf("%d", cont);
        printGraph(graph, i, numb1, cont); //imprimir ao contrario
        
    }

    return 0;
}
