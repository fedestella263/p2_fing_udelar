/*
  Módulo principal de la tarea 5.

Intérprete de comandos para probar los módulos.

Están creados una cadena_t `cad', un localizador_t `loc', un binario_t `b',
una pila_t `p', una cola_binarios_t `cb', un iterador_t `it', un conjunto_t
`cnj', una cola_prioridad_t `cp' y una tabla `t'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto' del módulo `info', con el agregado de que no puede incluir el
 símbolo ')'.

Si un parámetro es una secuencia de elementos de algún tipo termina con un
espacio en blanco y un punto.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a `cad', `b', `p', `cb', `it', `cnj', `cp' y `t' y
los vuelve a
crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/info.h"
#include "include/cadena.h"
#include "include/uso_tads.h"
#include "include/binario.h"
#include "include/pila.h"
#include "include/cola_binarios.h"
#include "include/iterador.h"
#include "include/conjunto.h"
#include "include/cola_prioridad.h"
#include "include/tabla.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256
#define MAX_PILA 10
#define MAX_TABLA 13
#define MAX_PRIORIDAD 50
#define MAX_CP 10

/*
 Convierte `n' a string.
 */
char *int_a_texto(int n) {
  char *res = new char[11];
  sprintf(res, "%d", n);
  return res;
}

/*
  Lee una cadena_t de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
 */
