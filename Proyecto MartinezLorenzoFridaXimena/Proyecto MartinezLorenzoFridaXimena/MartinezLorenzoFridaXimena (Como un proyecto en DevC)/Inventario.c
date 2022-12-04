#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"


//INVENTARIO FUNCIONES 


void AltaProd(InventarioPtr *inventario){ 
    int siAgregar, siDatos, i=1, c; // siDatos = validación de si los datos introducidos por el usuario son correctos o no
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\t\tBienvenido al apartado ALTA DE PRODUCTOS\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    do{
        InventarioPtr newProd; 
        newProd=(InventarioPtr)malloc(sizeof(Inventario)); 
        siAgregar=1; 
        printf("\nIngrese el ID del producto: ");
        scanf("%d", &newProd->producto.id);  
        fflush(stdin);
        printf("\nIngrese el nombre del producto: ");
        scanf("%[^\n]", newProd->producto.nombre); 
        fflush(stdin);
        printf("\nIngrese el precio de compra: ");
        scanf("%f", &newProd->producto.precioC);
        fflush(stdin);
        printf("\nIngrese el precio de venta: ");
        scanf("%f", &newProd->producto.precioV);
        fflush(stdin);
        printf("\nIngrese la cantidad de piezas en stock: ");
        scanf("%d", &newProd->producto.cant); 
		printf("\n"); 
        fflush(stdin);
        newProd->sig = NULL; 
        siDatos = PushInventarioNew(inventario, newProd); 
        if(siDatos){ //Si se agregó correctamente el producto y sus datos
            printf("\nProducto agregado al inventario correctamente\n");
            system("pause");
            do{ 
                system("cls");
                printf("¿Desea registrar mas productos en el inventario? Si=1 / No=0: ");
                if(scanf("%d", &siAgregar) != 1){ 
                    siAgregar= -1;
                    printf("Ingrese una opcion correcta\n");
                    system("pause");
                    c=getchar();
                    while (c != '\n');
                }
                if(siAgregar == 1)
                    system("cls"); 
            }while(siAgregar < 0 || siAgregar > 1);
        } else { 
            printf("\nFavor de ingresar los datos del producto a registrar correctamente\n");
            system("pause");
            system("cls");
        }
    } while(siAgregar);   
}
//___________________________________________________________________________________________________________

int PushInventarioNew(InventarioPtr *inventario, InventarioPtr newProd){ //1 ÉXITO / 0 SIN ÉXITO
    int noNuevo=0, inBien=0; 
    InventarioPtr temp, anterior, actual; 
    if(*inventario == NULL){ 
        *inventario=newProd;
        inBien++;
    } else {     
        temp = *inventario;
        while(temp != NULL){ 
            if(newProd->producto.id == temp->producto.id){  
                noNuevo++; 
                break;
            } else 
                temp = temp->sig;
        }
        if(noNuevo) 
            perror("ERROR\n El ID del producto introducido ya existe en el sistema\n");
        else {
            anterior=NULL; 
            actual =*inventario; 
            while(actual != NULL && newProd->producto.id > actual->producto.id){ 
                anterior=actual; 
                actual=actual->sig; 
            } 
            if(anterior==NULL){ 
                newProd->sig = *inventario;
                *inventario=newProd;
            } else {
                anterior->sig = newProd;
                newProd->sig = actual;
            }    
            inBien++; 
        }
    }
    return inBien;
}
//___________________________________________________________________________________________________________

