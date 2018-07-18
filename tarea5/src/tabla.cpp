#include "../include/tabla.h"
#include <assert.h>
#include <string.h>

struct rep_tabla {
    cadena_t *lista;
    nat tamanio;
    nat cantidad_elementos;
};

typedef rep_tabla *tabla_t;

tabla_t crear_tabla(nat tamanio) {
    tabla_t tabla = new rep_tabla;
    tabla->lista = new cadena_t[tamanio];
    
    for(nat x = 0; x < tamanio; x++)
        tabla->lista[x] = NULL;
    
    tabla->tamanio = tamanio;
    tabla->cantidad_elementos = 0;
    
    return tabla;
}

void asociar_en_tabla(int clave, char *valor, tabla_t &t) {
    assert(!esta_llena_tabla(t));
    
    int indice = clave % t->tamanio;
    cadena_t cad = t->lista[indice];
    localizador_t loc = NULL;
    
    // Ya existe una cadena.
    if(t->lista[indice] != NULL) {
        loc = inicio_cadena(cad);
        
        while(es_localizador(loc) && numero_info(info_cadena(loc, cad)) != clave)
            loc = siguiente(loc, cad);
        
    } else
        cad = t->lista[indice] = crear_cadena();
    
    // Ya existe la clave, la elimina para insertar la nueva.
    if(es_localizador(loc))
        remover_de_cadena(loc, cad);
    else
        t->cantidad_elementos++;
    
    insertar_al_final(crear_info(clave, valor), cad);
}

void eliminar_de_tabla(int clave, tabla_t &t) {
    assert(existe_asociacion(clave, t));
    
    int indice = clave % t->tamanio;
    cadena_t cad = t->lista[indice];
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc) && numero_info(info_cadena(loc, cad)) != clave)
        loc = siguiente(loc, cad);
    
    remover_de_cadena(loc, cad);
    
    if(es_vacia_cadena(cad)) {
        liberar_cadena(cad);
        t->lista[indice] = NULL;
    }
    
    t->cantidad_elementos--;
}

void liberar_tabla(tabla_t &t) {
    for(nat x = 0; x < t->cantidad_elementos; x++) {
        if(t->lista[x] != NULL)
            liberar_cadena(t->lista[x]);
    }
    
    delete[] t->lista;
    delete t;
}

bool existe_asociacion(int clave, tabla_t t) {
    int indice = clave % t->tamanio;
    cadena_t cad = t->lista[indice];
    
    if(cad == NULL)
        return false;
    
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc)) {
        if(numero_info(info_cadena(loc, cad)) == clave)
            return true;
        
        loc = siguiente(loc, cad);
    }
    
    return false;
}

char *valor_en_tabla(int clave, tabla_t t) {
    assert(existe_asociacion(clave, t));
    
    int indice = clave % t->tamanio;
    cadena_t cad = t->lista[indice];
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc) && numero_info(info_cadena(loc, cad)) != clave)
        loc = siguiente(loc, cad);
    
    return frase_info(info_cadena(loc, cad));
}

bool esta_llena_tabla(tabla_t t) {
    return t->cantidad_elementos == t->tamanio;
}
