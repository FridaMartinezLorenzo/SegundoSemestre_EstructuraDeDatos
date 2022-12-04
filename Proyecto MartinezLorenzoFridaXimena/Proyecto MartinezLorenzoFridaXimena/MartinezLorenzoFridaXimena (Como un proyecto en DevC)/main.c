/****************************************************************************************

PROGRAMA QUE REALIZA LAS FUNCIONALIDADES BÁSICAS DEL SUPERMERCADO

Asignatura: ESTRUCTURA DE DATOS 

Autor: Frida Ximena Martinez Lorenzo

Fecha: 10/06/22

*****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"


//funcion principal
 main(){ 
    int opcion=0, verificador, c, dato;
    int contInv=0, contCar=0, contGan=0;
    char opcion2, fecha[20];
    InventarioPtr inventario = NULL;
    CarteraCliPtr cartera = NULL;
    Cola colaClientes = {NULL, NULL};
    GananciaPtr gananciasT = NULL;

    RestaurarCont(&contInv, &contCar, &contGan);
    RestaurarInv(&inventario, contInv);
    RestaurarCar(&cartera, contCar);
    RestaurarGan(&gananciasT, contGan);
    system("pause");
   do {

        //Ciclo del menu
        do {
            opcion = 0;
            verificador = MenuPrincipal(&opcion);
            if (verificador){
                printf("Ingrese una opcion correcta\n");
                system("pause");
                while ( (c = getchar()) != '\n' ){} 
            }

        } while (verificador);

        if(opcion < 1 || opcion > 5)
            opcion=0;

        switch (opcion){

            //Gestion de productos
            case 1:

                do{
                    system("cls"); 
                    printf("\n\n\tIntroduzca la letra del apartado al que desea acceder:\n");
                    printf("\n\t\t[A] Alta de productos\n");
					printf("\t\t[B] Baja de productos\n");
					printf("\t\t[C] Actualizar producto\n");
                    printf("\t\t[D] Listar Productos\n ");
                    printf("\t\t[E] Regresar\n\t\tOPC:");
                    scanf("%c",&opcion2);
                    opcion2=toupper(opcion2);
                }while(opcion2 != 'A' && opcion2 != 'B' && opcion2 != 'C' && opcion2 != 'D'&& opcion2 != 'E');
                switch (opcion2){
                    case 'A':
                        	 AltaProd(&inventario);
                        break;
                    
					case 'B':
                       		 if(inventario == NULL)
                         		   printf("Todavia no existen datos de productos para eliminar\n");
                       		 else    
                            	BajaProd(&inventario);
                        break;
                    
					case 'C':
                       			 if(inventario == NULL)
                           			 printf("Todavia no existen datos de productos para actualizar\n");
                        		else    
                            		ActualizarProd(&inventario);                        
                        break;
                    
					case 'D':
                    		    if(inventario == NULL)
                            		printf("Todavia no existen datos de productos para listar\n");
                        		else    
                            		ListarProd(inventario);                                                
                        break;
                    
                    case 'E': break;
                    
                    default:
                        printf("ESA OPCION NO SE ENCUENTRA EN EL MENU\n");                
                }       

                break;

            // Gestion de clientes 
            case 2:

                do{
                    system("cls"); 
                    printf("\n\n\tIntroduzca la letra del apartado al que desea acceder:\n");
                    printf("\n\t\t[A] Alta de clientes\n");
					printf("\t\t[B] Baja de clientes\n");
					printf("\t\t[C] Actualizar cliente\n");
                    printf("\t\t[D] Listar clientes\n ");
                    printf("\t\t[E] Regresar\n\t\tOPC:");
                   	scanf("%c",&opcion2);
                    opcion2=toupper(opcion2);
                }while(opcion2 != 'A' && opcion2 != 'B' && opcion2 != 'C' && opcion2 != 'D'&& opcion2 != 'E');
                switch (opcion2){
                    case 'A':
                        AltaClientes(&cartera);
                        break;
                    case 'B':
                        if(cartera == NULL)
                            printf("Todavia no existen datos de clientes para eliminar\n");
                        else    
                            BajaCliente(&cartera);
                        break;
                    case 'C':
                        if(cartera == NULL)
                            printf("Todavia no existen datos de clientes para actualizar\n");
                        else    
                            ActualizarCliente(&cartera);                        
                        break;
                    case 'D':
                        if(cartera == NULL)
                            printf("Todavica no existen datos de clientes para listar\n");
                        else{
                            system("cls");     
                            ListarClientes(cartera);
                        }                                                    
                        break;
                    case 'E': break;
                    
                    default:
                        printf("No elegiste una opcion valida\n");                
                } 

                break;

            // Gestion de ventas 
            case 3:

                do{
                    system("cls"); 
                    printf("\n\n\tIntroduzca la letra del apartado al que desea acceder:\n");
                    printf("\n\t\t[A] Insertar cliente en la cola de cobro\n");
					printf("\t\t[B] Listar la cola actual de clientes\n");
                    printf("\t\t[C] Atender al primer cliente en la cola\n ");
                    printf("\t\t[D] Regresar \n\t\t OPC: ");
                    scanf("%c",&opcion2);
                    opcion2=toupper(opcion2);
                }while(opcion2 != 'A' && opcion2 != 'B' && opcion2 != 'C'&& opcion2 != 'D');
                switch (opcion2){
                    case 'A':
                        if((inventario == NULL && cartera == NULL) || (inventario != NULL && cartera == NULL) ||
                           (inventario == NULL && cartera != NULL)){
                            printf("Todavia no puede realizarse la operacion, no hay productos o clientes registrados\n");
                        } else 
                            insertarEnCola(&colaClientes, inventario, cartera);
                        break;
                    case 'B':
                        if(colaClientes.ini == NULL)
                            printf("Todavia no hay clientes formados en la cola de cobro\n");
                        else    
                            listarColaClientes(&colaClientes);
                        break;
                    case 'C':
                        if(colaClientes.ini == NULL)
                            printf("No se puede atender, no existe ningun cliente en la cola\n");
                        else    
                            atenderCliente(&colaClientes, &gananciasT);                        
                        break;
                    
                    case 'D': break;
                    default:
                        printf("No elegiste una opcion valida\n");                
                } 

                break;

            //Gestion de ganancias
            case 4:

                do{
                    system("cls"); 
                    printf("\n\n\tIntroduzca la letra del apartado al que desea acceder:\n");
                    printf("\t\t[A] Listar las ganancias totales\n");
					printf("\t\t[B] Consultar ganancias por dia\n");
					printf("\t\t[C] Regresar \n\t\tOPC: ");
                    scanf("%c",&opcion2);
                    opcion2=toupper(opcion2);
                }while(opcion2 != 'A' && opcion2 != 'B'&& opcion2 != 'C');
                switch (opcion2){
                    case 'A':
                        if(gananciasT == NULL)
                            printf("Todavia no hay ganancias que reportar\n");
                        else 
                            listarGanancias(gananciasT);    
                        break;
                    case 'B':
                        if(gananciasT == NULL)
                            printf("Todavia no existen ganancias para consultar\n");
                        else{
                            fflush(stdin);
                            printf("Introduzca la fecha de la cual quiere consultar los registros, " 
                                   "en formato dd/mm/aaaa :\n");
                            scanf("%[^\n]", fecha);
                            system("cls");
                            consultarGananDia(gananciasT, fecha);     
                        }    
                        break;
                    
                    case 'C': break;
                    
                    default:
                        printf("No elegiste una opcion valida\n");                
                } 

                break;

            // Guardar y salir
            case 5:
                if(colaClientes.ini != NULL){ 
                    printf("No se puede salir del sistema, todavia quedan clientes en la cola de cobro\n");
                    opcion=0;
                } else {
                    printf("\n");
                    contInv = GuardarInventario(&inventario);
                    contCar = GuardarCartera(&cartera);
                    contGan = GuardarGanancias(&gananciasT);
                    GuardarCont(contInv, contCar, contGan);
                	exit(1);
                }    
                break;

            default:
                printf("No elegiste una opcion valida\n");
        }
        system("pause");
    } while (opcion!=5);

}

int MenuPrincipal(int * opcion){
	
    int verificar=0, c;
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBienvenido al supermercado '1 2 3'\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
	printf("\n\tEliga una opcion\n ");
    printf("\t\t1. Gestion de productos\n");
    printf("\t\t2. Gestion de clientes\n");
    printf("\t\t3. Gestion de ventas\n");
    printf("\t\t4. Gestion de ganancias\n");
    printf("\t\t5. Salir\n \t\tOPC:");
    
    if (scanf("%d", opcion) != 1){
        *opcion = 0;
        verificar++;
    }
    return verificar;
}
