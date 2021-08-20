//
//  main.c
//  Grafo
//
//  Created by Franklin Carvalho on 12/08/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define Max 1024

/*
void *Dijkstra(Grafo *grafo, int t){
    int D[t],Pi[t],nodo,tamanho=1,x=0,part,dest,peso,flag;
    Aresta *solucao =(Aresta*)malloc(sizeof(Aresta)*50);
    Heap *elemento=(Heap*)malloc(sizeof(Heap));
    Heap *heap=(Heap*)malloc(sizeof(Heap)*1);
    Nodo *no=grafo->ListaNodos;
    Aresta *aux;
    for(int x=0; x < t;x++){
        D[x]=10000;
        Pi[x]=0;
    }
        printf("Informe o nodo de partida \n");
        scanf("%d",&nodo);
        part=nodo;
        x=0;
        D[nodo-1]=0;
        solucao[x].chave_adj=part;
        solucao[x].chave_part=part;
        solucao[x].peso=0;
        x++;
            while (no != NULL){
                if(no->chave == nodo){
                Aresta *aux=no->adj;
                    while(aux != NULL){
                        elemento->peso=aux->peso;
                        elemento->chave_part=aux->chave_part;
                        elemento->chave_dest=aux->chave_adj;
                        heap=buildHeap(heap,tamanho++,elemento);
                          aux=aux->prox;
                    }
                }
                no = no->prox;
            }
            while(tamanho != 0){
                elemento=deleteHeap(heap,tamanho--);
                dest=elemento->chave_dest;
                part=elemento->chave_part;
                peso=elemento->peso;
                flag=0;
                for(int i=0;i<=t;i++){
                    if(solucao[i].chave_adj==elemento->chave_dest){
                        flag=1;
                    }
                }
                if(flag!=1){
                    solucao[x].chave_adj=dest;
                    solucao[x].chave_part=nodo;
                    x++;
                }
                    if(D[dest-1] > D[part-1] + peso){
                        Pi[dest-1]=part;
                        D[dest-1]=D[part-1] + peso;
                        Nodo *no=grafo->ListaNodos;
                            while (no != NULL){
                                if(no->chave == dest){
                                    Aresta *aux=no->adj;
                                    while(aux != NULL){
                                        elemento->peso=aux->peso;
                                        elemento->chave_part=aux->chave_part;
                                        elemento->chave_dest=aux->chave_adj;
                                        heap=buildHeap(heap,tamanho++,elemento);
                                          aux=aux->prox;
                                    }
                                }
                                no = no->prox;
                            }
                    }
            }
            int v;
        for(int l=1;l<t;l++){
            v=solucao[l].chave_adj;
                for(int j=0; j < t;j++){
                    if(solucao[j].chave_adj == v){
                        solucao[j].peso = D[v-1];
                    }
                }
        }
        x--;
        while(x >= 0){
            printf("PARTIDA %d DESTINO %d PESO %d \n",solucao[x].chave_part,solucao[x].chave_adj,solucao[x].peso);
               x--;
       }
    return 0;
}
*/

