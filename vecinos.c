#include "vecinos.h"

unsigned int vecinos(unsigned char* a, unsigned int x, unsigned int y, unsigned int M, unsigned int N){
    unsigned int cant_vecinos = 0;

    unsigned int vecino_abajo_x = x+1;
    if (x+1 >= M){
        vecino_abajo_x = 0;
    }
    if (a[vecino_abajo_x * N + y] == 1) cant_vecinos++;

    unsigned int vecino_arriba_x = x-1;
    if (x == 0){
        vecino_arriba_x = M-1;
    }
    if (a[vecino_arriba_x * N + y] == 1) cant_vecinos++;

    unsigned int vecino_izq_y = y-1;
    if (y == 0){
        vecino_izq_y = N -1;
    }
    if (a[x * N + vecino_izq_y] == 1) cant_vecinos++;

    unsigned int vecino_der_y = y+1;
    if (y+1 >= N){
        vecino_der_y = 0;
    }
    if (a[x*N+vecino_der_y]==1) cant_vecinos++;

    if (a[vecino_abajo_x *N + vecino_der_y] == 1) cant_vecinos++;
    if (a[vecino_abajo_x *N + vecino_izq_y] == 1) cant_vecinos++;
    if (a[vecino_arriba_x *N + vecino_der_y] == 1) cant_vecinos++;
    if (a[vecino_arriba_x *N + vecino_izq_y] == 1) cant_vecinos++;
    return cant_vecinos;
}