#include "vecinos.h"

unsigned int vecinos(unsigned char* a, unsigned int x, unsigned int y, unsigned int M, unsigned int N){
    unsigned int cant_vecinos = 0;

    unsigned int vecino_der_x = x+1;
    if (x+1 >= N){
        vecino_der_x = 0;
    }
    if (a[vecino_der_x * N + y] == 1) cant_vecinos++;

    unsigned int vecino_izq_x = x-1;
    if (x == 0){
        vecino_izq_x = N-1;
    }
    if (a[vecino_izq_x * N + y] == 1) cant_vecinos++;

    unsigned int vecino_arriba_y = y-1;
    if (y == 0){
        vecino_arriba_y = M -1;
    }
    if (a[x * N + vecino_arriba_y] == 1) cant_vecinos++;

    unsigned int vecino_abajo_y = y+1;
    if (y+1 >= M){
        vecino_abajo_y = 0;
    }
    if (a[x*N+vecino_abajo_y]==1) cant_vecinos++;

    if (a[vecino_der_x *N + vecino_abajo_y] == 1) cant_vecinos++;
    if (a[vecino_der_x *N + vecino_arriba_y] == 1) cant_vecinos++;
    if (a[vecino_izq_x *N + vecino_abajo_y] == 1) cant_vecinos++;
    if (a[vecino_izq_x *N + vecino_arriba_y] == 1) cant_vecinos++;
    return cant_vecinos;
}