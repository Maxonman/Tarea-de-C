Para usar este programa primero debe habrir una terminal de Linux, posteriormente se hace uso del MAKEFILE, escribiendo make en la consola.

Luego se ejecuta el programa escribiendo ./out por consola.

El programa funciona escribiendo los siguientes comandos por consola:

-touch <Nombre_Del_Archivo> Este comando crea un archivo con el nombre escrito.

-mkdir <Nombre_Del_Directorio> Este comando crea un directorio con el nombre escrito.

-write <Nombre_Del_Archivo> <Contenido_Del_Archivo> Este comando escribe el contenido del archivo en el nombre del archivo escrito (El archivo debe encontrarse en el directorio actual).

-cd <Nombre_Del_Directorio> Selecciona un directorio que coincida con el nombre escrito y se convierte en el directorio actual, si el nombre escrito es .. entonces el nuevo directorio actual sera el padre del directorio actual.

-cat <Nombre_Del_Archivo> Este comandoEste comando imprime en pantalla el contenido del archivo cuyo nombre coincida con el escrito (El archivo debe encontrarse en el directorio actual).

-ls Esta funcion imprime por pantalla los nombres de todos los archivos y directorios que estan dentro del directorio actual.

-ls <Nombre_Del_Directorio> Este comando imprime por pantalla los nombres de todos los archivos y directorios que estan dentro del directorio cuyo nombre coincida con el escrito (Este directorio debe ser un subdirectorio del actual), si el usuario escribe . entonces actuara como un ls normal.

-mapdir <Instrucción> Ejecuta la instrucción dada en cada subdirectorio del directorio actual. La instrucción puede ser una de las siguientes instrucciones:

	-touch <Nombre_Del_Archivo>
	-mkdir <Nombre_Del_Directorio>
	-ls
	-ls <Nombre_Del_Directorio>

-salir Esta opción termina con el programa.


Nota: Los nombres de archivos y directorios solo pueden ser formados por letras, números y puntos.




Al usar salir se libera la memoria reservada por el programa.