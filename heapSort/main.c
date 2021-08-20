//
//  main.c
//  heapSort
//
//  Created by Franklin Carvalho on 02/06/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a,char *b){
    char *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void newSwap(char *A[][20], char *B[][20]){
    char temp[20];
    strcpy(temp, *A[20]);
    strcpy(*A[20], *B[20]);
    strcpy(*B[20], temp);
}

void Maxheapify(char A[][20],int n,int i){
    int l = (2*i)+1;
    int r = (2*i)+2;
    int largest = i;

    if(l<n && strcmp(A[l], A[largest])>0){
        largest = l;
    }
    if(r<n && strcmp(A[r], A[largest])>0){
        largest = r;
    }
    if(largest!=i){
        //swap(&A[i],&A[largest]);
        //swap
        char temp[20];
        strcpy(temp, A[i]);
        strcpy(A[i], A[largest]);
        strcpy(A[largest], temp);
        Maxheapify(A,n,largest);
    }
}
void Heapsort(char A[][20],int n){
    int i;

    for(i=n/2-1 ;i>=0; i--){
        Maxheapify(A,n,i);
    }
    for(i=n-1; i>=0; i--){
        //swap(&A[0],&A[i]);
        char temp[20];
        //for (j=0; j<20; j++) {
           // printf("antes %c %c\n",A[0][j], A[i][j]);
        //}
        if(strcmp(A[0], A[i])!= 0){
            strcpy(temp, A[0]);
            if(strlen(A[0])> strlen(A[i]))
                strncpy(A[0], A[i], strlen(A[0]));
            else
                strncpy(A[0], A[i], strlen(A[i]));
            if(strlen(A[i])> strlen(temp))
                strncpy(A[i], temp, strlen(A[i]));
            else
                strncpy(A[i], temp, strlen(temp));
        }
       
        //for (j=0; j<20; j++) {
            //printf("after %c %c\n",A[0][j], A[i][j]);
       // }
        Maxheapify(A,i,0);
    }
}

int verificaStr(char A[][20], int tam){
    int i,j, outRet;
    outRet = 0;
    
    for (i=0; i<tam; i++) {
        for (j=0; j<strlen(A[i]); j++) {
            if((A[i][j]<'a' && A[i][j]!='\0')|| (A[i][j]>'z' && A[i][j]!='\0')){
                outRet = i;
                //printf("%d %c\n", outRet, A[i][j]);
                break;
            }
            
        }
        if(outRet!= 0){
            break;
        }
    }
    return outRet;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //int n = sizeof(A)/sizeof(A[0]);
    int i, j;
    int totalNumb, parcialNumb, indices, verificacao;
    //char palavra [20];
    scanf("%d",&totalNumb);
    while (totalNumb>=1000) {
        scanf("%d",&totalNumb);
    }
    char vetStr[totalNumb][20];
    for (i=0; i<totalNumb; i++) {
        for (j=0; j<20; j++) {
            vetStr[i][j] = 0;
        }
    }
    for(i=0; i<totalNumb; i++){
        scanf("%s",vetStr[i]);
    }
    //for (i=0; i<totalNumb; i++) {
        //for (j=0; j<20; j++) {
           // printf("%c", vetStr[i][j]);
        //}
       // printf(" indice: %d ", i);
        //printf("\n");
   // }
    scanf("%d", &parcialNumb);
    while (parcialNumb>= totalNumb) {
        scanf("%d", &parcialNumb);
    }
    //int A[parcialNumb];
    char newVetstr[parcialNumb][20];
    for (i=0; i<parcialNumb; i++) {
        for (j=0; j<20; j++) {
            newVetstr[i][j] = 0;
        }
    }
    for (i=0; i<parcialNumb; i++) {
        scanf("%d", &indices);
        strcpy(newVetstr[i], vetStr[indices]);
            //newVetstr[i][j] = vetStr[indices][j];
            //printf(" %c",vetStr[indices][j]);
        //printf(" %d ", indices);
        //printf("\n");
    }
    verificacao =verificaStr(vetStr, totalNumb);
    //printf("verification %d\n", verificacao);
    if(verificacao!=0){
        printf("a palavra ");
        for (i=0; i<strlen(vetStr[verificacao]); i++) {
            printf("%c", vetStr[verificacao][i]);
        }
        printf(" eh invalida");
    }
    else{
        //printf("verif: %d", verificacao);
        printf("build_heap: ");
        for (i=0; i<parcialNumb; i++) {
            for (j=0; j<strlen(newVetstr[i]); j++) {
                printf("%c",newVetstr[i][j]);
            }
            //if(i<parcialNumb-1){
                printf(" ");
            //}
        }
        //printf("\n");
        //for (i=0; i<parcialNumb; i++) {
            //printf("i %s",newVetstr[i]);
            //Heapsort(newVetstr,parcialNumb);
        //}
        printf("\n");
        Heapsort(newVetstr,parcialNumb);
        printf("palavras: ");
        for (i=0; i<parcialNumb; i++) {
            for (j=0; j<strlen(newVetstr[i]); j++) {
                printf("%c",newVetstr[i][j]);
           }
            if(i<parcialNumb-1){
                printf(" ");
            }
        }
        
    }
    
    
return 0;
}
