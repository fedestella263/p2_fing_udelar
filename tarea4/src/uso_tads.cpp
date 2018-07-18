#include "../include/uso_tads.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/*
    Funcion auxiliar que compara dos cadenas en orden lexicográfico creciente.
*/
int comparar_cadenas_tads(const char *s1, const char *s2) {
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

iterador_t inverso_de_iter(nat a, nat b, iterador_t it) {
    assert(1 <= a && a <= b);
    iterador_t iterador = crear_iterador();
    nat x = 1;
    
    reiniciar_iter(it);
     
    // Ir hasta la posicion a.
    while(x < a && esta_definida_actual(it)) {
        avanzar_iter(it);
        x++;
    }
    
    if(x == a) {
        cadena_t cad = crear_cadena();
        
        // Copiar desde a hasta b.
        while(x <= b && esta_definida_actual(it)) {
            
            char* frase = actual_iter(it);
            char* copia_frase = new char[strlen(frase) + 1];
            strcpy(copia_frase, frase);
            
            insertar_al_final(crear_info(0, copia_frase), cad);
            
            avanzar_iter(it);
            x++;
        }
        
        // Va hasta el final para regresar en sentido inverso.
        localizador_t loc = final_cadena(cad);
        
        // Agregar las frases de la cadena al iterador en orden inverso.
        while(es_localizador(loc)) {
            
            char* frase = frase_info(info_cadena(loc, cad));
            char* copia_frase = new char[strlen(frase) + 1];
            strcpy(copia_frase, frase);
            
            agregar_a_iterador(copia_frase, iterador);
            loc = anterior(loc, cad);
        }
        
        liberar_cadena(cad);
    }
    
    reiniciar_iter(it);
    reiniciar_iter(iterador);
    return iterador;
}

iterador_t rango_en_conjunto(char *primero, char *ultimo, conjunto_t c) {
    assert(comparar_cadenas_tads(primero, ultimo) >= 0);
    
    iterador_t it_total = iterador_conjunto(c);
    iterador_t it_rango = crear_iterador();
    
    while(esta_definida_actual(it_total)) {
        char* frase = actual_iter(it_total);
        
        // Si esta en el rango, copia la cadena y la guarda.
        if(comparar_cadenas_tads(primero, frase) <= 0 && comparar_cadenas_tads(frase, ultimo) <= 0) {
            
            char* copia_frase = new char[strlen(frase) + 1];
            strcpy(copia_frase, frase);
            
            agregar_a_iterador(copia_frase, it_rango);
        }
        
        avanzar_iter(it_total);
    }
    
    // Retorna el inverso del iterador y libera memoria de los otros.
    iterador_t it_invertido = inverso_de_iter(1, MAX_ITER, it_rango);
    liberar_iterador(it_total);
    liberar_iterador(it_rango);
    return it_invertido;
}

bool esta_ordenada_por_frase(cadena_t cad) {
    
    if(!es_vacia_cadena(cad)) {
        localizador_t loc = inicio_cadena(cad);
        
        while(es_localizador(siguiente(loc, cad))) {
            localizador_t sig_loc = siguiente(loc, cad);
            
            char* frase = frase_info(info_cadena(loc, cad));
            char* frase_sig = frase_info(info_cadena(sig_loc, cad));
            
            if(comparar_cadenas_tads(frase, frase_sig) >= 0)
                return false;
            else
                loc = siguiente(loc, cad);
        }
    }
    
    return true;
}

/*
  Funcion auxiliar que imprime un determinado nivel de un arbol binario.
*/
void imprimir_k_nivel(nat k, binario_t b) {
    if(es_vacio_binario(b))
        return;
    else if(k == 1)
        printf("%s ", frase_info(raiz(b)));
    else if(k > 1) {
        imprimir_k_nivel(k-1, izquierdo(b));
        imprimir_k_nivel(k-1, derecho(b));
    }
}

void imprimir_por_niveles(binario_t b) {
    if(es_vacio_binario(b))
        return;
    else {
        // Imprime desde el nivel mas bajo al mas alto.
        for(nat x = altura_binario(b); x >= 1; x--) {
            imprimir_k_nivel(x, b);
            if(x > 1)
                printf("\n");
        }
    }
}

bool pertenece(int i, cadena_t cad) {
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc)) {
        if(numero_info(info_cadena(loc, cad)) == i)
            return true;
        
        loc = siguiente(loc, cad);
    }
    
    return false;
}

