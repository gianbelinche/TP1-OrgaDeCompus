#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "pruebas.h"
#include "life.h"

bool prueba_funcionamiento_general(){
    int M = 5;
    int N = 5;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[1][2] = 1;
    matriz[2][3] = 1;
    matriz[3][1] = 1;
    matriz[3][2] = 1;
    matriz[3][3] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[2][1] = 1;
    matriz_correcta[2][3] = 1;
    matriz_correcta[3][2] = 1;
    matriz_correcta[3][3] = 1;
    matriz_correcta[4][2] = 1;
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true; 

}

bool prueba_matriz_vacia(){
    int M = 10;
    int N = 10;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true; 
}

bool prueba_caso_borde_superior(){
    int M = 5;
    int N = 10;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[0][0] = 1;
    matriz[0][1] = 1;
    matriz[0][2] = 1;
    matriz[0][3] = 1;
    matriz[0][4] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[0][1] = 1;
    matriz_correcta[0][2] = 1;
    matriz_correcta[0][3] = 1;
    matriz_correcta[1][1] = 1;
    matriz_correcta[1][2] = 1;
    matriz_correcta[1][3] = 1;
    matriz_correcta[4][1] = 1;
    matriz_correcta[4][2] = 1;
    matriz_correcta[4][3] = 1;

    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true; 
}

bool prueba_caso_borde_inferior(){
    int M = 5;
    int N = 10;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[4][5] = 1;
    matriz[4][6] = 1;
    matriz[4][7] = 1;
    matriz[4][8] = 1;
    matriz[4][9] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[4][6] = 1;
    matriz_correcta[4][7] = 1;
    matriz_correcta[4][8] = 1;
    matriz_correcta[3][6] = 1;
    matriz_correcta[3][7] = 1;
    matriz_correcta[3][8] = 1;
    matriz_correcta[0][6] = 1;
    matriz_correcta[0][7] = 1;
    matriz_correcta[0][8] = 1;
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true; 
}

bool prueba_caso_borde_izquierdo(){
    int M = 10;
    int N = 5;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[0][0] = 1;
    matriz[1][0] = 1;
    matriz[2][0] = 1;
    matriz[3][0] = 1;
    matriz[4][0] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[1][0] = 1;
    matriz_correcta[2][0] = 1;
    matriz_correcta[3][0] = 1;
    matriz_correcta[1][1] = 1;
    matriz_correcta[2][1] = 1;
    matriz_correcta[3][1] = 1;
    matriz_correcta[1][4] = 1;
    matriz_correcta[2][4] = 1;
    matriz_correcta[3][4] = 1;
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true;
}

bool prueba_caso_borde_derecho(){
    int M = 10;
    int N = 5;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[5][4] = 1;
    matriz[6][4] = 1;
    matriz[7][4] = 1;
    matriz[8][4] = 1;
    matriz[9][4] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[6][4] = 1;
    matriz_correcta[7][4] = 1;
    matriz_correcta[8][4] = 1;
    matriz_correcta[6][3] = 1;
    matriz_correcta[7][3] = 1;
    matriz_correcta[8][3] = 1;
    matriz_correcta[6][0] = 1;
    matriz_correcta[7][0] = 1;
    matriz_correcta[8][0] = 1;
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true;
}

bool prueba_caso_borde_esquinas(){
    int M = 7;
    int N = 10;
    unsigned char* matriz[M];
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N);
        memset(matriz[i],0,N);
    }
    
    matriz[0][0] = 1;
    matriz[0][9] = 1;
    matriz[6][0] = 1;
    matriz[6][9] = 1;
    actualizar_matriz(matriz,M,N);
    unsigned char* matriz_correcta[M];
    for (int i = 0; i < M; i++){
        matriz_correcta[i] = malloc(N);
        memset(matriz_correcta[i],0,N);
    }
    matriz_correcta[0][0] = 1;
    matriz_correcta[0][9] = 1;
    matriz_correcta[6][0] = 1;
    matriz_correcta[6][9] = 1;
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            if (matriz[i][j] != matriz_correcta[i][j]){
                for (int i = 0; i < M; i++){
                    free(matriz[i]);
                    free(matriz_correcta[i]);
                }  
                return false;
            }
        }
    }
    for (int i = 0; i < M; i++){
        free(matriz[i]);
        free(matriz_correcta[i]);
    }   
    return true;
}
void pruebas(){

    printf("Prueba funcionamiento general: ");
    if (prueba_funcionamiento_general()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }

    printf("Prueba matriz vacia: ");
    if (prueba_matriz_vacia()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }

    printf("Prueba caso borde superior: ");
    if (prueba_caso_borde_superior()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }

    printf("Prueba caso borde inferior: ");
    if (prueba_caso_borde_inferior()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }
    printf("Prueba caso borde izquierdo: ");
    if (prueba_caso_borde_izquierdo()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }
    printf("Prueba caso borde derecho: ");
    if (prueba_caso_borde_derecho()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }
    printf("Prueba caso borde esquinas: ");
    if (prueba_caso_borde_esquinas()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }


}

int main(){
    pruebas();
    return 0;
}