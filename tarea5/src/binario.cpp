#include "../include/info.h"
#include "../include/cadena.h"
#include "../include/binario.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

struct rep_binario {
    info_t dato;
    nat cant_izq;
    rep_binario *izq;
    rep_binario *der;
};

typedef rep_binario *binario_t;

/*
    Funcion auxiliar que compara dos cadenas en orden lexicográfico creciente.
*/
int comparar_cadenas_binario(const char *s1, const char *s2) {
    unsigned int x = 0;

    while(x < strlen(s1) || x < strlen(s2)) {
        if(x >= strlen(s1) && x < strlen(s2))
            return -1;
        if(x >= strlen(s2) && x < strlen(s1))
            return 1;
        else if((s1[x]) < s2[x])
            return -1;
        else if(s1[x] > s2[x])
            return 1;

        x++;
    }
    return 0;
}

/* Constructoras */

/*
  Funcion auxiliar para construir un binario AVL desde una cadena, utiliza un 
  puntero hacia el localizador para ir avanzando mediante crea los nodos,
  un largo k para cada llamada recursiva y un puntero cad a la cadena para 
  avanzar el localizador.
*/
binario_t crear_balanceado_aux(localizador_t *loc, cadena_t cad, int k)
{
    if (k <= 0)
        return NULL;
    
    binario_t izq = crear_balanceado_aux(loc, cad, k/2);
    
    binario_t binario = new rep_binario;
    binario->dato = copia_info(info_cadena(*loc, cad));
    binario->izq = izq;
    binario->cant_izq = k/2; // Guarda cantidad nodos a la izquierda.
 
    // Avanzar el puntero al nodo para las llamadas siguientes.
    *loc = siguiente(*loc, cad);
    
    // La cantidad de nodos a construir en la rama derecha es
    // Total nodos - nodos en la rama izquierda - nodo raiz.
    binario->der = crear_balanceado_aux(loc, cad, k - k/2 -1);
    return binario;
}

binario_t crear_balanceado(cadena_t cad) {
    int largo = 0;
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc)) {
        largo++;
        loc = siguiente(loc, cad);
    }
    
    loc = inicio_cadena(cad);
    
    return crear_balanceado_aux(&loc, cad, largo);
}

binario_t crear_binario() {
    return NULL;
};

bool insertar_en_binario(info_t i, binario_t &b) {
    if(es_vacio_binario(b)) {
        b = new rep_binario;
        b->dato = i;
        b->izq = b->der = NULL;
        b->cant_izq = 0;
        return true;
        
    } else if(comparar_cadenas_binario(frase_info(i), frase_info(b->dato)) > 0)
        return insertar_en_binario(i, b->der);
    else if(comparar_cadenas_binario(frase_info(i), frase_info(b->dato)) < 0) {
        bool ret = insertar_en_binario(i, b->izq);
        
        if(ret)
            b->cant_izq++;
        
        return ret;
    } else
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
    else if(comparar_cadenas_binario(t, frase_info(b->dato)) > 0)
        return remover_de_binario(t, b->der);
    else if(comparar_cadenas_binario(t, frase_info(b->dato)) < 0)
        return remover_de_binario(t, b->izq);
    else {
        liberar_info(b->dato);
        if(!es_vacio_binario(b->izq) && !es_vacio_binario(b->der)) {
            b->dato = remover_mayor(b->izq);
            b->cant_izq--;
        } else {
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

/*
    Funcion auxiliar que calcula si un arbol es AVL, utiliza un puntero a una variable
    que se le pasa como parametro para retornar la altura del arbol.
*/
bool es_AVL(binario_t b, int* altura) {
    if(es_vacio_binario(b)) {
        *altura = 0;
        return true;
    }
    
    int alt_izq, alt_der; 
    bool avl_izq, avl_der;
    
    alt_izq = alt_der = 0;
    
    avl_izq = es_AVL(b->izq, &alt_izq);
    avl_der = es_AVL(b->der, &alt_der);
    
    // La altura del arbol es el mayor + 1.
    *altura = (alt_izq > alt_der ? alt_izq : alt_der) + 1;
    
    if((alt_izq - alt_der >= 2) || (alt_der - alt_izq >= 2))
        return false;
    else
        return avl_izq && avl_der;
}

bool es_AVL(binario_t b) {
    if(es_vacio_binario(b))
        return true;
    
    int altura;
    return es_AVL(b, &altura);
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
    else if(comparar_cadenas_binario(t, frase_info(b->dato)) == 0)
        return b;
    else if(comparar_cadenas_binario(t, frase_info(b->dato)) < 0)
        return buscar_subarbol(t, b->izq);
    else if(comparar_cadenas_binario(t, frase_info(b->dato)) > 0)
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
    info_t info = NULL;
    
    rep_binario* loc = b;

    while(loc) {
        
        if((loc->cant_izq + 1) == k) {
            info = loc->dato;
            break;
        
        } else if(k > loc->cant_izq) {
            k = k - (loc->cant_izq + 1);
            loc = loc->der;
        } else
            loc = loc->izq;
    }
 
    return info;
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
        b_filtrado->cant_izq = b->cant_izq;
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
