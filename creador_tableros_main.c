#include "creador_tableros.h"
#include <stdlib.h>
#include <string.h>
//Valores de retorno
#define ERROR -1
#define EXITO 0
//Configuraciones de comandos
#define CANTIDAD_DE_PARAMETROS 4
#define CANTIDAD_PARAMS_AYUDA 2
//Comandos de ayuda
#define COMANDO_AYUDA_1 "-h"
#define COMANDO_AYUDA_2 "--help"

enum POS_ARGUMENTOS {POS_M = 1, POS_AYUDA = 1, POS_N, POS_NOMBRE_ARCHIVO};


static void _imprimir_ayuda(){
    printf("Uso: \n");
    printf("    ./<Nombre ejecutable> <Ancho tablero> <Alto tablero> <nombre archivo salida>\n");
    imprimir_ayuda();
}

int main(int argc, const char**argv){

    if (argc != CANTIDAD_DE_PARAMETROS) {
        if (argc == CANTIDAD_PARAMS_AYUDA){
            if (!strcmp(argv[POS_AYUDA], COMANDO_AYUDA_1) || !strcmp(argv[POS_AYUDA], COMANDO_AYUDA_2)){
                _imprimir_ayuda();
                return EXITO;
            }
        }
        fprintf(stderr, "Error: cantidad de parámetros incorrecta\n");
        return ERROR;
    }
    creador_tableros_t creador;
    unsigned int M = atoi(argv[POS_M]);
    unsigned int N = atoi(argv[POS_N]);
    int estado = creador_tableros_crear(&creador, M, N, argv[POS_NOMBRE_ARCHIVO]);
    if (estado == ERROR) return ERROR;
    estado = creador_tableros_comenzar(&creador);
    creador_tableros_destruir(&creador);
    

    return estado;
}