struct AdjListNode{
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList{
    struct AdjListNode* head;
};

struct Graph{
    int v;
    struct AdjList *array;
};

struct AdjListNode* newAdjListNode(int dest, int weight){
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int v){
    int i;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;

    graph->array = (struct AdjList*)malloc(sizeof(struct AdjList)*v);

    for(i=0;i<v;i++)
        graph->array[i].head = NULL;

    return graph;
}

void AddEdge(struct Graph* graph,int src, int dest, int weight){
    struct AdjListNode* newNode = newAdjListNode(dest,weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src,weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

struct MinHeapNode{
    int v;
    int dist;
};

struct MinHeap{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode* newMinHeapNode(int v, int dist){
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity){
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(sizeof(struct MinHeapNode*)*capacity);

    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeapify(struct MinHeap* minHeap, int i){
    int l = 2*i + 1;
    int r = 2*i + 2;

    int smallest = i;

    if(l < minHeap->size && minHeap->array[l]->dist <  minHeap->array[smallest]->dist){
        smallest = l;
    }

    if(r < minHeap->size && minHeap->array[r]->dist < minHeap->array[smallest]->dist){
        smallest = r;
    }

    if(smallest!=i){
        struct MinHeapNode* smallestnode = minHeap->array[smallest];
        struct MinHeapNode* iNode = minHeap->array[i];

        minHeap->pos[smallestnode->v] = i;
        minHeap->pos[iNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[i]);
        MinHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* heap)
{
    return heap->size == 0;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist){
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while(i && minHeap->array[i]->dist < minHeap->array[(i-1)/2]->dist){
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i-1)/2]);

        i = (i-1)/2;
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap){
    if(isEmpty(minHeap)){
        return NULL;
    }

    struct MinHeapNode* root = minHeap->array[0];

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size-1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    MinHeapify(minHeap,0);

    return root;
}

int isInMinHeap(struct MinHeap* minHeap, int v){
    if(minHeap->pos[v] < minHeap->size){
        return 1;
    }

    else{
        return 0;
    }
}

void printpath(int parent[], int v){
    if(parent[v]==v){
        return;
    }
    printpath(parent,parent[v]);
    printf("%d->",parent[v]);
}

void printarr(int dist[], int n,int parent[]){
    int i;
    //printf("Vertex   distance from Source   Path\n");
    for(i=0; i<n ;i++){
        printf("%d",dist[i]);
        if (i<n-1) {
            printf(" ");
        }
        //printpath(parent,i);
        //printf("%d\n",i);
    }
}

void dijkstra(struct Graph* graph, int src, int restricao){
    int V = graph->v;
    int v;
    struct MinHeap* minHeap = createMinHeap(V);
    int dist[V];
    minHeap->size = V;
    int parent[V];
    parent[src] = src;

    for(v=0;v<V;v++){
        dist[v] = Max;
        minHeap->array[v] = newMinHeapNode(v,Max);
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    decreaseKey(minHeap,src,dist[src]);

    while(!isEmpty(minHeap)){
        struct MinHeapNode* minNode = extractMin(minHeap);
        struct AdjListNode* crawl;
        int u = minNode->v;

        for(crawl = graph->array[u].head; crawl; crawl = crawl->next){
            int v = crawl->dest;

            if(isInMinHeap(minHeap,v) && dist[u]<Max && dist[u]+crawl->weight < dist[v]){
                dist[v] = crawl->weight + dist[u];
                parent[v] = u;
                decreaseKey(minHeap,v,dist[v]);
            }
            
          
        }
    }
    printarr(dist,V,parent);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //Tfila fila;
    int initialNo, restricao, numbNo, numbArestas, arestasOringem, arestasDest, peso;
    int i;
    //Grafo *grafo=inicia();
    //Tfila_inicia(&fila);
   /* for (i=0; i<4; i++) {
        Tfila_insere(&fila, i+1);
    }
    for (i=0; i<fila.tamanho; i++) {
        printf("fila %d", fila.comeco->info);
        fila.comeco = fila.comeco->prox;
    }*/
    
    
    struct Graph* graph;

    
    do {
        scanf("%d",&initialNo);
    } while ((initialNo<0)||(initialNo>100));
    
    do {
        scanf("%d",&restricao);
    } while ((restricao<-1024)||(restricao>1024));
    
    do {
        scanf("%d",&numbNo);
    } while ((numbNo<0)||(numbNo>100));
    
    graph = createGraph(numbNo);
    
    do {
        scanf("%d",&numbArestas);
    } while ((numbArestas<1)||(numbArestas>1024));
    
    //grafo=lst_grafo(grafo,numbNo);
    
    for (i=0; i<numbArestas; i++) {
        scanf("%d",&arestasOringem);
        scanf("%d",&arestasDest);
        scanf("%d",&peso);
        AddEdge(graph, arestasOringem, arestasDest, peso);
        
        //grafo=adjacencia(grafo,arestasOringem,arestasDest,peso);
        //addEdge(graph, arestasOringem, arestasDest);
    }
        dijkstra(graph,initialNo, restricao);
    
    /*Nodo *no = grafo->ListaNodos;
                    no=grafo->ListaNodos;
                     while (no != NULL){
                         Aresta *aux=no->adj;
                            while(aux != NULL){
                                printf("Chave %d adjacencia %d Peso %d \n",no->chave,aux->chave_adj,aux->peso,aux->chave_part);
                                aux=aux->prox;
                            }
                        no = no->prox;
                     }
    Dijkstra(grafo, numbNo);*/


    //printGraph(graph);
    
    return 0;
}
