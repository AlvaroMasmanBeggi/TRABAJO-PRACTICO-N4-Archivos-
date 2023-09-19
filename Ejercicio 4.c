#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//declaro el tipo de dato estructura que vamos a usar//

struct ListadoDeImagenes
{
	int Codigo;
	char Nombre[MAX];
	char Extension[MAX];
	int Bytes;
	float Precio;
}stock[MAX];

//declaracion de las funciones a usar//

void AgregarImagen(struct ListadoDeImagenes *);
void EliminarImagen(struct ListadoDeImagenes *,int);
void ImprimirImagen(struct ListadoDeImagenes *);
void ModificarImagen(struct ListadoDeImagenes *,int);
int BuscarPorNombre(struct ListadoDeImagenes *, char *);
int BuscarPorExtension(struct ListadoDeImagenes *,char *);
int BuscarPorTamanoEnBytes(struct ListadoDeImagenes *,int);

//programa principal//

int main(int argc, char *argv[]) 
{
	int seleccionador,salir=0,cantidad=0,i=0,buscarcodigo,buscador,control=0,control1=0;
	int BuscarTamanoBytes;
	char buscar_nombre[MAX],buscar_extension[MAX];
	FILE *Archivo;
	
	
	while(salir!=1)
	{
		printf("\n\nMENU DE IMAGENES\n\n1-Agregar una nueva imagen\n2-Eliminar un elemento existente\n3-Modificar los datos de algún elemento\n4-Búsquedas por nombre de archivo, extensión, tamaño\n5-Mostrar todo\n6-Guardar en archivo y mostrarlo\n7-Salir\n\n");
		scanf("%d",&seleccionador);
		switch(seleccionador)
		{
		case 1: 			
				printf("\n\nIMAGEN %d",cantidad+1);
				AgregarImagen(&stock[cantidad]);
				cantidad++;
				break;
				
		case 2: printf("\nIngrese el codigo de la imagen a eliminar -> ");
				scanf("%d",&buscarcodigo);
				for(i=0;i<cantidad;i++)
				{
					EliminarImagen(&stock[i],buscarcodigo);
				}
				break;
				
		case 3: printf("\nIngrese el codigo de la imagen a modificar datos -> ");
				scanf("%d",&buscarcodigo);
				for(i=0;i<cantidad;i++)
				{
					ModificarImagen(&stock[i],buscarcodigo);
				}
				break;
				
		case 4: printf("\n¿Desea buscar...?\n1-Por Nombre de Archivo\n2-Por Extension\n3-Por Tamaño en Bytes de la imagen\n");
				scanf("%d",&buscador);
				fflush(stdin);
				switch(buscador)
				{
				case 1: fflush(stdin);
						printf("\nIngrese el nombre de la imagen a buscar: ");
						gets(buscar_nombre);
						fflush(stdin);
						control=0;
						for(i=0;i<cantidad;i++)
						{
							if((BuscarPorNombre(&stock[i],buscar_nombre))==1)
							{
								ImprimirImagen(&stock[i]);
								control=1;
							}
						}
						if(control==0)
						{
							printf("\nNo se ha encontrado en el stock de imagenes");
						}
						break;
						
				case 2:	fflush(stdin);
						printf("\nIngrese la extension de la imagen a buscar: ");
						gets(buscar_extension);
						control=0;
						fflush(stdin);
						for(i=0;i<cantidad;i++)
						{
							if((BuscarPorExtension(&stock[i],buscar_extension))==1)
							{
								ImprimirImagen(&stock[i]);
								control=1;
							}
						}
						if(control==0)
						{
							printf("\nNo se ha encontrado en el stock de imagenes");
						}
						break;
						
				case 3:	fflush(stdin);
						printf("\nIngrese el tamaño en Bytes de la imagen a buscar: ");
						scanf("%d",&BuscarTamanoBytes);
						control=0;
						fflush(stdin);
						for(i=0;i<cantidad;i++)
						{
							if((BuscarPorTamanoEnBytes(&stock[i],BuscarTamanoBytes))==1)
							{
								ImprimirImagen(&stock[i]);
								control=1;
							}
						}
						if(control==0)
						{
							printf("\nNo se ha encontrado en el stock de imagenes");
						}
						break;
						
				default: break;
				}
				break;
				
		case 5: for(i=0;i<cantidad;i++)
				{
					printf("\n------------------------------------------\n");
					printf("\nIMAGEN %d\n",i+1);
					ImprimirImagen(&stock[i]);
					printf("\n------------------------------------------\n");
				}
				break;
		case 6: if((Archivo=fopen("ArchivoImagenes","wb"))!=NULL)
				{
					fwrite(&stock,sizeof(struct ListadoDeImagenes),cantidad,Archivo);
				}
				else
				{
					printf("\nProblemas para abrir el archivo\n");
				}
				
				if((Archivo=fopen("ArchivoImagenes","rb"))!=NULL)
				{
					fread(&stock,sizeof(struct ListadoDeImagenes),cantidad,Archivo);
					for(i=0;i<cantidad;i++)
					{
						printf("\n------------------------------------------\n");
						printf("\nIMAGEN %d\n",i+1);
						ImprimirImagen(&stock[i]);
						printf("\n------------------------------------------\n");
					}
					
				}
				else
				{
					printf("\nProblemas para abrir el archivo\n");
				}
					
				break;
				
		case 7: salir=1;
				break;
				
		default:break;
		}
	}
	return 0;
}

