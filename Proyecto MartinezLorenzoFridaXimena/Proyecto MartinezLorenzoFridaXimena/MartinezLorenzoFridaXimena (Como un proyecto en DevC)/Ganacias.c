#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"


//GANANCIAS

void listarGanancias(GananciaPtr ganancias){ 
    int i=1;
    GananciaPtr actual; 
    actual = ganancias; 
    system("cls");
    printf("Listado de las ganancias obtenidas por la venta de productos:\n\n");
    while(actual != NULL){ 
        printf(" %d. ID: %d\n", i, actual->informacion.idGanancia);
        printf("     Fecha: %s\n", actual->informacion.fecha);
        printf("     Hora: %s\n", actual->informacion.hora);
        printf("     Ganancias: %.2f\n\n", actual->informacion.ganancia);
        actual = actual->sig;
        i++;
    }
    printf("FIN DEL LISTADO DE LAS GANANCIAS TOTALES\n");
}

void consultarGananDia(GananciaPtr ganancias, char fecha[]){ 
    int i=1;
    GananciaPtr actual, encontrado;
    encontrado = ganancias; 
    while(encontrado != NULL && strcmp(encontrado->informacion.fecha, fecha) != 0) 
        encontrado = encontrado->sig;    
    if(encontrado == NULL) 
        printf("No existen registros de ganancias en esa fecha, intentelo de nuevo\n");
    else{ 
        actual = encontrado; 
        printf("Listado de las ganancias obtenidas el '%s':\n\n", fecha);
        while(actual != NULL){ 
            if(strcmp(actual->informacion.fecha, fecha) == 0){   
                printf(" %d. ID: %d\n", i, actual->informacion.idGanancia);
                printf("     Fecha: %s\n", actual->informacion.fecha);
                printf("     Hora: %s\n", actual->informacion.hora);
                printf("     Ganancias: %.2f\n\n", actual->informacion.ganancia);
                i++;
            }
            actual = actual->sig; 
        }
        printf("Fin del listado de ganancias\n");
    }        
}
