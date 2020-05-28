#include "creador_tableros.h"
#include <stdlib.h>
#include <stdbool.h>
//Valores de retorno
#define EXITO 0
#define ERROR -1
//Valores del tablero
#define TABLERO_CELDA_PRENDIDA  1
#define TABLERO_CELDA_APAGADA   0
//Valores graficos
#define CELDA_PRENDIDA  "#"
#define CELDA_APAGADA   "."
#define COLUMNA         " | "
#define TECHO           "--"
#define SEPARADOR       " " 
#define OPERADOR        "O"
//Controles usuario
#define TECLA_AYUDA     'h'
#define TECLA_ESCAPE    'q'
#define TECLA_ARRIBA    'w'
#define TECLA_ABAJO     's'
#define TECLA_DERECHA   'd'
#define TECLA_IZQUIERDA 'a'
#define AGREGAR_CELDA   'p'
#define QUITAR_CELDA    'o'
//Tamanio de buffer
#define TAM_BUFFER_ENTRADA 256
//Opcion archivo
#define MODO_APERTURA "w"

////////////////Funciones privadas///////////////////

/*
Libera el tablero de juego.
Esta funcion no falla.
*/
static void _liberar_tablero(creador_tableros_t *self){
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
static int _inicializar_tablero(creador_tableros_t *self){
    int estado = EXITO;
    self->tablero = calloc(self->M + 1, sizeof(char*));
    if (!self->tablero) return ERROR;

    for (int y=0; y<self->M; y++){
        self->tablero[y] = calloc(self->N, sizeof(char));
        if (!self->tablero[y]){
            estado = ERROR;
            break;
        }
    }
    if (estado == ERROR) _liberar_tablero(self);
    return estado;
}

/*
Imprime el estado actual del tablero por pantalla, haciendo un pseudo clear anteriormente.
No falla.
*/
static void _imprimir_tablero(creador_tableros_t *self){
    //Hace algo similar a un clear en la pantalla
    printf("\e[1;1H\e[2J");
    printf("  ");
    for (int x = 0; x < self->N; x++) printf("%s", TECHO);
    printf("\n");
    for (int y = 0; y < self->M; y++){
        for (int x = 0; x < self->N; x++){
            if (x == 0){
                printf("%s", COLUMNA);
            }
            if (x == self->op_x && y == self->op_y){
                printf("%s", OPERADOR);
            }else{
                if (self->tablero[y][x]){
                    printf("%s", CELDA_PRENDIDA);
                }else{
                    printf("%s", CELDA_APAGADA);
                }
            }
            if (x == self->N-1){
                printf("%s\n", COLUMNA);
            }else{
                printf("%s", SEPARADOR);
            }
        }
    }
    printf("  ");
    for (int x = 0; x < self->N; x++) printf("%s", TECHO);
    printf("\n");
}
/*
Decide que tipo de impresion debera realizarse dependiendo del
ultimo comando leido.
Puede imprimir el tablero o la ayuda.
No falla.
*/
static void _imprimir(creador_tableros_t *self){
    if (self->ultima_op == TECLA_AYUDA){
        imprimir_ayuda();
    }else{
        _imprimir_tablero(self);
    }
}
/*
Guarda el estado del tablero en un archivo con un formato especial en donde
se escribira las coordenadas de cada celda viva del mismo, todas separadas por
un salto de linea.
En caso de exito devuelve 0.
En caso de fallo devuelve -1.
*/
static int _escribir_archivo(creador_tableros_t *self){
    int estado = EXITO;
    for (int y = 0; y < self->M; y++){
        for (int x = 0; x < self->N; x++){
            if (self->tablero[y][x]){
                estado = fprintf(self->archivo, "%d %d\n", x, y);
                if (estado < 0) return ERROR;
            }
        }
    }
    return EXITO;
}
/*
Actualiza la posicion del operador segun corresponda.
En caso de que la nueva posicion sea invalida se mantendra la posicion anterior.
*/
static void _moverse(creador_tableros_t *self, unsigned int nueva_x, unsigned int nueva_y){
    if (nueva_x < 0 || nueva_x >= self->N) return;
    if (nueva_y < 0 || nueva_y >= self->M) return;
    self->op_x = nueva_x;
    self->op_y = nueva_y;
}

/*
Parsea el comando ingresado, modificando el tablero de ser necesario.
Devuelve false si se detecta la tecla de escape.
Devuelve true en caso contrario.
*/
static bool _modificar_tablero(creador_tableros_t *self, const char entrada){
    switch (entrada){
        case TECLA_ESCAPE:
            return false;
        case TECLA_ARRIBA:
            _moverse(self, self->op_x, self->op_y-1);
            break;
        case TECLA_ABAJO:
            _moverse(self, self->op_x, self->op_y+1);
            break;
        case TECLA_DERECHA:
            _moverse(self, self->op_x+1, self->op_y);
            break;
        case TECLA_IZQUIERDA:
            _moverse(self, self->op_x-1, self->op_y);
            break;
        case AGREGAR_CELDA:
            self->tablero[self->op_y][self->op_x] = TABLERO_CELDA_PRENDIDA;
            break;
        case QUITAR_CELDA:
            self->tablero[self->op_y][self->op_x] = TABLERO_CELDA_APAGADA;
            break;
    }
    return true;
}

////////////////Funciones publicas///////////////////


int creador_tableros_crear(creador_tableros_t *self, unsigned int M, unsigned int N, const char* nombre_archivo){
    self->M = M;
    self->N = N;
    self->op_x = N/2;
    self->op_y = M/2;
    self->ultima_op = 0;
    int estado = _inicializar_tablero(self);
    if (estado == ERROR) _liberar_tablero(self);
    self->archivo = fopen(nombre_archivo, MODO_APERTURA);
    if (!self->archivo){
        _liberar_tablero(self);
        return ERROR;
    }
    return estado;
}   


void creador_tableros_destruir(creador_tableros_t *self){
    //Do nothing
}

int creador_tableros_comenzar(creador_tableros_t *self){
    bool continuar = true;
    char entrada[TAM_BUFFER_ENTRADA] = {0};
    unsigned int i = 0;
    while (continuar){
        i = 0;
        _imprimir(self);
        printf("Ingrese un comando(h para ayuda): ");
        fgets(entrada, TAM_BUFFER_ENTRADA, stdin);
        while (entrada[i] != '\n'){
            self->ultima_op = entrada[i];
            continuar = _modificar_tablero(self, entrada[i]);
            i++;
        }
    }
    printf("Generando archivo de salida...\n");
    int estado = _escribir_archivo(self);
    if (estado == ERROR){
        fprintf(stderr, "Error al generar el archivo de salida.\n");
        return ERROR;
    }
    printf("Archivo de salida generado exitosamente.\n");
    return EXITO;
}

void imprimir_ayuda(){
    printf("\n");
    printf("Comandos disponibles para el operador\n\n");
    printf("%c: Imprime ayuda\n", TECLA_AYUDA);
    printf("%c: Salir de la aplicacion\n", TECLA_ESCAPE);
    printf("%c: Mover hacia arriba\n", TECLA_ARRIBA);
    printf("%c: Mover hacia abajo\n", TECLA_ABAJO);
    printf("%c: Mover hacia la derecha\n", TECLA_DERECHA);
    printf("%c: Mover hacia la izquierda\n", TECLA_IZQUIERDA);
    printf("%c: Agregar celda\n", AGREGAR_CELDA);
    printf("%c: Quitar celda\n", QUITAR_CELDA);
    printf("\n");
}
