#ifndef __PARSEADOR_ARCHIVO__
#define __PARSEADOR_ARCHIVO__
#include <stdio.h>

typedef struct parseador_archivo{
    FILE *archivo;
}parseador_archivo_t;

/*
Inicializa la estructura parseador_archivo_t.
En caso de exito devuelve 0 y debera llamarse a parseador_archivo_destruir() 
para liberar los recursos utilizados al finalizar.
En caso de error devuelve -1 y no sera necesario llamar a parseador_archivo_destruir().
*/
int parseador_archivo_crear(parseador_archivo_t *self, const char* nombre_archivo);

/*
Destruye la estructura parseador_archivo_t, cerrando el archivo de entrada
y liberando los recursos utilizados.
Esta funcion no falla.
*/
void parseador_archivo_destruir(parseador_archivo_t *self);



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
                              char** tablero); 

#endif