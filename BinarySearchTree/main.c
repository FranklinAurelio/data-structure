//
//  main.c
//  BinarySearchTree
//
//  Created by Franklin Aurelio on 23/02/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50000

/*TAD FILA*/
typedef struct Scelula *Tapontador;
typedef struct Scelula{
    char info;
    Tapontador prox;
}Tcelula;
typedef struct{
    int tamanho;
    Tapontador comeco;
    Tapontador fim;
}Tfila;
 
void Tfila_inicia(Tfila *fila){
    fila->tamanho=0;
    fila->comeco=NULL;
    fila->fim=NULL;
}
void Tfila_retira(Tfila *fila,char *x){
    Tapontador aux;
    aux=fila->comeco;
    fila->comeco=fila->comeco->prox;
    *x=aux->info;
    fila->tamanho--;
    free(aux);
}
void Tfila_insere(Tfila *fila,char x){
    //printf("inserindo: %c", x);
    Tapontador novo;
    novo=(Tapontador)malloc(sizeof(Tcelula));
    if(novo!=NULL){
        novo->info=x;
        if(fila->tamanho!=0){
            fila->fim->prox=novo;
            fila->fim=novo;
            novo->prox=NULL;
            fila->tamanho++;
        }
        else{
            fila->comeco=novo;
            fila->fim=novo;
            fila->comeco->prox=NULL;
            fila->tamanho++;
        }
        novo=NULL;
    }
    else
        Tfila_insere(fila,x);
}

void printFila(Tfila *fila){
    Tapontador aux;
    int i;
    aux = fila->comeco;
    printf("(");
    for (i=0; i<fila->tamanho; i++) {
        if(aux->info != '(' && aux->info != ')'){
            printf("c");
        }
        if(aux->info != '(' && aux->info != ')'){
            printf("%d", aux->info - 48);
        }
        else{
        printf("%c", aux->info);
        }
        aux = aux->prox;
    }
    printf(")");
}
/*FIM DO TAD FILA*/

//Insertion and deletion in Binary Search Tree
struct Node{
    struct Node* left;
    int data;
    struct Node* right;
};

