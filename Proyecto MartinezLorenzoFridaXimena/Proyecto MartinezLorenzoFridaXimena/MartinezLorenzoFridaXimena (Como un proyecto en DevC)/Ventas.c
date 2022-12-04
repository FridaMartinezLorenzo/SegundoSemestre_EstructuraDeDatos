#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "mis_librerias.h"


//GESTION DE VENTAS (EL INTENTO) :c

void insertarEnCola(ColaPtr cola, InventarioPtr inv, CarteraCliPtr carteraC){
    int idCliente, idProducto, siCompra, c, yaEnCola;
    CarteraCliPtr clienteDatos;  
    InventarioPtr datosProd;
    NodoPtr nuevo, encontrado;
    nuevo=(NodoPtr) malloc(sizeof(NodoCola));
    if(nuevo == NULL)
        printf("No hay memoria disponible en el sistema\n");
        else { 
            do{ 
                system("cls");
                printf("______________________________________________________________________________________________\n");
				printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
                printf("\n\t\tAPARTADO DE SELECCION DE PRODUCTOS E INGRESO EN LA COLA\n");
				printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
  				printf("______________________________________________________________________________________________\n\n");
                ListarClientes(carteraC);
                printf("Ingrese su ID con el que esta registrado en el sistema: "); 
                scanf("%d", &idCliente); printf("\n");
                clienteDatos=buscarCliente(carteraC, idCliente); 
                if(clienteDatos != NULL){     
                    encontrado=cola->ini;
                    while(encontrado != NULL && encontrado->cliente.id != clienteDatos->cliente.id)
                        encontrado=encontrado->sig;
                    if(encontrado != NULL && encontrado->cliente.id == clienteDatos->cliente.id){ 
                        printf("El cliente seleccionado ya se encuentra en la cola de cobro \n Intetelo de nuevo\n");
                        yaEnCola=1;
                    } else {
                        printf("Bienvenido de nuevo, %s \n\n", clienteDatos->cliente.nombre);  
                        yaEnCola = 0;
                    }    
                } else 
                    yaEnCola = 1;
                system("pause");            
            } while(yaEnCola == 1);
            nuevo->cliente = clienteDatos->cliente; 
            nuevo->CarritoProd = NULL; 
            nuevo->sig = NULL;  
            do{
                siCompra = 0; 
                do{ 
                    system("cls");
                    printf("¿Que producto desea agregar a su carrito de compras? \n\n");
                    imprimirInventario(inv); 
                    printf("Ingrese el ID del producto: ");
                    scanf("%d", &idProducto); 
					printf("\n");
                    datosProd = datosProducto(inv, idProducto); 
                    if(datosProd == NULL){
                        printf("Â¡ERROR! \nEl ID introducido no se encontro en el inventario, intentelo de nuevo\n");
                        system("pause");
                        system("cls");
                    }    
                } while(datosProd == NULL);    
                pushCarritoComp(&nuevo->CarritoProd, datosProd); 
                do{ 
                    system("cls");
                    printf("Â¿Desea agregar mas productos a su carrito de compras? Si = 1 / No = 0: ");
                    if(scanf("%d", &siCompra) != 1){ 
                        siCompra=-1;
                        printf("Ingrese una opcion correcta\n");
                        system("pause");
                        c = getchar();
                        while (c != '\n'); 
                    }
                } while(siCompra < 0 || siCompra > 1);
                if(siCompra == 1 && verificaStock(inv) == 0){ 
                    system("cls");
                    printf("Todos los productos se han agotado, no es posible agregar mas productos\n");
                    siCompra = 0;
                }                
            } while(siCompra); 
            if(cola->ini == NULL) 
                cola->ini = nuevo;
            else
                cola->fin->sig = nuevo;
            cola->fin = nuevo; 
            printf("Ingreso del cliente '%s' en la cola de cobro satisfactoriamente\n", cola->fin->cliente.nombre);       
        }    
}
//_____________________________________________________________________________________________-

int verificaStock(InventarioPtr inventario){ 
    int verifica=0;
    InventarioPtr temporal;
    temporal = inventario;
    while(temporal != NULL){
        if(temporal->producto.cant > 0) 
            verifica++;
        temporal = temporal->sig;    
    }

    return verifica;
}
//___________________________________________________________________________________

CarteraCliPtr buscarCliente(CarteraCliPtr carteraC, int id){ 
    CarteraCliPtr temp; 
    temp =carteraC;
    while(temp != NULL && temp->cliente.id != id) 
        temp = temp->sig;    

    if(temp == NULL) 
        printf("El ID introducido no existe en la cartera, intentelo de nuevo\n");

    return temp;
}

//________________________________________________________________________________________

