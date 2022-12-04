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

