#include <string.h>

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
    memcpy(copia,original,M*N);
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            copia[i][j] = actualizar_celda(original,i,j,N,M);
        }
    }
    memcpy(original,copia,M*N);
}

int main(int argc, char* argv[]){

    unsigned char** matriz = {0};
    memset(matriz,0,20*20);
    actualizar_matriz(matriz,20,20); //Aun no probe que funcione, por ahora compila bien
    return 1;
}