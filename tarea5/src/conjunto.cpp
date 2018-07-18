#include "../include/conjunto.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

struct rep_conjunto {
    info_t dato;
    rep_conjunto *izq;
    rep_conjunto *der;
};

typedef rep_conjunto *conjunto_t;

/*
    Funcion auxiliar que compara dos cadenas en orden lexicográfico creciente.
*/
int comparar_cadenas_conjunto(const char *s1, const char *s2) {
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

conjunto_t crear_conjunto() {
    return NULL;
}

/*
  Funcion auxiliar para construir un conjunto AVL desde una cadena, utiliza un 
  puntero hacia el localizador para ir avanzando mediante crea los nodos,
  un largo k para cada llamada recursiva y un puntero cad a la cadena para 
  avanzar el localizador.
*/
conjunto_t construir_conjunto_aux(localizador_t *loc, cadena_t cad, int k)
{
    if (k <= 0)
        return NULL;
    
    conjunto_t izq = construir_conjunto_aux(loc, cad, k/2);
    
    conjunto_t conjunto = new rep_conjunto;
    conjunto->dato = copia_info(info_cadena(*loc, cad));
    conjunto->izq = izq;
 
    // Avanzar el puntero al nodo para las llamadas siguientes.
    *loc = siguiente(*loc, cad);
    
    // La cantidad de nodos a construir en la rama derecha es
    // Total nodos - nodos en la rama izquierda - nodo raiz.
    conjunto->der = construir_conjunto_aux(loc, cad, k - k/2 -1);
 
    return conjunto;
}

conjunto_t construir_conjunto(cadena_t cad) {
    int largo = 0;
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc)) {
        largo++;
        loc = siguiente(loc, cad);
    }
    
    loc = inicio_cadena(cad);
    
    return construir_conjunto_aux(&loc, cad, largo);
}

bool incluir(info_t i, conjunto_t &c) {
    if(es_vacio_conjunto(c)) {
        c = new rep_conjunto;
        c->dato = i;
        c->izq = c->der = NULL;
        return true;
    } else if(comparar_cadenas_conjunto(frase_info(i), frase_info(c->dato)) > 0)
        return incluir(i, c->der);
    else if(comparar_cadenas_conjunto(frase_info(i), frase_info(c->dato)) < 0)
        return incluir(i, c->izq);
    else
        return false;
}

/*
  Funcion auxiliar para convertir un conjunto a una cadena.
*/
cadena_t cadena_conjunto(conjunto_t c) {
    cadena_t cad = crear_cadena();
    
    if(es_vacio_conjunto(c))
        return cad;

    if(!es_vacio_conjunto(c->izq)) {
        cadena_t cad_izq = cadena_conjunto(c->izq);
        insertar_segmento_despues(cad_izq, final_cadena(cad), cad);
        liberar_cadena(cad_izq);
    }

    info_t info = copia_info(c->dato);
    insertar_al_final(info, cad);

    if(!es_vacio_conjunto(c->der)) {
        cadena_t cad_der = cadena_conjunto(c->der);
        insertar_segmento_despues(cad_der, final_cadena(cad), cad);
        liberar_cadena(cad_der);
    }

    return cad;
}

conjunto_t union_conjunto(conjunto_t s1, conjunto_t s2) {
    cadena_t cad_izq = cadena_conjunto(s1);
    cadena_t cad_der = cadena_conjunto(s2);
    cadena_t cad = crear_cadena();

    localizador_t cursor_cad_izq = inicio_cadena(cad_izq);
    localizador_t cursor_cad_der = inicio_cadena(cad_der);

    while(es_localizador(cursor_cad_izq) || es_localizador(cursor_cad_der)) {
        
        // No se ah llegado al final de las dos cadenas.
        if(es_localizador(cursor_cad_izq) && es_localizador(cursor_cad_der)) {
            
            if(comparar_cadenas_conjunto(frase_info(info_cadena(cursor_cad_izq, cad_izq)), frase_info(info_cadena(cursor_cad_der, cad_der))) < 0) {
                insertar_al_final(copia_info(info_cadena(cursor_cad_izq, cad_izq)), cad);
                cursor_cad_izq = siguiente(cursor_cad_izq, cad_izq);
                
            } else if(comparar_cadenas_conjunto(frase_info(info_cadena(cursor_cad_izq, cad_izq)), frase_info(info_cadena(cursor_cad_der, cad_der))) > 0) {
                insertar_al_final(copia_info(info_cadena(cursor_cad_der, cad_der)), cad);
                cursor_cad_der = siguiente(cursor_cad_der, cad_der);
                
            } else {
                insertar_al_final(copia_info(info_cadena(cursor_cad_izq, cad_izq)), cad);
                cursor_cad_izq = siguiente(cursor_cad_izq, cad_izq);
                cursor_cad_der = siguiente(cursor_cad_der, cad_der);
            }
        
        // Se termino la cadena derecha, agrega el resto de elementos de la izquierda.
        } else if(es_localizador(cursor_cad_izq)) {
            insertar_al_final(copia_info(info_cadena(cursor_cad_izq, cad_izq)), cad);
            cursor_cad_izq = siguiente(cursor_cad_izq, cad_izq);
        
        // Se termino la cadena izquierda, agrega el resto de elementos de la derecha.
        } else {
            insertar_al_final(copia_info(info_cadena(cursor_cad_der, cad_der)), cad);
            cursor_cad_der = siguiente(cursor_cad_der, cad_der);
        }
    }

    conjunto_t conjunto = construir_conjunto(cad);

    liberar_cadena(cad_izq);
    liberar_cadena(cad_der);
    liberar_cadena(cad);

    return conjunto;
}