void imprimirInventario(InventarioPtr inventario){ 
    InventarioPtr temp; 
    temp = inventario; 
    int i=1;
    while(temp != NULL){ 
        if(temp->producto.cant != 0){         
            printf("%d. %s \n", i, temp->producto.nombre); 
            printf("    ID del producto: %d\n", temp->producto.id); 
            printf("    Cantidad disponible: %d unidad(es)\n", temp->producto.cant); 
            printf("    Precio unitario: $%.2f\n\n", temp->producto.precioV); 
            i++;
        }
        temp = temp->sig; 
    }
    if(i == 1)
        printf("No hay productos disponibles por el momento, intentelo mas tarde\n");
    else
        printf("NOTA: Algunos productos pueden no ser mostrados debido a la falta de stock\n");    
}

//____________________________________________________________________________________________________________________________________________________

InventarioPtr datosProducto(InventarioPtr inventario, int idProducto){ 
    InventarioPtr temp; 
    temp = inventario; 
    while(temp != NULL && temp->producto.id != idProducto)
        temp = temp->sig;    

    return temp;
}

//__________________________________________________________________________________________________________________________________________________


void pushCarritoComp(InventarioPtr *carritoComp, InventarioPtr productoSe){ 
    int cant;
    InventarioPtr nuevo, encontrado;
    printf("Ingrese la cantidad de piezas que desee comprar de '%s', %d disponible(s): ", productoSe->producto.nombre, productoSe->producto.cant); 
    scanf("%d", &cant); printf("\n"); 
    while(cant < 1 || cant > productoSe->producto.cant){
        system("cls");
        printf("Ingrese una cantidad dentro del rango de existencia en stock, %d disponible(s): ", productoSe->producto.cant);
        scanf("%d", &cant);
	    printf("\n");            
    }
    encontrado = *carritoComp;
    while(encontrado != NULL && encontrado->producto.id != productoSe->producto.id) 
        encontrado = encontrado->sig;
    
    if(encontrado != NULL){
        encontrado->producto.cant = encontrado->producto.cant + cant;
        productoSe->producto.cant = productoSe->producto.cant - cant;
    } else {
        nuevo = (InventarioPtr) malloc(sizeof(Inventario));
        if(nuevo == NULL)
            printf("No hay memoria disponible para copiar los datos\n");
        else { 
            nuevo->producto = productoSe->producto; 
            nuevo->producto.cant = cant;
            productoSe->producto.cant = productoSe->producto.cant - cant; 
            nuevo->sig = NULL;
            if(*carritoComp == NULL)
                *carritoComp = nuevo;
            else{     
                nuevo->sig = *carritoComp;
                *carritoComp = nuevo;
            }
        }
    }
    printf("\nProducto(s) agregado(s) satisfactoriamente al carrito de compras\n");
    system("pause");    
}

//_____________________________________________________________________________________________________________________________________________________

void listarColaClientes(ColaPtr cola){
    int i=1;
    NodoPtr clientes; 
    InventarioPtr productos;
    clientes = cola->ini; 
    system("cls");
    printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tLISTADO DE CLIENTES ACTUALES EN LA COLA\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
  	printf("______________________________________________________________________________________________\n\n");
    while(clientes != NULL){ 
        printf("%d. ID: %d\n Nombre: %s\n Carrito de compras: \n\n", i, clientes->cliente.id, clientes->cliente.nombre); 
        recorrerCarrito(&clientes->CarritoProd);
        clientes = clientes->sig; 
        i++;
    }
    printf("FIN DE LA COLA\n");
}

//______________________________________________________________________________________________________________________________________________________


void recorrerCarrito(InventarioPtr *carrito){ 
    InventarioPtr temp1, temporal = NULL;
    while(*carrito != NULL){
        temp1 = *carrito;
        InventarioPtr actual;
        actual = (InventarioPtr) malloc(sizeof(Inventario));
        printf("     |  ID: %d\n     |  Producto: %s\n     |  Cantidad: %d pieza(s)\n\n", temp1->producto.id, temp1->producto.nombre, temp1->producto.cant);
        actual->producto = temp1->producto;
        actual->sig = temporal;
        temporal = actual;               
        *carrito = (*carrito)->sig;
        free(temp1);
    }
    while(temporal != NULL){
        temp1 = temporal;
        InventarioPtr original;
        original = (InventarioPtr) malloc(sizeof(Inventario));
        original->producto = temp1->producto;
        original->sig = *carrito;
        *carrito = original;
        temporal = temporal->sig;
        free(temp1);
    }
}

//________________________________________________________________________________________________________________________________________________

