#include "../include/info.h"
#include "../include/cadena.h"
#include "../include/binario.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct rep_binario {
    info_t dato;
    rep_binario *izq;
    rep_binario *der;
};

typedef rep_binario *binario_t;

/* Constructoras */

binario_t crear_binario() {
    return NULL;
};

bool insertar_en_binario(info_t i, binario_t &b) {
    if(es_vacio_binario(b)) {
        b = new rep_binario;
        b->dato = i;
        b->izq = b->der = NULL;
        return true;
    } else if(strtol(frase_info(i), NULL, 36) > strtol(frase_info(b->dato), NULL, 36))
        return insertar_en_binario(i, b->der);
    else if(strtol(frase_info(i), NULL, 36) < strtol(frase_info(b->dato), NULL, 36))
        return insertar_en_binario(i, b->izq);
    else
        return false;
};

/* Destructoras */

info_t remover_mayor(binario_t &b) {
    assert(!es_vacio_binario(b));

    info_t res;

    if(b->der == NULL) {
        res = b->dato;
        binario_t izq = b->izq;
        delete (b);
        b = izq;
    } else {
        res = remover_mayor(b->der);
    }
    return res;
};

bool remover_de_binario(const char *t, binario_t &b) {
    if(es_vacio_binario(b))
        return false;
    else if(strtol(t, NULL, 36) > strtol(frase_info(b->dato), NULL, 36))
        return remover_de_binario(t, b->der);
    else if(strtol(t, NULL, 36) < strtol(frase_info(b->dato), NULL, 36))
        return remover_de_binario(t, b->izq);
    else {
        liberar_info(b->dato);
        if(!es_vacio_binario(b->izq) && !es_vacio_binario(b->der))
            b->dato = remover_mayor(b->izq);
        else {
            binario_t aux;
            
            if(!es_vacio_binario(b->izq))
                aux = b->izq;
            else
                aux = b->der;
            
            delete b;
            b = aux;
        }
        return true;
    }
};

void liberar_binario(binario_t &b) {
    if(es_vacio_binario(b))
        return;

    liberar_info(b->dato);
    liberar_binario(b->izq);
    liberar_binario(b->der);
    delete b;
};

/* Predicados */

bool es_vacio_binario(binario_t b) {
    return b == NULL;
};

bool es_AVL(binario_t b) {
    if(es_vacio_binario(b))
        return true;
    else if((altura_binario(b->der) >= altura_binario(b->izq)) && (altura_binario(b->der) - altura_binario(b->izq)) > 1)
        return false;
    else if((altura_binario(b->izq) >= altura_binario(b->der)) && (altura_binario(b->izq) - altura_binario(b->der)) > 1)
        return false;
    else if(!es_AVL(b->izq) || !es_AVL(b->der))
        return false;
    else
        return true;
};

/* Selectoras */

info_t raiz(binario_t b) {
    assert(!es_vacio_binario(b));
    return b->dato;
};

binario_t izquierdo(binario_t b) {
    assert(!es_vacio_binario(b));
    return b->izq;
};

binario_t derecho(binario_t b) {
    assert(!es_vacio_binario(b));
    return b->der;
};

binario_t buscar_subarbol(const char *t, binario_t b) {
    if(es_vacio_binario(b))
        return NULL;
    else if(strtol(t, NULL, 36) == strtol(frase_info(b->dato), NULL, 36))
        return b;
    else if(strtol(t, NULL, 36) < strtol(frase_info(b->dato), NULL, 36))
        return buscar_subarbol(t, b->izq);
    else if(strtol(t, NULL, 36) > strtol(frase_info(b->dato), NULL, 36))
        return buscar_subarbol(t, b->der);
    else
        return NULL;
};

nat altura_binario(binario_t b) {
    if(es_vacio_binario(b))
        return 0;
    else if(es_vacio_binario(b->izq))
        return altura_binario(b->der)+1;
    else if(es_vacio_binario(b->der))
        return altura_binario(b->izq)+1;
    else {
        nat altura_izq = altura_binario(b->izq);
        nat altura_der = altura_binario(b->der);

        // retorna mayor(izq, der) + 1.
        return (altura_izq > altura_der ? altura_izq+1 : altura_der+1);
    }
};

nat cantidad_binario(binario_t b) {
    if(es_vacio_binario(b))
        return 0;
    else
        return cantidad_binario(b->izq) + cantidad_binario(b->der) + 1;
};

info_t kesimo_en_binario(nat k, binario_t b) {
    assert((1 <= k) && (k <= cantidad_binario(b)));

    nat cantidad_izq = cantidad_binario(b->izq);

    if((cantidad_izq + 1) == k)
        return b->dato;
    else if((cantidad_izq + 1) < k)
        return kesimo_en_binario(k-(cantidad_izq+1), b->der);
    else
        return kesimo_en_binario(k, b->izq);
};

cadena_t linealizacion(binario_t b) {
    if(es_vacio_binario(b))
        return crear_cadena();
    else {
        cadena_t cadena = crear_cadena();

        if(!es_vacio_binario(b->izq)) {
            cadena_t cadena_izq = linealizacion(b->izq);
            insertar_segmento_despues(cadena_izq, final_cadena(cadena), cadena);
            liberar_cadena(cadena_izq);
        }

        insertar_al_final(copia_info(b->dato), cadena);

        if(!es_vacio_binario(b->der)) {
            cadena_t cadena_der = linealizacion(b->der);
            insertar_segmento_despues(cadena_der, final_cadena(cadena), cadena);
            liberar_cadena(cadena_der);
        }

        return cadena;
    }
};

binario_t filtrado(int clave, binario_t b) {
    if(es_vacio_binario(b))
        return NULL;
    else {
        binario_t b_filtrado;
        binario_t nodo_izq_filtrado = filtrado(clave, b->izq);
        binario_t nodo_der_filtrado = filtrado(clave, b->der);

        if(numero_info(b->dato) < clave) {
            b_filtrado = new rep_binario;
            b_filtrado->dato = copia_info(b->dato);
        } else if(!es_vacio_binario(nodo_izq_filtrado) && !es_vacio_binario(nodo_der_filtrado)) {
            b_filtrado = new rep_binario;
            b_filtrado->dato = remover_mayor(nodo_izq_filtrado);
        } else if(!es_vacio_binario(nodo_izq_filtrado))
            return nodo_izq_filtrado;
        else if(!es_vacio_binario(nodo_der_filtrado))
            return nodo_der_filtrado;
        else
            return NULL;

        b_filtrado->izq = nodo_izq_filtrado;
        b_filtrado->der = nodo_der_filtrado;
        return b_filtrado;
    }
};

/* Salida */

static void imprimir_binario_altura(nat altura, binario_t b) {
    if(!es_vacio_binario(b)) {
        if(!es_vacio_binario(b->der))
            imprimir_binario_altura(altura+1, b->der);

        for(nat x = 0; x < altura; x++)
            printf("-");
        printf("(%d,%s)\n", numero_info(b->dato), frase_info(b->dato));

        if(!es_vacio_binario(b->izq))
            imprimir_binario_altura(altura+1, b->izq);
    }
}

void imprimir_binario(binario_t b) {
    printf("\n");
    imprimir_binario_altura(0, b);
};
