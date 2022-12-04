#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"

//FUNCIONES CON RESPECTO A LOS ARCHIVOS 

int GuardarInventario(InventarioPtr* inventario){

    FILE * archivo = fopen("Inventario.dat", "wb");
    InventarioPtr actual;
    int contador=0;
    if( archivo == NULL)
        perror("\nError al abrir el archivo 'Inventario' \n");
    else{
        while( *inventario != NULL){
            actual=*inventario;
            fwrite(&(actual->producto), sizeof(Producto), 1, archivo);
            *inventario = (*inventario)->sig;
            free(actual);
            contador++;
        }
        printf("\nINVENTARIO CARGADO CORRECTAMENTE \n");
    }
    fclose(archivo);

    return contador;
}

//_________________________________________________________________________________________________

int GuardarCartera(CarteraCliPtr *cartera){ 
    FILE * archivo= fopen("Clientes.dat", "wb");
    CarteraCliPtr actual;
    int contador=0;
    if(archivo == NULL)
        perror("\n Error al abrir el archivo 'Clientes'\n");
    else{
        while(*cartera != NULL){
            actual = *cartera;
            fwrite(&(actual->cliente), sizeof(Cliente), 1, archivo);
            *cartera = (*cartera)->sig;
            free(actual);
            contador++;
        }
        printf("\n CARTERA DE CLIENTES CORRECTAMENTE\n");
    }
    fclose(archivo);

    return contador;    
}

//_______________________________________________________________________________________________

int GuardarGanancias(GananciaPtr *ganancias){ 

    FILE *archivo= fopen("Ganancias.dat", "wb");
    GananciaPtr actual;
    int contador=0;
    if(archivo == NULL)
        perror("\nError al abrir el archivo 'Ganancias'\n");
    else{
        while(*ganancias != NULL){
            actual = *ganancias;
            fwrite(&(actual->informacion), sizeof(datosG), 1, archivo);
            *ganancias = (*ganancias)->sig;
            free(actual);
            contador++;
        }
        printf("\nREPORTE DE GANANCIAS GUARDADO CORRECTAMENTE\n");
    }
    fclose(archivo);

    return contador;    
}
//_______________________________________________________________________________________________________

//Guarda la cantidad de datos que existen en inventario, cartera y ganancias 

void GuardarCont(int cont1, int cont2, int cont3){ 
    FILE *archivo=fopen("contadores.dat", "wb");
    if(archivo == NULL)
       perror("\nError al abrir el archivo 'Contadores'\n");
    else{
        fwrite(&cont1,sizeof(int),1,archivo);
        fwrite(&cont2,sizeof(int),1,archivo);
        fwrite(&cont3,sizeof(int),1,archivo);
        printf("\nCANTIDAD DE PRODUCTOS TOTALES GUARDADOS CORRECTAMENTE\n");        
    }
    fclose(archivo);    
}
//___________________________________________________________________________________________________

void RestaurarCont(int *cont1, int *cont2, int *cont3){ 

    FILE *archivo= fopen("Contadores.dat", "rb");
    int cont, i;
    if(archivo == NULL)
        printf("\nNo existe el archivo 'Contadores'\n");
    else{  
        fread(&cont,sizeof(int),1,archivo);
        *cont1 =cont;
        fread(&cont,sizeof(int),1,archivo);
        *cont2 =cont;
        fread(&cont,sizeof(int),1,archivo);
        *cont3 =cont;
        printf("\nCANTIDAD DE PRODUCTOS RESTAURADOS\n");                        
    }
    fclose(archivo);    
}
//_______________________________________________________________________________________________________________

void RestaurarInv(InventarioPtr *inventario, int cantidad){ 

    FILE *archivo=fopen("Inventario.dat", "rb");
    InventarioPtr temp1, temporal = NULL;
    if(archivo == NULL)
        printf("\nNo existe el archivo 'Inventario' \n");
    else{
        while(cantidad){
            InventarioPtr actual;
            actual = (InventarioPtr) malloc(sizeof(Inventario));
            fread(&(actual->producto), sizeof(Producto), 1, archivo);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(archivo);
        while(temporal != NULL){
            InventarioPtr original;
            original = (InventarioPtr) malloc(sizeof(Inventario));
            temp1 = temporal;
            original->producto = temp1->producto;
            original->sig = *inventario;
            *inventario = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("\nINVENTARIO RESTAURADO CORRECTAMENTE\n");
    }    
}
//_______________________________________________________________________________________________________

void RestaurarCar(CarteraCliPtr *cartera, int cantidad){ 
    FILE *archivo= fopen("Clientes.dat", "rb");
    CarteraCliPtr temp1, temporal = NULL;
    if(archivo == NULL)
        printf("\nNo existe el archivo 'Clientes'\n");
    else{
        while(cantidad){
            CarteraCliPtr actual;
            actual = (CarteraCliPtr) malloc(sizeof(CarteraC));
            fread(&(actual->cliente), sizeof(Cliente), 1, archivo);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(archivo);
        while(temporal != NULL){
            CarteraCliPtr original;
            original = (CarteraCliPtr) malloc(sizeof(CarteraC));
            temp1 = temporal;
            original->cliente = temp1->cliente;
            original->sig = *cartera;
            *cartera = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("\nCARTERA DE CLIENTES RESTAURADOS CORRECTAMENTE\n");
    }     
}
//____________________________________________________________________________________________________________

void RestaurarGan(GananciaPtr *ganancias, int cantidad){ 
    FILE *archivo= fopen("Ganancias.dat", "rb");
    GananciaPtr temp1, temporal = NULL;
    if(archivo == NULL)
        printf("\nNo existe el archivo 'Ganancias'\n");
    else{
        while(cantidad){
            GananciaPtr actual;
            actual = (GananciaPtr) malloc(sizeof(Ganancia));
            fread(&(actual->informacion), sizeof(datosG), 1, archivo);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(archivo);
        while(temporal != NULL){
            GananciaPtr original;
            original = (GananciaPtr) malloc(sizeof(Ganancia));
            temp1 = temporal;
            original->informacion = temp1->informacion;
            original->sig = *ganancias;
            *ganancias = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("\nDATOS DE GANANCIAS RESTAURADOS CORRECTAMENTE\n");
    }    
}


