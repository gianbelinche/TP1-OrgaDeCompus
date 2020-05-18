#include "parseador_archivo.h"
#include <string.h> //Para strtok
#include <stdlib.h> //Para atoi
#define FORMATO_LECTURA "r"
#define DELIMITADOR " "
#define TAM_BUFFER_LINEA 5
#define LARGO_LINEA 3
#define CELDA_ENCENDIDA 1
#define EXITO 0
#define ERROR -1
//#define pos(x,y,M) (y*M + x) Se puede borrar si no lo usamos



////////////Funciones privadas////////////////

/*
Toma la linea leida, la parsea y chequea que las coordenadas
no queden fuera del rango de la matriz.
Llena la matriz tablero con las posiciones leidas del archivo.
En caso de fallo devuelve -1
En caso de exito devuelve 0
*/
static int _parsear_linea(char* linea, 
                          const unsigned int M, 
                          const unsigned int N, 
                          char** tablero){

    char* ptr_x = strtok(linea, DELIMITADOR);
    char* ptr_y = strtok(NULL, DELIMITADOR);
    if (!ptr_y) return ERROR;
    int x = atoi(ptr_x);
    int y = atoi(ptr_y);
    if (x < 0 || x >= N) return ERROR;
    if (y < 0 || y >= M) return ERROR;
    //tablero[pos(x, y, M)] = CELDA_ENCENDIDA;
    tablero[y][x] = CELDA_ENCENDIDA;
    return EXITO;
}

////////////Funciones publicas////////////////

int parseador_archivo_crear(parseador_archivo_t *self, const char* nombre_archivo){
    self->archivo = fopen(nombre_archivo, FORMATO_LECTURA);
    if (!self->archivo) return ERROR;
    return EXITO;
}

void parseador_archivo_destruir(parseador_archivo_t *self){
    //Siempre es bueno chequear que no cerremos un archivo no abierto
    if (self->archivo){
        fclose(self->archivo);
        self->archivo = NULL;
    }
}

int parseador_archivo_parsear(parseador_archivo_t *self, 
                              const unsigned int M,
                              const unsigned int N,
                              char** tablero){
    char linea[TAM_BUFFER_LINEA];
    int estado = 0;
    while(fgets(linea, TAM_BUFFER_LINEA, self->archivo) && estado == EXITO){
        linea[strlen(linea)] = 0;
        estado = _parsear_linea(linea, M, N, tablero);
    }

    return estado;
}