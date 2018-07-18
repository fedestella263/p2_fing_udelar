#include "../include/cola_binarios.h"
#include <stddef.h>
#include <assert.h>

struct nodo_cola {
    binario_t dato;
    nodo_cola *anterior;
    nodo_cola *siguiente;
};

struct rep_cola_binarios {
    nodo_cola *inicio;
    nodo_cola *final;
};

typedef rep_cola_binarios *cola_binarios_t;

cola_binarios_t crear_cola_binarios() {
    cola_binarios_t cola = new rep_cola_binarios;
    cola->inicio = cola->final = NULL;
    return cola;
}

void encolar(binario_t b, cola_binarios_t &c) {
    nodo_cola *nuevo = new nodo_cola;
    
    nuevo->dato = b;
    nuevo->siguiente = NULL;
    nuevo->anterior = c->final;
    
    if(c->final == NULL) {
        assert(c->inicio == NULL);
        c->inicio = nuevo;
    } else {
        assert(c->inicio != NULL);
        c->final->siguiente = nuevo;
    }
    
    c->final = nuevo;
}

void desencolar(cola_binarios_t &c) {
    if(es_vacia_cola_binarios(c))
        return;
        
    nodo_cola *elem = c->inicio;
    
    // Si hay un solo elemento, final apunta al siguiente.
    if(c->inicio == c->final)
        c->final = elem->siguiente;
    
    c->inicio = elem->siguiente;
    
    // Si hay un segundo elemento anterior apunta a NULL.
    if(elem->siguiente != NULL)
        elem->siguiente->anterior = NULL;
    
    delete elem;
}

void liberar_cola_binarios(cola_binarios_t &c) {
    nodo_cola *loc = c->inicio;
    nodo_cola *borrar;
    
    while(loc != NULL) {
        borrar = loc;
        loc = loc->siguiente;
        delete borrar;
    }
    
    c->inicio = c->final;
    delete c;
}

bool es_vacia_cola_binarios(cola_binarios_t c) {
    return c->inicio == NULL;
}

binario_t frente(cola_binarios_t c) {
    assert(!es_vacia_cola_binarios(c));
    return c->inicio->dato;
}