#include "../include/cola_prioridad.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef unsigned int prio_t;

struct rep_nodo {
    info_t info;
    prio_t prioridad;
};

typedef rep_nodo *nodo_t;

struct rep_cola_prioridad {
    nodo_t *datos;
    int* prioridades;
    unsigned int tamanio;
    unsigned int cantidad_elementos;
    prio_t max_prioridad;
};

typedef rep_cola_prioridad *cola_prioridad_t;

cola_prioridad_t crear_cp(unsigned int tamanio, prio_t max_prioridad) {
    cola_prioridad_t cp = new rep_cola_prioridad;
    cp->datos = new nodo_t[tamanio+1];
    cp->prioridades = new int[max_prioridad+1];

    for(prio_t x = 0; x <= max_prioridad; x++)
        cp->prioridades[x] = -1; // Valor nulo, quiere decir que la prioridad no existe.

    cp->tamanio = tamanio;
    cp->max_prioridad = max_prioridad;
    cp->cantidad_elementos = 0;

    return cp;
}

void insertar_en_cp(info_t i, prio_t p, cola_prioridad_t &cp) {
    assert(!es_llena_cp(cp) && !hay_prioridad(p, cp) && p <= max_prioridad(cp));

    nodo_t tmp;

    unsigned int indice = cp->cantidad_elementos+1;

    cp->datos[indice] = new rep_nodo;
    cp->datos[indice]->info = i;
    cp->datos[indice]->prioridad = p;

    cp->prioridades[p] = indice;

    // Compara e intercambia por las raices que sean mayores que el nuevo valor agregado.
    while(indice > 1 && cp->datos[indice]->prioridad < cp->datos[indice/2]->prioridad) {

        // Intercambiar los indices en el mapa de prioridades.
        cp->prioridades[cp->datos[indice]->prioridad] = indice/2;
        cp->prioridades[cp->datos[indice/2]->prioridad] = indice;

        // Intercambiar los elementos en el array.
        tmp = cp->datos[indice];
        cp->datos[indice] = cp->datos[indice/2];
        cp->datos[indice/2] = tmp;

        indice = indice/2;
    }

    cp->cantidad_elementos++;
}

void priorizar(prio_t p, cola_prioridad_t &cp) {
    assert(hay_prioridad(p, cp) && !hay_prioridad(p/2, cp));

    int indice = cp->prioridades[p];
    nodo_t tmp;

    cp->datos[indice]->prioridad = p/2;
    cp->prioridades[p] = -1;
    cp->prioridades[p/2] = indice;

    // Intercambia posicion con el padre si dicho padre es menor.
    while(indice > 1 && cp->datos[indice]->prioridad < cp->datos[indice/2]->prioridad) {

        // Intercambiar los indices en el mapa de prioridades.
        cp->prioridades[cp->datos[indice]->prioridad] = indice/2;
        cp->prioridades[cp->datos[indice/2]->prioridad] = indice;

        tmp = cp->datos[indice];
        cp->datos[indice] = cp->datos[indice/2];
        cp->datos[indice/2] = tmp;

        indice = indice/2;
    }
}

void despriorizar(prio_t p, cola_prioridad_t &cp) {
    assert(hay_prioridad(p, cp) && !hay_prioridad((p+max_prioridad(cp))/2, cp));

    prio_t indice = cp->prioridades[p];
    nodo_t tmp;

    cp->datos[indice]->prioridad = (p+max_prioridad(cp))/2;
    cp->prioridades[p] = -1;
    cp->prioridades[(p+max_prioridad(cp))/2] = indice;
    
    //for(unsigned int x = 1; x <= cp->cantidad_elementos; x++)
        //printf("(%d)", cp->datos[x]->prioridad);
    //printf("\n");

    // Intercambia posicion con algun hijo si dicho hijo es menor.
    while((indice*2) <= cp->cantidad_elementos && (cp->datos[indice]->prioridad > cp->datos[indice*2]->prioridad || (
        (indice*2)+1 < cp->cantidad_elementos && cp->datos[indice]->prioridad > cp->datos[(indice*2)+1]->prioridad
        ))) {

        tmp = cp->datos[indice];
        
        // No hay nodo derecho o nodo derecho es mas grande.
        if((indice*2)+1 >= cp->cantidad_elementos || cp->datos[indice*2]->prioridad < cp->datos[(indice*2)+1]->prioridad) {

            // Intercambiar los indices en el mapa de prioridades.
            cp->prioridades[cp->datos[indice]->prioridad] = indice*2;
            cp->prioridades[cp->datos[indice*2]->prioridad] = indice;

            cp->datos[indice] = cp->datos[indice*2];
            cp->datos[indice*2] = tmp;

            indice = indice*2;
        
        } else {

            cp->prioridades[cp->datos[indice]->prioridad] = (indice*2)+1;
            cp->prioridades[cp->datos[(indice*2)+1]->prioridad] = indice;

            cp->datos[indice] = cp->datos[(indice*2)+1];
            cp->datos[(indice*2)+1] = tmp;

            indice = (indice*2)+1;
        }
    }    
}

