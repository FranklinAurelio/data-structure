//
//  main.c
//  AVL
//
//  Created by Franklin Carvalho on 05/07/21.
//
 
#include "stdio.h"
#include "stdlib.h"
 
typedef struct Scelula *Tapontador;
typedef struct Scelula{
    int info;
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
void Tfila_retira(Tfila *fila){
    Tapontador aux;
    aux=fila->comeco;
    fila->comeco=fila->comeco->prox;
    //*x=aux->info;
    fila->tamanho--;
    free(aux);
}
void Tfila_insere(Tfila *fila,int x){
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
    
    for (i=0; i<fila->tamanho; i++) {
        printf("%d", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}
 
struct Node{
    int data;
    int height;
    struct Node* left;
    struct Node* right;
};
//Insertion and deletion in AVL Tree
struct Node* NewNode(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}
 
int max(int a,int b){
     return (a>b)?a:b;
}
 
int height(struct Node* node){
    if(node==NULL){
        return 0;
    }
 
     return node->height;
}
 
int Balance(struct Node* node){
    if(node==NULL){
        return 0;
    }
 
     return height(node->left) - height(node->right);
}
 
struct Node* LeftRotate(struct Node* z){
    struct Node* y = z->right;
    struct Node* t2 = y->left;
 
    y->left = z;
    z->right = t2;
 
    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
 
    return y;
}
 
struct Node* RightRotate(struct Node* z){
    struct Node* y = z->left;
    struct Node* t3 = y->right;
 
    y->right = z;
    z->left = t3;
 
    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
 
    return y;
}
 
void Preorder(struct Node* root){
    if(root==NULL){
        return;
    }
 
    printf("%d ",root->data);
    Preorder(root->left);
    Preorder(root->right);
}
 
struct Node* FindMin(struct Node* node){
    while(node->left!=NULL){
        node = node->left;
    }
 
    return node;
}
 
struct Node* Delete(struct Node* root,int data){
    if(root==NULL){
        return root;
    }
 
    if(data < root->data){
        root->left = Delete(root->left,data);
    }
 
    else if(data > root->data){
        root->right = Delete(root->right,data);
    }
 
    else{
        if(root->right==NULL && root->left==NULL){
            free(root);
            root = NULL;
        }
 
        else if(root->left!=NULL && root->right==NULL){
            struct Node* temp = root->left;
            root = root->left;
            free(temp);
        }
 
        else if(root->right!=NULL && root->left==NULL){
            struct Node* temp = root->right;
            root = root->right;
            free(temp);
        }
        else{
            struct Node* temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }
    }
    if(root==NULL){
        return root;
    }
 
    root->height = 1 + max(height(root->left),height(root->right));
 
    int balance = Balance(root);
 
    //Left Left Case
    if(balance > 1 && Balance(root->left) >=0){
        return RightRotate(root);
    }
 
    // Right Right Case
    if(balance < -1 && Balance(root->right) <=0){
        return LeftRotate(root);
    }
 
    // Left Right Case
    if(balance > 1 && Balance(root->left) < 0){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    
    //Right Left Case
    if(balance < -1 && Balance(root->right) > 0){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}
 
struct Node* Insert(struct Node* root,int data){
    if(root==NULL){
        return NewNode(data);
    }
 
    if(data < root->data){
        root->left = Insert(root->left,data);
    }
 
    else if(data > root->data){
        root->right = Insert(root->right,data);
    }
 
    else{
        return root;
    }
 
    root->height = max(height(root->left),height(root->right))+1;
 
    int balance = Balance(root);
 
    // Left Left Case
    if(balance > 1 && data < root->left->data){
        return RightRotate(root);
    }
 
    // Right Right Case
    if(balance < -1 && data > root->right->data){
        return LeftRotate(root);
    }
 
    //Left Right Case
    if(balance > 1 && data > root->left->data){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
 
    // Right Left Case
    if(balance < -1 && data < root->right->data){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
 
    return root;
}
 
// calculo da altura do nó
int Max(int x,int y)
{
    return(x>y?x:y);
}
 
int findheight(struct Node* root){
    if(root==NULL)
        return -1;
 
    return((Max(findheight(root->left),findheight(root->right)))+1);
}
 
int findheightL(struct Node* root)
{
    if(root==NULL)
        return -1;
 
    return(findheight(root->left)+1);
}
 
int findheightR(struct Node* root)
{
    if(root==NULL)
        return -1;
 
    return(findheight(root->right)+1);
}
 
 
void queueOfSearch(int numb, Tfila *fila){
   
    if (numb < 0){
        return;
    }
  
    Tfila_insere(fila, numb);
  
}
struct Node* Search(struct Node* root,int data, int * verification){
    if(root==NULL){
        *verification = 0;
        return root;
    }
 
    else if(data < root->data){
        return Search(root->left,data, verification);
    }
 
    else if(data > root->data){
        return Search(root->right,data, verification);
    }
 
    else{
 
        *verification = 1;
        return root;
        
    }
 
}
 
 
int main(int argc, const char * argv[]) {
    // insert code here...
    Tfila fila;
    Tfila filaAuxAdd;
    Tfila filaAuxRem;
    struct Node* root = NULL;
    struct Node* rootAux = NULL;
    int  nodeTree, node, i, numb, hight, hightR, hightL,hight2, hightR2, hightL2;
    int verification, existente = 0;
    Tfila_inicia(&fila);
    Tfila_inicia(&filaAuxAdd);
    Tfila_inicia(&filaAuxRem);
   
    i = 0;
    
    scanf("%d", &nodeTree);
        if(nodeTree>=0){
            root = Insert(root, nodeTree);
            rootAux = Insert(rootAux, nodeTree);
            //queueOfSearch(nodeTree, &filaAux);
        }
    while (nodeTree >=0) {
            scanf("%d", &nodeTree);
            if(nodeTree>=0){
                root = Insert(root, nodeTree);
                rootAux = Insert(rootAux, nodeTree);
                //queueOfSearch(nodeTree, &filaAux);
            }
        }
    //printf("\nPreorder traversal of tree is : \n");
    //Preorder(root);
    
    hight = findheight(root);
    hightL = findheightL(root);
    hightR = findheightR(root);
    scanf("%d", &node);
    queueOfSearch(node, &fila);
        while (node>=0) {
            scanf("%d", &node);
            if(node>=0){
                queueOfSearch(node, &fila);
            }
            else{
                break;
            }
        }
    for (i=0; i<fila.tamanho; i++) {
            
           Search(root, fila.comeco->info, &verification);
            //printf("size %d", fila.tamanho);
           
            if(verification == 1){
               root = Delete(root, fila.comeco->info);
                existente = fila.comeco->info;
                queueOfSearch(fila.comeco->info, &filaAuxRem);
                //Preorder(root);
                //printf("\n");
            }
            else{
                //printf("here");
                root = Insert(root, fila.comeco->info);
                queueOfSearch(fila.comeco->info, &filaAuxAdd);
                //vetNum[j] = fila.comeco->info;
                //Preorder(root);
            }
        //printf("%d", fila.comeco->info);
            fila.comeco = fila.comeco->prox;
        }
    
    /*for (i=0; i<filaAuxRem.tamanho; i++) {
        Delete(rootAux, filaAuxRem.comeco->info);
        filaAuxRem.comeco = filaAuxRem.comeco->prox;
    }*/
    for (i=0; i<filaAuxAdd.tamanho; i++) {
        Insert(rootAux, filaAuxAdd.comeco->info);
        filaAuxAdd.comeco = filaAuxAdd.comeco->prox;
    }
   
    
    
    scanf("%d",&numb);
        while (numb<0) {
            scanf("%d",&numb);
        }
    //printf("root %d\n",rootAux->data);
    printf("%d,%d,%d\n",hight, hightL,hightR);
    root = Search(root, numb, &verification);
    //printf("\n");
    //Preorder(rootAux);
    if (verification ==1) {
        hight2 = findheight(root);
        hightL2 = findheightL(root);
        hightR2 = findheightR(root);
        printf("%d,%d,%d\n",hight2, hightL2,hightR2);
    }
    else{
        printf("Valor nao encontrado");
    }
    
    
    return 0;
}
