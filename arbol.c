#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

/*Descripción de la función:

La función crear_lista crea y devuelve una lista vacía de nodos con un tamaño máximo inicial especificado. La lista se implementa como un arreglo dinámico de nodos.

Parámetros:

    -largo_maximo_inicial (int): El tamaño máximo inicial del arreglo dinámico de nodos que se va a crear.

Retorno:

lista (Lista*): Un puntero a la lista creada.*/
Lista* crear_lista(int largo_maximo_inicial) {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista->largo_actual = 0;
    lista->largo_maximo = largo_maximo_inicial;
    lista->arreglo = (Nodo*) malloc(largo_maximo_inicial * sizeof(Nodo));
    return lista;
}

/*Descripción de la función:

Esta función tiene como objetivo insertar un nodo en una lista dada. Si la lista está llena (es decir, el número de elementos en la lista es igual al tamaño máximo de la lista), la función aumenta el tamaño máximo de la lista multiplicando el tamaño máximo actual por dos. Luego, se inserta el nodo en la lista y se incrementa el contador de longitud actual de la lista.

Parametros:

    -lista (puntero a Lista): un puntero a la lista en la que se va a insertar el nodo.
    -nodo (puntero a Nodo): un puntero al nodo que se va a insertar en la lista.

Retorno:

La función no devuelve nada (void).*/
void insertar_lista(Lista* lista, Nodo* nodo) {
    if (lista->largo_actual >= lista->largo_maximo) {
        lista->largo_maximo *= 2;
        lista->arreglo = (Nodo*) realloc(lista->arreglo, lista->largo_maximo * sizeof(Nodo));
    }
    
    lista->arreglo[lista->largo_actual] = *nodo;
    lista->largo_actual += 1;
}

/*Descripción de la función:
La función "crear_nodo" crea un nuevo nodo con los siguientes parámetros:

Parametros:

    -padre (Nodo*): puntero al nodo padre del nuevo nodo.
    -tipo (char*): una cadena de caracteres que representa el tipo del nodo.
    -nombre (char*): una cadena de caracteres que representa el nombre del nodo.

Retorno:

nuevo_nodo (Nodo*): un puntero al nodo recién creado.
*/
Nodo* crear_nodo(Nodo* padre,  char* tipo, char* nombre) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->padre = (struct Nodo *)padre;
    strncpy(nuevo_nodo->tipo, tipo, sizeof(nuevo_nodo->tipo) - 1);
    nuevo_nodo->tipo[sizeof(nuevo_nodo->tipo) - 1] = '\0';
    if (strcmp(nuevo_nodo->tipo, "Directorio") == 0) {
        nuevo_nodo->contenido = (Directorio*)malloc(sizeof(Directorio));
        strncpy(((Directorio*) nuevo_nodo->contenido)->nombre, nombre, sizeof(((Directorio*) nuevo_nodo->contenido)->nombre) - 1);
        ((Directorio*) nuevo_nodo->contenido)->nombre[sizeof(((Directorio*) nuevo_nodo->contenido)->nombre) - 1] = '\0';
        ((Directorio*) nuevo_nodo->contenido)->hijos = crear_lista(4);
    }
    else{
        nuevo_nodo->contenido = (Archivo*)malloc(sizeof(Archivo));
        strncpy(((Archivo*) nuevo_nodo->contenido)->nombre, nombre, sizeof(((Archivo*) nuevo_nodo->contenido)->nombre) - 1);
        ((Archivo*) nuevo_nodo->contenido)->nombre[sizeof(((Archivo*) nuevo_nodo->contenido)->nombre) - 1] = '\0';
    
    }
    return nuevo_nodo;
}

