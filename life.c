#include <string.h>
#include <stdlib.h>
#include "life.h"

//calcula la cantidad de vecinos de una celda
unsigned int vecinos(unsigned char* a, unsigned int x, unsigned int y, unsigned int fila, unsigned int columna){
    unsigned int cant_vecinos = 0;
    int i = x;
    int j = y;
    int M = fila; //Segun el enunciado recibe unsigned int, pero para que esto funcione necesito ints, ya que quiero que si i=0, i-1 = -1, entonces (i-1)%5 = -1
    int N = columna; //Luego, ((i-1)%5 + 5)%5 = 4, que es el comportamiento deseado. Si fueran unsigned, (i-1)%5 = 0, por lo que no sirve
    if (a[(( (i+1)%M + M) %M) * N + j] == 1) cant_vecinos++; //maldito c que el operador modulo no funciona como en python, y tengo que hacer este truco
    if (a[(( (i-1)%M + M) %M) * N + j] == 1) cant_vecinos++;
    if (a[i * N + ( ((j+1)%N)+ N) %N] == 1) cant_vecinos++;
    if (a[i * N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i+1)%M) +M) %M *N + ( ((j+1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i+1)%M) +M) %M *N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++; //Se pueden optimizar mas si es necesario, por ahora esta bien asi.
    if (a[( ((i-1)%M) +M) %M *N + ( ((j+1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i-1)%M) +M) %M *N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++;
    return cant_vecinos;
}

//Devuelve 1 si la celda estara prendida o 0 si estara apagada
char actualizar_celda(unsigned char** a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned char a_formato_vector[M*N];
    for (int i = 0; i < M;i++){
        for (int j = 0; j < N; j++){
            a_formato_vector[i*N+j] = a[i][j];
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
            copia[i][j] = actualizar_celda(original,i,j,M,N);
        }
    }
    for (int i = 0; i <M;i++){
        memcpy(original[i],copia[i],N);
    }
}