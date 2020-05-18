#ifndef __CREADOR_ARCHIVO_PBM__
#define __CREADOR_ARCHIVO_PBM__

typedef struct creador_archivo_pbm{
    char* nombre_archivo;
    char* prefijo;
    char* linea;
    unsigned int tam_nombre_archivo;
    unsigned int contador;
    unsigned int M;
    unsigned int N;
    unsigned int escala;
}creador_archivo_pbm_t;

/*
Inicializa la estructura creador_archivo_pbm.
Los archivos generados seran de ancho N*escala pixeles y
alto M*escala pixeles.
En caso de fallo devuelve -1 y no sera necesario llamar al destructor.
En caso de exito devuelve 0 y sera necesario llamar al destructor al finalizar.
*/
int creador_archivo_pbm_crear(creador_archivo_pbm_t *self, 
                              const char* prefijo,
                              const unsigned int M,
                              const unsigned int N,
                              const unsigned int escala);

/*
Destruye la estructura creador_archivo_pbm liberando los recursos.
No falla.
*/
void creador_archivo_pbm_destruir(creador_archivo_pbm_t *self);

/*
Crea un archivo en formato pbm con los datos de la matriz tablero.
El ancho y alto de la matriz es especificado en el creador de la estructura.
Tras cada llamada a esta funcion se crea un unico archivo pbm de nombre
prefijo_xxx.pbm donde xxx es el numero de archivos creados hasta el momento.
En caso de fallo devuelve -1.
En caso de exito devuelve 0.
*/
int creador_archivo_pbm_nuevo_archivo(creador_archivo_pbm_t *self, unsigned char** tablero);

#endif