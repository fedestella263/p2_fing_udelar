#include "../include/cadena.h"
#include "../include/info.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h> 

struct nodo {
    info_t dato;
    nodo *anterior;
    nodo *siguiente;
};

struct rep_cadena {
    nodo *inicio;
    nodo *final;
};

cadena_t crear_cadena() {
    cadena_t res = new rep_cadena;
    res->inicio = res->final = NULL;
    return res;
}

void insertar_al_final(info_t i, cadena_t &cad) {
    nodo *nuevo = new nodo;
    
    nuevo->dato = i;
    nuevo->siguiente = NULL;
    nuevo->anterior = cad->final;
    
    if(cad->final == NULL) {
        assert(cad->inicio == NULL);
        cad->inicio = nuevo;
    } else {
        assert(cad->inicio != NULL);
        cad->final->siguiente = nuevo;
    }
    
    cad->final = nuevo;
}

void insertar_antes(info_t i, localizador_t loc, cadena_t &cad) {
    assert(localizador_en_cadena(loc, cad));
    
    nodo *nuevo = new nodo;
    
    nuevo->dato = i;
    nuevo->siguiente = loc;
    nuevo->anterior = loc->anterior;
    
    if(inicio_cadena(cad) == loc)
        cad->inicio = nuevo;
    else
        loc->anterior->siguiente = nuevo;    
    
    loc->anterior = nuevo;
}

void insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t &cad) {
    assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
    
    if(es_vacia_cadena(cad)) {
        cad->inicio = sgm->inicio;
        cad->final = sgm->final;
    } else {
        if(!es_vacia_cadena(sgm)) {
            sgm->inicio->anterior = loc;
            sgm->final->siguiente = loc->siguiente;
            
            if(es_final_cadena(loc, cad))
                cad->final = sgm->final;
            else
                loc->siguiente->anterior = sgm->final;
            
            loc->siguiente = sgm->inicio;
        }
    }
    
    sgm->inicio = sgm->final = NULL;
}

cadena_t segmento_cadena(localizador_t desde, localizador_t hasta, cadena_t cad) {
    assert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));
    
    cadena_t res = crear_cadena();
    
    if(!es_vacia_cadena(cad)) {
        localizador_t loc = desde;
        
        while(loc != hasta->siguiente) {
            info_t info = copia_info((loc->dato));
            insertar_al_final(info, res);
            loc = loc->siguiente;
        }
    }
    
    return res;
}

cadena_t separar_segmento(localizador_t desde, localizador_t hasta, cadena_t &cad) {
    assert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));
    
    cadena_t cadena = crear_cadena();
    
    cadena->inicio = desde;
    cadena->final = hasta;
    
    if(es_localizador(desde) && es_localizador(desde->anterior))
        desde->anterior->siguiente = hasta->siguiente;
        
    if(es_localizador(hasta) && es_localizador(hasta->siguiente))
        hasta->siguiente->anterior = desde->anterior;
    
    if(es_inicio_cadena(desde, cad))
        cad->inicio = es_localizador(hasta) ? hasta->siguiente : NULL;
    
    if(es_final_cadena(hasta, cad))
        cad->final = es_localizador(desde) ? desde->anterior : NULL;
    
    if(es_localizador(desde))
        desde->anterior = NULL;
    
    if(es_localizador(hasta))
        hasta->siguiente = NULL;
    
    return cadena;
}

cadena_t mezcla(cadena_t c1, cadena_t c2) {
    assert(esta_ordenada(c1) && esta_ordenada(c2));
    
    localizador_t cursor_c1 = inicio_cadena(c1);
    localizador_t cursor_c2 = inicio_cadena(c2);
    cadena_t cadena = crear_cadena();
    
    while(es_localizador(cursor_c1) || es_localizador(cursor_c2)) {
        
        if(es_localizador(cursor_c1) && es_localizador(cursor_c2)) {
            
            if(numero_info(info_cadena(cursor_c1, c1)) <= numero_info(info_cadena(cursor_c2, c2))) {
                insertar_al_final(copia_info(info_cadena(cursor_c1, c1)), cadena);
                cursor_c1 = cursor_c1->siguiente;
            } else {
                insertar_al_final(copia_info(info_cadena(cursor_c2, c2)), cadena);
                cursor_c2 = cursor_c2->siguiente;
            }
            
        } else if(es_localizador(cursor_c1)) {
            insertar_al_final(copia_info(info_cadena(cursor_c1, c1)), cadena);
            cursor_c1 = cursor_c1->siguiente;
        } else {
            insertar_al_final(copia_info(info_cadena(cursor_c2, c2)), cadena);
            cursor_c2 = cursor_c2->siguiente;
        }
            
    }
    
    return cadena;
}

/* Destructoras */

void remover_de_cadena(localizador_t &loc, cadena_t &cad) {
    assert(localizador_en_cadena(loc, cad));
    
    if(es_inicio_cadena(loc, cad))
        cad->inicio = loc->siguiente;
    
    if(es_final_cadena(loc, cad))
        cad->final = loc->anterior;
    
    if(es_localizador(loc->siguiente))
        loc->siguiente->anterior = loc->anterior;
    
    if(es_localizador(loc->anterior))
        loc->anterior->siguiente = loc->siguiente;
    
    liberar_info(loc->dato);
    delete loc;
}

