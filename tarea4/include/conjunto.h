/*
  Módulo de definición de `conjunto_t'.

  Se define un conjunto de elementos de tipo `info_t'.
  No puede haber dos elementos con la misma frase.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CONJUNTO_H
#define _CONJUNTO_H

#include "info.h"
#include "cadena.h"
#include "iterador.h"

// Declaración del tipo `conjunto_t'
// struct rep_conjunto es la representación de `conjunto_t',
// definida en conjunto.cpp
typedef struct rep_conjunto *conjunto_t;

/* Constructoras */

/*  Devuelve un conjunto_t vacío (sin elementos). */
conjunto_t crear_conjunto();

/*
  Devuelve un conjunto_t con los mismos elementos que están en `cad'.
  El conjunto_t devuelto no comparte memoria con `cad'.
  Precondición: los elementos de `cad' están en orden lexicográfico creciente
  estricto (esto es, creciente y no hay dos iguales) según sus frases.
  El tiempo de ejecución en peor caso es O(n.log n), donde `n' es la cantidad
  de elementos de `cad'.
  Mientras en el conjunto_t devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece_conjunto' deben ejecutarse en tiempo O(log n)
  en peor  caso.
 */
conjunto_t construir_conjunto(cadena_t cad);

/*
  Incluye `i' en `c'.
  Si en `c' ya había un elemento con frase igual a la de `i' no hace nada.
  Devuelve `true' si y sólo si se incluyó `i'.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `c'.
 */
bool incluir(info_t i, conjunto_t &c);

/*
  Devuelve un conjunto_t con los elementos cuyas frases pertenecen a `c1'
  o `c2'. Si en ambos conjuntos hay un elemento con la misma frase en el
  conjunto_t devuelto se debe incluir el que pertenece a `c1'.
  El tiempo de ejecucion en peor caso es O(n1 + n2 + n.log n), siendo `n1' y
  `n2' la cantidad de elementos de `c1' y `c2' respectivamente y `n' la del
  conjunto_t resultado.
  Mientras en el conjunto_t devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece_conjunto' deben ejecutarse en tiempo O(log n)
  en peor caso.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t union_conjunto(conjunto_t s1, conjunto_t s2);

/*
  Devuelve un conjunto_t con los elementos cuyas frases pertenecen a `c1'
  y `c2'. El  dato numérico en el conjunto_t devuelto debe ser el del elemento
  de `c1'-
  El tiempo de ejecucion en peor caso es O(n1 + n2 + n.log n), siendo `n1' y
  `n2' la cantidad de elementos de `c1' y `c2' respectivamente y `n' la del
  conjunto_t resultado.
  Mientras en el conjunto_t devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece_conjunto' deben ejecutarse en tiempo O(log n)
  en peor caso.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t interseccion(conjunto_t c1, conjunto_t c2);

/*
  Devuelve un conjunto_t con los elementos de `c1' cuyos datos de texto no
  pertenecen a `c2'.
  El tiempo de ejecucion en peor caso es O(n1 + n2 + n.log n), siendo `n1' y
  `n2' la cantidad de elementos de `c1' y `c2' respectivamente y `n' la del
  conjunto_t resultado.
  Mientras en el conjunto_t devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece_conjunto` deben ejecutarse en tiempo O(log n)
  en peor caso.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t diferencia(conjunto_t c1, conjunto_t c2);

/* Destructoras */

/*
  Excluye de `c' el elemento cuyo dato de texto es `t' y libera la memoria
  asignada a ese elemento.
  Si en `c' no había tal elemento no hace nada.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `c'.
 */
void excluir(char *t, conjunto_t &c);

/* Libera la memoria asignada a `c' y la de todos sus elementos. */
void liberar_conjunto(conjunto_t &c);

/* Predicados */

/*
  Devuelve `true' si y sólo si el dato de texto de algún elemento de `c' es
  igual a `t'.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `c'.
 */
bool pertenece_conjunto(char *t, conjunto_t c);

/*
  Devuelve `true' si y sólo `c' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_conjunto(conjunto_t c);

/* Selectoras */

/*
  Devuelve un iterador a las frases de los elementos de `c'.
  En la recorrida del iterador devuelto los textos aparecerán en orden
  lexicográfico creciente.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `c'.
  El iterador resultado NO comparte memoria con `c'.
 */
iterador_t iterador_conjunto(conjunto_t c);

#endif