struct Queue{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front = NULL;
struct Queue* rear = NULL;

int isEmpty(){
    if(front==NULL)
        return 1;
    else
        return 0;
}

void Pop(){
    if(isEmpty())
        return;

    struct Queue* temp = front;
    front = front->next;
    free(temp);

    
}

struct Node* Pfront(){
    struct Node* temp ;
    temp = front->data;
    return temp;
}

void Enqeue(struct Node* data){
    struct Queue* temp;
    temp = (struct Queue*)malloc(sizeof(struct Queue));
    temp->data = data;
    temp->next=NULL;

    if(front==NULL && rear==NULL){
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear =temp;
}

struct Node* NewNode(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = NULL;
    temp->data = data;
    temp->right = NULL;

    return temp;
}

void PostOrder(struct Node* root){
    if(root==NULL)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ",root->data);
}

struct Node* FindMin(struct Node* root){
    while(root->left!=NULL)
        root = root->left;

    return root;
}

void LevelOrder(struct Node* root){
    if(root==NULL)
        return;

    Enqeue(root);

    while(!isEmpty()){
        struct Node* current = Pfront();
        printf("%d ",current->data);
        if(current->left!=NULL)
            Enqeue(current->left);
        if(current->right!=NULL)
            Enqeue(current->right);

        Pop();
    }
}

struct Node* Delete(struct Node* root,int data){
    if(root==NULL)
        return root;

    else if(data < root->data)
        root->left = Delete(root->left,data);

    else if(data > root->data)
        root->right = Delete(root->right,data);

    else{
        if(root->left==NULL && root->right==NULL){
            free(root);
            root = NULL;
        }

        else if(root->left!=NULL && root->right==NULL){
            struct Node* temp = root->left;
            free(temp);
            root = root->left;
        }
        else if(root->right!=NULL&& root->left==NULL){
            struct Node* temp = root->right;
            free(temp);
            root = root->right;
        }

        else{
            struct Node* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }

    }
    return root;
}

struct Node* Search(struct Node* root,int data, int * verification){
    if(root==NULL){
        *verification = 0;
        return root;
    }

    else if(data < root->data){
        root->left = Search(root->left,data, verification);
    }

    else if(data > root->data){
        root->right = Search(root->right,data, verification);
    }

    else if(data == root->data){
        //printf("entrou aqui\n");
        //printf("%d\n", data);
        //printf("%d\n", root->data);
        *verification = 1;
        //return root;
    }
    
    return root;
}

void InOrder(struct Node* root){
    if(root==NULL)
        return;

    InOrder(root->left);
    printf("%d ",root->data);
    InOrder(root->right);
}

void PreOrder(struct Node* root){
    if(root==NULL)
        return;

    printf("(%d) ",root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void treeToString(struct Node* root, Tfila *fila){
   
    if (root == NULL)
        return;
  
    Tfila_insere(fila, root->data + '0');
  
   // if (!root->left && !root->right)
        //return;
    
    if(root->left){
     
        Tfila_insere(fila,'(');
        
        treeToString(root->left, fila);
        
        Tfila_insere(fila, ')');
     
    }
    if (root->left == NULL){
        Tfila_insere(fila,'(');
        Tfila_insere(fila,')');
    }
    
    if (root->right) {
        Tfila_insere(fila, '(');
    
        treeToString(root->right, fila);
        
        Tfila_insere(fila, ')');

    }
    if (root->right == NULL){
        Tfila_insere(fila,'(');
        Tfila_insere(fila,')');
    }
    
}

struct Node* insert(struct Node* root,int data){
    if(root==NULL)
        root =  NewNode(data);

    else if(data <= root->data)
        root->left = insert(root->left,data);
    
    else root->right = insert(root->right,data);

    return root;

}

void traverse(struct Node* root){
    PreOrder(root);
    printf("\n");
    //printf("\nInorder traversal  :   "); InOrder(root);
    //printf("\nPostOrder traversal:   "); PostOrder(root);
    //printf("\nLevel Order Traversal: ");LevelOrder(root);
}

//MAIN de acordo o enuciado
/*int main(int argc, const char * argv[]) {
    // insert code here...
    Tfila fila;
    struct Node* root = NULL;
    int node, i, j,cont;
    long sizeTree;
    char nodeTree;
    int verification;
    char vet[50000];
    char vetAux[50000];
   // char fina [5];
    char aux1[5], aux2[5];
    
    //char aux;
    Tfila_inicia(&fila);
    i = 0;
    j = 1;
    cont = 0;
    sizeTree = 0;
    

    scanf("%c",&nodeTree);
    while (nodeTree != '\n'){
        vetAux[j] = nodeTree;
        if(nodeTree != ' '){
           // printf("%c\n", nodeTree);
            vet[i] = nodeTree;
            //printf("%c\n", vet[i]);
            sizeTree ++;
            i++;
        }
        if(j!= 1 && vetAux[j-1]!= ' ' && vetAux[j] != ' ' ){
            aux1[0] = vet[i-2];
            aux2[0] = vet[i-1];
        
            strncat(aux1, aux2,5);
           
            cont ++;
           
        }
        sizeTree = sizeTree - cont;
        j++;
        scanf("%c", &nodeTree);
       
        
    }
    for(i = 0; i<sizeTree-1; i++){
        root = insert(root, vet[i]-48);
        //printf("inserindo %d\n", vet[i]);
    }
    //scanf("%d", &node);
    //printf("size %d\n", sizeTree);
    node = vet[sizeTree-1] - 48;
    //printf("node %d\n", node);
    Search(root, node, &verification);
    //printf("%d", verification);
   
    if(verification == 1){
        Delete(root, node);
    }
    else{
        //printf("here");
        root = insert(root, node);
    }
    //nunca entra aqui?
    //else if (verification == 0){
       // printf("here");
       // root = insert(root, node);
   // }
    //traverse(root);
    treeToString(root, &fila);
    printFila(&fila);
    
    return 0;
}
 */
 

//MAIN de acordo a entrada de test exemplo
int main(int argc, const char * argv[]) {
    // insert code here...
    Tfila fila;
    struct Node* root = NULL;
    int sizeTree, nodeTree, node, i;
    int verification;
    Tfila_inicia(&fila);
    i = 0;
    scanf("%d", &sizeTree);
    for(i = 0; i<sizeTree; i++){
        scanf("%d", &nodeTree);
        root = insert(root, nodeTree);
    }
    scanf("%d", &node);
 
    Search(root, node, &verification);
    //printf("%d", verification);
   
    if(verification == 1){
        Delete(root, node);
    }
    else{
        //printf("here");
        root = insert(root, node);
    }
    //nunca entra aqui?
    //else if (verification == 0){
       // printf("here");
       // root = insert(root, node);
   // }
    //traverse(root);
    treeToString(root, &fila);
    printFila(&fila);
    
    return 0;
}
 
 
 
