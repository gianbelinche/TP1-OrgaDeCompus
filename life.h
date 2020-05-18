#ifndef __LIFE_H__
#define __LIFE_H__
#include "creador_archivo_pbm.h"

typedef struct life{
    unsigned char **tablero;
    unsigned int M;
    unsigned int N;
    unsigned int iteraciones;
    creador_archivo_pbm_t creador_pbm;
}life_t;

/*
Inicializa la estructura life_t.
Levanta el tablero de juego desde el archivo de nombre "archivo_entrada".
En caso de exito devuelve 0 y debera llamarse a life_destruir() para liberar
los recursos utilizados.
En caso de fallo devuelve -1 y no sera necesario llamar a life_destruir().
*/
int life_crear(life_t *self, 
               const unsigned int M, 
               const unsigned int N, 
               const unsigned int iteraciones,
               const char* archivo_entrada,
               const char* prefijo_salida);

/*
Comienza la ejecucion del juego.
Escribe "iteraciones" iteraciones del juego en "iteraciones" archivos .pbm
con nombre "prefijo_salida_xxx.pbm".
En caso de exito devuelve 0.
En caso de fallo devuelve -1.
*/
int life_comenzar(life_t* self);

/*
Destruye la estructura life_t, liberando los recursos utilizados.
Esta funcion no falla.
*/
void life_destruir(life_t* self);


void actualizar_matriz(unsigned char** original, unsigned int M, unsigned int N);

#endif