void BajaProd(InventarioPtr *inventario){ 
    int idProd; 
    InventarioPtr temporal, anterior, actual; 
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBienvenido al apartado BAJA DE PRODUCTOS\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    printf("Ingrese el ID del producto que desee eliminar del inventario: ");
    scanf("%d", &idProd); printf("\n"); 
    temporal = *inventario; 
    if(temporal->producto.id == idProd){ 
        *inventario = (*inventario)->sig;
        printf("Producto '%s' eliminado del inventario correctamente\n", temporal->producto.nombre);
        free(temporal); 
    } else { 
        anterior = *inventario; 
        actual = (*inventario)->sig; 
        while(actual != NULL && actual->producto.id != idProd){ 
            anterior = actual; 
            actual = actual->sig; 
        }
        if(actual != NULL){ 
            temporal = actual; 
            anterior->sig = actual->sig; 
            printf("Producto '%s' eliminado del inventario correctamente\n", temporal->producto.nombre); 
            free(temporal); 
        } else 
            printf("El ID introducido no fue encontrado en el inventario de productos,\n Intentelo de nuevo\n");
    }            
}
//___________________________________________________________________________________________________________

void ActualizarProd(InventarioPtr *inventario){ 

    int idProd, eleccion; //eleecion: guarda lo que seleciono el usuario a modificar 
    InventarioPtr temporal; 
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBienvenido al apartado ACTUALIZAR DATOS DE PRODUCTO\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    printf("\n\nIntroduce el ID del producto que desee modificar: ");
    scanf("%d", &idProd); 
	printf("\n"); 
    temporal = *inventario; 
    
    while(temporal != NULL && temporal->producto.id != idProd) 
        temporal=temporal->sig; 
    if(temporal == NULL) 
        printf("El ID introducido no fue encontrado en el inventario de productos \n Intentelo de nuevo\n");    
    else{ 
		system("cls");
    	printf("______________________________________________________________________________________________\n");
        printf("\n\t\tDatos del producto que pueden ser modificados: \n");
    	printf("______________________________________________________________________________________________\n\n");
        printf("1. Nombre\n2. Precio de compra\n3. Precio de venta\n4. Cantidad de piezas disponibles\n");
        printf("\n\nNOTA: El ID del producto no puede ser modificado\n OPC:");
        scanf("%d", &eleccion); 
        printf("\n");
        
        while(eleccion < 1 || eleccion > 4){ 
            system("cls");
            printf("Ingrese una opcion correcta \n");
            printf("1. Nombre\n2. Precio de compra\n3. Precio de venta\n4. Cantidad de piezas disponibles\n");
            printf("Nota: El ID del producto no puede ser modificado\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &eleccion); 
			printf("\n");
        }
        switch(eleccion){ 
            case 1: //modificar el nombre
                fflush(stdin);
                temporal->producto.nombre[0]='\0'; 
                printf("Ingrese el nombre con el que quiere actualizar el producto: ");
                scanf("%[^\n]", temporal->producto.nombre); 
				printf("\n");
                break;
            case 2: //modificar el precio de compra
                fflush(stdin);
                printf("Ingrese la cantidad con la que quiere remplazar el precio de compra: ");
                scanf("%f", &temporal->producto.precioC); 
				printf("\n");
                break;
            case 3: //modificar el precio de venta
                fflush(stdin);
                printf("Ingrese la cantidad con la que quiere remplazar el precio de venta: ");
                scanf("%f", &temporal->producto.precioV);
			    printf("\n");
                break;
            case 4: //modificar la cantidad de piezas en stock
                fflush(stdin);
                printf("Introduce el valor con la que quiere reemplazar la cantidad de productos en existencia: ");
                scanf("%d", &temporal->producto.cant); 
				printf("\n");
                break;
            default:
                printf("No elegiste una opcion valida\n");                
        }
        printf("El cambio en la informacion del producto se realizo correctamente\n");
    }
}
//___________________________________________________________________________________________________________
void ListarProd(InventarioPtr inventario){ 
    int i=1;
    InventarioPtr temporal; 
    temporal = inventario;
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tProductos registrados en el inventario: \n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    while(temporal != NULL){ 
        printf("%d. ID: %d\n Nombre: %s\n Precio Compra: %.2f\t Precio Venta: %.2f\n %d pieza(s) restante(s)\n\n", i, temporal->producto.id, temporal->producto.nombre, temporal->producto.precioC, temporal->producto.precioV, temporal->producto.cant);
        temporal = temporal->sig; 
        i++;
    }
    printf("\nFIN DEL INVENTARIO\n");
}