/*Descripcion de la función:
La función busca un archivo en un directorio dado. Si encuentra el archivo, devuelve un puntero al nodo correspondiente en la estructura de datos, de lo contrario devuelve NULL.

Parametros:

    -directorio (Nodo*): Un puntero al nodo del directorio en el que se va a buscar el archivo.
    -nombre_archivo ( char*): El nombre del archivo a buscar.

Retorno:

(Nodo*): Si se encuentra el archivo, devuelve un puntero al nodo correspondiente. De lo contrario, devuelve NULL.*/
Nodo* buscar_archivo(Nodo* directorio,  char* nombre_archivo) {
    if (strcmp(directorio->tipo, "Directorio") != 0) {
        printf("Error el nodo no es un directorio.\n");
        return NULL;
    }

    Directorio* contenido_directorio = (Directorio*)directorio->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Archivo") == 0) {
            Archivo* archivo = (Archivo*)nodo->contenido;
            if (strcmp(archivo->nombre, nombre_archivo) == 0) {
                return nodo;
            }
        }
    }


    return NULL;
}

/*Descripción de la función:
Esta función busca un nodo de tipo "Directorio" en el contenido de un nodo de tipo "Directorio" dado, que tenga el nombre especificado. Si se encuentra un nodo que cumple con estas condiciones, se devuelve un puntero al nodo encontrado. Si no se encuentra un nodo coincidente, se devuelve un puntero nulo.

Parámetros:

    -directorio_actual (Nodo*): Un puntero al nodo de tipo "Directorio" que se usará como el directorio actual.
    -nombre_directorio ( char*): Un puntero a una cadena de caracteres que representa el nombre del directorio que se está buscando.

Retorno:

(Nodo*): Un puntero al nodo que coincide con los criterios de búsqueda o NULL si no se encontró ningún nodo coincidente.*/
Nodo* buscar_directorio(Nodo* directorio_actual,  char* nombre_directorio) {
    if (strcmp(directorio_actual->tipo, "Directorio") != 0) {
        return NULL;
    }

    Directorio* contenido_directorio = (Directorio*)directorio_actual->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Directorio") == 0) {
            Directorio* directorio = (Directorio*)nodo->contenido;
            if (strcmp(directorio->nombre, nombre_directorio) == 0) {
                return nodo;
            }
        }
    }

    return NULL;
}

/*Descripción de la función:
La función "touch" crea un nuevo archivo en el directorio actual especificado. El archivo creado tiene un nombre especificado por el parámetro "nombre_archivo" y no contiene ningún contenido.

Parametros:

    -actual (Nodo*): el nodo que representa el directorio actual donde se creará el nuevo archivo.
    -nombre_archivo ( char*): el nombre del nuevo archivo que se creará.

Retorno:

La función no tiene retorno, pero crea un nuevo nodo de archivo y lo inserta en la lista de hijos del nodo de directorio actual.*/
void touch(Nodo* actual,  char* nombre_archivo) {


    Nodo* nuevo_nodo_archivo = crear_nodo(actual, "Archivo", nombre_archivo);
    Directorio* directorio_actual = (Directorio*)actual->contenido;
    insertar_lista(directorio_actual->hijos, nuevo_nodo_archivo);
    free(nuevo_nodo_archivo);
}

/*Descripción de la función:

La función ls permite listar el contenido de un directorio especificado por el usuario. Si se especifica un nombre de directorio como argumento, entonces se lista el contenido de ese directorio en particular. En caso contrario, se listará el contenido del directorio actual especificado por el nodo directorio_actual.

La función recorre los hijos del directorio a listar, los cuales son nodos que pueden ser archivos o directorios. Para cada nodo, se imprime su nombre o se agrega un prefijo "./" en caso de que sea un subdirectorio. Si el nodo no es ni archivo ni directorio, entonces se imprime su tipo.

Parámetros:

    -directorio_actual: Un puntero al nodo que representa el directorio actual.
    -nombre_directorio: Una cadena de caracteres que especifica el nombre del directorio cuyo contenido se desea listar. Si es NULL, se listarán los archivos y subdirectorios del directorio actual.

Retorno: 

La función no retorna ningún valor.*/
void ls(Nodo* directorio_actual,  char* nombre_directorio) {
    Nodo* directorio_a_listar = directorio_actual;

    if (nombre_directorio != NULL) {
        if (strcmp(nombre_directorio, ".") == 0) {
            // Si el nombre del directorio es "." simplemente llamamos a la función ls con NULL
            ls(directorio_a_listar, NULL);
            return;
        }        
        directorio_a_listar = buscar_directorio(directorio_actual, nombre_directorio);
        if (directorio_a_listar == NULL) {
            printf("Error el directorio %s no existe.\n", nombre_directorio);
            return;
        }
    } else if (strcmp(directorio_actual->tipo, "Directorio") != 0) {
        printf("Error el nodo no es un directorio.\n");
        return;
    }

    Directorio* contenido_directorio = (Directorio*)directorio_a_listar->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Archivo") == 0) {
            Archivo* archivo = (Archivo*)nodo->contenido;
            printf("%s\n", archivo->nombre);
        } else if (strcmp(nodo->tipo, "Directorio") == 0) {
            Directorio* subdir = (Directorio*)nodo->contenido;
            printf("./%s\n", subdir->nombre);
        } else {
            printf("%s\n", nodo->tipo);
        }
    }
}

