#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////  
//Estructuras de datos internos del supermercado y datos de los clientes


typedef struct{
    int id; //numero de indentificacion del producto
    char nombre[30]; //nombre del producto
    float precioC; //precio de compra
    float precioV; //precio de venta
    int cant; //cantidad de productos solicitados por el cliente / cantidad de piezas disponibles en el inventario
}Producto; //datos del producto

typedef struct{
    int id; //numero de indentificacion del cliente
    char nombre[30]; //nombre del cliente;
    char telefono[15]; //numero de telefono del cliente
}Cliente; //datos del cliente

typedef struct inventario{
    Producto producto; //datos del producto en el inventario
    struct inventario *sig; //Apuntador al siguiente producto en la lista 
}Inventario; //Listado del inventario de productos existentes

typedef struct nodoCola{
    Cliente cliente; //datos de identificacion del cliente
    Inventario *CarritoProd; //Pila de productos seleccionados por el cliente
    float efectivo; //cantidad que da el cliente para pagar sus productos
    float total; //valor total de los productos selecionados
    struct nodoCola *sig; //Apuntador al siguiente cliente en la cola
}NodoCola; //Datos del cliente y los productos que comprará

typedef struct{
    NodoCola *ini; //Primer cliente en la cola
    NodoCola *fin; //ultimo cliente en la cola
}Cola; //Cola de clientes

typedef struct carteraC{
    Cliente cliente; //datos del cliente
    struct carteraC *sig; //apuntador a los datos del siguiente cliente registrado
}CarteraC; //listado de clientes registrados en el sistema

typedef struct{ 
    int idGanancia; //numero que identifica a las ganancias de la compra realizada
    char fecha[20]; //fecha en que se realizó la compra
    char hora[20]; //hora en que se realizo la compra
    float ganancia; //Cantidad total de dinero obtenido de las compras del cliente
}datosG; //Datos de las ganancias

typedef struct ganancia{
    datosG informacion; //datos de las ganancias
    struct ganancia *sig; //apuntador a al siguiente registro de ganancias de ventas
}Ganancia; //Listado de ganancias totales en el supermercado

/////////////////////////////////////////////////////////////////////////
//Prototipo de funciones y declaración de apuntadores a los tipos de datos

typedef Cola *colaPtr;
typedef Inventario *inventarioPtr;
typedef CarteraC *carteraCliPtr;
typedef NodoCola *nodoPtr;
typedef Ganancia *gananciaPtr;

int guardarInventario(inventarioPtr *inventario);
int guardarCartera(carteraCliPtr *cartera);
int guardarGanancias(gananciaPtr *ganancias);
void guardarCont(int cont1, int cont2, int cont3);
void restaurarCont(int *cont1, int *cont2, int *cont3);
void restaurarInv(inventarioPtr *inventario, int cantidad);
void restaurarCar(carteraCliPtr *cartera, int cantidad);
void restaurarGan(gananciaPtr *ganancias, int cantidad);

int menuPrincipal(int *opcion);

void altaProd(inventarioPtr *inventario);
int pushInventarioNew(inventarioPtr *inventario, inventarioPtr newProd);
void bajaProd(inventarioPtr *inventario);
void actualizarProd(inventarioPtr *inventario);
void listarProd(inventarioPtr inventarioPtr);

void altaClientes(carteraCliPtr *cartera);
int pushClienteNew(carteraCliPtr *cartera, carteraCliPtr clienteNew);
void bajaCliente(carteraCliPtr *cartera);
void actualizarCliente(carteraCliPtr *cartera);
void listarClientes(carteraCliPtr cartera);

void insertarEnCola(colaPtr cola, inventarioPtr inv, carteraCliPtr carteraC);
int verificaStock(inventarioPtr inventario);
carteraCliPtr buscarCliente(carteraCliPtr carteraC, int id);
void imprimirInventario(inventarioPtr inventario);
inventarioPtr datosProducto(inventarioPtr inventario, int idProducto);
void pushCarritoComp(inventarioPtr *carritoComp, inventarioPtr productoSe);
void listarColaClientes(colaPtr cola);
void recorrerCarrito(inventarioPtr *carrito);
void atenderCliente(colaPtr cola, gananciaPtr *ganancias);
float calcularGanancia(inventarioPtr carritoProd);
void imprimirTicket(float ingreso, inventarioPtr carritoProd, float efectivo);
void registrarGanancia(gananciaPtr *ganancias, float ingreso);
void obtenerFecha(gananciaPtr ganancias);

void listarGanancias(gananciaPtr ganancias);
void consultarGananDia(gananciaPtr ganancias, char fecha[]);


/////////////////////////////////////////////////////////////////////////

