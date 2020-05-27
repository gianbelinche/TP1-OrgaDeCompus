#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Para usar atoi
#include "pruebas.h"
#include "life.h"
#include "version_conway.h"

//Valores de retorno
#define ERROR -1
#define EXITO 0
#define FINALIZAR 1
//Tamanios de buffer
#define TAM_BUFFER_VERSION 64
//Comandos
#define COMANDO_AYUDA_1 "-h"
#define COMANDO_AYUDA_2 "--help"
#define COMANDO_VERSION_1 "-V"
#define COMANDO_VERSION_2 "--version"
//Mensajes de error
#define MENSAJE_ERROR_PARAMETROS "Error en la cantidad de parámetros\n"
//Mensaje version
#define MENSAJE_VERSION "conway version %s\n"

enum NUM_PARAMS {MIN_NUM_PARAMS = 2,
                 NUM_PARAMS_SIN_OUTPREFIX = 5,
                 NUM_PARAMS_CON_OUTPREFIX = 7};

enum POS_ARGUMENTOS {POS_VERSION = 1,
                     POS_AYUDA = 1,
                     POS_NUM_ITERACIONES = 1,
                     POS_M,
                     POS_N,
                     POS_ARCHIVO_ENTRADA,
                     POS_INDICADOR_PREFIJO_SALIDA,
                     POS_PREFIJO_SALIDA};


void imprimir_ayuda() {
    printf("Uso:\n");
    printf("  conway -h\n");
    printf("  conway -V\n");
    printf("  conway i M N inputfile [-o outputprefix]\n");
    printf("Opciones:\n");
    printf("  -h, --help\t Imprime este mensaje\n");
    printf("  -V, --version\t Da la versión del programa.\n");
    printf("  -o\t\t Prefijo de los archivos de salida.\n");
    printf("Ejemplos:\n");
    printf("  conway 10 20 20 glider -o estado\n");
    printf("  Representa 10 iteraciones del Juego de la Vida en una matriz de 20x20,\n");
    printf("  con un estado inicial tomado del archivo ‘‘glider’’.\n");
    printf("  Los archivos de salida se llamarán estado_n.pbm\n");
    printf("  Si no se da un prefijo para los archivos de salida,\n");
    printf("  el prefijo será el nombre del archivo de entrada.\n");
}

void imprimir_version() {
    char version[TAM_BUFFER_VERSION] = {0};
    printf(MENSAJE_VERSION, obtener_version(version));
}

int chequear_parametros(int argc, char* argv[]) {
    if (argc < MIN_NUM_PARAMS) {
        fprintf(stderr, MENSAJE_ERROR_PARAMETROS);
        return ERROR;
    }

    if (!strcmp(argv[POS_AYUDA], COMANDO_AYUDA_1) || !strcmp(argv[POS_AYUDA], COMANDO_AYUDA_2)){
        imprimir_ayuda();
        return FINALIZAR;
    }

    if (!strcmp(argv[POS_VERSION], COMANDO_VERSION_1) || !strcmp(argv[POS_VERSION], COMANDO_VERSION_2)){
        imprimir_version();
        return FINALIZAR;
    }

    if ((argc != NUM_PARAMS_SIN_OUTPREFIX) && (argc != NUM_PARAMS_CON_OUTPREFIX)){
        /*Con "-o outputprefix" son 7, sino 5*/
        fprintf(stderr, MENSAJE_ERROR_PARAMETROS);
        return ERROR;
    }

    return EXITO;
}

int main(int argc, char* argv[]){
    int estado = chequear_parametros(argc, argv);
    if (estado == ERROR){
        return ERROR;
    }else if (estado == FINALIZAR){
        return EXITO;
    }
    int M = atoi(argv[POS_M]);
    int N = atoi(argv[POS_N]);
    int iteraciones = atoi(argv[POS_NUM_ITERACIONES]);
    char* nombre_archivo = argv[POS_ARCHIVO_ENTRADA];
    char* prefijo = nombre_archivo;
    
    if (M<=0 || N <=0 || iteraciones <= 0) return ERROR;
    if (argc == NUM_PARAMS_CON_OUTPREFIX){
        prefijo = argv[POS_PREFIJO_SALIDA];
    }

    life_t juego;
    estado = life_crear(&juego, M, N, iteraciones, nombre_archivo, prefijo);
    if (estado == ERROR) return ERROR;
    estado = life_comenzar(&juego);
    life_destruir(&juego);
   
    return estado;
}