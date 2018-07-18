/*
  Módulo de definición de `pila_t'.

  `pila_t' es una estructura lineal acotada con comportamiento LIFO cuyos
   elementos son strings.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

// Declaración del tipo `pila_t'
// struct rep_pila es la representación de `pila_t', definida en pila.cpp
typedef struct rep_pila *pila_t;

/* Constructoras */

/*
  Devuelve una pila_t vacía (sin elementos) que puede tener hasta `tamanio'
  elementos.
 */
pila_t crear_pila(int tamanio);

/*
  Apila`t' en `p'.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(char *t, pila_t &p);

/* Destructoras */

/*
  Remueve de `p' el elemento que está en la cima.
  Libera la memoria del elemento removido.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila_t &p);

/* Libera la memoria asignada a `p' y la de todos sus elementos. */
void liberar_pila(pila_t &p);

/* Predicados */

/* Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). */
bool es_vacia_pila(pila_t p);

/*
  Devuelve `true' si y sólo si la cantidad de elementos en `p' es `tamanio'
  (siendo `tamanio' el valor del parámetro con que fue creada `p').
 */
bool es_llena_pila(pila_t p);

/* Selectoras */

/*
  Devuelve el elemento que está en la cima de `p'.
  Precondición: ! es_vacia_pila(p);
 */
char *cima(pila_t p);

#endif