int main(){ //función principal
    int opcion, verificador, c, dato;
    int contInv = 0, contCar = 0, contGan = 0;
    char opcion2, fecha[20];
    inventarioPtr inventario = NULL;
    carteraCliPtr cartera = NULL;
    Cola colaClientes = {NULL, NULL};
    gananciaPtr gananciasT = NULL;

    /* Se restauran los datos de los archivos (en caso de que existan) */
    restaurarCont(&contInv, &contCar, &contGan);
    restaurarInv(&inventario, contInv);
    restaurarCar(&cartera, contCar);
    restaurarGan(&gananciasT, contGan);
    system("pause");

    do {

        /* Ciclo del menú */
        do {
            opcion = 0;
            verificador = menuPrincipal(&opcion);
            if (verificador){
                printf("Ingrese una opcion correcta\n");
                system("pause");
                while (( c = getchar()) != '\n' && c != EOF){} //Limpia caracteres restantes en el buffer de entrada
            }
            setbuf(stdin, NULL);
        } while (verificador);

        if(opcion < 1 || opcion > 5)
            opcion = 0;

        /* Operaciones a realizar según sea lo elegido por el usuario */
        switch (opcion){

            /* Gestión de productos */
            case 1:

                do{
                    system("cls"); 
                    printf("Introduzca la letra del apartado al que desea acceder:\n");
                    printf("[a] Alta de productos\n[b] Baja de productos\n[c] Actualizar producto\n"
                           "[d] Listar Productos\n");
                    printf("----> ");
                    opcion2 = getchar();
                }while(opcion2 != 'a' && opcion2 != 'b' && opcion2 != 'c' && opcion2 != 'd');
                switch (opcion2){
                    case 'a':
                        altaProd(&inventario);
                        break;
                    case 'b':
                        if(inventario == NULL)
                            printf("Todav%ca no existen datos de productos para eliminar\n", 161);
                        else    
                            bajaProd(&inventario);
                        break;
                    case 'c':
                        if(inventario == NULL)
                            printf("Todav%ca no existen datos de productos para actualizar\n", 161);
                        else    
                            actualizarProd(&inventario);                        
                        break;
                    case 'd':
                        if(inventario == NULL)
                            printf("Todav%ca no existen datos de productos para listar\n", 161);
                        else    
                            listarProd(inventario);                                                
                        break;
                    
                    default:
                        printf("No elegiste una opci%cn v%clida\n", 162, 160);                
                }       

                break;

            /* Gestión de clientes */
            case 2:

                do{
                    system("cls"); 
                    printf("Introduzca la letra del apartado al que desea acceder:\n");
                    printf("[a] Alta de clientes\n[b] Baja de clientes\n[c] Actualizar cliente\n"
                           "[d] Listar clientes\n");
                    printf("----> ");
                    opcion2 = getchar();
                }while(opcion2 != 'a' && opcion2 != 'b' && opcion2 != 'c' && opcion2 != 'd');
                switch (opcion2){
                    case 'a':
                        altaClientes(&cartera);
                        break;
                    case 'b':
                        if(cartera == NULL)
                            printf("Todav%ca no existen datos de clientes para eliminar\n", 161);
                        else    
                            bajaCliente(&cartera);
                        break;
                    case 'c':
                        if(cartera == NULL)
                            printf("Todav%ca no existen datos de clientes para actualizar\n", 161);
                        else    
                            actualizarCliente(&cartera);                        
                        break;
                    case 'd':
                        if(cartera == NULL)
                            printf("Todav%ca no existen datos de clientes para listar\n", 161);
                        else{
                            system("cls");     
                            listarClientes(cartera);
                        }                                                    
                        break;
                    
                    default:
                        printf("No elegiste una opci%cn v%clida\n", 162, 160);                
                } 

                break;

            /* Gestión de ventas */
            case 3:

                do{
                    system("cls"); 
                    printf("Introduzca la letra del apartado al que desea acceder:\n");
                    printf("[a] Insertar cliente en la cola de cobro\n[b] Listar la cola actual de clientes\n"
                           "[c] Atender al primer cliente en la cola\n");
                    printf("----> ");
                    opcion2 = getchar();
                }while(opcion2 != 'a' && opcion2 != 'b' && opcion2 != 'c');
                switch (opcion2){
                    case 'a':
                        if((inventario == NULL && cartera == NULL) || (inventario != NULL && cartera == NULL) ||
                           (inventario == NULL && cartera != NULL)){
                            printf("Todav%ca no puede realizarse la operaci%cn, no hay productos o clientes registrados\n", 161, 162);
                        } else 
                            insertarEnCola(&colaClientes, inventario, cartera);
                        break;
                    case 'b':
                        if(colaClientes.ini == NULL)
                            printf("Todav%ca no hay clientes formados en la cola de cobro\n", 161);
                        else    
                            listarColaClientes(&colaClientes);
                        break;
                    case 'c':
                        if(colaClientes.ini == NULL)
                            printf("No se puede atender, no existe ning%cn cliente en la cola\n", 163);
                        else    
                            atenderCliente(&colaClientes, &gananciasT);                        
                        break;
                    default:
                        printf("No elegiste una opci%cn v%clida\n", 162, 160);                
                } 

                break;

            /* Gestión de ganancias */
            case 4:

                do{
                    system("cls"); 
                    printf("Introduzca la letra del apartado al que desea acceder:\n");
                    printf("[a] Listar las ganancias totales\n[b] Consultar ganancias por d%ca\n", 161);
                    printf("----> ");
                    opcion2 = getchar();
                }while(opcion2 != 'a' && opcion2 != 'b');
                switch (opcion2){
                    case 'a':
                        if(gananciasT == NULL)
                            printf("Todav%ca no hay ganancias que reportar\n", 161);
                        else 
                            listarGanancias(gananciasT);    
                        break;
                    case 'b':
                        if(gananciasT == NULL)
                            printf("Todav%ca no existen ganancias para consultar\n", 161);
                        else{
                            fflush(stdin);
                            printf("Introduce la fecha de la cu%cl quiere consultar los registros, " 
                                   "en formato 'dd/mm/aaaa' (sin comillas):\n", 160);
                            scanf("%[^\n]", fecha);
                            system("cls");
                            consultarGananDia(gananciasT, fecha);     
                        }    
                        break;
                    default:
                        printf("No elegiste una opci%cn v%clida\n", 162, 160);                
                } 

                break;

            /* Guardar y salir */
            case 5:
                if(colaClientes.ini != NULL){ 
                    printf("No se puede salir del sistema, todav%ca quedan clientes en la cola de cobro\n", 161);
                    opcion = 0;
                } else {
                    printf("\n");
                    contInv = guardarInventario(&inventario);
                    contCar = guardarCartera(&cartera);
                    contGan = guardarGanancias(&gananciasT);
                    guardarCont(contInv, contCar, contGan);
                }    
                break;

            default:
                printf("No elegiste una opci%cn v%clida\n", 162, 160);
        }
        system("pause");
    } while (opcion != 5);

    return 0;
}

/////////////////////////////////////////////////////////////////////////
//Funciones de guardado/restauración de los datos del supermercado

int guardarInventario(inventarioPtr *inventario){ //guarda los datos almacenados en inventario
    FILE *fichero;
    inventarioPtr actual;
    int cont = 0;
    if((fichero = fopen("inventario.dat", "wb")) == NULL)
        printf("No se puede abrir el archivo 'inventario'\n");
    else{
        while(*inventario != NULL){
            actual = *inventario;
            fwrite(&(actual->producto), sizeof(Producto), 1, fichero);
            *inventario = (*inventario)->sig;
            free(actual);
            cont++;
        }
        printf("Datos de inventario guardados correctamente\n");
    }
    fclose(fichero);

    return cont;
}

int guardarCartera(carteraCliPtr *cartera){ //guarda los datos almacenados de los clientes
    FILE *fichero;
    carteraCliPtr actual;
    int cont = 0;
    if((fichero = fopen("clientes.dat", "wb")) == NULL)
        printf("No se puede abrir el archivo 'clientes'\n");
    else{
        while(*cartera != NULL){
            actual = *cartera;
            fwrite(&(actual->cliente), sizeof(Cliente), 1, fichero);
            *cartera = (*cartera)->sig;
            free(actual);
            cont++;
        }
        printf("Datos de los clientes guardados correctamente\n");
    }
    fclose(fichero);

    return cont;    
}

int guardarGanancias(gananciaPtr *ganancias){ //guarda los datos de las ganancias obtenidas
    FILE *fichero;
    gananciaPtr actual;
    int cont = 0;
    if((fichero = fopen("ganancias.dat", "wb")) == NULL)
        printf("No se puede abrir el archivo 'ganancias'\n");
    else{
        while(*ganancias != NULL){
            actual = *ganancias;
            fwrite(&(actual->informacion), sizeof(datosG), 1, fichero);
            *ganancias = (*ganancias)->sig;
            free(actual);
            cont++;
        }
        printf("Datos de las ganancias guardados correctamente\n");
    }
    fclose(fichero);

    return cont;    
}

void guardarCont(int cont1, int cont2, int cont3){ //guarda la cantidad de datos que existen en inventario, cartera y ganancias 
    FILE *fichero;
    if((fichero = fopen("contadores.dat", "wb")) == NULL)
        printf("No se puede abrir el archivo 'contadores'\n");
    else{
        fwrite(&cont1, sizeof(int), 1, fichero);
        fwrite(&cont2, sizeof(int), 1, fichero);
        fwrite(&cont3, sizeof(int), 1, fichero);
        printf("Cantidad de productos totales guardado correctamente\n");        
    }
    fclose(fichero);    
}

void restaurarCont(int *cont1, int *cont2, int *cont3){ //restaura la cantidad de datos que fueron guardados en los archivos
    FILE *fichero;
    int cont, i;
    if((fichero = fopen("contadores.dat", "rb")) == NULL)
        printf("El archivo 'contadores' todav%ca no existe en el sistema\n", 161);
    else{  
        fread(&cont, sizeof(int), 1, fichero);
        *cont1 = cont;
        fread(&cont, sizeof(int), 1, fichero);
        *cont2 = cont;
        fread(&cont, sizeof(int), 1, fichero);
        *cont3 = cont;
        printf("Cantidad de productos restaurados\n");                        
    }
    fclose(fichero);    
}