cadena_t leer_cadena() {
  cadena_t res = crear_cadena();
  info_t info = leer_info(MAX_PALABRA);
  while (es_valida_info(info)) {
    insertar_al_final(info, res);
    info = leer_info(MAX_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_cadena

// Libera la memoria de `cb' y de sus binarios. //
void destruir_cola_binarios(cola_binarios_t cb) {
  while (!es_vacia_cola_binarios(cb)) {
    binario_t f = frente(cb);
    desencolar(cb);
    liberar_binario(f);
  }
  liberar_cola_binarios(cb);
} // destruir_cola_binarios

// programa principal
int main() {

  cola_prioridad_t cp = crear_cp(MAX_CP, MAX_PRIORIDAD);
  tabla_t t = crear_tabla(MAX_TABLA);

  pila_t p = crear_pila(MAX_PILA);
  cola_binarios_t cb = crear_cola_binarios();
  iterador_t it = crear_iterador();
  conjunto_t cnj = crear_conjunto();

  binario_t b = crear_binario();
  cadena_t cad = crear_cadena();
  localizador_t loc = inicio_cadena(cad); // no válido porque cad es vacía

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

      // operaciones de cola_prioridad

    } else if (!strcmp(nom_comando, "insertar_en_cp")) {
      if (es_llena_cp(cp))
        printf("cp esta llena.\n");
      else {
        prio_t prio;
        scanf("%u", &prio);
        if (hay_prioridad(prio, cp) || prio > max_prioridad(cp))
          printf("Valor no válido.\n");
        else {
          info_t info = leer_info(MAX_LINEA);
          insertar_en_cp(info, prio, cp);
          printf("Insertado en cp.\n");
        }
      }

    } else if (!strcmp(nom_comando, "priorizar")) {
      prio_t prio;
      scanf("%u", &prio);
      if (!hay_prioridad(prio, cp) || hay_prioridad(prio / 2, cp))
        printf("Valor no válido-\n");
      else {
        priorizar(prio, cp);
        printf("Priorizado.\n");
      }

    } else if (!strcmp(nom_comando, "despriorizar")) {
      prio_t prio;
      scanf("%u", &prio);
      if (!hay_prioridad(prio, cp) ||
          hay_prioridad((prio + max_prioridad(cp)) / 2, cp))
        printf("Valor no válido.\n");
      else {
        despriorizar(prio, cp);
        printf("Despriorizado.\n");
      }

    } else if (!strcmp(nom_comando, "eliminar_prioritario")) {
      if (es_vacia_cp(cp))
        printf("cp está vacía.\n");
      else {
        eliminar_prioritario(cp);
        printf("Eliminado el prioritario de cp.\n");
      }

    } else if (!strcmp(nom_comando, "es_vacia_cp")) {
      printf("cp %s vacia.\n", es_vacia_cp(cp) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "es_llena_cp")) {
      printf("cp %s llena.\n", es_llena_cp(cp) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "hay_prioridad")) {
      prio_t prio;
      scanf("%u", &prio);
      printf("%s prioridad.\n", hay_prioridad(prio, cp) ? "Hay" : "No hay");

    } else if (!strcmp(nom_comando, "prioritario")) {
      if (es_vacia_cp(cp))
        printf("cp está vacía.\n");
      else {
        char *txt_info = info_a_texto(prioritario(cp));
        printf("%s.\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "prioridad_prioritario")) {
      if (es_vacia_cp(cp))
        printf("cp está vacía.\n");
      else {
        printf("%d.\n", prioridad_prioritario(cp));
      }

    } else if (!strcmp(nom_comando, "max_prioridad")) {
      printf("%d.\n", max_prioridad(cp));

      // operaciones de tabla

    } else if (!strcmp(nom_comando, "asociar_en_tabla")) {
      if (esta_llena_tabla(t))
        printf("t esta llena.\n");
      else {
        int clave;
        scanf("%d", &clave);
        char *valor = new char[MAX_PALABRA];
        scanf("%s", valor);
        asociar_en_tabla(clave, valor, t);
        printf("Asociado.\n");
      }

    } else if (!strcmp(nom_comando, "eliminar_de_tabla")) {
      int clave;
      scanf("%d", &clave);
      if (!existe_asociacion(clave, t))
        printf("No existe asociación en t.\n");
      else {
        eliminar_de_tabla(clave, t);
        printf("Desasociado.\n");
      }

    } else if (!strcmp(nom_comando, "existe_asociacion")) {
      int clave;
      scanf("%d", &clave);
      printf("%s asociación en t.\n",
             existe_asociacion(clave, t) ? "Existe" : "NO existe");

    } else if (!strcmp(nom_comando, "valor_en_tabla")) {
      int clave;
      scanf("%d", &clave);
      if (!existe_asociacion(clave, t))
        printf("No existe asociación en t.\n");
      else
        printf("%s.\n", valor_en_tabla(clave, t));

    } else if (!strcmp(nom_comando, "esta_llena_tabla")) {
      printf("t %s llena.\n", esta_llena_tabla(t) ? "está" : "NO está");

      // operaciones de pila

    } else if (!strcmp(nom_comando, "apilar")) {
      if (es_llena_pila(p))
        printf("p está llena.\n");
      else {
        char *txt = new char[MAX_PALABRA];
        scanf("%s", txt);
        apilar(txt, p);
        printf("Apilado.\n");
      }

    } else if (!strcmp(nom_comando, "cima")) {
      if (es_vacia_pila(p))
        printf("p está vacía.\n");
      else {
        printf("%s.\n", cima(p));
      }

    } else if (!strcmp(nom_comando, "desapilar")) {
      if (es_vacia_pila(p))
        printf("p está vacía.\n");
      else {
        desapilar(p);
        printf("Desapilado.\n");
      }

    } else if (!strcmp(nom_comando, "es_vacia_pila")) {
      printf("p %s vacia.\n", es_vacia_pila(p) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "es_llena_pila")) {
      printf("p %s llena.\n", es_llena_pila(p) ? "está" : "NO está");

      // operaciones de cola_binarios

    } else if (!strcmp(nom_comando, "encolar")) {
      cadena_t bal = leer_cadena();
      if (!esta_ordenada_por_frase(bal))
        printf("Cadena no ordenada.\n");
      else {
        binario_t bin = crear_balanceado(bal);
        encolar(bin, cb);
        printf("Encolado.\n");
      }
      liberar_cadena(bal);

    } else if (!strcmp(nom_comando, "frente")) {
      if (es_vacia_cola_binarios(cb))
        printf("cb está vacía.\n");
      else {
        binario_t f = frente(cb);
        imprimir_binario(f);
      }

    } else if (!strcmp(nom_comando, "desencolar")) {
      if (es_vacia_cola_binarios(cb))
        printf("cb está vacía.\n");
      else {
        binario_t f = frente(cb);
        desencolar(cb);
        liberar_binario(f);
        printf("Desencolado.\n");
      }

    } else if (!strcmp(nom_comando, "es_vacia_cola_binarios")) {
      printf("cb %s vacia.\n", es_vacia_cola_binarios(cb) ? "está" : "NO está");

      // operaciones de iterador

    } else if (!strcmp(nom_comando, "agregar_a_iterador")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      agregar_a_iterador(txt, it);
      printf("Agregado.\n");

    } else if (!strcmp(nom_comando, "reiniciar_iter")) {
      reiniciar_iter(it);
      printf("Reiniciado.\n");

    } else if (!strcmp(nom_comando, "avanzar_iter")) {
      avanzar_iter(it);
      printf("Avanzado.\n");

    } else if (!strcmp(nom_comando, "actual_iter")) {
      if (!esta_definida_actual(it))
        printf("Actual no definida.\n");
      else
        printf("%s.\n", actual_iter(it));

    } else if (!strcmp(nom_comando, "hay_siguiente_en_iter")) {
      if (!esta_definida_actual(it))
        printf("Actual no definida.\n");
      else
        printf("%s siguiente.\n", hay_siguiente_en_iter(it) ? "Hay" : "No hay");

    } else if (!strcmp(nom_comando, "esta_definida_actual")) {
      printf("Actual de it %s definida.\n",
             esta_definida_actual(it) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "iterador_a_cadena")) {
      cadena_t cad_iter = iterador_a_cadena(it);
      imprimir_cadena(cad_iter);
      liberar_cadena(cad_iter);

      // operaciones de conjunto

    } else if (!strcmp(nom_comando, "construir_conjunto")) {
      cadena_t cad_cnj = leer_cadena();
      if (!esta_ordenada_por_frase(cad_cnj))
        printf("Cadena no ordenada.\n");
      else {
        liberar_conjunto(cnj);
        cnj = construir_conjunto(cad_cnj);
        iterador_t it_cnj = iterador_conjunto(cnj);
        cadena_t cad_it = iterador_a_cadena(it_cnj);
        imprimir_cadena(cad_it);
        liberar_cadena(cad_it);
        liberar_iterador(it_cnj);
      }
      liberar_cadena(cad_cnj);

    } else if (!strcmp(nom_comando, "incluir")) {
      info_t info = leer_info(MAX_LINEA);
      bool incluido = incluir(info, cnj);
      printf("%s.\n", incluido ? "Se incluyó" : "No se incluyó");
      if (!incluido)
        liberar_info(info);

    } else if (!strcmp(nom_comando, "union_conjunto")) {
      cadena_t cad_cnj_2 = leer_cadena();
      if (!esta_ordenada_por_frase(cad_cnj_2))
        printf("Cadena no ordenada.\n");
      else {
        conjunto_t cnj_2 = construir_conjunto(cad_cnj_2);
        conjunto_t cnj_un = union_conjunto(cnj, cnj_2);
        iterador_t it_un = iterador_conjunto(cnj_un);
        cadena_t cad_it = iterador_a_cadena(it_un);
        imprimir_cadena(cad_it);
        liberar_cadena(cad_it);
        liberar_iterador(it_un);
        liberar_conjunto(cnj_2);
        liberar_conjunto(cnj_un);
      }
      liberar_cadena(cad_cnj_2);

    } else if (!strcmp(nom_comando, "interseccion")) {
      cadena_t cad_cnj_2 = leer_cadena();
      if (!esta_ordenada_por_frase(cad_cnj_2))
        printf("Cadena no ordenada.\n");
      else {
        conjunto_t cnj_2 = construir_conjunto(cad_cnj_2);
        conjunto_t cnj_int = interseccion(cnj, cnj_2);
        iterador_t it_int = iterador_conjunto(cnj_int);
        cadena_t cad_it = iterador_a_cadena(it_int);
        imprimir_cadena(cad_it);
        liberar_cadena(cad_it);
        liberar_iterador(it_int);
        liberar_conjunto(cnj_2);
        liberar_conjunto(cnj_int);
      }
      liberar_cadena(cad_cnj_2);

    } else if (!strcmp(nom_comando, "diferencia")) {
      cadena_t cad_cnj_2 = leer_cadena();
      if (!esta_ordenada_por_frase(cad_cnj_2))
        printf("Cadena no ordenada.\n");
      else {
        conjunto_t cnj_2 = construir_conjunto(cad_cnj_2);
        conjunto_t cnj_dif = diferencia(cnj, cnj_2);
        iterador_t it_dif = iterador_conjunto(cnj_dif);
        cadena_t cad_it = iterador_a_cadena(it_dif);
        imprimir_cadena(cad_it);
        liberar_cadena(cad_it);
        liberar_iterador(it_dif);
        liberar_conjunto(cnj_2);
        liberar_conjunto(cnj_dif);
      }
      liberar_cadena(cad_cnj_2);

    } else if (!strcmp(nom_comando, "excluir")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      excluir(txt, cnj);
      delete[] txt;
      printf("Excluido.\n");

    } else if (!strcmp(nom_comando, "pertenece_conjunto")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      printf("%s.\n",
             pertenece_conjunto(txt, cnj) ? "Pertenece" : "No pertenece");
      delete[] txt;

    } else if (!strcmp(nom_comando, "es_vacio_conjunto")) {
      printf("cnj %s vacio.\n", es_vacio_conjunto(cnj) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "iterador_conjunto")) {
      iterador_t it_cnj = iterador_conjunto(cnj);
      cadena_t cad_cnj = iterador_a_cadena(it_cnj);
      imprimir_cadena(cad_cnj);
      liberar_cadena(cad_cnj);
      liberar_iterador(it_cnj);

      // operaciones de binario

    } else if (!strcmp(nom_comando, "crear_balanceado")) {
      cadena_t bal = leer_cadena();
      if (!esta_ordenada_por_frase(bal)) {
        printf("Cadena no ordenada.\n");
      } else {
        liberar_binario(b);
        b = crear_balanceado(bal);
        imprimir_binario(b);
        liberar_cadena(bal);
      }

    } else if (!strcmp(nom_comando, "insertar_en_binario")) {
      info_t info = leer_info(MAX_PALABRA);
      bool insertado = insertar_en_binario(info, b);
      if (!insertado)
        liberar_info(info);
      printf("%s.\n", insertado ? "Insertado" : "No insertado");

    } else if (!strcmp(nom_comando, "remover_mayor")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else {
        info_t info = remover_mayor(b);
        char *txt_info = info_a_texto(info);
        printf("%s\n", txt_info);
        liberar_info(info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "remover_de_binario")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      bool removido = remover_de_binario(txt, b);
      printf("%s.\n", removido ? "Removido" : "NO removido");
      delete[] txt;

    } else if (!strcmp(nom_comando, "es_vacio_binario")) {
      printf("%s.\n", es_vacio_binario(b) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "es_AVL")) {
      printf("%s.\n", es_AVL(b) ? "AVL" : "No AVL");

    } else if (!strcmp(nom_comando, "raiz")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else {
        info_t info = raiz(b);
        char *txt_info = info_a_texto(info);
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "izquierdo")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else
        imprimir_binario(izquierdo(b));

    } else if (!strcmp(nom_comando, "derecho")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else
        imprimir_binario(derecho(b));

    } else if (!strcmp(nom_comando, "buscar_subarbol")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      binario_t sub = buscar_subarbol(txt, b);
      if (es_vacio_binario(sub))
        printf("sub es vacío.\n");
      else {
        char *txt_info = info_a_texto(raiz(sub));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }
      delete[] txt;

    } else if (!strcmp(nom_comando, "altura_binario")) {
      printf("%d.\n", altura_binario(b));

    } else if (!strcmp(nom_comando, "cantidad_binario")) {
      printf("%d.\n", cantidad_binario(b));

    } else if (!strcmp(nom_comando, "kesimo_en_binario")) {
      unsigned int k;
      scanf("%u", &k);
      if ((k < 1) || (k > cantidad_binario(b)))
        printf("k fuera de rango.\n");
      else {
        char *txt_info = info_a_texto(kesimo_en_binario(k, b));
        printf("%s.\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "linealizacion")) {
      cadena_t lineal = linealizacion(b);
      imprimir_cadena(lineal);
      liberar_cadena(lineal);

    } else if (!strcmp(nom_comando, "filtrado")) {
      unsigned int clave;
      scanf("%u", &clave);
      binario_t filtro = filtrado(clave, b);
      imprimir_binario(filtro);
      liberar_binario(filtro);

    } else if (!strcmp(nom_comando, "imprimir_binario")) {
      imprimir_binario(b);

      // operaciones de cadena

    } else if (!strcmp(nom_comando, "insertar_al_final")) {
      info_t info = leer_info(MAX_LINEA);
      insertar_al_final(info, cad);
      printf("Insertado al final.\n");

    } else if (!strcmp(nom_comando, "insertar_antes")) {
      info_t info = leer_info(MAX_LINEA);
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        insertar_antes(info, loc, cad);
        printf("Insertado antes de loc.\n");
      }

    } else if (!strcmp(nom_comando, "insertar_segmento_despues")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        cadena_t sgm = leer_cadena();
        insertar_segmento_despues(sgm, loc, cad);
        liberar_cadena(sgm);
        printf("Segmento insertado después de loc.\n");
      }

    } else if (!strcmp(nom_comando, "segmento_cadena")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cadena_t sgm = segmento_cadena(loc_desde, loc_hasta, cad);
        imprimir_cadena(sgm);
        liberar_cadena(sgm);
      }

    } else if (!strcmp(nom_comando, "separar_segmento")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cadena_t sgm = separar_segmento(loc_desde, loc_hasta, cad);
        imprimir_cadena(sgm);
        liberar_cadena(sgm);
      }

    } else if (!strcmp(nom_comando, "mezcla")) {
      cadena_t otra = leer_cadena();
      if (!esta_ordenada(cad) || !esta_ordenada(otra))
        printf("Cadena no ordenada.\n");
      else {
        cadena_t mzc = mezcla(cad, otra);
        imprimir_cadena(mzc);
        liberar_cadena(mzc);
      }
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "remover_de_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        remover_de_cadena(loc, cad);
        printf("Removido.\n");
      }

    } else if (!strcmp(nom_comando, "es_localizador")) {
      printf("loc%s válido.\n", es_localizador(loc) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_vacia_cadena")) {
      printf("cad%s.\n", es_vacia_cadena(cad) ? " vacia" : " no vacia");

    } else if (!strcmp(nom_comando, "esta_ordenada")) {
      printf("cad%s.\n", esta_ordenada(cad) ? " ordenada" : " no ordenada");

    } else if (!strcmp(nom_comando, "es_final_cadena")) {
      printf("loc%s es final de cad.\n",
             es_final_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_inicio_cadena")) {
      printf("loc%s es incio de cad.\n",
             es_inicio_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "localizador_en_cadena")) {
      printf("loc%s pertenece a cad.\n",
             localizador_en_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "precede_en_cadena")) {
      nat k1;
      scanf("%u", &k1);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad))
        printf("Posición fuera de rango.\n");
      else if (!localizador_en_cadena(loc, cad))
        printf("loc no pertenece a cad.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        printf("loc1%s precede a loc.\n",
               precede_en_cadena(loc1, loc, cad) ? "" : " no");
      }

    } else if (!strcmp(nom_comando, "inicio_cadena")) {
      loc = inicio_cadena(cad);
      printf("loc al inicio.\n");

    } else if (!strcmp(nom_comando, "final_cadena")) {
      loc = final_cadena(cad);
      printf("loc al final.\n");

    } else if (!strcmp(nom_comando, "kesimo")) {
      unsigned int k;
      scanf("%u", &k);
      loc = kesimo(k, cad);
      printf("loc en la posición %u.\n", k);

    } else if (!strcmp(nom_comando, "siguiente")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = siguiente(loc, cad);
        printf("loc al siguiente.\n");
      }

    } else if (!strcmp(nom_comando, "anterior")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = anterior(loc, cad);
        printf("loc al anterior.\n");
      }

    } else if (!strcmp(nom_comando, "menor_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = menor_en_cadena(loc, cad);
        printf("loc avanzó hasta el menor.\n");
      }

    } else if (!strcmp(nom_comando, "siguiente_clave")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        int clave;
        scanf("%d", &clave);
        loc = siguiente_clave(clave, loc, cad);
        printf("loc avanzó buscando %d.\n", clave);
      }

    } else if (!strcmp(nom_comando, "anterior_clave")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        int clave;
        scanf("%d", &clave);
        loc = anterior_clave(clave, loc, cad);
        printf("loc retrocedió buscando %d.\n", clave);
      }

    } else if (!strcmp(nom_comando, "info_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        char *txt_info = info_a_texto(info_cadena(loc, cad));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "cambiar_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        info_t nueva_info = leer_info(MAX_PALABRA);
        info_t anterior_info = info_cadena(loc, cad);
        cambiar_en_cadena(nueva_info, loc, cad);
        liberar_info(anterior_info);
        printf("Cambio.\n");
      }

    } else if (!strcmp(nom_comando, "intercambiar")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad) || (k2 < 1) || (k2 > cantidad))
        printf("Posición fuera de rango.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        localizador_t loc2 = kesimo(k2, cad);
        intercambiar(loc1, loc2, cad);
        printf("Intercambio.\n");
      }

    } else if (!strcmp(nom_comando, "imprimir_cadena")) {
      imprimir_cadena(cad);

      // operaciones de uso_tads

    } else if (!strcmp(nom_comando, "mayores")) {
      nat k, max;
      scanf("%u %u", &k, &max);
      if (k == 0)
        printf("k = 0.\n");
      else {
        cadena_t datos = leer_cadena();
        cadena_t res = mayores(datos, k, max);
        imprimir_cadena(res);
        liberar_cadena(datos);
        liberar_cadena(res);
      }

    } else if (!strcmp(nom_comando, "inverso_de_iter")) {
      nat a, b;
      scanf("%u %u", &a, &b);
      if (a < 1 || b < a)
        printf("Posiciones no válidas.\n");
      else {
        iterador_t inv = inverso_de_iter(a, b, it);
        while (esta_definida_actual(inv)) {
          printf("%s ", actual_iter(inv));
          avanzar_iter(inv);
        }
        printf("\n");
        liberar_iterador(inv);
      }

    } else if (!strcmp(nom_comando, "rango_en_conjunto")) {
      char *prim = new char[MAX_PALABRA];
      scanf("%s", prim);
      char *ult = new char[MAX_PALABRA];
      scanf("%s", ult);
      if (strcmp(prim, ult) > 0)
        printf("Orden incorrecto.\n");
      else {
        iterador_t rango = rango_en_conjunto(prim, ult, cnj);
        reiniciar_iter(rango);
        while (esta_definida_actual(rango)) {
          printf("%s ", actual_iter(rango));
          avanzar_iter(rango);
        }
        printf("\n");
        liberar_iterador(rango);
      }
      delete[] prim;
      delete[] ult;

    } else if (!strcmp(nom_comando, "imprimir_por_niveles")) {
      imprimir_por_niveles(b);
      printf("\n");

    } else if (!strcmp(nom_comando, "esta_ordenada_por_frase")) {
      cadena_t ord = leer_cadena();
      printf("%s.\n",
             esta_ordenada_por_frase(ord) ? "Ordenada" : "No ordenada");
      liberar_cadena(ord);

    } else if (!strcmp(nom_comando, "pertenece")) {
      int i;
      scanf("%d", &i);
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (!strcmp(nom_comando, "son_iguales")) {
      cadena_t otra = leer_cadena();
      printf("%s.\n",
             son_iguales(cad, otra) ? "Son iguales" : "No son iguales");
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "concatenar")) {
      cadena_t otra = leer_cadena();
      cadena_t conc = concatenar(cad, otra);
      imprimir_cadena(conc);
      liberar_cadena(conc);
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "ordenar")) {
      ordenar(cad);
      printf("Ordenada.\n");

    } else if (!strcmp(nom_comando, "cambiar_todos")) {
      int original, nuevo;
      scanf("%d %d", &original, &nuevo);
      cambiar_todos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (!strcmp(nom_comando, "subcadena")) {
      int menor, mayor;
      scanf("%d %d", &menor, &mayor);
      if (!esta_ordenada(cad) || (mayor < menor) || !pertenece(menor, cad) ||
          !pertenece(mayor, cad))
        printf("No se cumplen las precondiciones.\n");
      else {
        cadena_t sub = subcadena(menor, mayor, cad);
        imprimir_cadena(sub);
        liberar_cadena(sub);
      }

    } else if (!strcmp(nom_comando, "reiniciar")) {
      liberar_cadena(cad);
      cad = crear_cadena();
      loc = inicio_cadena(cad);
      liberar_binario(b);
      b = crear_binario();
      liberar_pila(p);
      p = crear_pila(MAX_PILA);
      destruir_cola_binarios(cb);
      cb = crear_cola_binarios();
      liberar_iterador(it);
      it = crear_iterador();
      liberar_conjunto(cnj);
      cnj = crear_conjunto();
      liberar_cp(cp);
      cp = crear_cp(MAX_CP, MAX_PRIORIDAD);
      liberar_tabla(t);
      t = crear_tabla(MAX_TABLA);
      printf("Estructuras reiniciadas.\n");

      // Comandos para tests de tiempo
    } else if (!strcmp(nom_comando, "tiempo_balanceado")) {
      const nat MAX = 4000000;
      const nat MIN = 1000000;
      cadena_t cad = crear_cadena();
      for (nat i = MIN; i < MAX; i++) {
        insertar_al_final(crear_info(i, int_a_texto(i)), cad);
      }
      printf("Crear balanceado. \n");
      binario_t bal = crear_balanceado(cad);
      printf(" Liberar binario. \n");
      liberar_binario(bal);
      liberar_cadena(cad);

    } else if (!strcmp(nom_comando, "tiempo_cnj")) {
      cadena_t cad = crear_cadena();
      for (int i = 1000000; i <= 1500000; i++) {
        insertar_al_final(crear_info(i, int_a_texto(i)), cad);
      }
      for (int i = 2000000; i <= 2500000; i++) {
        insertar_al_final(crear_info(i, int_a_texto(i)), cad);
      }
      conjunto_t c1 = construir_conjunto(cad);
      liberar_cadena(cad);

      cad = crear_cadena();
      for (int i = 1300000; i <= 2200000; i++) {
        insertar_al_final(crear_info(i, int_a_texto(i)), cad);
      }
      conjunto_t c2 = construir_conjunto(cad);
      liberar_cadena(cad);

      printf("\n Diferencia.\n");
      conjunto_t d = diferencia(c1, c2);

      char t1[] = "1000000";
      char t2[] = "1500000";
      assert(pertenece_conjunto(t1, d) && !pertenece_conjunto(t2, d));

      printf(" Pertenece.\n");
      for (int i = 0; i < 10000; i++) {
        pertenece_conjunto(t1, d);
        pertenece_conjunto(t2, d);
      }

      liberar_conjunto(c1);
      liberar_conjunto(c2);
      liberar_conjunto(d);

    } else if (!strcmp(nom_comando, "tiempo_kesimo")) {
      const nat MAX = 20000;
      const nat MIN = 10000;
      printf("Construir árbol. \n");
      binario_t a = crear_binario();
      for (nat i = MAX; i > MIN; i--)
        insertar_en_binario(crear_info(i, int_a_texto(i)), a);
      printf("Obtener kesimo. \n");
      for (int i = 0; i < 2000; i++)
        for (int k = 1; k < 5; k++)
          kesimo_en_binario(k, a);
      printf(" Liberar binario. \n");
      liberar_binario(a);

    } else if (!strcmp(nom_comando, "tiempo_balanceadoAvl")) {
      const nat MAX = 60000;
      const nat MIN = 10000;
      printf("Construir árbol. \n");
      cadena_t cad = crear_cadena();
      for (nat i = MIN; i < MAX; i++) {
        insertar_al_final(crear_info(i, int_a_texto(i)), cad);
      }
      binario_t a = crear_balanceado(cad);
      printf("¿Es AVL?. \n");
      for (int i = 0; i < 3000; i++)
        es_AVL(a);
      printf(" Liberar binario. \n");
      liberar_binario(a);
      liberar_cadena(cad);

    } else if (!strcmp(nom_comando, "tiempo_tabla")) {
      const nat MAX = 1000000;
      const nat MODULO = 50000000;
      srand(1);
      tabla_t t = crear_tabla(MAX);
      for (nat j = 0; j < MAX; j++) {
        nat rnd = rand() % MODULO;
        asociar_en_tabla(rnd, int_a_texto(rnd), t);
      }
      for (nat j = 0; j < MAX; j++) {
        nat rnd = rand() % MODULO;
        if (existe_asociacion(rnd, t))
          valor_en_tabla(rnd, t);
      }
      liberar_tabla(t);

    } else if (!strcmp(nom_comando, "tiempo_cp")) {
      const nat TAMANIO = 1000000;
      const nat max_prioridades = 1000000;
      printf("\n prueba 1. \n");
      cola_prioridad_t cp = crear_cp(TAMANIO, max_prioridades);
      for (nat i = TAMANIO; i >= 1; i--) {
        info_t info = crear_info(i, int_a_texto(i));
        insertar_en_cp(info, i, cp);
      }
      for (nat i = 1; i <= TAMANIO; i++)
        eliminar_prioritario(cp);

      liberar_cp(cp);

      printf(" prueba 2. \n");
      cp = crear_cp(TAMANIO, max_prioridades);
      for (nat i = 1; i <= TAMANIO; i++) {
        info_t info = crear_info(i, int_a_texto(i));
        insertar_en_cp(info, i, cp);
      }
      for (nat i = 1; i <= TAMANIO; i++)
        eliminar_prioritario(cp);

      liberar_cp(cp);

      printf(" prueba 3. \n");
      cp = crear_cp(TAMANIO, max_prioridades);
      info_t info = crear_info(max_prioridades, int_a_texto(max_prioridades));
      insertar_en_cp(info, numero_info(info), cp);
      for (nat i = 1; i <= TAMANIO; i++) {
        info = crear_info(1, int_a_texto(1));
        insertar_en_cp(info, numero_info(info), cp);
        eliminar_prioritario(cp);
      }
      liberar_cp(cp);

    } else if (!strcmp(nom_comando, "tiempo_mayores")) {

      const nat TAMANIO = 1000000;
      const nat MAX = 100000;
      const nat k = 100000;
      srand(1);
      cadena_t cadena = crear_cadena();
      for (nat i = 1; i <= TAMANIO; i++) {
        char *txt = new char[1];
        txt[0] = '\0';
        info_t info = crear_info(rand() % MAX, txt);
        insertar_al_final(info, cadena);
      }
      cadena_t res = mayores(cadena, k, MAX);
      liberar_cadena(cadena);
      liberar_cadena(res);

      for (int i = 1; i < 1000; i++) {
        cadena = crear_cadena();
        char *txt = new char[1];
        txt[0] = '\0';
        insertar_al_final(crear_info(1, txt), cadena);
        txt = new char[1];
        txt[0] = '\0';
        insertar_al_final(crear_info(TAMANIO, txt), cadena);
        txt = new char[1];
        txt[0] = '\0';
        insertar_al_final(crear_info(TAMANIO / 2, txt), cadena);
        res = mayores(cad, k, MAX);
        liberar_cadena(cadena);
        liberar_cadena(res);
      }

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  liberar_cadena(cad);
  liberar_binario(b);
  liberar_pila(p);
  destruir_cola_binarios(cb);
  liberar_iterador(it);
  liberar_conjunto(cnj);
  liberar_cp(cp);
  liberar_tabla(t);
  return 0;
}
