/*
  Módulo de definición de `tabla_t'.

  Se define una tabla acotada de asociaciones de número a texto.
  La cantidad máxima de asociaciones queda determinada por el parámetro
  `tamanio' pasado en `crear_tabla'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/cadena.h"

struct rep_tabla; // representación de `tabla_t', definida en `tabla.cpp'.

typedef rep_tabla *tabla_t;

/*
 Crea una tabla_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
tabla_t crear_tabla(nat tamanio);

/*
  Inserta en `t' la asociación entre `clave' y `valor'.
  Si ya existía una asociación para `clave' es reemplazada por la
  nueva.
  Precondición: ! esta_llena_tabla(t).
  El tiempo de ejecución es O(1) en promedio.
 */
void asociar_en_tabla(int clave, char *valor, tabla_t &t);

/*
  Elimina de `t' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, t).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_tabla(int clave, tabla_t &t);

/*
  Libera la memoria asignada a `t' y todos sus elementos.
 */
void liberar_tabla(tabla_t &t);

/*
  Devuelve `true' si y sólo si en `t' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, tabla_t t);

/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `t'.
  Precondición: existe_asociacion(clave, t).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_tabla(int clave, tabla_t t);

/*
  Devuelve `true' si y sólo si `t' tiene `tamanio' elementos.
 */
bool esta_llena_tabla(tabla_t t);
