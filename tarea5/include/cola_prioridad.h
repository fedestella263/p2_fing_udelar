/*
  Módulo de definición de `cola_de_prioridad_t`.

  Se definen las colas de prioridad acotadas en las que los elementos son de
  tipo  `info_t'.
  Debe implementarse con un heap.

  La cantidad máxima de elementos que puede contener una cola es `tamanio',
  que es un parámetro pasado al crear la cola.

  El orden de prioridad de los elementos está determinado por un valor `p'
  de tipo `prio_t' que es pasado al insertar los elementos y luego tal vaz
  modificado.
  Los valores de `prio_t' son naturales en el rango 0 .. `max_prioridad',
  donde `max_prioridades' es un parámetro de `crear_cp'.

  Se considera que el elemento prioritario es aquel que fue insertado con un
  menor valor de `p'.
  No puede haber dos elementos insertados con el mismo valor de `p'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_PRIORIDAD_H
#define _COLA_PRIORIDAD_H

#include "info.h"

// tipo para el valor que determina el orden de prioridad
typedef unsigned int prio_t;

struct rep_cola_prioridad; // representación de `cola_de_prioridad', definida en
                           // `cola_de_prioridad.cpp'.

typedef rep_cola_prioridad *cola_prioridad_t;

/*
  Devuelve una `cola_de_prioridad' que puede contener hasta `tamanio' elementos.
  Los valores que determinan la prioridad pueden estar en el rango
  0 .. max_prioridad.
 */
cola_prioridad_t crear_cp(unsigned int tamanio, prio_t max_prioridad);

/*
  Si inserta el elemento `i', cuya orden de prioridad queda determinado por `p'.
  Precondición ! es_llena_cp(cp) y ! hay_prioridad(p,cp) y p <=
  max_prioridad(cp).
  El tiempo de ejecución es O(log tamanio).
 */
void insertar_en_cp(info_t i, prio_t p, cola_prioridad_t &cp);

/*
  Reduce a p/2 el valor de prioridad del elemento asociado al valor `p'.
  Precondición: hay_prioridad(p, cp) y ! hay_prioridad(p/2, cp).
  El tiempo de ejecución es O(log tamanio).
 */
void priorizar(prio_t p, cola_prioridad_t &cp);

/*
  Aumenta a (p+max_prioridad)/2 el valor de prioridad del elemento asociado
  al valor `p'.
  Precondición: hay_prioridad(p, cp) y ! hay_prioridad((p+max_prioridad(cp))/2,
  cp).
  El tiempo de ejecución es O(log tamanio).
 */
void despriorizar(prio_t p, cola_prioridad_t &cp);

/*
  Elimina el elemento prioritario de `cp' y libera la memoria que tiene
  asignada.
  Precondición: ! es_vacia_cp(cp).
  El tiempo de ejecución es O(log tamanio).
 */
void eliminar_prioritario(cola_prioridad_t &cp);

/*  Libera la menoria asignada a `cp' y a sus elementos. */
void liberar_cp(cola_prioridad_t &cp);

/*
  Devuelve `true' si y sólo si en `cp' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacia_cp(cola_prioridad_t cp);

/*
  Devuelve `true' si y sólo si en `cp' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_llena_cp(cola_prioridad_t cp);

/*
  Devuelve `true' si y sólo si un elemento de `cp' está asociado al valor `p'.
  El tiempo de ejecución es O(1).
 */
bool hay_prioridad(prio_t p, cola_prioridad_t cp);

/*
  Devuelve el elemento prioritario de `cp'.
  Precondición: ! es_vacia_cp(cp).
  El tiempo de ejecución es O(1).
 */
info_t prioritario(cola_prioridad_t cp);

/*
  Devuelve el valor asociado al elemento prioritario.
  Precondición: ! es_vacia_cp(cp),
  El tiempo de ejecución es O(1).
 */
prio_t prioridad_prioritario(cola_prioridad_t cp);

/*
  Devuelve el máximo valor del rango para el parámetro `p', establecido en 
  crear_cp.
 */
prio_t max_prioridad(cola_prioridad_t cp);

#endif
