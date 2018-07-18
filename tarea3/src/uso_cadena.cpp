#include "../include/uso_cadena.h"
#include "../include/cadena.h"
#include "../include/info.h"

#include <assert.h> 
#include <string.h> 

bool pertenece(int i, cadena_t cad) {
    localizador_t cursor = inicio_cadena(cad);
    
    while(es_localizador(cursor) && i != numero_info(info_cadena(cursor, cad)))
        cursor = siguiente(cursor, cad);  
    
    return es_localizador(cursor) && i == numero_info(info_cadena(cursor, cad));
}

nat longitud(cadena_t cad) {
    nat cont = 0;
    localizador_t cursor = inicio_cadena(cad);
    
    while(es_localizador(cursor)) {
        cursor = siguiente(cursor, cad);
        cont++;
    }
    
    return cont;
}

bool son_iguales(cadena_t c1, cadena_t c2) {
    if(es_vacia_cadena(c1) && es_vacia_cadena(c2))
        return true;
    
    localizador_t cursor_c1 = inicio_cadena(c1);
    localizador_t cursor_c2 = inicio_cadena(c2);

    while(es_localizador(cursor_c1) && es_localizador(cursor_c2) && son_iguales(info_cadena(cursor_c1, c1), info_cadena(cursor_c2, c2))) {
        cursor_c1 = siguiente(cursor_c1, c1);
        cursor_c2 = siguiente(cursor_c2, c2);
    }

    return !es_localizador(cursor_c1) && !es_localizador(cursor_c2);
}

cadena_t concatenar(cadena_t c1, cadena_t c2) {
    cadena_t cadena = crear_cadena();
    localizador_t cursor_c1 = inicio_cadena(c1);
    localizador_t cursor_c2 = inicio_cadena(c2);

    while(es_localizador(cursor_c1)) {
        insertar_al_final(copia_info(info_cadena(cursor_c1, c1)), cadena);
        cursor_c1 = siguiente(cursor_c1, c1);
    }
    
    while(es_localizador(cursor_c2)) {
        insertar_al_final(copia_info(info_cadena(cursor_c2, c2)), cadena);
        cursor_c2 = siguiente(cursor_c2, c2);
    }
    
    return cadena;
}

void ordenar(cadena_t &cad) {
    bool reordenar = true;

    while(reordenar) {
        reordenar = false;
        localizador_t cursor = inicio_cadena(cad);
        
        while(es_localizador(cursor) && es_localizador(siguiente(cursor, cad))) {
            if(numero_info(info_cadena(cursor, cad)) > numero_info(info_cadena(siguiente(cursor, cad), cad))) {
                intercambiar(cursor, siguiente(cursor, cad), cad);
                reordenar = true;
            }
            cursor = siguiente(cursor, cad);
        }
    }
}

void cambiar_todos(int original, int nuevo, cadena_t &cad) {
    localizador_t cursor = inicio_cadena(cad);

    while(es_localizador(cursor)) {
        if(numero_info(info_cadena(cursor, cad)) == original) {
            info_t info = info_cadena(cursor, cad); 
            
            char *frase = new char[strlen(frase_info(info)) + 1];
            strcpy(frase, frase_info(info));
            
            liberar_info(info);
            
            cambiar_en_cadena(crear_info(nuevo, frase), cursor, cad);
        }
        cursor = siguiente(cursor, cad);
    }
}

cadena_t subcadena(int menor, int mayor, cadena_t cad) {
    assert(esta_ordenada(cad) && pertenece(menor, cad) && pertenece(mayor, cad));
    
    cadena_t cadena = crear_cadena();
    localizador_t cursor = inicio_cadena(cad);
    
    while(es_localizador(cursor) && numero_info(info_cadena(cursor, cad)) <= mayor) {
        if(menor <= numero_info(info_cadena(cursor, cad))) 
            insertar_al_final(copia_info(info_cadena(cursor, cad)), cadena);
        cursor = siguiente(cursor, cad);
    }
    
    return cadena;
}