/*Descripción de la función: Esta función crea un nuevo directorio en el sistema de archivos basado en nodos.

Parámetros:

    -actual (puntero a Nodo): Puntero al nodo que representa el directorio padre donde se creará el nuevo directorio.
    -nombre_directorio (puntero a char): Puntero a la cadena de caracteres que contiene el nombre del nuevo directorio a crear.

Retorno:

Esta función no devuelve ningún valor.*/
void mkdir(Nodo* actual, char* nombre_directorio) {

    Nodo* nuevo_nodo_directorio = crear_nodo(actual, "Directorio", nombre_directorio);
    Directorio* directorio_actual = (Directorio*)actual->contenido;    
    insertar_lista(directorio_actual->hijos, nuevo_nodo_directorio);
    free(nuevo_nodo_directorio);

}

/*Descripción de la función:
La función se encarga de buscar el directorio con el nombre especificado dentro de la lista de hijos del directorio actual. Si el directorio es encontrado, la función devuelve el nodo que representa al directorio encontrado. Si el directorio no es encontrado, se muestra un mensaje de error y se devuelve el nodo que representa el directorio actual.

Parámetros:

    -actual (Nodo*): Puntero al nodo que representa el directorio actual.
    -nombre_directorio (char*): Puntero al string que representa el nombre del directorio al que se quiere cambiar.

Retorno:

(Nodo*): Puntero al nodo que representa el nuevo directorio actual si se encuentra el directorio con el nombre especificado. Puntero al nodo que representa el directorio actual si no se encuentra el directorio especificado o si ocurre un error.*/
Nodo* cd(Nodo* actual,  char* nombre_directorio) {
    if (strcmp(actual->tipo, "Directorio") != 0) {
        printf("Error el nodo actual no es un directorio.\n");
        return actual;
    }
    if (strcmp(nombre_directorio, "..") == 0) {
        if (actual->padre != NULL) {
            return (Nodo *)actual->padre;
        } else {
            printf("Error ya estás en el directorio raíz.\n");
            return actual;
        }
    }
    Directorio* directorio_actual = (Directorio*)actual->contenido;
    for (int i = 0; i < directorio_actual->hijos->largo_actual; i++) {
        Nodo* nodo = &directorio_actual->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Directorio") == 0) {
            Directorio* subdir = (Directorio*)nodo->contenido;
            if (strcmp(subdir->nombre, nombre_directorio) == 0) {
                return nodo;
            }
        }
    }

    printf("Error el directorio '%s' no se encuentra en el directorio actual.\n", nombre_directorio);
    return actual;
}

