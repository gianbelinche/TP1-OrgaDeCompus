#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Para usar atoi
#include "pruebas.h"
#include "life.h"

#define ERROR -1
#define EXITO 0

enum POS_ARGUMENTOS {POS_NUM_ITERACIONES = 1,
                     POS_M,
                     POS_N,
                     POS_ARCHIVO_ENTRADA,
                     POS_INDICADOR_PREFIJO_SALIDA,
                     POS_PREFIJO_SALIDA};


    //argv[0] es conway
    //argv[1] es el numero de iteraciones
    //argv[2] es M
    //argv[3] es N
    //argv[4] es inputfile
    //argv[6] es outputfile

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
    printf("conway version\n"); /*Completar*/
}

int chequear_parametros(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Error en la cantidad de parámetros\n");
        return ERROR;
    }

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) { /*Se podria cambiar por strncmp*/
        imprimir_ayuda();
        return 2/*cambiar*/;
    }

    if (!strcmp(argv[1], "-V") || !strcmp(argv[1], "--version")) {
        imprimir_version();
        return 2/*cambiar*/;
    }

    if ((argc != 5) && (argc != 7)) {
        /*Con "-o outputprefix" son 7, sino 5*/
        fprintf(stderr, "Error en la cantidad de parámetros\n");
        return ERROR;
    }

    return EXITO;
}

int main(int argc, char* argv[]){
    int estado = chequear_parametros(argc, argv);
    if (estado == ERROR) {
        return ERROR;
    } else if (estado == 2/*Cambiar*/)  {
        return EXITO;
    }
    int M = atoi(argv[POS_M]);
    int N = atoi(argv[POS_N]);
    int iteraciones = atoi(argv[POS_NUM_ITERACIONES]);
    char* nombre_archivo = argv[POS_ARCHIVO_ENTRADA];
    char* prefijo = nombre_archivo;
    
    if (M<=0 || N <=0 || iteraciones <= 0) return ERROR;
    if (argc == 7 /*Se indica outprefix*/){
        prefijo = argv[POS_PREFIJO_SALIDA];
    }

    life_t juego;
    estado = life_crear(&juego, M, N, iteraciones, nombre_archivo, prefijo);
    if (estado == ERROR) return ERROR;
    estado = life_comenzar(&juego);
    life_destruir(&juego);
    /*
    ESTO SERIA ASI, Y EL argv[4] ES EL ARCHIVO DE ENTRADA
    PERO PARA TRABAJAR CON ESTO HAY QUE CAMBIAR UN POCO LAS LOGICA
    DE CREACION DE LA MATRIZ Y ESO Y LLAMAR AL PARSEADOR CON EL
    argv[4].
    */
    //int num_archivos = argv[1];
    //matriz de MxN
    //int M = argv[2];
    //int N = argv[3];
    //char *salida = NULL;
    //if (argc == 7) {
    //    salida = argv[6];
    //}
    
    //pruebas();    
    return estado;
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