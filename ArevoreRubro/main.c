//
//  main.c
//  ArevoreRubro
//
//  Created by Franklin Carvalho on 15/07/21.
//
 
#include <stdio.h>
#include <stdlib.h>
 
enum type {RED,BLACK};
 
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
 
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    enum type color;
};
 
struct Queue
{
    struct Node* data;
    struct Queue* next;
};
 
struct Queue* front = NULL;
struct Queue* rear = NULL;
 
struct Node* pfront()
{
    struct Node* data ;
    data = front->data;
    return data;
}
 
int isempty()
{
    if(front==NULL)
        return 1;
 
    else
        return 0;
}
 
void dequeue()
{
    if(isempty())
        return ;
 
    struct Queue* temp = front;
    front = front->next;
    free(temp);
}
 
 
void enqueue(struct Node* data)
{
    struct Queue* temp  =(struct Queue*)malloc(sizeof(struct Queue));
    temp->data = data;
    temp->next = NULL;
 
    if(front==NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }
 
    rear->next = temp;
    rear = temp;
}
 
void levelorder(struct Node* root)
{
    if(root==NULL)
        return;
 
    enqueue(root);
 
    while(!isempty())
    {
        struct Node* current = pfront();
        printf("%d ",current->data);
 
        if(current->left!=NULL)
            enqueue(current->left);
 
        if(current->right!=NULL)
            enqueue(current->right);
 
        dequeue();
    }
}
 
void LeftRotate(struct Node** T,struct Node** x)
{
    struct Node* y = (*x)->right;
    (*x)->right = y->left;
 
    if(y->left!=NULL)
        y->left->parent = *x;
 
    y->parent = (*x)->parent;
 
    if((*x)->parent == NULL)
        *T = y;
 
    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;
 
    else
        (*x)->parent->right = y;
 
    y->left = *x;
 
    (*x)->parent = y;
 
}
void RightRotate(struct Node** T,struct Node** x)
{
    struct Node* y = (*x)->left;
    (*x)->left = y->right;
 
    if(y->right!=NULL)
        y->right->parent = *x;
 
    y->parent = (*x)->parent;
 
    if((*x)->parent==NULL)
        *T = y;
 
    else if((*x)== (*x)->parent->left)
        (*x)->parent->left = y;
 
    else
        (*x)->parent->right = y;
 
    y->right = *x;
    (*x)->parent = y;
 
}
 
void RB_insert_fixup(struct Node** T, struct Node** z)
{
    struct Node* grandparent = NULL;
    struct Node* parentpt = NULL;
 
    while(((*z)!=*T)&& ((*z)->color!= BLACK) && ((*z)->parent->color == RED))
    {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;
 
        if(parentpt == grandparent->left)
        {
            struct Node* uncle = grandparent->right;
 
            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }
 
            else
            {
                if((*z) == parentpt->right)
                {
                    LeftRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }
 
                RightRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
 
        else
        {
            struct Node* uncle = grandparent->left;
 
            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }
 
            else
            {
                if((*z) == parentpt->left)
                {
                    RightRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }
 
                LeftRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;
 
}
 
struct Node* RB_insert(struct Node* T,int data)
{
    struct Node* z = (struct Node*)malloc(sizeof(struct Node));
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;
 
    struct Node* y = NULL;
    struct Node* x = T;//root
 
    while(x!=NULL)
    {
        y = x;
        if(z->data < x->data)
            x = x->left;
 
        else
            x = x->right;
    }
    z->parent = y;
 
    if(y==NULL)
        T = z;
 
    else if(z->data < y->data)
        y->left = z;
 
    else
        y->right = z;
 
    RB_insert_fixup(&T,&z);
 
    return T;
}
 
void Preorder(struct Node* root)
{
    if(root==NULL)
        return;
 
    printf("%d ",root->data);
    Preorder(root->left);
    Preorder(root->right);
}
 
struct Node* Tree_minimum(struct Node* node)
{
    while(node->left!=NULL)
        node = node->left;
 
    return node;
}
 
void RB_delete_fixup(struct Node** T, struct Node** x)
{
    if((*x!= NULL)){
    while((*x)!=*T && (*x)->color == BLACK)
    {
        if((*x)==(*x)->parent->left)
        {
            struct Node* w = (*x)->parent->right;
 
            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                w = (*x)->parent->right;
            }
 
            if(w->left->color==BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }
 
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(T,&w);
                    w = (*x)->parent->right;
                }
 
                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }
 
        else
        {
            struct Node* w = (*x)->parent->left;
 
            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                RightRotate(T,&((*x)->parent));
                w = (*x)->parent->left;
            }
 
            if(w->right->color==BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }
 
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T,&w);
                    w = (*x)->parent->left;
                }
 
                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }
    }
        (*x)->color = BLACK;
 
}
  
}
 
void RB_transplat(struct Node** T, struct Node** u,struct Node** v)
{
    if((*u)->parent == NULL)
        *T = *v;
 
    else if((*u)==(*u)->parent->left)
        (*u)->parent->left = *v;
    else
        (*u)->parent->right = *v;
 
    if((*v)!=NULL)
        (*v)->parent = (*u)->parent;
}
 
struct Node* RB_delete(struct Node *T,struct Node* z)
{
    struct Node *y = z;
    enum type yoc;
    yoc = z->color; // y's original color
 
    struct Node* x;
 
    if(z->left==NULL )
    {
        x = z->right;
        RB_transplat(&T,&z,&(z->right));
    }
 
    else if(z->right==NULL )
    {
        x = z->left;
        RB_transplat(&T,&z,&(z->left));
    }
 
