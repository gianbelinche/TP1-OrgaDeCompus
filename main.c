#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pruebas.h"

//calcula la cantidad de vecinos de una celda
unsigned int vecinos(unsigned char* a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned int cant_vecinos = 0;
    if (a[((i+1)%M)*M + j] == 1) cant_vecinos++;
    if (a[((i-1)%M)*M + j] == 1) cant_vecinos++;
    if (a[i * M + ((j+1)%N)] == 1) cant_vecinos++;
    if (a[i * M + ((j-1)%N)] == 1) cant_vecinos++;
    if (a[((i+1)%M)*M + ((j+1)%N)] == 1) cant_vecinos++;
    if (a[((i+1)%M)*M + ((j-1)%N)] == 1) cant_vecinos++; //Se pueden optimizar mas si es necesario, por ahora esta bien asi.
    if (a[((i-1)%M)*M + ((j+1)%N)] == 1) cant_vecinos++;
    if (a[((i-1)%M)*M + ((j-1)%N)] == 1) cant_vecinos++;
    return cant_vecinos;
}

//Devuelve 1 si la celda estara prendida o 0 si estara apagada
char actualizar_celda(unsigned char** a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned char a_formato_vector[M*N];
    for (int i = 0; i < M;i++){
        for (int j = 0; j < N; j++){
            a_formato_vector[i*M+j] = a[i][j];
        }
    }

    unsigned int cant_vecinos = vecinos(a_formato_vector,i,j,M,N);
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

    printf("Prueba funcionamiento general: ");
    if (prueba_funcionamiento_general()) {
        printf("OK\n");
    } else {
        printf("Error\n");
    }    
    return 1;
}


/*

//////////////////PARAMETROS DE INGRESO/////////////////////

El programa debera ser capaz de tomar los siguientes argumentos de entrada:

- conway -h --> Imprime un mensaje de ayuda que describe el uso del programa

- conway i M N inputfile [-o outputprefix]

Donde i representa la cantidad de estados consecutivos a imprimir

M y N representan el tamanio de la matriz del juego

inputfile es el archivo desde donde se levantaran las posiciones de las celdas prendidas

outputprefix es el prefijo que se le debera agregar a los archivos .pbm
que se impriman tras la ejecucion

-o permite saber que el comando posterior es el outputprefix (util para parsear) 

Ej:
    conway 10 20 20 glider -0 estado

    i = 10 --> 10 iteraciones impresas
    M = N = 20 --> Tamanio de la matriz de 20x20
    glider --> Se levanta la informacion del archivo de nombre "glider"
    -o estado --> Los i archivos generados deberan nombrarse de la siguiente forma:
            estado_1.pbm
            estado_2.pbm
                .
                .
                .
            estado_i.pbm

*/