nat longitud(cadena_t cad) {
    localizador_t loc = inicio_cadena(cad);
    nat cantidad = 0;
    
    while(es_localizador(loc)) {
        cantidad++;
        loc = siguiente(loc, cad);
    }
    
    return cantidad;
}

bool son_iguales(cadena_t c1, cadena_t c2) {
    localizador_t loc1, loc2;
    loc1 = inicio_cadena(c1);
    loc2 = inicio_cadena(c2);
    
    while(es_localizador(loc1) || es_localizador(loc2)) {
        
        if(es_localizador(loc1) != es_localizador(loc2))
            return false;
        
        info_t info1 = info_cadena(loc1, c1);
        info_t info2 = info_cadena(loc2, c2);
        
        if(numero_info(info1) != numero_info(info2) || comparar_cadenas_tads(frase_info(info1), frase_info(info2)) != 0)
            return false;
        
        loc1 = siguiente(loc1, c1);
        loc2 = siguiente(loc2, c2);
    }
    
    return true;
}

cadena_t concatenar(cadena_t c1, cadena_t c2) {
    localizador_t loc1, loc2;
    cadena_t cad = crear_cadena();
    
    loc1 = inicio_cadena(c1);
    loc2 = inicio_cadena(c2);
    
    while(es_localizador(loc1)) {
        insertar_al_final(copia_info(info_cadena(loc1, c1)), cad);
        loc1 = siguiente(loc1, c1);
    }
    
    while(es_localizador(loc2)) {
        insertar_al_final(copia_info(info_cadena(loc2, c2)), cad);
        loc2 = siguiente(loc2, c2);
    }
    
    return cad;
}

void ordenar(cadena_t &cad) {
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc) && es_localizador(siguiente(loc, cad))) {
        if(numero_info(info_cadena(loc, cad)) > numero_info(info_cadena(siguiente(loc, cad), cad))) {
            intercambiar(loc, siguiente(loc, cad), cad);
            loc = inicio_cadena(cad);
        } else
            loc = siguiente(loc, cad);
    }
}

void cambiar_todos(int original, int nuevo, cadena_t &cad) {
    localizador_t loc = inicio_cadena(cad);
    
    while(es_localizador(loc)) {
        if(numero_info(info_cadena(loc, cad)) == original) {
            info_t info_original = info_cadena(loc, cad);
            
            char* frase = frase_info(info_original);
            char* copia_frase = new char[strlen(frase) + 1];
            strcpy(copia_frase, frase);
            
            info_t info_nueva = crear_info(nuevo, copia_frase);
            cambiar_en_cadena(info_nueva, loc, cad);
            liberar_info(info_original);
        }
        
        loc = siguiente(loc, cad);
    }
}

cadena_t subcadena(int menor, int mayor, cadena_t cad) {
    assert(esta_ordenada(cad) && menor <= mayor && pertenece(menor, cad) && pertenece(mayor, cad));
    
    localizador_t loc = inicio_cadena(cad);
    cadena_t cad_resultado = crear_cadena();
    
    while(es_localizador(loc)) {
        if(menor <= numero_info(info_cadena(loc, cad)) && mayor >= numero_info(info_cadena(loc, cad)))
            insertar_al_final(copia_info(info_cadena(loc, cad)), cad_resultado);
        
        loc = siguiente(loc, cad);
    }
    
    return cad_resultado;
}