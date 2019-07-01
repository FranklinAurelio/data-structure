    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(){
        int i, j, sizeX, sizeY, sizeZ, cont, cont_x, cont_y;
        cont=0;
        j=0;
        char Caracter;
        char *variable_X, *variable_Y, *variable_Z;

        scanf("%d", &sizeX);
        //printf("%d",sizeX)
        sizeX++;
        scanf("%d", &sizeY);
        //printf("%d",sizeY);
        sizeY++;
        getchar();
        scanf("%c", &Caracter);
        //printf("%c",Caracter);
        variable_X = (char *) malloc (sizeX * sizeof(char));
        variable_Y = (char *) malloc (sizeY * sizeof(char));
        getchar();
        scanf("%s", variable_X);
        getchar();
        scanf("%s", variable_Y);

        for(i = 0; variable_X[i] != '\0'; i++)
            if(variable_X[i] == Caracter) cont++;
        cont_x = i + 1;


        for(i = 0; variable_Y[i] != '\0'; i++)
            if(variable_Y[i] == Caracter) cont++;
        cont_y = i + 1;

        sizeZ = cont_x + cont_y - 1;
        variable_Z = (char *) malloc(sizeZ  * sizeof(char));

        for(i = cont_x - 2; i >= 0; i--, j++){
            variable_Z[j] = variable_X[i];
        }
        j = 0;

        for(i = cont_y - 2; i >= 0; i--, j++){
            variable_Z[j + cont_x - 1] = variable_Y[i];
        }

        variable_Z[sizeZ - 1] = '\0';

        puts(variable_Z);
        printf("%d\n", (sizeZ - 1));
        printf("%d\n", cont);

        free(variable_X);
        free(variable_Y);
        free(variable_Z);

        return 0;
    }