conjunto_t interseccion(conjunto_t c1, conjunto_t c2) {
    cadena_t cad_izq = cadena_conjunto(c1);
    cadena_t cad_der = cadena_conjunto(c2);
    cadena_t cad = crear_cadena();

    localizador_t cursor_cad_izq = inicio_cadena(cad_izq);
    localizador_t cursor_cad_der = inicio_cadena(cad_der);

    while(es_localizador(cursor_cad_izq) && es_localizador(cursor_cad_der)) {
        
        if(comparar_cadenas_conjunto(frase_info(info_cadena(cursor_cad_izq, cad_izq)), frase_info(info_cadena(cursor_cad_der, cad_der))) < 0)
            cursor_cad_izq = siguiente(cursor_cad_izq, cad_izq);
            
        else if(comparar_cadenas_conjunto(frase_info(info_cadena(cursor_cad_izq, cad_izq)), frase_info(info_cadena(cursor_cad_der, cad_der))) > 0)
            cursor_cad_der = siguiente(cursor_cad_der, cad_der);
            
        else {
            insertar_al_final(copia_info(info_cadena(cursor_cad_izq, cad_izq)), cad);
            cursor_cad_izq = siguiente(cursor_cad_izq, cad_izq);
            cursor_cad_der = siguiente(cursor_cad_der, cad_der);
        }    
    }

    conjunto_t conjunto = construir_conjunto(cad);

    liberar_cadena(cad_izq);
    liberar_cadena(cad_der);
    liberar_cadena(cad);

    return conjunto;
}

conjunto_t diferencia(conjunto_t c1, conjunto_t c2) {
    cadena_t cad_c1 = cadena_conjunto(c1);
    cadena_t cad = crear_cadena();

    localizador_t loc_c1 = inicio_cadena(cad_c1);

    while(es_localizador(loc_c1)) {

        if(!pertenece_conjunto(frase_info(info_cadena(loc_c1, cad_c1)), c2))
            insertar_al_final(copia_info(info_cadena(loc_c1, cad_c1)), cad);

        loc_c1 = siguiente(loc_c1, cad_c1);
    }

    conjunto_t conjunto = construir_conjunto(cad);

    liberar_cadena(cad_c1);
    liberar_cadena(cad);

    return conjunto;
}

/* Destructoras */

/*
  Funcion auxiliar para remover el mayor.
  Precondicion: !es_vacio_conjunto(c)
*/
info_t remover_mayor(conjunto_t &c) {
    assert(!es_vacio_conjunto(c));

    info_t res;

    if(c->der == NULL) {
        res = c->dato;
        conjunto_t izq = c->izq;
        delete (c);
        c = izq;
    } else {
        res = remover_mayor(c->der);
    }
    return res;
};

void excluir(char *t, conjunto_t &c) {
    if(es_vacio_conjunto(c))
        return;
    else if(comparar_cadenas_conjunto(t, frase_info(c->dato)) > 0)
        return excluir(t, c->der);
    else if(comparar_cadenas_conjunto(t, frase_info(c->dato)) < 0)
        return excluir(t, c->izq);
    else {
        liberar_info(c->dato);
        if(!es_vacio_conjunto(c->izq) && !es_vacio_conjunto(c->der))
            c->dato = remover_mayor(c->izq);
        else {
            conjunto_t aux;

            if(!es_vacio_conjunto(c->izq))
                aux = c->izq;
            else
                aux = c->der;

            delete c;
            c = aux;
        }
    }
}

void liberar_conjunto(conjunto_t &c) {
    if(es_vacio_conjunto(c))
        return;

    liberar_info(c->dato);
    liberar_conjunto(c->izq);
    liberar_conjunto(c->der);
    delete c;
}

bool pertenece_conjunto(char *t, conjunto_t c) {
    if(es_vacio_conjunto(c))
        return false;
    else if(comparar_cadenas_conjunto(t, frase_info(c->dato)) == 0)
        return true;
    else if(comparar_cadenas_conjunto(t, frase_info(c->dato)) < 0)
        return pertenece_conjunto(t, c->izq);
    else if(comparar_cadenas_conjunto(t, frase_info(c->dato)) > 0)
        return pertenece_conjunto(t, c->der);
    else
        return false;
}

bool es_vacio_conjunto(conjunto_t c) {
    return c == NULL;
}

iterador_t iterador_conjunto(conjunto_t c) {
    if(es_vacio_conjunto(c))
        return crear_iterador();

    iterador_t iterador = crear_iterador();

    // Obtiene iterador nodo izquierdo y lo copia al iterador actual.
    if(!es_vacio_conjunto(c->izq)) {
        iterador_t i_izq = iterador_conjunto(c->izq);
        while(esta_definida_actual(i_izq)) {
            char* p_string = actual_iter(i_izq);
            char* c_string = new char[strlen(p_string) + 1];
            strcpy(c_string, p_string);

            agregar_a_iterador(c_string, iterador);

            avanzar_iter(i_izq);
        }
        liberar_iterador(i_izq);
    }

    // Copia la frase del dato info del conjunto.
    char* p_frase = frase_info(c->dato);
    char* c_frase = new char[strlen(p_frase) + 1];
    strcpy(c_frase, p_frase);
    agregar_a_iterador(c_frase, iterador);

    // Obtiene iterador nodo derecho y lo copia al iterador actual.
    if(!es_vacio_conjunto(c->der)) {
        iterador_t i_der = iterador_conjunto(c->der);
        while(esta_definida_actual(i_der)) {
            char* p_string = actual_iter(i_der);
            char* c_string = new char[strlen(p_string) + 1];
            strcpy(c_string, p_string);

            agregar_a_iterador(c_string, iterador);

            avanzar_iter(i_der);
        }
        liberar_iterador(i_der);
    }
    
    reiniciar_iter(iterador);
    return iterador;
}