/*Descripción de la función:

La función write se encarga de escribir el contenido pasado como argumento en el archivo con el nombre especificado en el directorio actual.

Parámetros:

    -directorio_actual (Nodo*): Puntero al nodo del directorio actual.
    -nombre_archivo (char*): Nombre del archivo a escribir.
    -contenido (char*): Contenido a escribir en el archivo.

Retorno:

La funcion no retorna nada.*/
void write(Nodo* directorio_actual,  char* nombre_archivo,  char* contenido) {

    Directorio* contenido_directorio = (Directorio*)directorio_actual->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Archivo") == 0) {
            Archivo* archivo = (Archivo*)nodo->contenido;
            if (strcmp(archivo->nombre, nombre_archivo) == 0) {
                strncpy(archivo->contenido, contenido, sizeof(archivo->contenido) - 1);
                archivo->contenido[sizeof(archivo->contenido) - 1] = '\0';
                return;
            }
        }
    }

    printf("Error el archivo %s no se encuentra en el directorio actual.\n", nombre_archivo);
    return;
}

/*Descripción de la función:

Imprime el contenido de un archivo en el directorio actual, dado su nombre.
Parámetros:

    -directorio_actual (Nodo*): el nodo que representa el directorio actual.
    -nombre_archivo ( char*): el nombre del archivo cuyo contenido se desea imprimir.

Retorno:

La función no retorna ningún valor. Si el archivo no se encuentra en el directorio actual, se imprime un mensaje de error. Si se encuentra, se imprime su contenido en la consola.*/
void cat(Nodo* directorio_actual,  char* nombre_archivo) {

    Directorio* contenido_directorio = (Directorio*)directorio_actual->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Archivo") == 0) {
            Archivo* archivo = (Archivo*)nodo->contenido;
            if (strcmp(archivo->nombre, nombre_archivo) == 0) {
                printf("%s\n", archivo->contenido);
                return;
            }
        }
    }

    printf("Error el archivo %s no se encuentra en el directorio actual.\n", nombre_archivo);
}

/*Descripcion de la funcion
    Esta función ejecuta un comando dado en todos los subdirectorios de un directorio dado.

Parametros:
    - actual (Nodo*): Un puntero al directorio actual.
    - cmd (char*): El comando a ejecutar en los subdirectorios.
    - arg (char*): El argumento que se utilizará con el comando. Puede ser NULL si no se necesita.

Retorno:
    Esta función no devuelve nada, pero puede ejecutar una de las siguientes acciones:
    - Ejecuta el comando "mkdir" en cada subdirectorio con el argumento dado.
    - Ejecuta el comando "touch" en cada subdirectorio con el argumento dado.
    - Ejecuta el comando "ls" en cada subdirectorio. Si el argumento no es NULL, lo utiliza como argumento para el comando "ls".
    - Imprime "Comando no reconocido" si el comando dado no es "mkdir", "touch" o "ls".*/

void mapdir(Nodo* actual, char* cmd,  char* arg) {

    Directorio* contenido_directorio = (Directorio*)actual->contenido;
    for (int i = 0; i < contenido_directorio->hijos->largo_actual; i++) {
        Nodo* nodo = &contenido_directorio->hijos->arreglo[i];
        if (strcmp(nodo->tipo, "Directorio") == 0) {
            if (strcmp(cmd, "mkdir") == 0) {
                mkdir(nodo, arg);
            } else if (strcmp(cmd, "touch") == 0) {
                touch(nodo, arg);
            } else if (strcmp(cmd, "ls") == 0) {
                if (arg[0] == '\0'){
                    ls(nodo, NULL);
                }
                else{
                    ls(nodo, arg);
                }
                
            } else {
                printf("Comando no reconocido.\n");
            }
        }
    }
}

/*Descripción de la función:

Esta funcion recorre el arbol y libera la memoria de cada uno de los nodos.

Parametros:

    -nodo (Nodo*): el nodo que representa el valor de la raiz.

Retorno:

Esta funcion no retorna nada.*/

void liberar_contenido(Nodo* nodo) {
    if (strcmp(nodo->tipo, "Directorio") == 0) {
        
        for (int i = 0; i < ((Directorio*) nodo->contenido)->hijos->largo_actual; i++) {
            liberar_contenido(&(((Directorio*) nodo->contenido)->hijos->arreglo[i]));
        }
        free(((Directorio*) nodo->contenido)->hijos->arreglo);
        free(((Directorio*) nodo->contenido)->hijos);
    }

    free(nodo->contenido);

}