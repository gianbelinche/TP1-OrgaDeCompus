#include <stdlib.h>
#include <string.h>
#include "pruebas.h"
#include "life.h"

bool prueba_funcionamiento_general(){
    unsigned char* matriz[5];
    for (int i = 0; i < 5; i++){
        matriz[i] = malloc(5);
        memset(matriz[i],0,5);
    }
    
    matriz[1][2] = 1;
    matriz[2][3] = 1;
    matriz[3][1] = 1;
    matriz[3][2] = 1;
    matriz[3][3] = 1;
    actualizar_matriz(matriz,5,5);
    unsigned char* matriz_correcta[5];
    for (int i = 0; i < 5; i++){
        matriz_correcta[i] = malloc(5);
        memset(matriz_correcta[i],0,5);
    }
    matriz_correcta[2][1] = 1;
    matriz_correcta[2][3] = 1;
    matriz_correcta[3][2] = 1;
    matriz_correcta[3][3] = 1;
    matriz_correcta[4][2] = 1;
    for (int i = 0; i < 5 ; i++){
        for (int j = 0; j < 5; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < 5; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < 5; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true; 

}