#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"



int main() {
 
    Nodo* nodo_raiz = crear_nodo(NULL, "Directorio", "");

    Nodo* directorio_actual = nodo_raiz;
    char comando[256];
    char nombre_archivo[128];
    char nombre_directorio[128];
    char contenido[256];

    while (1) {
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = '\0';
        if (strcmp(comando, "salir") == 0) {
            break;
        }
        else if (sscanf(comando, "cd %127s", nombre_directorio) == 1) {
            directorio_actual = cd(directorio_actual, nombre_directorio);
        }
        else if (strncmp(comando, "mapdir", 6) == 0) {
            char cmd[32];
            char arg[128];
            arg[0] = '\0';
            if (sscanf(comando + 7, "%31s %127s", cmd, arg) == 2) {
                mapdir(directorio_actual, cmd, arg);
            }
            else if (sscanf(comando + 7, "%31s %127s", cmd, arg) == 1) {
                mapdir(directorio_actual, cmd, arg);
            }
        }

        else if (strncmp(comando, "ls", 2) == 0) {
            
            if (comando[2] == ' ') {
                sscanf(comando + 3, "%127s", nombre_directorio);
                ls(directorio_actual, nombre_directorio);
            } else if (comando[2] == '\0') {
                ls(directorio_actual, NULL);
            }
        
        }

        else if (sscanf(comando, "mkdir %127s", nombre_directorio) == 1) {
            mkdir(directorio_actual, nombre_directorio);
        }
        else if (sscanf(comando, "write %127s %255[^\n]", nombre_archivo, contenido) == 2) {
            write(directorio_actual, nombre_archivo, contenido);
        }
        else if (sscanf(comando, "cat %127s", nombre_archivo) == 1) {
            cat(directorio_actual, nombre_archivo);
        }
        else if (sscanf(comando, "touch %127s", nombre_archivo) == 1) {
            touch(directorio_actual, nombre_archivo);
        } 
        else {
            printf("Comando no reconocido.\n");
        }
    }
    
    liberar_contenido(nodo_raiz);
    free(nodo_raiz);
    
    
    return 0;
}