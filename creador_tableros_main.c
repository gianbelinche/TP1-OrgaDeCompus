#include "creador_tableros.h"
#include <stdlib.h>
#define ERROR -1
#define EXITO 0
#define CANTIDA_DE_PARAMETROS 4

enum POS_ARGUMENTOS {POS_M=1, POS_N, POS_NOMBRE_ARCHIVO};
int main(int argc, const char**argv){

    if (argc != CANTIDA_DE_PARAMETROS) return ERROR;
    creador_tableros_t creador;
    unsigned int M = atoi(argv[POS_M]);
    unsigned int N = atoi(argv[POS_N]);
    int estado = creador_tableros_crear(&creador, M, N, argv[POS_NOMBRE_ARCHIVO]);
    if (estado == ERROR) return ERROR;
    estado = creador_tableros_comenzar(&creador);
    creador_tableros_destruir(&creador);
    

    return estado;
}