void restaurarInv(inventarioPtr *inventario, int cantidad){ //restaura los datos guardados del inventario
    FILE *fichero;
    inventarioPtr temp1, temporal = NULL;
    if((fichero = fopen("inventario.dat", "rb")) == NULL)
        printf("El archivo 'inventario' todav%ca no existe en el sistema\n", 161);
    else{
        while(cantidad){
            inventarioPtr actual;
            actual = (inventarioPtr) malloc(sizeof(Inventario));
            fread(&(actual->producto), sizeof(Producto), 1, fichero);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(fichero);
        while(temporal != NULL){
            inventarioPtr original;
            original = (inventarioPtr) malloc(sizeof(Inventario));
            temp1 = temporal;
            original->producto = temp1->producto;
            original->sig = *inventario;
            *inventario = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("Datos del inventario restaurados\n");
    }    
}

void restaurarCar(carteraCliPtr *cartera, int cantidad){ //restaura los datos guardados de los clientes
    FILE *fichero;
    carteraCliPtr temp1, temporal = NULL;
    if((fichero = fopen("clientes.dat", "rb")) == NULL)
        printf("El archivo 'clientes' todav%ca no existe en el sistema\n", 161);
    else{
        while(cantidad){
            carteraCliPtr actual;
            actual = (carteraCliPtr) malloc(sizeof(CarteraC));
            fread(&(actual->cliente), sizeof(Cliente), 1, fichero);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(fichero);
        while(temporal != NULL){
            carteraCliPtr original;
            original = (carteraCliPtr) malloc(sizeof(CarteraC));
            temp1 = temporal;
            original->cliente = temp1->cliente;
            original->sig = *cartera;
            *cartera = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("Datos de los clientes restaurados\n");
    }     
}

void restaurarGan(gananciaPtr *ganancias, int cantidad){ //restaura los datos guardados de las ganancias
    FILE *fichero;
    gananciaPtr temp1, temporal = NULL;
    if((fichero = fopen("ganancias.dat", "rb")) == NULL)
        printf("El archivo 'ganancias' todav%ca no existe en el sistema\n", 161);
    else{
        while(cantidad){
            gananciaPtr actual;
            actual = (gananciaPtr) malloc(sizeof(Ganancia));
            fread(&(actual->informacion), sizeof(datosG), 1, fichero);
            actual->sig = temporal;
            temporal = actual;
            cantidad--;
        }
        fclose(fichero);
        while(temporal != NULL){
            gananciaPtr original;
            original = (gananciaPtr) malloc(sizeof(Ganancia));
            temp1 = temporal;
            original->informacion = temp1->informacion;
            original->sig = *ganancias;
            *ganancias = original;
            temporal = temporal->sig;
            free(temp1);
        }
        printf("Datos de las ganancias restaurados\n");
    }    
}

/////////////////////////////////////////////////////////////////////////
//Funciones del programa

int menuPrincipal(int *opcion){ //la función muestra el menú de opciones principales del programa
    int verificar = 0, c;
    system("CLS");
    printf("Sistema del Supermercado\n"
           "Elija una opci%cn:\n", 162);
    printf("1. Gesti%cn de productos\n"
           "2. Gesti%cn de clientes\n"
           "3. Gesti%cn de ventas\n"
           "4. Gesti%cn de ganancias\n"
           "5. Salir\n", 162, 162, 162, 162);
    printf("----> ");
    if (scanf("%i", opcion) != 1){
        *opcion = 0;
        verificar++;
    }
    return verificar;
}

void altaProd(inventarioPtr *inventario){ //la función recibe la lista del inventario en la cuál registra los datos de un nuevo producto
    int siAgregar, siDatos, i = 1, c; //siAgregar = confirmación si el usuario quiere seguir registrando productos / siDatos = confirmación si los datos introducidos por el usuario son correctos o no
    system("cls");
    printf("Bienvenido al apartado ALTA DE PRODUCTOS\n\n");
    do{
        inventarioPtr newProd; //nuevo producto a introducir en la lista inventario
        newProd = (inventarioPtr) malloc(sizeof(Inventario)); //asignación de memoria 
        siAgregar = 1; //asignación de valor a la confirmación de agregar más productos en caso que los datos introducidos no sean correctos
        printf("Ingrese el ID del producto a dar de alta en el sistema (n%cmero %cnico del producto): ", 163, 163);
        scanf("%d", &newProd->producto.id); printf("\n"); //se obtiene el ID del nuevo producto
        fflush(stdin);
        printf("Ingrese el nombre del producto a registrar: ");
        scanf("%[^\n]", newProd->producto.nombre); printf("\n"); //se obtiene el nombre del nuevo producto
        fflush(stdin);
        printf("Ingrese el precio de compra: ");
        scanf("%f", &newProd->producto.precioC); printf("\n"); //se obtiene el precio de compra del nuevo producto
        fflush(stdin);
        printf("Ingrese el precio de venta: ");
        scanf("%f", &newProd->producto.precioV); printf("\n"); //se obtiene el precio de venta del nuevo producto
        fflush(stdin);
        printf("Ingrese la cantidad de piezas disponibles en stock: ");
        scanf("%d", &newProd->producto.cant); printf("\n"); //se obtiene la cantidad de piezas disponibles
        fflush(stdin);
        newProd->sig = NULL; //se asigna NULL al apuntador sig. ya que todavia el producto no ha sido insertado en la lista inventario
        siDatos = pushInventarioNew(inventario, newProd); //se inserta el producto y sus datos en la lista inventario
        if(siDatos){ //si se agregó correctamente el producto y sus datos
            printf("Producto agregado al inventario correctamente\n");
            system("pause");
            do{ //mientras que el usuario introduzca un valor incorrecto en la confirmación de agregar más productos
                system("cls");
                printf("%cDesea registrar m%cs productos en el inventario? Si = 1 / No = 0: ", 168, 160);
                if(scanf("%d", &siAgregar) != 1){ //si lo introducido por el usuario no es correcto
                    siAgregar = -1; //se asigna un valor fuera del rango de opciones
                    printf("Ingrese una opci%cn correcta\n", 162);
                    system("pause");
                    while (( c = getchar()) != '\n' && c != EOF); //Limpia caracteres restantes en el buffer de entrada
                }
                if(siAgregar == 1)
                    system("cls"); 
            }while(siAgregar < 0 || siAgregar > 1);
        } else { //si no se pudo agregar el producto y sus datos correctamente a la lista inventario se salta la confimación de agregar y se vuelve a iniciar el ciclo
            printf("Ingrese los datos del producto a registrar correctamente\n");
            system("pause");
            system("cls");
        }
    } while(siAgregar);   
}

int pushInventarioNew(inventarioPtr *inventario, inventarioPtr newProd){ //la función insertar el producto y sus datos en la lista inventario, retorna '1' si la inserción se realizó correctamente y '0' en caso contrario
    int noNuevo = 0, inBien = 0; //noNuevo = verifica si el producto ya existe en el inventario / inBien = la variable que retorna la función e indica el resultado del proceso 
    inventarioPtr temp, anterior, actual; //apuntadores para el manejo del inventario  
    if(*inventario == NULL){ //si no hay productos almacenados en el inventario
        *inventario = newProd; //lo apuntado por inventario pasa a ser newProd
        inBien++; //se incrementa la variable que confirma la inserción de los datos en el inventario satisfactoriamente
    } else {     
        temp = *inventario; //se le asigna a temp a lo que apunta inventario
        while(temp != NULL){ //mientras no se llegue al fin del inventario
            if(newProd->producto.id == temp->producto.id){  //si se ecuentra coincidencia entre el ID introducido por el usuario y alguno almacenado en el inventario
                noNuevo++; //se indica que los datos introducidos no son correctos
                break;
            } else //si no se encuentra coicidencia 
                temp = temp->sig; //avanza al siguiente producto en el inventario
        }
        if(noNuevo) //si se encontraron coincidencias
            printf("Error, el ID del producto introducido ya existe en el sistema\n");
        else { //si no se encontraron coincidencias se inserta el producto de manera ordenada
            anterior = NULL; //a anterior se le asigna NULL
            actual = *inventario; //a actual se le asigna lo apuntado por inventario
            while(actual != NULL && newProd->producto.id > actual->producto.id){ //mientras el ID proporcioando por el usuario sea mayor al que se encuentra apuntado actualmente y no sea el fin de la lista
                anterior = actual; //a anterior se le asigna lo apuntado por actual
                actual = actual->sig; //actual avanza al siguiente pruducto en la lista
            } 
            if(anterior == NULL){ //si anterior apunta a NULL 
                newProd->sig = *inventario; //se le asigna a newProd en su campo sig. lo apuntado por inventario
                *inventario = newProd; //lo apuntado por inventario será newProd
            } else { //si anterior no es igual a NULL
                anterior->sig = newProd; //a lo apuntado por anterior en su campo sig. se le asigna newProd
                newProd->sig = actual; //a newProd en su campo sig. se le asigna lo apuntado por actual
            }    
            inBien++; //se incrementa la variable que confirma la inserción de los datos en el inventario satisfactoriamente
        }
    }
    return inBien;
}

void bajaProd(inventarioPtr *inventario){ //la función recibe la lista inventario de la cual el usuario quiere eliminar un producto
    int idProd; //ID del pruducto que el usuario quiere eliminar
    inventarioPtr temporal, anterior, actual; //apuntadores para el manejo y modificación de la lista inventario
    system("cls");
    printf("Bienvenido al apartado BAJA DE PRODUCTOS\n\n");
    printf("Ingrese el ID del producto que desee eliminar del inventario: ");
    scanf("%d", &idProd); printf("\n"); //se obtiene el ID del producto que el usuario quiere eliminar
    temporal = *inventario; //a temporal se le asigna lo apuntado por inventario
    if(temporal->producto.id == idProd){ //si lo asignado a temporal en su campo ID es igual a el ID introducido por el usuario 
        *inventario = (*inventario)->sig; //se le asigna a inventario lo que tiene en su campo siguiente
        printf("Producto '%s' eliminado del inventario correctamente\n", temporal->producto.nombre);
        free(temporal); //se libera el producto de memoria
    } else { //si el ID introducido por el usuario no es el mismo que tiene temporal en su campo ID
        anterior = *inventario; //a anterior se le asigna lo apuntado por inventario
        actual = (*inventario)->sig; //a actual se le asigna lo que tiene inventario en su campo siguiente
        while(actual != NULL && actual->producto.id != idProd){ //mientras lo apuntado por actual sea diferente de NULL (fin de inventario) y el ID introducido por el usuario sea diferente al que tiene actual en su campo siguiente
            anterior = actual; //a anterior se le asigna lo apuntado por actual
            actual = actual->sig; //a actual se le asigna lo que tiene en su campo siguiente
        }
        if(actual != NULL){ //si actual no llegó al fin del inventario encontrado alguna coincidencia entre los ID's
            temporal = actual; //a temporal se le asigna lo apuntado por actual
            anterior->sig = actual->sig; //a anterior en su campo sig. se le asigna actual en su campo sig
            printf("Producto '%s' eliminado del inventario correctamente\n", temporal->producto.nombre); 
            free(temporal); //se libera lo apuntado por temporal de memoria
        } else //si actual llegó al fin del inventario y no encontró alguna coincidencia entre los ID's
            printf("El ID introducido no fue encontrado en el inventario de productos, int%cntelo de nuevo\n", 130);
    }            
}

void actualizarProd(inventarioPtr *inventario){ //la función recibe la lista inventario y según quiera el usuario, modifica cierta información del producto
    int idProd, eleccion; //idProd = ID del producto que el usuario quiere modificar / eleccion = guarda lo que seleciono el usuario a modificar 
    inventarioPtr temporal; //apuntador temporal a la lista inventario
    system("cls");
    printf("Bienvenido al apartado ACTUALIZAR DATOS DE PRODUCTO\n\n");
    printf("Introduce el ID del producto que desee modificar: ");
    scanf("%d", &idProd); printf("\n"); //se obtiene el ID del producto que el usuario quiere modificar
    temporal = *inventario; //se le asigna a temporal lo apuntado por inventario
    while(temporal != NULL && temporal->producto.id != idProd) //mientras no se llegue al fin de la lista y no se encuentren coincidencias entre el ID dado por el usuario y al que apunta temporal en ese momento
        temporal = temporal->sig; //se avanza al siguiente elemento en la lista
    if(temporal == NULL) //si se llegó al fin de la lista y no se encontraron coincidencias entre los ID's
        printf("El ID introducido no fue encontrado en el inventario de productos, int%cntelo de nuevo\n", 130);    
    else{ //si no se llegó al fin de lista y se encontraron coincidencias entre los ID's
        printf("Datos del producto que pueden ser modificados: \n");
        printf("1. Nombre\n2. Precio de compra\n3. Precio de venta\n4. Cantidad de piezas disponibles\n");
        printf("Nota: El ID del producto no puede ser modificado\n");
        printf("Seleccione una opci%cn: ", 162);
        scanf("%d", &eleccion); //se obtiene la elección del usuario del dato a modificar
        while(eleccion < 1 || eleccion > 4){ //mientras que la elección del usuario no sea correcta se repite el ciclo
            system("cls");
            printf("Ingrese una opci%cn correcta \n", 162);
            printf("1. Nombre\n2. Precio de compra\n3. Precio de venta\n4. Cantidad de piezas disponibles\n");
            printf("Nota: El ID del producto no puede ser modificado\n");
            printf("Seleccione una opci%cn: ", 162);
            scanf("%d", &eleccion); printf("\n");
        }
        switch(eleccion){ //según sea lo que el usuario eligió
            case 1: //modificar el nombre
                fflush(stdin);
                memset(temporal->producto.nombre, '\0', 30); 
                printf("Ingrese el nombre con el que quiere actualizar el producto: ");
                scanf("%[^\n]", temporal->producto.nombre); printf("\n");
                break;
            case 2: //modificar el precio de compra
                fflush(stdin);
                printf("Ingrese la cantidad con la que quiere remplazar el precio de compra: ");
                scanf("%f", &temporal->producto.precioC); printf("\n");
                break;
            case 3: //modificar el precio de venta
                fflush(stdin);
                printf("Ingrese la cantidad con la que quiere remplazar el precio de venta: ");
                scanf("%f", &temporal->producto.precioV); printf("\n");
                break;
            case 4: //modificar la cantidad de piezas en stock
                fflush(stdin);
                printf("Introduce el valor con la que quiere reemplazar la cantidad de productos en existencia: ");
                scanf("%d", &temporal->producto.cant); printf("\n");
                break;
            default:
                printf("No elegiste una opci%cn correcta\n", 162);                
        }
        printf("El cambio en la informaci%cn del producto se realiz%c correctamente\n", 162, 162);
    }
}

void listarProd(inventarioPtr inventario){ //la función lista todos los productos existentes en el inventario (si tiene productos almacenados)
    int i = 1; //numero del producto en el inventario
    inventarioPtr temporal; //apuntador a inventario
    temporal = inventario; //se le asigna a temporal lo apuntado por inventario
    system("cls");
    printf("Productos registrados en el inventario: \n\n");
    while(temporal != NULL){ //mientras no se llegue al fin del inventario
        printf("%d. ID: %d\n"
               "   Nombre: %s\n"
               "   %d pieza(s) restante(s)\n\n", i, temporal->producto.id, temporal->producto.nombre, temporal->producto.cant); //se muestra el nombre y la cantidad de piezas disponibles
        temporal = temporal->sig; //se avanza al siguiente producto en la lista
        i++;
    }
    printf("FIN DEL INVENTARIO\n");
}



void altaClientes(carteraCliPtr *cartera){ //la función introduce en la cartera de clientes los datos de un nuevo cliente en el supermercado
    int siAgregar, siBien, c; //siAgregar = confirmación del usuario si se desea agregar más clientes / siBien = confirmación que devuelve la función pushClienteNew de acuerdo al resultado del proceso
    system("cls");
    printf("Bienvenido al apartado ALTA DE CLIENTES\n\n");
    do{ //hacer mientras se quieran agregar más clientes a la cartera
        siAgregar = 1; //por defecto siAgregar es igual a '1' en caso de que surja algún error en la insersión de los datos
        carteraCliPtr clienteNew; //nuevo nodo clienteNew que gurdará los datos del cliente
        clienteNew = (carteraCliPtr) malloc(sizeof(CarteraC)); //asignación de memoria
        printf("Introduce el ID del nuevo cliente: ");
        scanf("%d", &clienteNew->cliente.id); printf("\n"); //se obtiene el ID del cliente
        fflush(stdin);
        printf("Introduce el nombre del nuevo cliente: ");
        scanf("%[^\n]", clienteNew->cliente.nombre); printf("\n"); //se obtiene el nombre del cliente
        fflush(stdin);
        printf("Introduce el n%cmero de tel%cfono del nuevo cliente: ", 163, 130);
        scanf("%[^\n]", clienteNew->cliente.telefono); printf("\n"); //se obtiene el telefono del cliente
        fflush(stdin);
        clienteNew->sig = NULL; //se le asigna NULL a clienteNew en su campo sig. ya que todavia no ha sido insertado en la cartera
        siBien = pushClienteNew(cartera, clienteNew); //insersión del nodo clienteNew en la cartera
        if(siBien){ //si la insersión de clienteNew se realizó satisfactoriamente
            printf("Cliente agregado a la cartera correctamente\n");
            system("pause");
            do{ //hacer mientras que la opción introducida por el cliente sea errónea
                system("cls");
                printf("%cDesea agregar m%cs clientes a la cartera? Si = 1 / No = 0: ", 168, 160);
                if(scanf("%d", &siAgregar) != 1){ //si lo introducido por el usuario no es correcto
                    siAgregar = -1; //se asigna un valor fuera del rango de opciones
                    printf("Ingrese una opci%cn correcta\n", 162);
                    system("pause");
                    while (( c = getchar()) != '\n' && c != EOF); //Limpia caracteres restantes en el buffer de entrada
                }
                if(siAgregar == 1)
                    system("cls"); 
            } while(siAgregar < 0 || siAgregar > 1);
        } else { //si la insersión de clienteNew no se realizó satisfactoriamente
            printf("Ingrese los datos del cliente a registrar correctamente\n");
            system("pause");
            system("cls");
        }
    } while(siAgregar); 
}

int pushClienteNew(carteraCliPtr *cartera, carteraCliPtr clienteNew){ //la función recibe la cartera de clientes y el nodo clienteNew que se le agregará, regresa '1' si el proceso se realizó de forma correcta y '0' en caso contrario
    int noNuevo = 0, inBien = 0; //noNuevo = verifica si el cliente ya existe en la cartera / inBien = la variable que retorna la función e indica el resultado del proceso 
    carteraCliPtr temp, anterior, actual; //apuntadores para el manejo de la cartera  
    if(*cartera == NULL){ //si no hay datos de clientes almacenados en la cartera
        *cartera = clienteNew; //lo apuntado por cartera pasa a ser clienteNew
        inBien++; //se incrementa la variable que confirma la inserción de los datos del cliente en la cartera satisfactoriamente
    } else {     
        temp = *cartera; //se le asigna a temp a lo que apunta cartera
        while(temp != NULL){ //mientras no se llegue al fin de la cartera
            if(clienteNew->cliente.id == temp->cliente.id){  //si se ecuentra coincidencia entre el ID introducido por el usuario y alguno almacenado en la cartera
                noNuevo++; //se indica que los datos introducidos no son correctos
                break;
            } else //si no se encuentra coicidencia 
                temp = temp->sig; //avanza al siguiente cliente en la cartera
        }
        if(noNuevo) //si se encontraron coincidencias
            printf("Error, el ID del cliente introducido ya existe en el sistema\n");
        else { //si no se encontraron coincidencias se inserta los datos del cliente de manera ordenada
            anterior = NULL; //a anterior se le asigna NULL
            actual = *cartera; //a actual se le asigna lo apuntado por cartera
            while(actual != NULL && clienteNew->cliente.id > actual->cliente.id){ //mientras el ID proporcioando por el usuario sea mayor al que se encuentra apuntado actualmente y no sea el fin de la lista
                anterior = actual; //a anterior se le asigna lo apuntado por actual
                actual = actual->sig; //actual avanza al siguiente cliente en la lista
            } 
            if(anterior == NULL){ //si anterior apunta a NULL 
                clienteNew->sig = *cartera; //se le asigna a clienteNew en su campo sig. lo apuntado por cartera
                *cartera = clienteNew; //lo apuntado por cartera será clienteNew
            } else { //si anterior no es igual a NULL
                anterior->sig = clienteNew; //a lo apuntado por anterior en su campo sig. se le asigna clienteNew
                clienteNew->sig = actual; //a clienteNew en su campo sig. se le asigna lo apuntado por actual
            }    
            inBien++; //se incrementa la variable que confirma la inserción de los datos del cliente en la cartara satisfactoriamente
        }
    }

    return inBien;    
}

void bajaCliente(carteraCliPtr *cartera){ //la funcion recibe la cartera de clientes y elimina los datos del cliente marcado del sistema
    int idCliente;
    carteraCliPtr temporal, actual, anterior;
    system("cls");
    printf("BIENVENIDO AL APARTADO BAJA DE CLIENTES\n\n");
    printf("Ingresa el ID del cliente a dar de baja del sistema: ");
    scanf("%d", &idCliente); printf("\n"); //se obtiene el ID del cliente a eliminar
    temporal = *cartera; //se le asigna a temporal lo apuntado por cartera
    if(temporal->cliente.id == idCliente){ //si el primer cliente en la cartera es el buscado
        *cartera = (*cartera)->sig; //se le asigna a cartera el cliente sig
        printf("El cliente '%s' fue eliminado del sistema satisfactoriamente\n", temporal->cliente.nombre);
        free(temporal);
    } else { //si el cliente buscado no es el primero en la cartera
        anterior = *cartera; //se le asigna a anterior lo apuntado por cartera
        actual = (*cartera)->sig; //se le asigna a actual el siguiente cliente en la cartera
        while(actual != NULL && actual->cliente.id != idCliente){ //mientras no se llegue al fin de la cartera y los ID's comparados no sean iguales
            anterior = actual; //a anterior se le asigna lo apuntado por actual
            actual = actual->sig; //actual obtiene la direccion del cliente siguiente en la cartera
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

void actualizarCliente(carteraCliPtr *cartera){ //la función recibe la cartera de clientes y actualiza el dato indicado del cliente proporcionado
    int idCliente, eleccion;
    carteraCliPtr temporal;
    system("cls");
    printf("BIENVENIDO AL APARTADO ACTUALIZAR DATOS DE CLIENTE\n\n");
    printf("Ingresa el ID del cliente a actualizar sus datos: ");
    scanf("%d", &idCliente); printf("\n"); //se obtiene el ID del cliente a actualizar
    temporal = *cartera; //se le asigna a temporal lo apuntado por cartera
    while(temporal != NULL && temporal->cliente.id != idCliente) //mientras no se llegue al fin de la cartera y los ID's comparados no sean iguales
        temporal = temporal->sig; //se avanza al sig cliente
    if(temporal == NULL) //si no se encontró al cliente
        printf("El ID introducido no est%c asociado a ningun cliente en la cartera, intentelo de nuevo\n", 160);
    else{ //si el cliente fue encontrado
        printf("Datos del cliente que pueden ser modificados: \n");
        printf("1. Nombre del cliente\n2. N%cmero telef%cnico\n", 163, 162);
        printf("Nota: el ID del cliente no puede ser modificado\n");
        printf("Seleccione una opci%cn: ", 162);
        scanf("%d", &eleccion); printf("\n"); //se obtiene el dato a modificar del cliente
        while(eleccion < 1 || eleccion > 2){ //mientras se elija una opción incorrecta
            system("cls");
            printf("ingrese una opci%cn correcta \n", 162);
            printf("1. Nombre del cliente\n2. N%cmero telef%cnico\n", 163, 162);
            printf("Nota: el ID del cliente no puede ser modificado\n");
            printf("Seleccione una opci%cn: ", 162);
            scanf("%d", &eleccion); printf("\n");
        }
        switch(eleccion){ //según sea lo que el usuario eligió
            case 1: //modificar el nombre del cliente
                fflush(stdin);
                memset(temporal->cliente.nombre, '\0', 30); 
                printf("Ingrese el nombre con el que quiere actualizar al cliente: ");
                scanf("%[^\n]", temporal->cliente.nombre); printf("\n");
                break;
            case 2: //modificar el numero de telefono
                fflush(stdin);
                memset(temporal->cliente.telefono, '\0', 15);
                printf("Ingrese el n%cmero telef%cnico con el que se quiere actualizar al cliente: ", 163, 162);
                scanf("%[^\n]", temporal->cliente.telefono); printf("\n");
                break;
            default:
                printf("No elegiste una opci%cn correcta\n", 162);                
        }
        printf("El cambio en la informaci%cn del cliente se realiz%c correctamente\n", 162, 162);
    }        
}

void listarClientes(carteraCliPtr cartera){ //la función recibe la cartera de clientes y muestra en pantalla los datos de los clientes registrados
    int i = 1; //numero del cliente en la cartera
    carteraCliPtr temporal;
    temporal = cartera;
    printf("Clientes listados en la cartera: \n\n");
    while(temporal != NULL){ //mientras no se llegue al fin de la cartera
        printf("%d. ID: %d\n"
               "   Nombre: %s\n"
               "   Tel%cfono: %s\n\n", i, temporal->cliente.id, temporal->cliente.nombre, 130, temporal->cliente.telefono); //se muestra el nombre y el numero telefonico
        temporal = temporal->sig; //se avanza al siguiente cliente en la lista
        i++;
    }
    printf("FIN DE LA CARTERA\n");
}



void insertarEnCola(colaPtr cola, inventarioPtr inv, carteraCliPtr carteraC){ //la función va insertarndo los nodo cliente en la cola con todos los datos de sus compras
    int idCliente, idProducto, siCompra, c, yaEnCola;
    carteraCliPtr clienteDatos; //apuntador a la direccion de memoria de la ubicación de los datos del cliente en la lista
    inventarioPtr datosProd; //apuntador a la direccion de memoria de la ubicacion de los datos del cliente en la lista
    nodoPtr nuevo, encontrado; //creación de nuevo nodo cliente
    nuevo = (nodoPtr) malloc(sizeof(NodoCola)); //asignación dinámica de memoria al nodo
    if(nuevo == NULL) //si no hay memoria disponible
        printf("No hay memoria disponible en el sistema\n");
        else { //si la asignación de la memoria fue correcta
            do{ //se repite el ciclo si el cliente ingresa un ID incorrecto
                system("cls");
                printf("APARTADO DE SELECCION DE PRODUCTOS E INGRESO EN LA COLA\n");
                listarClientes(carteraC);
                printf("Ingrese su ID con el que est%c registrado en el sistema: ", 160); //pedir la identificación del cliente
                scanf("%d", &idCliente); printf("\n");
                clienteDatos = buscarCliente(carteraC, idCliente); //busca el ID del cliente en la cartera y retorna un apuntador a la ubicacion de los datos del cliente
                if(clienteDatos != NULL){     
                    encontrado = cola->ini;
                    while(encontrado != NULL && encontrado->cliente.id != clienteDatos->cliente.id)
                        encontrado = encontrado->sig;
                    if(encontrado != NULL && encontrado->cliente.id == clienteDatos->cliente.id){ 
                        printf("El cliente seleccionado ya se encuentra en la cola de cobro, int%cntelo de nuevo\n", 130);
                        yaEnCola = 1;
                    } else {
                        printf("Bienvenido de nuevo, %s \n\n", clienteDatos->cliente.nombre);  
                        yaEnCola = 0;
                    }    
                } else 
                    yaEnCola = 1;
                system("pause");            
            } while(yaEnCola == 1);
            nuevo->cliente = clienteDatos->cliente; //se copian en el nuevo nodo cliente los datos obtenidos por el apuntador del ciclo anterior
            nuevo->CarritoProd = NULL; //El apuntador al carrito de compras del cliente se iguala a NULL ya que todavia no hay productos seleccionados
            nuevo->sig = NULL; //el apuntador al sig. nodoCliente se iguala a NULL porque nodoCliente todavia no ha entrado a la cola de clientes 
            do{ //llenado del carrito de compras
                siCompra = 0; //bandera para confirmar si el cliente quiere agregar más productos a su carrito
                do{ //hacer mientras el usuario ingrese un ID incorrecto
                    system("cls");
                    printf("%cQu%c producto desea agregar a su carrito de compras? \n\n", 168, 130);
                    imprimirInventario(inv); //muestra en pantalla el inventario de productos
                    printf("Ingrese el ID del producto: ");
                    scanf("%d", &idProducto); printf("\n"); //se obtiene el ID del producto seleccionado
                    datosProd = datosProducto(inv, idProducto); //se obtiene la direccion de memoria en la lista del producto seleccionado
                    if(datosProd == NULL){ //si no se encontró el ID
                        printf("Error: el ID introducido no se encontr%c en el inventario, int%cntelo de nuevo\n", 162, 130);
                        system("pause");
                        system("cls");
                    }    
                } while(datosProd == NULL);    
                pushCarritoComp(&nuevo->CarritoProd, datosProd); //inserta el producto selecionado en el carrito de compras
                do{ //confirmación si el cliente desea o no agregar más productos a su carrito
                    system("cls");
                    printf("%cDesea agregar m%cs productos a su carrito de compras? Si = 1 / No = 0: ", 168, 160);
                    if(scanf("%d", &siCompra) != 1){ //si lo introducido por el usuario no es correcto
                        siCompra = -1; //se asigna un valor fuera del rango de opciones
                        printf("Ingrese una opci%cn correcta\n", 162);
                        system("pause");
                        while (( c = getchar()) != '\n' && c != EOF); //Limpia caracteres restantes en el buffer de entrada
                    }
                } while(siCompra < 0 || siCompra > 1);
                if(siCompra == 1 && verificaStock(inv) == 0){ //si el usuario desea agregar más productos pero ya no existen más productos en stock
                    system("cls");
                    printf("Todos los productos se han agotado, no es posible agregar m%cs productos\n", 160);
                    siCompra = 0;
                }                
            } while(siCompra); //mientras se quiera agregar más productos
            if(cola->ini == NULL) //si este nodo cliente es el primer cliente en la cola
                cola->ini = nuevo;
            else //si no es el primer cliente en la cola
                cola->fin->sig = nuevo;
            cola->fin = nuevo; //nodo cliente entra como el ultimo nodo en la cola
            printf("Ingreso del cliente '%s' en la cola de cobro satisfactoriamente\n", cola->fin->cliente.nombre);       
        }    
}

int verificaStock(inventarioPtr inventario){ //la función verifica si existe stock de productos en el inventario, devuelve '0' si está vacio o devuelve cualquier num. positivo en otro caso
    int verifica = 0;
    inventarioPtr temporal;
    temporal = inventario;
    while(temporal != NULL){ //mientras no se llegue al fin del inventario
        if(temporal->producto.cant > 0) //si se encuentra existencia en stock del producto
            verifica++;
        temporal = temporal->sig;    
    }

    return verifica;
}

carteraCliPtr buscarCliente(carteraCliPtr carteraC, int id){ //la función busca el ID del cliente en la cartera y devuelve todos los datos almacenados en la estructura cliente
    carteraCliPtr temp; //apuntador a la ubicación de los datos del cliente
    temp = carteraC; //se le asigna el contenido apuntado por carteraCliptr
    while(temp != NULL && temp->cliente.id != id) //mientras no se llegue al fin del listado y los ID's sean diferentes
        temp = temp->sig;    

    if(temp == NULL) //si no se hayo una coincidencia entre el ID almaceando en el sistema y el proporcionado
        printf("El ID introducido no existe en la cartera, int%cntelo de nuevo\n", 130);

    return temp;
}

void imprimirInventario(inventarioPtr inventario){ //la función muestra en pantalla el inventario de productos existentes en el supermercado
    int i = 1;
    inventarioPtr temp; //apuntador a inventario
    temp = inventario; //se le asigna el contenido apuntado por la variable inventario
    while(temp != NULL){ //mientras no se llegue al fin del inventario
        if(temp->producto.cant != 0){ //si el producto todavia tiene cantidad disponible en stock         
            printf("%d. %s \n", i, temp->producto.nombre); //muestra el nombre del producto
            printf("    ID del producto: %d\n", temp->producto.id); //muestra el ID del producto
            printf("    Cantidad disponible: %d unidad(es)\n", temp->producto.cant); //muestra la cantidad en existencia de piezas  
            printf("    Precio unitario: $%.2f\n\n", temp->producto.precioV); //muestra el precio por unidad del producto
            i++;
        }
        temp = temp->sig; //se asigna al apuntador el siguiente producto en la lista
    }
    if(i == 1)
        printf("No hay productos disponibles por el momento, int%cntelo mas tarde\n", 130);
    else
        printf("NOTA: Algunos productos pueden no ser mostrados debido a la falta de stock\n");    
}

inventarioPtr datosProducto(inventarioPtr inventario, int idProducto){ //la función busca en el inventario y devuelve el apuntador al producto en inventario con todo su contenido
    inventarioPtr temp; //apuntador a inventario
    temp = inventario; //se le asigna a temp lo apuntado por inventario
    while(temp != NULL && temp->producto.id != idProducto) //mientras temp no llegue al fin del inventerio
        temp = temp->sig;    

    return temp;
}

void pushCarritoComp(inventarioPtr *carritoComp, inventarioPtr productoSe){ //la función inserta el producto seleccionado por el cliente en su carrito de compras 
    int cant;
    inventarioPtr nuevo, encontrado; //nuevo nodo que almacena los datos del producto seleccionado por el cliente
    printf("Ingrese la cantidad de piezas que desee comprar de '%s', %d disponible(s): ", productoSe->producto.nombre, productoSe->producto.cant); 
    scanf("%d", &cant); printf("\n"); //se obtiene la cantidad de piezas que el cliente quiere
    while(cant < 1 || cant > productoSe->producto.cant){ //mientras que la cantidad de piezas seleccionadas por el cliente no este dentro del rango de existencia se repite el ciclo
        system("cls");
        printf("Ingrese una cantidad dentro del rango de existencia en stock, %d disponible(s): ", productoSe->producto.cant);
        scanf("%d", &cant); printf("\n");            
    }
    encontrado = *carritoComp;
    while(encontrado != NULL && encontrado->producto.id != productoSe->producto.id) //se busca si el mismo producto ya fue insertado anteriormente al carrito
        encontrado = encontrado->sig;
    
    if(encontrado != NULL){ //si el dato ya había sido introducido anteriormente
        encontrado->producto.cant = encontrado->producto.cant + cant; //se aumenta la cantidad a comprar de ese producto de acuerdo a lo ingresado por el cliente
        productoSe->producto.cant = productoSe->producto.cant - cant; //se resta esa cantidad aumentada al producto en el inventario
    } else { //si el producto es insertado en el carrito por primera vez, se crea un nuevo nodo y se inserta a la pila
        nuevo = (inventarioPtr) malloc(sizeof(Inventario)); //asignación dinámica de memoria en el nodo
        if(nuevo == NULL) //si no se puedo asignar memoria
            printf("No hay memoria disponible para copiar los datos\n");
        else { //si la asignación de memoria se hizo correctamente
            //asignación final de los datos del producto seleccionado en el nuevo nodo  
            nuevo->producto = productoSe->producto; 
            nuevo->producto.cant = cant;
            productoSe->producto.cant = productoSe->producto.cant - cant; 
            nuevo->sig = NULL;
            //inserción del nodo producto en la lista del carrito de compras
            if(*carritoComp == NULL)
                *carritoComp = nuevo;
            else{     
                nuevo->sig = *carritoComp;
                *carritoComp = nuevo;
            }
        }
    }
    printf("Producto(s) agregado(s) satisfactoriamente al carrito de compras\n");
    system("pause");    
}

void listarColaClientes(colaPtr cola){ //la función lista la cola de clientes actual junto a su carrito de compras propio
    int i = 1;
    nodoPtr clientes; //apuntador a los clientes en la cola
    inventarioPtr productos;
    clientes = cola->ini; //a clientes se le asigna el primer cliente en la cola
    system("cls");
    printf("LISTADO DE CLIENTES ACTUALES EN LA COLA\n");
    while(clientes != NULL){ //mientras no se llegue al fin de la cola
        printf("%d. ID: %d\n"
               "   Nombre: %s\n"
               "   Carrito de compras: \n\n", i, clientes->cliente.id, clientes->cliente.nombre); //imprimir los datos
        recorrerCarrito(&clientes->CarritoProd); //imprimir carrito
        clientes = clientes->sig; //se avanza al siguiente cliente en la cola
        i++;
    }
    printf("FIN DE LA COLA\n");
}

void recorrerCarrito(inventarioPtr *carrito){ //la función recibe la pila del carrito e imprime sus datos mientras la recorre
    inventarioPtr temp1, temporal = NULL;
    while(*carrito != NULL){ //mientras la pila no esté vacia
        temp1 = *carrito;
        inventarioPtr actual;
        actual = (inventarioPtr) malloc(sizeof(Inventario));
        printf("     |  ID: %d\n"  
               "     |  Producto: %s\n"
               "     |  Cantidad: %d pieza(s)\n\n", temp1->producto.id, temp1->producto.nombre, 
               temp1->producto.cant);
        actual->producto = temp1->producto;
        actual->sig = temporal;
        temporal = actual;               
        *carrito = (*carrito)->sig;
        free(temp1);
    }
    while(temporal != NULL){ //se regresa a su posición original
        temp1 = temporal;
        inventarioPtr original;
        original = (inventarioPtr) malloc(sizeof(Inventario));
        original->producto = temp1->producto;
        original->sig = *carrito;
        *carrito = original;
        temporal = temporal->sig;
        free(temp1);
    }
}

void atenderCliente(colaPtr cola, gananciaPtr *ganancias){ //la función atiende al primer cliente en la cola, imprime el ticket y registra las ganancias  
    float ingresoT; //variable en la cual se guarda el total a pagar
    nodoPtr actual; //apuntador al cliente a atender
    actual = cola->ini; //se asigna a actual el primer cliente en la cola
    system("cls");
    printf("APARTADO ATENDER AL CLIENTE\n");
    printf("Bienvenido a la caja de cobro, %s\n", actual->cliente.nombre);
    ingresoT = calcularGanancia(actual->CarritoProd); //se obtiene el total a a pagar
    actual->total = ingresoT;
    printf("Total a pagar por los productos en su carrito de compras: $%.2f\n", ingresoT);
    printf("Ingrese la cantidad ($) con la que desea pagar: ");
    scanf("%f", &actual->efectivo); //se obtiene la cantidad con la que el cliente pagará sus productos
    while(actual->efectivo < ingresoT){ //mientras el cliente ingrese una cantidad menor al total
        system("cls");
        printf("Digite una cantidad correcta de dinero, por favor\n");
        printf("Total a pagar por los productos en su carrito de compras: $%.2f\n", ingresoT);
        printf("Ingrese la cantidad ($) con la que desea pagar: ");
        scanf("%f", &actual->efectivo);
    }
    imprimirTicket(ingresoT, actual->CarritoProd, actual->efectivo); //se imprime el ticket de compra
    registrarGanancia(ganancias, ingresoT); //se registran los datos de la ganancia en la lista de ganancias
    if(cola->ini == cola->fin) //si nodoCliente es el unico en la cola
        cola->fin = actual->sig;
    cola->ini = actual->sig;
    free(actual); //se libera la memoria
    printf("El cliente ha salido de la cola exitosamente\n");    
}

float calcularGanancia(inventarioPtr carritoProd){ //la función calcula el total a pagar respecto a los productos en el carrito de compras
    float ganaciaUni, ingresoT = 0;
    while(carritoProd != NULL){ //mientras no se llegue al fin del carrito
        ganaciaUni = carritoProd->producto.precioV * (float)carritoProd->producto.cant; //se multiplica la cantidad por el precio del prod
        ingresoT += ganaciaUni; //se suma al total
        carritoProd = carritoProd->sig; //se avanza al sig producto
    }

    return ingresoT;
}

void imprimirTicket(float ingreso, inventarioPtr carritoProd, float efectivo){ //la función imprime el ticket de las compras del cliente
    float total, cambio = 0;
    if(ingreso < efectivo) //si el efectivo que de el cliente para pagar es mayor al total
        cambio = efectivo - ingreso;
    system("cls");      
    printf("                            - - -   SUPERMERCADO > 1 2 3<   - - -                            \n");
    printf("                                      Su ticket de compra                                      \n\n");
    printf("idProducto    Nombre                          Cantidad    Precio Unitario    Total por Producto\n");
    while(carritoProd != NULL){ //mientras no se llegue al fin del carrito
        total = carritoProd->producto.precioV * (float)carritoProd->producto.cant; //se obtiene el total a pagar por prod     
        printf("%-*d%-*s%*d    %*.2f    %*.2f\n", 14, carritoProd->producto.id, 32, carritoProd->producto.nombre, 
                8, carritoProd->producto.cant, 15, carritoProd->producto.precioV, 18, total); //se imprimen los datos del prod
        carritoProd = carritoProd->sig; //se avanza al sig producto       
    }
    printf("\nTotal a pagar:%*.2f\n", 81, ingreso);
    printf("Su pago:%*.2f\n", 87, efectivo);
    printf("Su cambio:%*.2f\n", 85, cambio);
    printf("                                    %cGracias por su compra!                                    \n", 173);
    printf("                                    Le atendi%c: Frida Mart%nez                                    \n", 162, 161);
    printf("           SUPERMERCADO >1 2 3< agradece su preferencia con los precios m%s bajos           \n\n", 160);
}

void registrarGanancia(gananciaPtr *ganancias, float ingreso){ //la función registra las ingresos obtenidas en el listado de ganancias
    gananciaPtr registro; //nodo a insertar en la lista 
    registro = (gananciaPtr) malloc(sizeof(Ganancia));
    if(registro == NULL)
        printf("No hay memoria disponible\n");
    else{
        registro->informacion.ganancia = ingreso; //se registran los ingresos
        if(*ganancias == NULL) //si es el primer registro en la lista
            registro->informacion.idGanancia = 1;
        else //si no es el primer registro en la lista
            registro->informacion.idGanancia = (*ganancias)->informacion.idGanancia + 1;
        obtenerFecha(registro); //se obtiene la hora y fecha actual y se registra
        registro->sig = NULL;
        if(*ganancias == NULL) //si es el primer nodo a registrar en la lista
            *ganancias = registro;
        else{ //si no es el primer nodo a registrar
            registro->sig = *ganancias;
            *ganancias = registro;
        }    
    }    
}

void obtenerFecha(gananciaPtr ganancias){ //la función obtiene la fecha y horas actuales y las registra
    time_t tiempo = time(0);
    struct tm *fecha = localtime(&tiempo);
    char fechaAc[20], horaAc[20];
    strftime(fechaAc, 20, "%d/%m/%Y", fecha);
    strftime(horaAc, 20, "%H:%M:%S", fecha);
    strcpy(ganancias->informacion.fecha, fechaAc);
    strcpy(ganancias->informacion.hora, horaAc);
}

void listarGanancias(gananciaPtr ganancias){ //la función lista los datos de todas las ganancias registradas
    int i = 1;
    gananciaPtr actual; //apuntador al nodo actual en la lista
    actual = ganancias; //se asigna a actual el primer nodo en la lista
    system("cls");
    printf("Listado de las ganancias obtenidas por la venta de productos:\n\n");
    while(actual != NULL){ //mientras no se llegue al fin del listado
        printf(" %d. ID: %d\n", i, actual->informacion.idGanancia);
        printf("     Fecha: %s\n", actual->informacion.fecha);
        printf("     Hora: %s\n", actual->informacion.hora);
        printf("     Ganancias: %.2f\n\n", actual->informacion.ganancia);
        actual = actual->sig;
        i++;
    }
    printf("FIN DEL LISTADO DE LAS GANANCIAS TOTALES\n");
}

void consultarGananDia(gananciaPtr ganancias, char fecha[]){ //la función lista las ganancias de una fecha especifica, si existen
    int i = 1;
    gananciaPtr actual, encontrado; //apuntadores para controlar el listado
    encontrado = ganancias; //a encontrado se le asigna el primer nodo en la lista
    while(encontrado != NULL && strcmp(encontrado->informacion.fecha, fecha) != 0) //mientras no se llegue al fin de la lista y las fechas comparadas sean diferentes
        encontrado = encontrado->sig;    
    if(encontrado == NULL) //si no hay ningún registro en esa fecha 
        printf("No existen registros de ganancias en esa fecha, int%cntelo de nuevo\n", 130);
    else{ //si se encontró un registro
        actual = encontrado; //se le asigna a actual el registro encontrado
        printf("Listado de las ganancias obtenidas el '%s':\n\n", fecha);
        while(actual != NULL){ //se recorre buscando otros registros mientras no se llegue al fin de la lista
            if(strcmp(actual->informacion.fecha, fecha) == 0){ //si se encontró un registro se imprimen sus datos    
                printf(" %d. ID: %d\n", i, actual->informacion.idGanancia);
                printf("     Fecha: %s\n", actual->informacion.fecha);
                printf("     Hora: %s\n", actual->informacion.hora);
                printf("     Ganancias: %.2f\n\n", actual->informacion.ganancia);
                i++;
            }
            actual = actual->sig; //se avanza al sig registro en la lista
        }
        printf("Fin del listado de ganancias\n");
    }        
}
