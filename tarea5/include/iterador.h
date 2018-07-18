/*
  Módulo de definición de `iterador_t'.

  Estructura para recorrer una colección de strings.
  Tiene implcícita una posición actual.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _ITERADOR_H
#define _ITERADOR_H

#include "cadena.h"

// maxima longitud de los strings
#define MAX_ITER 256

// Declaración del tipo `iterador_t'
// struct rep_iterador es la representación de `iterador_t',
// definida en iterador.cpp
typedef struct rep_iterador *iterador_t;

/*
  Crea un iterador_t vacío (sin elementos) cuya posición actual no está
  definida.
  El tiempo de ejecución es O(1).
 */
iterador_t crear_iterador();

/*
  Agrega `t' al final de `i'. No se modifica la posición actual.
  El tiempo de ejecución es O(1).
 */
void agregar_a_iterador(char *t, iterador_t &i);

/*
  Mueve la posición actual al primero.
  Si en `i' no hay elementos no hace nada.
  El tiempo de ejecución es O(1).
 */
void reiniciar_iter(iterador_t &i);

/*
  Avanza la posición actual hacia el siguiente.
  Si ! hay_siguiente_en_iter(i) la posición actual queda indefinida;
  Si la posición actual no está definida no hace nada.
  El tiempo de ejecución es O(1).
 */
void avanzar_iter(iterador_t &i);

/*
  Devuelve el elemento de la posición actual.
  Precondición: esta_definida_actual(i).
  El tiempo de ejecución es O(1).
 */
char *actual_iter(iterador_t &i);

/*
  Devuelve `true' si y sólo si en `i' hay un elemento siguiente al de la
  posición actual.
  Precondición: esta_definida_actual(i).
  El tiempo de ejecución es O(1).
 */
bool hay_siguiente_en_iter(iterador_t i);

/*
  Devuelve `true' si y sólo si la posición actual de `i' está definida.
  El tiempo de ejecución es O(1).
 */
bool esta_definida_actual(iterador_t i);

/*
  Devuelve una cadena con todos los elementos que se pueden recorrer con `i'.
  El dato numérico de los elementos debe ser 0.
  Al terminar, la posicion actual debe permanecer donde estaba al empezar la
  operación.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `i'.
  La cadena resultado no debe compartir memoria con `i'.
 */
cadena_t iterador_a_cadena(iterador_t i);

/*
  Libera la memoria asignada a `i' y la de sus elementos).
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `i'.
 */
void liberar_iterador(iterador_t &i);

#endif
