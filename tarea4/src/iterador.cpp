#include "../include/iterador.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>

struct nodo_iterador {
    char* frase;
    nodo_iterador* siguiente;
};

struct rep_iterador {
    nodo_iterador* pos;
    nodo_iterador* inicio;
};

typedef struct rep_iterador *iterador_t;

iterador_t crear_iterador() {
    iterador_t iterador = new rep_iterador;
    iterador->pos = NULL;     // Posicion indefinida.
    iterador->inicio = NULL;
    
    return iterador;
}

void agregar_a_iterador(char *t, iterador_t &i) {
    nodo_iterador* loc = i->inicio;
    nodo_iterador* nodo = new nodo_iterador;
    
    nodo->frase = t;
    nodo->siguiente = NULL;
    
    if(i->inicio == NULL)
        i->inicio = nodo;
    else {
        while(loc->siguiente != NULL)
            loc = loc->siguiente;
        
        loc->siguiente = nodo;
    }
}

void reiniciar_iter(iterador_t &i) {
    i->pos = i->inicio;
}

void avanzar_iter(iterador_t &i) {
    if(esta_definida_actual(i))
        i->pos = i->pos->siguiente;
}

char *actual_iter(iterador_t &i) {
    assert(esta_definida_actual(i));
    return i->pos->frase;
}

bool hay_siguiente_en_iter(iterador_t i) {
    assert(esta_definida_actual(i));
    return i->pos->siguiente != NULL;
}

bool esta_definida_actual(iterador_t i) {
    return i->pos != NULL;
}

cadena_t iterador_a_cadena(iterador_t i) {
    cadena_t cad = crear_cadena();
    nodo_iterador* loc = i->inicio;
    
    while(loc != NULL) {
        char* copia_string = new char[strlen(loc->frase) + 1];
        strcpy(copia_string, loc->frase);
        insertar_al_final(crear_info(0, copia_string), cad);
        loc = loc->siguiente;
    }
    
    return cad;
}

void liberar_iterador(iterador_t &i) {
    nodo_iterador* loc = i->inicio;
    nodo_iterador* tmp;
    
    while(loc != NULL) {
        delete[] loc->frase;
        tmp = loc;
        loc = loc->siguiente;
        delete tmp;
    }
    
    delete i;
}   