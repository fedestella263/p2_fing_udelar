/*
  Módulo de definición de `cola_binarios_t'.

  `cola_binarios_t' es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `binario'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_BINARIO_H
#define _COLA_BINARIO_H

#include "binario.h"

// Declaración del tipo `cola_binarios_t'
// struct rep_cola_binarios es la representación de `cola_binarios_t',
// definida en cola_binarios.cpp
typedef struct rep_cola_binarios *cola_binarios_t;

/* Constructoras */

/*  Devuelve una cola_binarios_t vacía (sin elementos). */
cola_binarios_t crear_cola_binarios();

/* Encola `b' en `c'. */
void encolar(binario_t b, cola_binarios_t &c);

/* Destructoras */

/*
  Remueve de `c' el elemento que está en el frente.
  No libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_binarios_t &c);

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_binarios(cola_binarios_t &c);

/* Predicados */

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_binarios(cola_binarios_t c);

/* Selectoras */

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_binarios(c);
 */
binario_t frente(cola_binarios_t c);

#endif
