#include <stdio.h>
#include "pruebas.h"

int main(int argc, char* argv[]){
    pruebas();    
    return 1;
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