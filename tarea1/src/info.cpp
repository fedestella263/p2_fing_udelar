/*
    Módulo de implementación de `info_t`.
    
    Se implementa struct rep_info como un registro
    con dos campos, uno numérico y otro de texto.
    
    Laboratorio de Programación 2.
    InCo-FIng-UDELAR
*/

#include "../include/info.h"

#include <string.h>
#include <stdio.h>
#include <limits.h>

struct rep_info {
    int num;
    
    // Arreglo cuyo tamaño se determina en tiempo de ejecución.
    char *frase;
};

info_t crear_info(int num, char *frase) {
    info_t nueva = new rep_info;
    
    nueva->num = num;
    nueva->frase = frase; // Comparte memoria con el parámetro.
    
    return nueva;
} 

info_t copia_info(info_t info) {
    info_t copia = new rep_info;
    
    copia->num = info->num;
    
    // Se reserva memoria y se copia el contenido del parámetro.
    copia->frase = new char[strlen(info->frase)+1];
    strcpy(copia->frase, info->frase);
    
    return copia;
}

void liberar_info(info_t &info) {
    delete[] info->frase; // Se libera la memoria del arreglo.
    delete info;
}

int numero_info(info_t info) {
    return info->num;
}

char *frase_info(info_t info) {
    return info->frase;
}

bool son_iguales(info_t i1, info_t i2) {
    // Si las dos frases son iguales retorna 0, y luego compara los numeros.
    return (strcmp(i1->frase, i2->frase) == 0 && i1->num == i2->num);
}

bool es_valida_info(info_t info) {
    // Valida que el campo num no supere el maximo para int.
    return (info->num != INT_MAX);
}

char *info_a_texto(info_t info) {
    char copia_num[11];
    
    sprintf(copia_num, "%d", info->num);
    char *texto = new char[strlen(copia_num) + strlen(info->frase) + 4]; // Reserva la memoria necesaria para la cadena.
    
    strcpy(texto, "(");
    strcat(texto, copia_num);
    strcat(texto, ",");
    strcat(texto, info->frase);
    strcat(texto, ")");
    
    return texto;
}

info_t leer_info(int max) {
    info_t leido;
    int num;
    char *cadena = new char[max + 1];
    char simbolo;
    bool error = false;
    
    scanf(" %c", &simbolo);
    
    // Lee la información de la consola y valida que sea correcta.
    if(simbolo != '(')
        error = true;
    else {
        scanf("%d", &num);
        scanf(" %c", &simbolo);
        
        if(simbolo != ',')
            error = true;
        else {
            int pos = 0;
            int c = getchar();
            
            while((c != ')' && (c != '\n'))) {
                cadena[pos] = c;
                pos++;
                c = getchar();
            }
            cadena[pos] = '\0';
            
            if(c == '\n') {
                error = true;
                ungetc('\n', stdin);
            }
        }
    }
    
    // Si ocurrio un error retorna una estructura info por defecto.
    if(error) {
        char *nulo = new char[1];
        nulo[0] = '\0';
        leido = crear_info(INT_MAX, nulo);
    } else {
        char *frase = new char[strlen(cadena) + 1];
        strcpy(frase, cadena);
        leido = crear_info(num, frase);
    }
    
    // Libera la cadena y retorna la estructura info ingresada.
    delete[] cadena;
    return leido;
}

info_t combinar_info(info_t i1, info_t i2) {
    // Reserva memoria necesaria para la frase.
    char *frase = new char[strlen(i1->frase) + strlen(i2->frase) + 1];
    
    // Concatena las dos frases.
    strcpy(frase, i1->frase);
    strcat(frase, i2->frase);
    
    // Retorna la recien creada estructura info.
    return crear_info(i1->num + i2->num, frase);
}