#include <string.h>
#include <stdlib.h>
#include "life.h"
#include "parseador_archivo.h"
#include "creador_archivo_pbm.h"
#include "vecinos.h"

//Valores de retorno
#define EXITO 0
#define ERROR -1
//Configuracion de creador_archivo_pbm
#define ESCALA 16
//Mensajes
#define MENSAJE_PROCESANDO_NUEVO_ARCHIVO "Leyendo estado inicial...\n"
#define MENSAJE_OPERACION_COMPLETADA "Listo\n"
enum ESTADOS_CELDA {APAGADA, PRENDIDA};

////////////////Funciones privadas//////////////////////

/*
Libera el tablero de juego.
Esta funcion no falla.
*/
static void _liberar_tablero(life_t *self){
    int cont = 0;
    if (self->tablero){
        while(self->tablero[cont]){
            free(self->tablero[cont]);
            self->tablero[cont] = NULL;
            cont++;
        }
        free(self->tablero);
        self->tablero = NULL;
    }
}

/*
Inicializa el tablero de juego con un tamanio de M*N.
Cada celda del tablero sera inicializada dinamicamente con el valor 0.
En caso de fallo devuelve -1.
En caso de exito devuelve 0.
*/
static int _inicializar_tablero(life_t *self){
    int estado = EXITO;
    self->tablero = calloc(self->M + 1, sizeof(char*));
    if (!self->tablero) return ERROR;

    for (int y=0; y<self->M; y++){
        self->tablero[y] = calloc(self->N, sizeof(char));
        if (!self->tablero){
            estado = ERROR;
            break;
        }
    }
    if (estado == ERROR) _liberar_tablero(self);
    return estado;
}
/*
//calcula la cantidad de vecinos de una celda
unsigned int vecinos(unsigned char* a, unsigned int x, unsigned int y, unsigned int fila, unsigned int columna){
    unsigned int cant_vecinos = 0;
    int i = x;
    int j = y;
    int M = fila; //Segun el enunciado recibe unsigned int, pero para que esto funcione necesito ints, ya que quiero que si i=0, i-1 = -1, entonces (i-1)%5 = -1
    int N = columna; //Luego, ((i-1)%5 + 5)%5 = 4, que es el comportamiento deseado. Si fueran unsigned, (i-1)%5 = 0, por lo que no sirve
    if (a[(( (i+1)%M + M) %M) * N + j] == 1) cant_vecinos++; //maldito c que el operador modulo no funciona como en python, y tengo que hacer este truco
    if (a[(( (i-1)%M + M) %M) * N + j] == 1) cant_vecinos++;
    if (a[i * N + ( ((j+1)%N)+ N) %N] == 1) cant_vecinos++;
    if (a[i * N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i+1)%M) +M) %M *N + ( ((j+1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i+1)%M) +M) %M *N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++; //Se pueden optimizar mas si es necesario, por ahora esta bien asi.
    if (a[( ((i-1)%M) +M) %M *N + ( ((j+1)%N) +N) %N] == 1) cant_vecinos++;
    if (a[( ((i-1)%M) +M) %M *N + ( ((j-1)%N) +N) %N] == 1) cant_vecinos++;
    return cant_vecinos;
}*/


//Devuelve 1 si la celda estara prendida o 0 si estara apagada
char actualizar_celda(unsigned char** a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
    unsigned char a_formato_vector[M*N];
    for (int i = 0; i < M;i++){
        for (int j = 0; j < N; j++){
            a_formato_vector[i*N+j] = a[i][j];
        }
    }

    unsigned int cant_vecinos = vecinos(a_formato_vector,i,j,M,N);
    if (cant_vecinos == 3 && (!a[i][j])) return PRENDIDA;
    if ((cant_vecinos == 2 || cant_vecinos == 3) && a[i][j]) return PRENDIDA;
    return APAGADA;
}
void actualizar_matriz(unsigned char** original, unsigned int M, unsigned int N){
    unsigned char copia[M][N];
    for (int i = 0; i <M;i++){
        memcpy(copia[i],original[i],N);
    }  
    for (int i = 0; i < M ; i++){
        for (int j = 0; j < N; j++){
            copia[i][j] = actualizar_celda(original,i,j,M,N);
        }
    }
    for (int i = 0; i <M;i++){
        memcpy(original[i],copia[i],N);
    }
}

///////////////////////Funciones publicas////////////////////


int life_crear(life_t *self, 
               const unsigned int M, 
               const unsigned int N, 
               const unsigned int iteraciones,
               const char* archivo_entrada,
               const char* prefijo_salida){
    self->M = M;
    self->N = N;
    self->iteraciones = iteraciones;
    parseador_archivo_t entrada;
    int estado = _inicializar_tablero(self);
    if (estado == ERROR) return ERROR;

    estado = parseador_archivo_crear(&entrada, archivo_entrada);
    if (estado == ERROR){
        _liberar_tablero(self);
        return ERROR;
    }
    printf(MENSAJE_PROCESANDO_NUEVO_ARCHIVO);
    estado = parseador_archivo_parsear(&entrada, M, N, self->tablero);
    if (estado == ERROR){
        _liberar_tablero(self);     
        parseador_archivo_destruir(&entrada);
        return ERROR;
    }

    estado = creador_archivo_pbm_crear(&self->creador_pbm, 
                                       prefijo_salida,
                                       self->M,
                                       self->N,
                                       ESCALA);
    if (estado == ERROR){
        _liberar_tablero(self);
        creador_archivo_pbm_destruir(&self->creador_pbm);
    }
    parseador_archivo_destruir(&entrada);
    return estado;
}

int life_comenzar(life_t* self){
    int contador_iteraciones = 0;
    int estado = EXITO;
    while(contador_iteraciones < self->iteraciones){
        estado = creador_archivo_pbm_nuevo_archivo(&self->creador_pbm, self->tablero);
        if (estado == ERROR) break;
        actualizar_matriz(self->tablero, self->M, self->N);
        contador_iteraciones++;
    }
    printf(MENSAJE_OPERACION_COMPLETADA);
    return estado;
}

void life_destruir(life_t* self){
    creador_archivo_pbm_destruir(&self->creador_pbm);
    _liberar_tablero(self);
}