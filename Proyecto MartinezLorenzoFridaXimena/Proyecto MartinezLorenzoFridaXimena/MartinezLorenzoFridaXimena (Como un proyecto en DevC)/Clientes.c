#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"


//CLIENTES 

void AltaClientes(CarteraCliPtr *cartera){ 
    int siAgregar, siBien, c; 
    system("cls");  
	printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBienvenido al apartado ALTA DE CLIENTES\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    do{ 
        siAgregar=1; // es igual a '1' en caso de que surja algún error en la insersión de los datos
        CarteraCliPtr clienteNew; 
        clienteNew = (CarteraCliPtr)malloc(sizeof(CarteraC));
        printf("Introduce el ID del nuevo cliente: ");
        scanf("%d", &clienteNew->cliente.id); printf("\n"); 
        fflush(stdin);
        printf("Introduce el nombre del nuevo cliente: ");
        scanf("%[^\n]", clienteNew->cliente.nombre); printf("\n"); 
        fflush(stdin);
        printf("Introduce el numero de telefono del nuevo cliente: ");
        scanf("%[^\n]", clienteNew->cliente.telefono); printf("\n");
        fflush(stdin);
        clienteNew->sig = NULL; 
        siBien = PushClienteNew(cartera, clienteNew); 
        if(siBien){ 
            printf("Cliente agregado a la cartera correctamente\n");
            system("pause");
            do{ 
                system("cls");
                printf("�Desea agregar mas clientes a la cartera? Si=1 / No=0: ");
                if(scanf("%d", &siAgregar) != 1){
                    siAgregar= -1; 
                    printf("Ingrese una opcion correcta\n");
                    system("pause");
                    c=getchar();
                    while (c != '\n'); 
                }
                if(siAgregar == 1)
                    system("cls"); 
            } while(siAgregar < 0 || siAgregar > 1);
        } else { 
            printf("Datos del cliente ingresados correctamente\n");
            system("pause");
            system("cls");
        }
    } while(siAgregar); 
}
//__________________________________________________________________________________________________________________

int PushClienteNew(CarteraCliPtr *cartera, CarteraCliPtr clienteNew){ 
    int noNuevo=0, inBien=0; 
    CarteraCliPtr temp, anterior, actual;  
    if(*cartera == NULL){ 
        *cartera = clienteNew; 
        inBien++; 
    } else {     
        temp = *cartera;
        while(temp != NULL){ 
            if(clienteNew->cliente.id == temp->cliente.id){ 
                noNuevo++;
                break;
            } else 
                temp = temp->sig;
        }
        if(noNuevo) 
            perror("ERROR\n el ID del cliente introducido ya existe en el sistema\n");
        else { 
            anterior = NULL;
            actual = *cartera; 
            while(actual != NULL && clienteNew->cliente.id > actual->cliente.id){
                anterior = actual;
                actual = actual->sig; 
            } 
            if(anterior == NULL){ 
                clienteNew->sig = *cartera;
                *cartera = clienteNew; 
            } else { 
                anterior->sig = clienteNew;
                clienteNew->sig = actual; 
            }    
            inBien++;
        }
    }

    return inBien;    
}
//____________________________________________________________________________________________________________________

void BajaCliente(CarteraCliPtr *cartera){ 
    int idCliente;
    CarteraCliPtr temporal, actual, anterior;
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBIENVENIDO AL APARTADO BAJA DE CLIENTES\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    printf("Ingresa el ID del cliente a dar de baja del sistema: ");
    scanf("%d", &idCliente); 
	printf("\n"); 
    temporal = *cartera; 
    if(temporal->cliente.id == idCliente){ 
        *cartera = (*cartera)->sig; 
        printf("El cliente '%s' fue eliminado del sistema satisfactoriamente\n", temporal->cliente.nombre);
        free(temporal);
    } else { 
        anterior = *cartera; 
        actual = (*cartera)->sig; 
        while(actual != NULL && actual->cliente.id != idCliente){ 
            anterior = actual; 
            actual = actual->sig; 
        }
        if(actual != NULL){ //si se encontró al cliente, se elimina
            temporal = actual;
            anterior->sig = actual->sig;
            printf("El cliente '%s' fue eliminado del sistema satisfactoriamente\n", temporal->cliente.nombre);
            free(temporal);
        } else //si no se encontro al cliente
            printf("El ID del cliente introducido no fue encontrado en la cartera de clientes, int%cntelo de nuevo\n", 130);
    }
}
//__________________________________________________________________________________________________________________

void ActualizarCliente(CarteraCliPtr *cartera){ //la función recibe la cartera de clientes y actualiza el dato indicado del cliente proporcionado
    int idCliente, eleccion;
    CarteraCliPtr temporal;
    system("cls");
	printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBIENVENIDO AL APARTADO ACTUALIZAR DATOS DE CLIENTE\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    printf("\nIngresa el ID del cliente a actualizar sus datos: ");
    scanf("%d", &idCliente); 
	printf("\n");
    temporal = *cartera; 
    while(temporal != NULL && temporal->cliente.id != idCliente) 
        temporal = temporal->sig; 
    if(temporal == NULL) 
        printf("El ID introducido no esta asociado a ningun cliente en la cartera, intentelo de nuevo\n");
    else{
        printf("Datos del cliente que pueden ser modificados: \n");
        printf("1. Nombre del cliente\n2. Numero telefonico\n");
        printf("\n\nNota: el ID del cliente no puede ser modificado\n OPC: ");
        scanf("%d", &eleccion); 
		printf("\n"); 
        while(eleccion < 1 || eleccion > 2){ 
            system("cls");
            printf("ingrese una opcion correcta \n");
            printf("1. Nombre del cliente\n2. Numero telefonico\n");
            printf("\n\nNota: el ID del cliente no puede ser modificado\n OPC: ");
            scanf("%d", &eleccion); printf("\n");
        }
        switch(eleccion){ 
            case 1: //modificar el nombre del cliente
                fflush(stdin);
                temporal->cliente.nombre[0]='\0';
                printf("Ingrese el nombre con el que quiere actualizar al cliente: ");
                scanf("%[^\n]", temporal->cliente.nombre); 
				printf("\n");
                break;
            case 2: //modificar el numero de telefono
                fflush(stdin);
                temporal->cliente.telefono[0]='\0';
                printf("Ingrese el numero telefonico con el que se quiere actualizar al cliente: ");
                scanf("%[^\n]", temporal->cliente.telefono);
			    printf("\n");
                break;
            default:
                printf("No elegiste una opcion correcta\n");                
        }
        printf("\nActualizacion del cliente se realizo correctamente\n");
    }        
}
//___________________________________________________________________________________________________

void ListarClientes(CarteraCliPtr cartera){ 
    int i=1;
    CarteraCliPtr temporal;
    temporal = cartera;
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\n\t\tLISTADO DE LA CARTERA DE CLIENTES \n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    while(temporal != NULL){ 
        printf("%d. ID: %d\nNombre: %s\nTelefono: %s\n\n", i, temporal->cliente.id, temporal->cliente.nombre, temporal->cliente.telefono);
        temporal = temporal->sig; 
        i++;
    }
    printf("\nFIN DE LA CARTERA DE CLIENTES\n");
}
