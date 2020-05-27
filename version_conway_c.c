#include "version_conway.h"
#include <string.h>

const char* VERSION = "C";

char* obtener_version(char* buffer){
    long unsigned int tam = strlen(VERSION);
    memcpy(buffer, VERSION, tam);
    buffer[tam] = 0;
    return buffer;
}