//codigo de las funciones//

void AgregarImagen(struct ListadoDeImagenes *A)
{
	fflush(stdin);
	printf("\nCodigo de la imagen: ");
	scanf("%d",&A->Codigo);
	fflush(stdin);
	printf("\nNombre de la imagen: ");
	gets(A->Nombre);
	fflush(stdin);
	printf("\nExtension de la imagen: ");
	gets(A->Extension);
	fflush(stdin);
	printf("\nBytes de la imagen: ");
	scanf("%d",&A->Bytes);
	fflush(stdin);
	printf("\nPrecio de la imagen: ");
	scanf("%f",&A->Precio);
	fflush(stdin);
}


void EliminarImagen(struct ListadoDeImagenes *A,int cod)
{
	if(A->Codigo==cod)
	{
		A->Codigo=0;
		strcpy(A->Nombre,"Vacio");
		strcpy(A->Extension,"Vacio");
		A->Bytes=0;
		A->Precio=0.0;
	}
}

void ImprimirImagen(struct ListadoDeImagenes *A)
{
	printf("\n\n---------------------------------------\n\n");
	printf("\n\nCodigo de la imagen: %d",A->Codigo);
	
	printf("\n\nNombre de la imagen: ");
	puts(A->Nombre);
	
	printf("\nExtension de la imagen: ");
	puts(A->Extension);
	
	printf("\nBytes de la imagen: %d",A->Bytes);
	
	printf("\n\nPrecio de la imagen: %f",A->Precio);
	printf("\n\n---------------------------------------\n\n");
}


void ModificarImagen(struct ListadoDeImagenes *A,int cod)
{
	if(A->Codigo==cod)
	{
		fflush(stdin);
		printf("\nIngrese el nuevo codigo: ");
		scanf("%d",&A->Codigo);
		fflush(stdin);
		printf("\nIngrese el nuevo nombre: ");
		gets(A->Nombre);
		fflush(stdin);
		printf("\nIngrese la nueva extension: ");
		gets(A->Extension);
		fflush(stdin);
		printf("\nIngrese el nuevo tamaño en Bytes: ");
		scanf("%d",&A->Bytes);
		fflush(stdin);
		printf("\nIngrese el nuevo precio: ");
		scanf("%f",&A->Precio);
		fflush(stdin);
	}
}


int BuscarPorNombre(struct ListadoDeImagenes *A,char *B)
{
	int encontrar=0;
	
	if(strcmp(B,A->Nombre)==0)
	{
		encontrar=1;
	}
	
	return encontrar;
}

int BuscarPorExtension(struct ListadoDeImagenes *A,char *B)
{
	int encontrar=0;
	if(strcmp(B,A->Extension)==0)
	{
		encontrar=1;
	}
	return encontrar;
}

int BuscarPorTamanoEnBytes(struct ListadoDeImagenes *A, int Bytes)
{
	int encontrar=0;
	if(A->Bytes == Bytes)
	{
		encontrar=1;
	}
	return encontrar;
}
