#include "parseador_archivo.h"
#include <string.h> //Para strtok
#include <stdlib.h> //Para atoi
#include <errno.h>
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

/*
Inicializa la estructura parseador_archivo_t.
En caso de exito devuelve 0 y debera llamarse a parseador_archivo_destruir() 
para liberar los recursos utilizados al finalizar.
En caso de error devuelve -1 y no sera necesario llamar a parseador_archivo_destruir().
*/
int parseador_archivo_crear(parseador_archivo_t *self, const char* nombre_archivo){
    self->archivo = fopen(nombre_archivo, FORMATO_LECTURA);
    if (!self->archivo) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return ERROR;
    }
    return EXITO;
}

/*
Destruye la estructura parseador_archivo_t, cerrando el archivo de entrada
y liberando los recursos utilizados.
Esta funcion no falla.
*/
void parseador_archivo_destruir(parseador_archivo_t *self){
    //Siempre es bueno chequear que no cerremos un archivo no abierto
    if (self->archivo){
        fclose(self->archivo);
        self->archivo = NULL;
    }
}

/*
Parsea el archivo de entrada y almacena los resultados leidos en la
matriz tablero.
En caso de que los valores leidos desde el archivo no respeten el rango
de la matriz de tamanio MxN la funcion devolvera -1
En caso de exito la funcion devolvera 0 y la matriz tablero contendra
los valores de celdas leidos desde el archivo.
*/
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