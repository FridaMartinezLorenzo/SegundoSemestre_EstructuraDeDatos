
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


typedef struct{
    int id; 
    char nombre[30]; 
    float precioC; 
    float precioV; 
    int cant; //Stock
}Producto; 

typedef struct cliente{
    int id;
    char nombre[30]; 
    char telefono[15]; 
}Cliente; 

typedef struct inventario{
    Producto producto; 
    struct inventario *sig; 
}Inventario;

typedef struct nodoCola{
    Cliente cliente; 
    Inventario *CarritoProd; 
    float efectivo; //cantidad que da el cliente para pagar sus productos
    float total; //valor total de los productos selecionados
    struct nodoCola *sig; 
}NodoCola; 

typedef struct{
    NodoCola *ini; 
    NodoCola *fin;
}Cola;

typedef struct carteraC{
    Cliente cliente; 
    struct carteraC *sig; 
}CarteraC; 

//Dividi la estructura sugerida de ganancia en dos 

typedef struct{ 
    int idGanancia; //numero que identifica a las ganancias de la compra
    char fecha[20]; 
    char hora[20]; 
    float ganancia; 
}datosG; 

typedef struct ganancia{
    datosG informacion;
    struct ganancia *sig; 
}Ganancia; 


typedef Cola * ColaPtr;
typedef NodoCola * NodoPtr;
typedef Ganancia * GananciaPtr;
typedef CarteraC * CarteraCliPtr;
typedef Inventario * InventarioPtr;

//____________________________________________________________________________________________
//PROTOTIPADOS
 
int MenuPrincipal(int *opcion);

int GuardarCartera(CarteraCliPtr * cartera);
int GuardarGanancias(GananciaPtr * ganancias);
int GuardarInventario(InventarioPtr * inventario);
void GuardarCont(int cont1, int cont2, int cont3);
void RestaurarCar(CarteraCliPtr * cartera, int cantidad);
void RestaurarGan(GananciaPtr * ganancias, int cantidad);
void RestaurarCont(int * cont1, int * cont2, int * cont3);
void RestaurarInv(InventarioPtr * inventario, int cantidad);


void AltaProd(InventarioPtr *inventario);
int PushInventarioNew(InventarioPtr *inventario, InventarioPtr newProd);
void BajaProd(InventarioPtr *inventario);
void ActualizarProd(InventarioPtr *inventario);
void ListarProd(InventarioPtr InventarioPtr);

void AltaClientes(CarteraCliPtr *cartera);
int PushClienteNew(CarteraCliPtr *cartera, CarteraCliPtr clienteNew);
void BajaCliente(CarteraCliPtr *cartera);
void ActualizarCliente(CarteraCliPtr *cartera);
void ListarClientes(CarteraCliPtr cartera);

InventarioPtr datosProducto(InventarioPtr inventario, int idProducto);
CarteraCliPtr buscarCliente(CarteraCliPtr carteraC, int id);
void insertarEnCola(ColaPtr cola, InventarioPtr inv, CarteraCliPtr carteraC);
int verificaStock(InventarioPtr inventario);
void imprimirInventario(InventarioPtr inventario);
float calcularGanancia(InventarioPtr carritoProd);
void pushCarritoComp(InventarioPtr *carritoComp, InventarioPtr productoSe);
void listarColaClientes(ColaPtr cola);
void recorrerCarrito(InventarioPtr *carrito);
void atenderCliente(ColaPtr cola, GananciaPtr *ganancias);
void imprimirTicket(float ingreso, InventarioPtr carritoProd, float efectivo);
void registrarGanancia(GananciaPtr *ganancias, float ingreso);
void obtenerFecha(GananciaPtr ganancias);

void listarGanancias(GananciaPtr ganancias);
void consultarGananDia(GananciaPtr ganancias, char fecha[]);


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



//INVENTARIO FUNCIONES 


void AltaProd(InventarioPtr *inventario){ 
    int siAgregar, siDatos, i=1, c; // siDatos = validaciÃ³n de si los datos introducidos por el usuario son correctos o no
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
        if(siDatos){ //Si se agregÃ³ correctamente el producto y sus datos
            printf("\nProducto agregado al inventario correctamente\n");
            system("pause");
            do{ 
                system("cls");
                printf("Â¿Desea registrar mas productos en el inventario? Si=1 / No=0: ");
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

int PushInventarioNew(InventarioPtr *inventario, InventarioPtr newProd){ //1 Ã‰XITO / 0 SIN Ã‰XITO
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
    printf("Introduce el ID del producto que desee modificar: ");
    scanf("%d", &idProd); 
	printf("\n"); 
    temporal = *inventario; 
    
    while(temporal != NULL && temporal->producto.id != idProd) 
        temporal=temporal->sig; 
    if(temporal == NULL) 
        printf("El ID introducido no fue encontrado en el inventario de productos \n Intentelo de nuevo\n");    
    else{ 
    	printf("______________________________________________________________________________________________\n");
        printf("\nDatos del producto que pueden ser modificados: \n");
    	printf("______________________________________________________________________________________________\n\n");
        printf("1. Nombre\n2. Precio de compra\n3. Precio de venta\n4. Cantidad de piezas disponibles\n");
        printf("NOTA: El ID del producto no puede ser modificado\n OPC:");
        scanf("%d", &eleccion); 
        
        while(eleccion < 1 || eleccion > 4){ 
            system("cls");
            printf("Ingrese una opci%cn correcta \n", 162);
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
        siAgregar=1; // es igual a '1' en caso de que surja algÃºn error en la insersiÃ³n de los datos
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
                printf("¿Desea agregar mas clientes a la cartera? Si=1 / No=0: ");
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
        if(actual != NULL){ //si se encontrÃ³ al cliente, se elimina
            temporal = actual;
            anterior->sig = actual->sig;
            printf("El cliente '%s' fue eliminado del sistema satisfactoriamente\n", temporal->cliente.nombre);
            free(temporal);
        } else //si no se encontro al cliente
            printf("El ID del cliente introducido no fue encontrado en la cartera de clientes, int%cntelo de nuevo\n", 130);
    }
}
//__________________________________________________________________________________________________________________

void ActualizarCliente(CarteraCliPtr *cartera){ //la funciÃ³n recibe la cartera de clientes y actualiza el dato indicado del cliente proporcionado
    int idCliente, eleccion;
    CarteraCliPtr temporal;
    system("cls");
	printf("______________________________________________________________________________________________\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\tBIENVENIDO AL APARTADO ACTUALIZAR DATOS DE CLIENTE\n\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("______________________________________________________________________________________________\n\n");
    printf("Ingresa el ID del cliente a actualizar sus datos: ");
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
        printf("Nota: el ID del cliente no puede ser modificado\n OPC: ");
        scanf("%d", &eleccion); 
		printf("\n"); 
        while(eleccion < 1 || eleccion > 2){ 
            system("cls");
            printf("ingrese una opcion correcta \n");
            printf("1. Nombre del cliente\n2. Numero telefonico\n");
            printf("Nota: el ID del cliente no puede ser modificado\n OPC: ");
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
                printf("Ingrese el n%cmero telefonico con el que se quiere actualizar al cliente: ");
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
    printf("\nFIN DE LA CARTERA\n");
}

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

//GANANCIAS__________________________________________________________________________________________________________________________________________________

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
//_____________________________________________________________________________________________________________________________________________________________

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
