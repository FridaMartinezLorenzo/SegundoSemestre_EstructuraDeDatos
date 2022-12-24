#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 50
typedef struct lista{
	char name[30];
	struct lista *sig;
}LISTA;

typedef struct tabla{
	LISTA *lista;
}TABLAS_HASH;


void InsertarLista(LISTA **,char []);
void Imprimir(TABLAS_HASH []);
int DeterminarIndice (char []);

int main()
{
	TABLAS_HASH alumnos[TAM]={NULL};
	FILE *archivo=fopen("nombres2.txt","r");
	if(archivo==NULL)
		perror("\nERROR AL ABRIR EL ARCHIVO");
	else{
		char name[30]={'\0'};
		int c=0, flag=0;
		int indice=0;
		while(!feof(archivo)&&(flag!=1))
		{
			//fscanf(archivo,"%s[\n]",name);
			fgets(name,30,archivo);
			indice=DeterminarIndice(name);
			InsertarLista(&alumnos[indice].lista,name);
			c++;
			if(c==50)
				flag=1;
		}
		fclose(archivo);
		Imprimir(alumnos);
	}
 return 8;
}
//_________________________________________________________________________________________________________
int DeterminarIndice (char n[])
{
	int indice=0,lg=strlen(n),aux;
	int i=0; 
	for( ; i<lg-1 ; i++ )
	{
		n[i]=toupper(n[i]); //TRABAJA CON EN MAYUSCULAS
		aux = n[i];
		indice+= aux-64;
	}
		indice=indice%50;
	return indice;
}

//______________________________________________________________________________________________________________
void InsertarLista(LISTA**listaT, char dato[]){

	LISTA *nuevo,*ant,*act;
	nuevo=(LISTA*)malloc(sizeof(LISTA));
	if(nuevo==NULL)
		printf("No hay memoria\n");
	else {
		strcpy(nuevo->name,dato);
		nuevo->sig=NULL;
	if(*listaT==NULL)
		*listaT=nuevo;
	else {
		ant=NULL;
		act=*listaT;
		
		
	while((act!=NULL) && (strcmp(dato,act->name)>0)){
		ant=act;
		act=act->sig;
	}
		if(ant==NULL){
			nuevo->sig=*listaT;
			*listaT=nuevo;
		} else{
			ant->sig=nuevo;
			nuevo->sig=act;
			}
       }	
	}
}

//___________________________________________________________________________________________________________________

void Imprimir(TABLAS_HASH a[])
{
	int i=0;
	for ( ;i<TAM;i++)
	{
		if(a[i].lista!=NULL)
		{
			printf("\n\nIndice: %d\n",i);
			LISTA *boat=a[i].lista;
			while(boat!=NULL)
			{
				printf("\t\t%s ",boat->name);
				boat=boat->sig;
			}
		}	
	}
}
