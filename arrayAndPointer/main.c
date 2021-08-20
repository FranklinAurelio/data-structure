//
//  main.c
//  arrayAndPointer
//
//  Created by Franklin Aurelio on 16/08/20.
//  Copyright © 2020 Franklin Aurelio. All rights reserved.
//  RA: 120384
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    int votos, candidatos, cont, vencedor, nWin, *vetVotos = 0, i, j;
    nWin = 0;
    j = 0;
    i = 0;
    cont = 0;
    vencedor = 0;
    // leitura do numero de candidatos
    printf("digite o numero de candidatos: \n");
    scanf("%d",&candidatos);
    printf("a eleicao aconntecera com %d candidatos \n", candidatos);
    do {
        //votacao
        printf("digite o numero do candidato que deseja escolher: \n");
        printf("para encerrara a votacao digite um valor negativo!\n");
        scanf("%d", &votos);
        if(votos > candidatos){
            printf("\n");
            printf("valor incorreto, deigite novamente\n");
            printf("\n");
        }
        else{
        vetVotos = (int *) malloc (sizeof(int));
            if (vetVotos == NULL) {
                printf("nao foi possivel alocar memoria! \n");
            }
        vetVotos[i] = votos;
            i++;
        }
    } while (votos >= 0);
    //analise dos votos
    for (i=0; i<candidatos; i++) {
        for (j = 0; j< sizeof(vetVotos); j++) {
            if (i == vetVotos[j]) {
                cont ++;
            }
        }
        if (vencedor <= cont) {
            vencedor = cont;
            nWin = i+1;
        }
    }
    //resultado
    printf("o vencedor e o candidato numero %d!!!",nWin);
    free(vetVotos);
    return 0;
}