void atenderCliente(ColaPtr cola, GananciaPtr *ganancias){ 
    float ingresoT; 
    NodoPtr actual; 
    actual = cola->ini; 
    system("cls");
    printf("______________________________________________________________________________________________\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tAPARTADO ATENDER AL CLIENTE\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
  	printf("______________________________________________________________________________________________\n\n");
    printf("Bienvenido a la caja de cobro, %s\n", actual->cliente.nombre);
    ingresoT = calcularGanancia(actual->CarritoProd); 
    actual->total = ingresoT;
    printf("Total a pagar por los productos en su carrito de compras: $%.2f\n", ingresoT);
    printf("Ingrese la cantidad ($) con la que desea pagar: ");
	 //se obtiene la cantidad con la que el cliente pagarÃ¡ sus productos
    scanf("%f", &actual->efectivo);
    while(actual->efectivo < ingresoT){
        system("cls");
        printf("Digite una cantidad correcta de dinero, por favor\n");
        printf("Total a pagar por los productos en su carrito de compras: $%.2f\n", ingresoT);
        printf("Ingrese la cantidad ($) con la que desea pagar: ");
        scanf("%f", &actual->efectivo);
    }
     //se imprime el ticket de compra
    imprimirTicket(ingresoT, actual->CarritoProd, actual->efectivo);
    registrarGanancia(ganancias, ingresoT); 
    if(cola->ini == cola->fin) 
        cola->fin = actual->sig;
    cola->ini = actual->sig;
    free(actual); 
    printf("El cliente ha salido de la cola exitosamente\n");    
}

//_____________________________________________________________________________________________________________________________________________

float calcularGanancia(InventarioPtr carritoProd){ 
    float ganaciaUni, ingresoT = 0;
    while(carritoProd != NULL){ 
        ganaciaUni = carritoProd->producto.precioV * (float)carritoProd->producto.cant; 
        ingresoT += ganaciaUni;
        carritoProd = carritoProd->sig; 
    }

    return ingresoT;
}

//____________________________________________________________________________________________________________________________________________

void obtenerFecha(GananciaPtr ganancias){ 
    time_t tiempo = time(0);
    struct tm *fecha = localtime(&tiempo);
    char fechaAc[20], horaAc[20];
    strftime(fechaAc, 20, "%d/%m/%Y", fecha);
    strftime(horaAc, 20, "%H:%M:%S", fecha);
    strcpy(ganancias->informacion.fecha, fechaAc);
    strcpy(ganancias->informacion.hora, horaAc);
}

//______________________________________________________________________________________________________________________________________________

void registrarGanancia(GananciaPtr *ganancias, float ingreso){ 
    GananciaPtr registro; 
    registro = (GananciaPtr) malloc(sizeof(Ganancia));
    if(registro == NULL)
        printf("No hay memoria disponible\n");
    else{
        registro->informacion.ganancia = ingreso; 
        if(*ganancias == NULL) 
            registro->informacion.idGanancia=1;
        else
            registro->informacion.idGanancia = (*ganancias)->informacion.idGanancia+1;
        obtenerFecha(registro); 
        registro->sig = NULL;
        if(*ganancias == NULL) 
            *ganancias = registro;
        else{
            registro->sig = *ganancias;
            *ganancias = registro;
        }    
    }    
}
//_________________________________________________________________________________________________________________________________________________

void imprimirTicket(float ingreso, InventarioPtr carritoProd, float efectivo){ 
    float total, cambio = 0;
    if(ingreso < efectivo) 
        cambio = efectivo - ingreso;
    system("cls");      
    printf("\n______________________________________________________________________________________________");
    printf("\n\t\t SUPERMERCADO '1 2 3' \n");
    printf("\n______________________________________________________________________________________________");
    printf("\n\n\t\tSu ticket de compra                                      \n\n");
    printf("\tidProducto    Nombre                          Cantidad    Precio Unitario    Total por Producto\n");
    while(carritoProd != NULL){ 
        total = carritoProd->producto.precioV * (float)carritoProd->producto.cant;     
        printf("%-*d%-*s%*d    %*.2f    %*.2f\n", 14, carritoProd->producto.id, 32, carritoProd->producto.nombre,8, carritoProd->producto.cant, 15, carritoProd->producto.precioV, 18, total); 
        carritoProd = carritoProd->sig;       
    }
    printf("\nTotal a pagar: .2f\n", ingreso);
    printf("Su pago: .2f\n", efectivo);
    printf("Su cambio: .2f\n", cambio);
    printf("                                ¡Gracias por su compra! Vuelva pronto:)                                    \n" );
    printf("                                    Le atendio: Frida Martinez                                   \n");
    printf("        							 Agradecemos su preferencia         \n\n");
}
