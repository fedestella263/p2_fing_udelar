/*
  Módulo de definición de `uso_tads'.

  Se definen funciones sobre tads.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_TADS_H
#define _USO_TADS_H

#include "info.h"
#include "cadena.h"
#include "binario.h"
#include "iterador.h"
#include "conjunto.h"

/* **************  NUEVO  ************** */
/*
  Devuelve una cadena_t ordenada de manera creciente según los valores numéricos
  de sus elementos con los hasta `k' elementos de `cad' cuyos valores numéricos
  sean mayores entre los que están en el rango 0 .. `max'.
  Si en `cad' hay más de un elemento con el mismo valor numérico el único de
  ellos que se debe incluir en la cadena_t resultado es el que aparece primero
  en `cad'.
  La cadena_t resultado no comparte memoria con `cad'.
  El tiempo de ejecución es O(n.log k), donde `n' es la cantidad de elementos de
  `cad'.
  Precondición: k > 0.
 */
cadena_t mayores(cadena_t cad, unsigned int k, unsigned int max);

/*
  Devuelve un iterador_t con elementos de `it' en orden inverso de como están
  en `it'.
  Si `a' es mayor que la cantidad de elementos de `it' devuelve un iterador_t
  vacio. En otro caso devuelve los que están entre las posiciones `a' y `b' o,
  si `b' es mayor que la cantidad de elementos, entre `a' y el último elemento
  de `it'.
  Se considera que el primer elemento está en la posición 1.
  El iterador_t devuelto no debe compartir memoria con `it'.
  Al terminar `it' y el iterador_t devuelte deben quedar reiniciados.
  Precondición: 1 <= a <= b.

  No se pueden usar operaciones de un TAD que no sea iterador.

 */
iterador_t inverso_de_iter(nat a, nat b, iterador_t &it);

/*
  Devuelve un iterador_t con los elementos de `c' que están entre `primero' y
  `ultimo', ambos incluidos.
  El iterador_t resultado debe estar en orden lexicográfico decreciente.
  El iterador_t devuelto no debe compartir memoria con `c'.
  Precondición: `primero' precede o es igual a `ultimo' en orden lexicográfico.
 */
iterador_t rango_en_conjunto(char *primero, char *ultimo, conjunto_t c);

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma creciente
  (creciente de manera estricta) según las frases de sus elementos.
  Si es_vacia_cadena (cad) devuelve `true'.
 */
bool esta_ordenada_por_frase(cadena_t cad);

/*
  Imprime las frases de los nodos de `b' en orden decreciente de
  niveles (desde las hojas hasta la raíz), un nivel por línea.
  En cada nivel los textos se imprimen en orden lexicográfico creciente.
  Después de cada texto se imprime un espacio en blanco.
  Si `b' es vacío no imprime nada.
 */
void imprimir_por_niveles(binario_t b);

/*
  Devuelve `true' si y sólo si en `cad' hay un elemento cuyo dato numérico es
  `i'.
 */
bool pertenece(int i, cadena_t cad);

/*  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena_t cad);

/*
  Devuelve `true' si y sólo si `c1' y `c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si es_vacia_cadenat(c1) y es_vacia_cadena(c2) devuelve `true'.
 */
bool son_iguales(cadena_t c1, cadena_t c2);

/*
  Devuelve el resultado de concatenar `c2' después de `c1'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
 */
cadena_t concatenar(cadena_t c1, cadena_t c2);

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */
void ordenar(cadena_t &cad);

/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
 */
void cambiar_todos(int original, int nuevo, cadena_t &cad);

/*
  Devuelve la cadena_t de elementos de `cad' que cumplen
  "menor <= numero_info (elemento) <= mayor".
  El orden relativo de los elementos en la cadena_t resultado debe ser el mismo
  que en `cad'.
  La cadena_t resultado no comparte memoria con `cad'.
  Precondición: esta_ordenada (cad), `menor' <= `mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
 */
cadena_t subcadena(int menor, int mayor, cadena_t cad);

#endif
