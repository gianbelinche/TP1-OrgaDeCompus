#include "creador_archivo_pbm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//Valores de retorno
#define EXITO 0
#define ERROR -1
//Opcion de apertura
#define NUEVO_ARCHIVO_ESCRITURA "w"
//Configuraciones formato pbm
#define EXTENSION_ARCHIVO ".pbm"
#define MAGIC_NUMBER "P1\n"
//Tamanios de buffer
#define TAM_BUFFER_ANCHO_Y_ALTO 128
#define TAM_BUFFER_CONTADOR 3
#define ESPACIO_PARA_FORMATO 9 //Fin de cadena + sufijo _000.pbm 

//////////////Funciones privadas///////////////////
/*
Crea una linea para ser escrita en el archivo de formato .pbm
La linea es conformada teniendo en cuenta el factor de escala y 
los valores del tablero en la posicion y.
Esta funcion no falla.
*/
static void _crear_linea(creador_archivo_pbm_t *self, unsigned char **tablero, const unsigned int y){
    int cont = 0;
    for (int x=0; x<self->N; x++){
        for (int k=0; k<self->escala; k++){
            if (tablero[y][x]){
                self->linea[cont] = '1';
            }else{
                self->linea[cont] = '0';
            }
            cont++;
        }
    }
    self->linea[cont] = '\n';
}

/*
Actualiza el nombre del archivo actual segun el contador de archivos creados
No falla
*/
static void _actualizar_nombre_archivo(creador_archivo_pbm_t *self){
    snprintf(self->nombre_archivo, 
             self->tam_nombre_archivo, 
             "%s_%03d%s", 
             self->prefijo, 
             self->contador, 
             EXTENSION_ARCHIVO);
}

/*
Escribe los parametros iniciales al comienzo del archivo de formato .pbm
Estos parametros son:
    - "Magic number" que representa la version del formato, ej: P1, P4.
    - Ancho y alto de la imagen medido en pixeles.
Esta funcion no falla.
*/
static void _inicializar_archivo(creador_archivo_pbm_t *self, FILE* archivo){
    char ancho_y_alto[TAM_BUFFER_ANCHO_Y_ALTO] = {0};
    snprintf(ancho_y_alto, 
             TAM_BUFFER_ANCHO_Y_ALTO, 
             "%d %d\n", 
             self->N*self->escala, 
             self->M*self->escala);
    fputs(MAGIC_NUMBER, archivo);
    fputs(ancho_y_alto, archivo);
}

//////////////Funciones publicas///////////////////

int creador_archivo_pbm_crear(creador_archivo_pbm_t *self, 
                              const char* prefijo,
                              const unsigned int M,
                              const unsigned int N,
                              const unsigned int escala){
    self->M = M;
    self->N = N;
    self->escala = escala;
    self->contador = 1;
    long unsigned int largo_prefijo = strlen(prefijo);
    self->prefijo = calloc(largo_prefijo + 1, sizeof(char));
    if (!self->prefijo) return ERROR;
    memcpy(self->prefijo, prefijo, largo_prefijo);
    self->tam_nombre_archivo = largo_prefijo + ESPACIO_PARA_FORMATO;
    self->nombre_archivo = calloc(self->tam_nombre_archivo, sizeof(char));
    if (!self->nombre_archivo){
        free(self->prefijo);
        self->prefijo = NULL;
        self->tam_nombre_archivo = 0;
        return ERROR;
    }
    //Dos bytes de mas para el fin de cadena y el salto de linea
    self->linea = calloc((self->N)*self->escala+2, sizeof(char));
    if (!self->linea){
        free(self->prefijo);
        free(self->nombre_archivo);
        self->nombre_archivo = NULL;
        self->prefijo = NULL;
        self->tam_nombre_archivo = 0;
    }
    return EXITO;
}

void creador_archivo_pbm_destruir(creador_archivo_pbm_t *self){
    if (self->prefijo){
        free(self->prefijo);
        self->prefijo = NULL;
    }
    if (self->nombre_archivo){
        free(self->nombre_archivo);
        self->nombre_archivo = NULL;
    }
    if (self->linea){
        free(self->linea);
        self->linea = NULL;
    }
}

int creador_archivo_pbm_nuevo_archivo(creador_archivo_pbm_t *self, unsigned char** tablero){
    _actualizar_nombre_archivo(self);
    FILE *archivo = fopen(self->nombre_archivo, NUEVO_ARCHIVO_ESCRITURA);
    if (!archivo) return ERROR;
    _inicializar_archivo(self, archivo);
    int estado = EXITO;

    for (int y=0; y<self->M; y++){
        for (int k=0; k<self->escala; k++){
            _crear_linea(self, tablero, y);
            if(fputs(self->linea, archivo) == EOF){
                estado = ERROR;
                break;
            }
        }
    }    
    //Pongo aca el mensaje para imprimir error en caso de error
    if (estado == ERROR){
        fprintf(stdout, 
                "Error al grabar %s_%d%s\n", 
                self->prefijo, 
                self->contador, 
                EXTENSION_ARCHIVO);
    }else{
        fprintf(stdout,  
                "Grabando %s_%d%s\n", 
                self->prefijo, 
                self->contador, 
                EXTENSION_ARCHIVO);
    }
    self->contador++;
    fclose(archivo);
    return estado;
}
