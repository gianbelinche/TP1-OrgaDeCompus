#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//calcula la cantidad de vecinos de una celda
unsigned int vecinos(unsigned char** a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned int cant_vecinos = 0;
    if (a[(i+1)%M][j] == 1) cant_vecinos++;
    if (a[(i-1)%M][j] == 1) cant_vecinos++;
    if (a[i][(j+1)%N] == 1) cant_vecinos++;
    if (a[i][(j-1)%N] == 1) cant_vecinos++;
    if (a[(i+1)%M][(j+1)%N] == 1) cant_vecinos++;
    if (a[(i+1)%M][(j-1)%N] == 1) cant_vecinos++; //Se pueden optimizar mas si es necesario, por ahora esta bien asi.
    if (a[(i-1)%M][(j+1)%N] == 1) cant_vecinos++;
    if (a[(i-1)%M][(j-1)%N] == 1) cant_vecinos++;
    return cant_vecinos;
}

//Devuelve 1 si la celda estara prendida o 0 si estara apagada
char actualizar_celda(unsigned char** a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned int cant_vecinos = vecinos(a,i,j,M,N);
    if (cant_vecinos == 3 && (!a[i][j])) return 1;
    if ((cant_vecinos == 2 || cant_vecinos == 3) && a[i][j]) return 1;
    return 0;
}
void actualizar_matriz(unsigned char** original,unsigned int M, unsigned int N){
    unsigned char copia[M][N];
    for (int i = 0; i <M;i++){
        memcpy(copia[i],original[i],N);
    }  
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            copia[i][j] = actualizar_celda(original,i,j,N,M);
        }
    }
    for (int i = 0; i <M;i++){
        memcpy(original[i],copia[i],N);
    }
}

int main(int argc, char* argv[]){

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
    actualizar_matriz(matriz,5,5); //Aun no probe que funcione, por ahora compila bien
    for (int i = 0; i < 5 ; i++){
        for (int j = 0; j < 5; j++){
            printf("%d",matriz[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 5; i++){
        free(matriz[i]);
    }
    return 1;
}