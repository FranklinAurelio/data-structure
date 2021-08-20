//
//  main.c
//  insertionSort_recursivo
//
//  Created by Franklin Carvalho on 12/05/21.
//

#include <stdio.h>
#include <stdlib.h>

void sort(int A[],int n){
    int i,value,h;
    for(i=1;i<n;i++){
        value = A[i];
        h = i;
        while(h>0 && A[h-1] > value){
            A[h] = A[h-1];
            h = h-1;
        }
        A[h] = value;
    }
}
int recursive_binary_search(int vector[], int begin, int end, int item){
    int i = (begin + end) / 2;
    
    if (begin > end) {
        return end+1;
    }
    if (vector[i] == item) {
        return  i;
    }
    else if (vector[i] < item) {
        return recursive_binary_search(vector, i + 1, end, item);
    }
    else {
        if(item< vector[i-1]){
            return recursive_binary_search(vector, begin, i - 1, item);;
        }
      //tratar os nimeros menores
        else{
            return i;
        }
    }
}

int sort_recursive(int vet[],int n, int i, int cont){
    int valor, j, ind;
    valor = vet[i];
    j = i;
    ind =  recursive_binary_search(vet, 0, j, valor);
    cont --;
    while (j > ind) {
        vet[j] = vet[j-1];
        j--;
    }
    vet[ind]= valor;
    printf("%d %d %d\n",cont, vet[ind],ind);
    i= i+1;
    if(i==n){
        return EXIT_SUCCESS;
    }
    return  sort_recursive(vet,n,i, cont);
    
        
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //int vet[] = {7,4,8,5,6,9,3,2,1};
    int n, i, j, numb, cont;
    i=1;
    scanf("%d", &n);
    while (n>1000) {
        scanf("%d", &n);
    }
    int vet[n];
    for (j=0; j<n; j++) {
        vet[j]=0;
    }
    cont = n;
    for (j=0; j<n; j++) {
        scanf("%d",&numb);
        vet[j]=numb;
    }

    sort_recursive(vet,n,i,cont);

    for(i=0;i<n;i++)
        printf("%d ",vet[i]);
    return 0;
}