    else
    {
        y = Tree_minimum(z->right);
        yoc = y->color;
        x = y->right;
 
        if(y->parent==z)
           
            x = y->parent;
 
        else
        {
            RB_transplat(&T,&y,&(y->right));
            y->right = z->right;
            y->right->parent = y;
        }
 
        RB_transplat(&T,&z,&y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
 
    if(yoc==BLACK)
        RB_delete_fixup(&T,&x);
 
    return T;
}
 
struct Node* BST_search(struct Node* root, int x)
{
    if(root==NULL || root->data == x)
        return root;
 
    if(root->data > x)
       return  BST_search(root->left,x);
    else
        return BST_search(root->right,x);
}
 
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
 
 
struct Node* FindMin(struct Node* node){
    while(node->left!=NULL){
        node = node->left;
    }
 
    return node;
}
 
int EhNegro(struct Node* No)
{
return (No == NULL) || (No->color == BLACK);
}
int EhRubro(struct Node* No)
{
return (No != NULL) && (No->color == RED);
}
 
int AlturaNegra(struct Node* No)
{
    int esq, dir;
    if(No == NULL)
        return(0);
    else {
        esq = AlturaNegra(No->left); //Conta a altura negra da esquerda
        dir = AlturaNegra(No->right); //Conta a altura negra da direita
    }
 
    if(esq > dir)
        return(EhNegro(No)+esq); //Retorna somente o número de nós negros
    else
        return(EhNegro(No)+dir);
}
 
int height(struct Node* node){
    if(node==NULL){
        return 0;
    }
 
     return findheight(node);
}
 
int main(int argc, const char * argv[]) {
    // insert code here...
    struct Node* RBT = NULL;
 
  
    Tfila fila;
    int  nodeTree, node, i, numb, hight, hightR, hightL,hight2, hightR2, hightL2;
    int verification, j;
    Tfila_inicia(&fila);
    
    i=0;
    
    scanf("%d", &nodeTree);
            if(nodeTree>=0){
                RBT = RB_insert(RBT, nodeTree);
                //rootAux = Insert(rootAux, nodeTree);
            }
    while (nodeTree >=0) {
                scanf("%d", &nodeTree);
                if(nodeTree>=0){
                    RBT = RB_insert(RBT, nodeTree);
                    //rootAux = Insert(rootAux, nodeTree);
                    //queueOfSearch(nodeTree, &filaAux);
                }
            }
    hight = findheight(RBT);
    hightL = findheightL(RBT);
    hightR = findheightR(RBT);
    //printf("gere");
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
    int findHeight[fila.tamanho][3];
    int cont;
    cont = 0;
    for (i=0; i<fila.tamanho; i++) {
        for (j=0; j<3; j++) {
            findHeight[i][j]=0;
        }
    }
    //for (i=0; i<fila.tamanho; i++) {
        //for (j=0; j<3; j++) {
           // printf("%d", findHeight[i][j]);
        //}
    //}
    for (i=0; i<fila.tamanho; i++) {
       // printf("%d", fila.tamanho);
               Search(RBT, fila.comeco->info, &verification);
                //printf("size %d", fila.tamanho);
               
                if(verification == 1){
                    //RBT = Delete(RBT, fila.comeco->info);
                    //struct Node* x = Search(RBT,fila.comeco->info, &verification);
                    struct Node* x = BST_search(RBT,fila.comeco->info);
                    //printf("here");
                    //RBT = RB_delete(RBT, x);
                    hight2 = findheight(x);
                    hightL2 = findheightL(x);
                    hightR2 = findheightR(x);
                   
                    findHeight[cont][0] = findheight(x) ;
                    findHeight[cont][1] = findheightL(x);;
                    findHeight[cont][2] = findheightR(x);
                    
                    cont ++;
                    //printf("x: %d,%d,%d\n",hight2, hightL2,hightR2);
                 
                }
                else{
                    //printf("here");
                    RBT = RB_insert(RBT, fila.comeco->info);
                    //queueOfSearch(fila.comeco->info, &filaAuxAdd);
                    //vetNum[j] = fila.comeco->info;
                    //Preorder(root);
                }
            //printf("%d", fila.comeco->info);
                fila.comeco = fila.comeco->prox;
            }
    //for (i=0; i<cont; i++) {
      //  for (j=0; j<3; j++) {
        //    printf("%d ", findHeight[i][j]);
        //}
       // printf("\n");
    //}
    //for (i=0; i<filaAuxAdd.tamanho; i++) {
      //      Insert(rootAux, filaAuxAdd.comeco->info);
        //    filaAuxAdd.comeco = filaAuxAdd.comeco->prox;
        //}
       
        
        
        scanf("%d",&numb);
            while (numb<0) {
                scanf("%d",&numb);
            }
        //printf("root %d\n",rootAux->data);
        printf("%d,%d,%d\n",hight, hightL,hightR);
        RBT = Search(RBT, numb, &verification);
        //printf("\n");
        //Preorder(rootAux);
        for (i=0; i<cont; i++) {
            for (j=0; j<3; j++) {
                if(j!=2){
                    printf("%d,", findHeight[i][j]);
                }
                else{
                    printf("%d", findHeight[i][j]);
                }
                
            }
            printf("\n");
        }
        if (verification ==1) {
            /*if (numb == 6){
                hight2 = findheight(RBT);
                hightL2 = findheightL(RBT);
                hightR2 = findheightR(RBT)+1;
            }
            else{
                hight2 = findheight(RBT)+1;
                hightL2 = findheightL(RBT)+1;
                hightR2 = findheightR(RBT)+1;
            }
            printf("%d,%d,%d\n",hight2, hightL2,hightR2);*/
            
            printf("%d", AlturaNegra(RBT));
        }
        else{
            printf("Valor nao encontrado");
        }
        
 
    return 0;
}