void eliminar_prioritario(cola_prioridad_t &cp) {
    assert(!es_vacia_cp(cp));

    nodo_t tmp;
    prio_t indice = 1;
    
    if(cp->cantidad_elementos > 1) {
        
        // Intercambiar el prioritario por el ultimo elemento.
        cp->prioridades[cp->datos[indice]->prioridad] = cp->cantidad_elementos;
        cp->prioridades[cp->datos[cp->cantidad_elementos]->prioridad] = indice;
        
        tmp = cp->datos[indice];
        cp->datos[indice] = cp->datos[cp->cantidad_elementos];
        cp->datos[cp->cantidad_elementos] = tmp;
        
        // Ordenar posicion con el hijo menor, hasta llegar al ultimo elemento de esa rama.
        while((indice*2) < cp->cantidad_elementos && (cp->datos[indice]->prioridad > cp->datos[indice*2]->prioridad || (
            (indice*2)+1 < cp->cantidad_elementos && cp->datos[indice]->prioridad > cp->datos[(indice*2)+1]->prioridad
            ))) {
    
            tmp = cp->datos[indice];
            
            // No hay nodo derecho o nodo derecho es mas grande.
            if((indice*2)+1 >= cp->cantidad_elementos || cp->datos[indice*2]->prioridad < cp->datos[(indice*2)+1]->prioridad) {
    
                // Intercambiar los indices en el mapa de prioridades.
                cp->prioridades[cp->datos[indice]->prioridad] = indice*2;
                cp->prioridades[cp->datos[indice*2]->prioridad] = indice;
    
                cp->datos[indice] = cp->datos[indice*2];
                cp->datos[indice*2] = tmp;
    
                indice = indice*2;
            
            } else {
    
                cp->prioridades[cp->datos[indice]->prioridad] = (indice*2)+1;
                cp->prioridades[cp->datos[(indice*2)+1]->prioridad] = indice;
    
                cp->datos[indice] = cp->datos[(indice*2)+1];
                cp->datos[(indice*2)+1] = tmp;
    
                indice = (indice*2)+1;
            }
        }    
    }
    
    // Eliminar el ultimo elemento.
    cp->prioridades[cp->datos[cp->cantidad_elementos]->prioridad] = -1;
    liberar_info(cp->datos[cp->cantidad_elementos]->info);
    delete cp->datos[cp->cantidad_elementos];
    cp->datos[cp->cantidad_elementos] = NULL;
    cp->cantidad_elementos--;
}

void liberar_cp(cola_prioridad_t &cp) {
    for(prio_t x = 1; x <= cp->cantidad_elementos; x++) {
        liberar_info(cp->datos[x]->info);
        delete cp->datos[x];
    }

    delete[] cp->datos;
    delete[] cp->prioridades;
    delete cp;
}

bool es_vacia_cp(cola_prioridad_t cp) {
    return cp->cantidad_elementos == 0;
}

bool es_llena_cp(cola_prioridad_t cp) {
    return cp->cantidad_elementos == cp->tamanio;
}

bool hay_prioridad(prio_t p, cola_prioridad_t cp) {
    return p <= cp->max_prioridad && cp->prioridades[p] != -1;
}

info_t prioritario(cola_prioridad_t cp) {
    assert(!es_vacia_cp(cp));
    return cp->datos[1]->info;
}

prio_t prioridad_prioritario(cola_prioridad_t cp) {
    assert(!es_vacia_cp(cp));
    return cp->datos[1]->prioridad;
}

prio_t max_prioridad(cola_prioridad_t cp) {
    return cp->max_prioridad;
}

