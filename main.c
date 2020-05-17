#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR 1
#define EXITO 0

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
    printf("conway version "); /*Completar*/
}

int chequear_parametros(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Error en la cantidad de parámetros");
        return ERROR;
    }

    if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")) { /*Se podria cambiar por strncmp*/
        imprimir_ayuda();
        return 2/*cambiar*/;
    }

    if (strcmp(argv[1], "-V" || strcmp(argv[1], "--version")) {
        imprimir_version();
        return 2/*cambiar*/;
    }

    if ((argc != 5) && (argc != 7)) {
        /*Con "-o outputprefix" son 7, sino 5*/
        fprintf(stderr, "Error en la cantidad de parámetros");
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
    
    return EXITO;
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