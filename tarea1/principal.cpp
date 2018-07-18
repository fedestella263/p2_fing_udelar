/*
  Módulo principal de la tarea 1.

  Procesador de comandos que prueba las operaciones declaradas en info.h.
  
  Lee comandos desde la entrada estándar e imprime en la salida estándar.

  Cada comando ocupa una línea. Empieza con un nombre y opcionalmente tiene
  parámetros.

  El comando con nombre 'Fin' termina la ejecución del programa.
  El comando con nombre '#' representa un comentario.

  La entrada y salida se pueden redirigir a archivos. 
  Un ejemplo de ejecución es
  $ ./principal < test/01.in > test/01.sal 

  En test/01.in hay dos comandos: el primero es un comentario y el segundo
  es 'Fin'.
  El programa llama a 'crear_info', entra en el bucle, ejecuta las dos
  iteraciones correspondientes a los comandos y luego de salir del bucle 
  llama a 'liberar_info' y termina.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/info.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_PALABRA 32
#define MAX_LINEA 100

// programa principal
int main() {

  // Arreglo de chars de tamaño 1
  char *nulo = new char[1];
  // Ssímbolo de terminación en la primera posición 
  nulo[0] = '\0';
  info_t info = crear_info(0, nulo);

  char resto_linea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    char nom_comando[MAX_PALABRA];
    scanf("%s", nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      scanf("%[^\n]", resto_linea);
      printf("# %s.\n", resto_linea);

    } else if (!strcmp(nom_comando, "imprimir_numero")) {
      printf("El dato numérico es %d.\n", numero_info(info));

    } else if (!strcmp(nom_comando, "imprimir_frase")) {
      printf("El dato de texto es %s.\n", frase_info(info));

    } else if (!strcmp(nom_comando, "imprimir_info")) {
      char *txt_info = info_a_texto(info);
      printf("El info es %s.\n", txt_info);
      delete[] txt_info;

    } else if (!strcmp(nom_comando, "son_iguales")) {
      info_t i1, i2;
      i1 = leer_info(MAX_LINEA);
      i2 = leer_info(MAX_LINEA);
      printf("%son iguales.\n", son_iguales(i1, i2) ? "S" : "No s");
      liberar_info(i1);
      liberar_info(i2);

    } else if (!strcmp(nom_comando, "copiar_info")) {
      info_t copia = copia_info(info);
      char *txt_copia = info_a_texto(copia);
      printf("La copia es %s.\n", txt_copia);
      delete[] txt_copia;
      liberar_info(copia);

    } else if (!strcmp(nom_comando, "cambiar_numero")) {
      int num;
      scanf("%d", &num);
      char *copia_texto = new char[strlen(frase_info(info)) + 1];
      strcpy(copia_texto, frase_info(info));
      liberar_info(info);
      info = crear_info(num, copia_texto);
      printf("El nuevo número es %d.\n", num);

    } else if (!strcmp(nom_comando, "cambiar_frase")) {
      int num = numero_info(info);
      liberar_info(info);
      char *nueva_frase = new char[MAX_LINEA];
      scanf("%*c%[^\n]", nueva_frase); // %*c para saltar el espacio en blanco
      info = crear_info(num, nueva_frase);
      printf("la nueva frase es %s.\n", nueva_frase);

    } else if (!strcmp(nom_comando, "leer_info")) {
      liberar_info(info);
      info = leer_info(MAX_LINEA);
      if (es_valida_info(info)) {
        char *txt_info = info_a_texto(info);
        printf("El nuevo info es %s.\n", txt_info);
        delete[] txt_info;
      } else {
        printf("Formato no válido.\n");
      }

    } else if (!strcmp(nom_comando, "combinar_info")) {
      info_t i1, i2;
      i1 = leer_info(MAX_LINEA);
      i2 = leer_info(MAX_LINEA);
      liberar_info(info);
      info = combinar_info(i1, i2);
      liberar_info(i1);
      liberar_info(i2);
      char *txt_info = info_a_texto(info);
      printf("El info combinado es %s.\n", txt_info);
      delete[] txt_info;

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  liberar_info(info);

  return 0;
}