void liberar_cadena(cadena_t &cad) {
    nodo *a_borrar;
    
    while(cad->inicio != NULL) {
        a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberar_info(a_borrar->dato);
        delete (a_borrar);
    }
    
    delete cad;
}

bool es_localizador(localizador_t loc) {
    return loc != NULL;    
}

bool es_vacia_cadena(cadena_t cad) {
    return (cad->inicio == NULL) && (cad->final == NULL);
}

bool esta_ordenada(cadena_t cad) {
    bool res = true;
    
    if(!es_vacia_cadena(cad)) {
        localizador_t loc = inicio_cadena(cad);
        
        while(res && es_localizador(loc->siguiente)) {
            localizador_t sig_loc = loc->siguiente;
            
            if(numero_info(info_cadena(loc, cad)) > numero_info(info_cadena(sig_loc, cad)))
                res = false;
            else
                loc = loc->siguiente;
        }
    }
    
    return res;
}

bool es_final_cadena(localizador_t loc, cadena_t cad) {
    return !es_vacia_cadena(cad) && (final_cadena(cad) == loc);
}

bool es_inicio_cadena(localizador_t loc, cadena_t cad) {
    return !es_vacia_cadena(cad) && (inicio_cadena(cad) == loc);
}

bool localizador_en_cadena(localizador_t loc, cadena_t cad) {
    if(es_vacia_cadena(cad))
        return false;
    
    localizador_t cursor = inicio_cadena(cad);
    
    while(cursor != loc && es_localizador(cursor->siguiente))
        cursor = cursor->siguiente;
    
    return cursor == loc;
}

bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad) {
    localizador_t cursor = loc1;
    
    while(es_localizador(cursor) && (cursor != loc2))
        cursor = cursor->siguiente;
    
    return ((cursor == loc2) && (localizador_en_cadena(loc1, cad)));
}

/* Posicionamiento */

localizador_t inicio_cadena(cadena_t cad) {
    return es_vacia_cadena(cad) ? NULL : cad->inicio;
}

localizador_t final_cadena(cadena_t cad) {
    return es_vacia_cadena(cad) ? NULL : cad->final;
}

localizador_t kesimo(nat k, cadena_t cad) {
    nat cont = 1;
    localizador_t cursor = inicio_cadena(cad);
    
    while(k > cont && es_localizador(cursor)) {
        cursor = cursor->siguiente;
        cont++;
    }
    
    return k == cont ? cursor : NULL;
}

localizador_t siguiente(localizador_t loc, cadena_t cad) {
    assert(localizador_en_cadena(loc, cad));
    return es_final_cadena(loc, cad) ? NULL : loc->siguiente;
}

localizador_t anterior(localizador_t loc, cadena_t cad) {
    assert(localizador_en_cadena(loc, cad));
    return es_inicio_cadena(loc, cad) ? NULL : loc->anterior;
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad) {
    assert(localizador_en_cadena(loc, cad));
    
    localizador_t res = loc;
    
    while(es_localizador(loc->siguiente)) {
        loc = loc->siguiente;
        
        if(numero_info(info_cadena(loc, cad)) < numero_info(info_cadena(res, cad)))
            res = loc;
    }
    
    return res;
}

localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad) {
    assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
    
    localizador_t res = loc;
    
    if(es_vacia_cadena(cad))
        res = NULL;
    else {
        while(es_localizador(res) && numero_info(info_cadena(res, cad)) != clave)
            res = res->siguiente;
    }
    
    return res;
}

localizador_t anterior_clave(int clave, localizador_t loc, cadena_t cad) {
    assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
    
    localizador_t cursor = loc;
    
    while(es_localizador(cursor) && clave != numero_info(info_cadena(cursor, cad)))
        cursor = cursor->anterior;
    
    return (es_localizador(cursor) && (clave == numero_info(info_cadena(cursor, cad)))) ? cursor : NULL;
}

/* Selectoras */

info_t info_cadena(localizador_t loc, cadena_t cad) {
    assert(localizador_en_cadena(loc, cad));
    return loc->dato;
}

/* Modificadoras */

void cambiar_en_cadena(info_t i, localizador_t loc, cadena_t &cad) {
    assert(localizador_en_cadena(loc, cad));
    
    loc->dato = i;
}

void intercambiar(localizador_t loc1, localizador_t loc2, cadena_t &cad) {
    assert(localizador_en_cadena(loc1, cad) && localizador_en_cadena(loc2, cad));
    
    info_t temp = info_cadena(loc1, cad);
    loc1->dato = info_cadena(loc2, cad);
    loc2->dato = temp;
}

/* Salida */

void imprimir_cadena(cadena_t cad) {
    localizador_t cursor = inicio_cadena(cad);
    
    while(es_localizador(cursor)) {
        printf("(%d,%s)", numero_info(info_cadena(cursor, cad)), frase_info(info_cadena(cursor, cad)));
        cursor = cursor->siguiente;
    }
    
    printf("\n");
}