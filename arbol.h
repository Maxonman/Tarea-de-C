#ifndef ARBOL_H
#define ARBOL_H

#include <stddef.h>

typedef struct {
    struct Nodo* padre;
    char tipo[64];
    void* contenido;
} Nodo;

typedef struct {
    int largo_actual;
    int largo_maximo;
    Nodo* arreglo;
} Lista;

typedef struct {
    char nombre[128];
    Lista* hijos;
} Directorio;

typedef struct {
    char nombre[128];
    char contenido[256];
} Archivo;

Lista* crear_lista(int largo_maximo_inicial);
void insertar_lista(Lista* lista, Nodo* nodo);
Nodo* crear_nodo(Nodo* padre,  char* tipo, char* nombre);
Nodo* buscar_archivo(Nodo* directorio,  char* nombre_archivo);
Nodo* buscar_directorio(Nodo* directorio_actual,  char* nombre_directorio);
void touch(Nodo* actual,  char* nombre_archivo);
void ls(Nodo* directorio_actual,  char* nombre_directorio);
void mkdir(Nodo* actual,  char* nombre_directorio);
Nodo* cd(Nodo* actual,  char* nombre_directorio);
void write(Nodo* directorio_actual,  char* nombre_archivo,  char* contenido);
void cat(Nodo* directorio_actual,  char* nombre_archivo);
void mapdir(Nodo* actual,  char* cmd,  char* arg);
void liberar_memoria(Nodo* directorio_raiz);
void liberar_memoria_recursivo(Nodo* nodo_actual);
void liberar_contenido(Nodo* nodo);


#endif // ARBOL_H
