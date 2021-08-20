//
//  main.c
//  cousinNumberIdentifier
//
//  Created by Franklin Carvalho on 15/04/21.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define max 1000000
int main(int argc, const char * argv[]) {
    int numSize,i, numbers;
    scanf("%d", &numSize);
    while (numSize<1||numSize>10) {
        scanf("%d",&numSize);
    }
    int vetNum[numSize], vetRes[numSize];
    for (i=0; i<numSize; i++) {
        vetNum[i]=0;
        vetRes[i]=0;
    }
    for(i=0; i<numSize;i++){
        scanf("%d", &numbers);
        while (numbers<2||numbers>max) {
            scanf("%d",&numbers);
        }
        vetNum[i] = numbers;
        if(numbers == 2 || numbers == 3 || numbers == 5 || numbers == 11){
           // printf("%d 1\n", numbers);
            vetRes[i] = 1;
        }
        else if(numbers % 2 == 0){
            //printf("%d 0\n",numbers);
            vetRes[i] = 0;
        }
        else if(numbers % 3 == 0){
            //printf("%d 0\n", numbers);
            vetRes[i] = 0;
        }
        else if(numbers % 5 == 0){
            //printf("%d 0\n", numbers);
            vetRes[i] = 0;
        }
        else if (numbers % 11 == 0){
            //printf("%d 0\n", numbers);
            vetRes[i] = 0;
        }
        else{
            //printf("%d 1\n", numbers);
            vetRes[i] = 1;
        }
    }
    for(i=0; i<numSize;i++){
        printf("%d %d\n", vetNum[i], vetRes[i]);
    }
    return 0;
}
