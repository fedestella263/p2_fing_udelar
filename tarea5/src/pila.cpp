#include "../include/pila.h"
#include <assert.h>

struct rep_pila {
    char** array;
    int tope;
    int cota;
};
typedef rep_pila *pila_t;

pila_t crear_pila(int tamanio) {
    pila_t pila = new rep_pila;
    pila->array = new char*[tamanio];
    pila->tope = -1;
    pila->cota = tamanio;

    return pila;
}

void apilar(char *t, pila_t &p) {
    if(es_llena_pila(p))
        return;

    p->tope++;
    p->array[p->tope] = t;
}

void desapilar(pila_t &p) {
    if(es_vacia_pila(p))
        return;

    delete[] p->array[p->tope];
    p->tope--;
}

void liberar_pila(pila_t &p) {
    for(int x = 0; x <= p->tope; x++)
        delete[] p->array[x];

    delete[] p->array;
    delete p;
}

bool es_vacia_pila(pila_t p) {
    return p->tope == -1;
}

bool es_llena_pila(pila_t p) {
    return p->tope == p->cota-1;
}

char *cima(pila_t p) {
    assert(!es_vacia_pila(p));
    return p->array[p->tope];
}
