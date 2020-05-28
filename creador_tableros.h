#ifndef __CREADOR_TABLEROS__
#define __CREADOR_TABLEROS__
#include <stdio.h>

typedef struct creador_tableros{
    FILE* archivo;
    char** tablero;
    unsigned int M;
    unsigned int N;
    unsigned int op_x;
    unsigned int op_y;
    char ultima_op;
}creador_tableros_t;

/*
Inicializa la estructura creador_tableros_t.
Se le debera pasar un tablero inicializado con cada posicion a cero
de tamanio MxN.
En caso de fallo devuelve -1.
En caso de exito devuelve 0.
La estructura debera ser destruida llamando a creador_tableros_destruir
unicamente si esta funcion devuelve 0.
*/
int creador_tableros_crear(creador_tableros_t *self, unsigned int M, unsigned int N, const char* nombre_archivo);



/*
Libera la estructura creador_tableros_t junto a todos los recursos utilizados.
No liberara el tablero pasado al constructor.
Esta funcion no falla.
*/
void creador_tableros_destruir(creador_tableros_t *self);

/*
Comienza a crear el tablero.
Utiliza stdout para imprimir el estado actual del tablero.
Permite modificar en tiempo real la posicion de las celdas prendidas y apagadas.
En caso de fallo devuelve -1.
En caso de exito devuelve 0.
*/
int creador_tableros_comenzar(creador_tableros_t *self);


#endif
