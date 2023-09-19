#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
#define LONG_NOM_ARCHIVO 20

//declaro las funciones a usar//

int  VerificarNombredeArchivo(char *);
void NuevoNombreArchivo(char *,char *);
void CrearArchivoOrigen(FILE *,char *);
void CopiarArchivo(FILE *, FILE *, char *,char *);

//programa principal//


int main(int argc, char *argv[]) 
{
	
	char Nombre_Archivo[LONG_NOM_ARCHIVO];
	char Nombre_Archivo_Copia[LONG_NOM_ARCHIVO+10];
	FILE *archivo_origen;
	FILE *archivo_destino;
	
	do
	{
		printf("\nIngrese el Nombre del Archivo origen con su extension: ");
		gets(Nombre_Archivo);
		fflush(stdin);
		
	} while((VerificarNombredeArchivo(&Nombre_Archivo[0]))!=1);
	
	CrearArchivoOrigen(archivo_origen,&Nombre_Archivo[0]);
	
	NuevoNombreArchivo(&Nombre_Archivo[0],&Nombre_Archivo_Copia[0]);
	
	CopiarArchivo(archivo_origen,archivo_destino,&Nombre_Archivo_Copia[0],&Nombre_Archivo[0]);
	
	return 0;
}


//codigo de ls funciones//



int  VerificarNombredeArchivo(char *A)
{
	char Cadena1[30],Cadena2[20];
	char *Paux=&Cadena1[0];
	char *Paux1=A;
	int VerificacionDeNombre=0,verificacion=0,VerificacionDeExtension=0,i=0,existe_punto=0;
	
	while(*Paux1!='\0')
	{
		if(*Paux1 == '.')
		{
			existe_punto=1;
		}
		Paux1++;
	}
	
	if(existe_punto==1)
	{
		while(*A!='.')
		{
			Cadena1[i]=*A;
			i++;
			A++;
			Cadena1[i]='\0';
		}
		
		
		A++;
		i=0;
		
		while(*A!='\0')
		{
			Cadena2[i]=*A;
			A++;
			i++;
			Cadena2[i]='\0';
		}
		
		
		while(*Paux!='\0')
		{
			if(*Paux==':' || *Paux==',' || *Paux==' ' || *Paux==';' || *Paux=='.' || *Paux=='[' || *Paux==']' || *Paux=='{' || *Paux=='}' || *Paux=='(' || *Paux==')' || *Paux=='=' || *Paux==' ' || *Paux=='/' || *Paux=='&' || *Paux=='%' || *Paux=='$' || *Paux=='#' || *Paux=='"' || *Paux=='!' || *Paux=='*' || *Paux=='-' || *Paux=='+' || *Paux=='<' || *Paux=='>' )
			{
				
				VerificacionDeNombre=0;
				break;
			}
			else
			{
				VerificacionDeNombre=1;
			}
			Paux++;
		}
		
		
		if(strcmp(Cadena2,"txt")==0)
		{
			VerificacionDeExtension=1;
		}
		else 
		{
			if(strcmp(Cadena2,"c")==0)
			{
				VerificacionDeExtension=1;
			}
			else
			{
				if(strcmp(Cadena2,"cpp")==0)
				{
					VerificacionDeExtension=1;
				}
				else
				{
					VerificacionDeExtension=0;
				}
			}
		}
		
		if( (VerificacionDeExtension==1) && (VerificacionDeNombre ==1) )
		{
			verificacion=1;
		}
		else 
		{
			verificacion=0;
		}
	}	
	
	return(verificacion);
}


void NuevoNombreArchivo(char *A,char *B)
{	
	strcpy(B,"Copia de ");
	strcat(B,A);
}

void CrearArchivoOrigen(FILE *A,char *Nom_Archivo)
{
	char TextoAlArchivo[MAX];
	
	if((A=fopen(Nom_Archivo,"w+"))!= NULL)
	{
		printf("\nIngrese lo que desea escribir en el archivo a copiar: ");
		gets(TextoAlArchivo);
		fprintf(A,"%s",TextoAlArchivo);
	}
	else
	{
		printf("\nProblemas para abrir el archivo origen");
	}
	fclose(A);
}

void CopiarArchivo(FILE *Origen, FILE *Destino, char *Nombre_Destino, char *Nombre_Origen)
{
	char Texto_Archivo[MAX];
	
	if((Origen=fopen(Nombre_Origen,"r"))!=NULL)
	{
		fgets(Texto_Archivo,MAX,Origen);
		printf("\nSe lee desde el origen: %s",Texto_Archivo);
		
	}
	else
	{
		printf("\nProblemas para abrir el archivo origen");
	}
	fclose(Origen);
	
	if((Destino=fopen(Nombre_Destino,"w+"))!=NULL)
	{
		fputs(Texto_Archivo,Destino);
	}
	else
	{
		printf("\nProblemas para abrir el archivo destino");
	}
	fclose(Destino);
	
	if((Destino=fopen(Nombre_Destino,"r"))!=NULL)
	{
		fgets(Texto_Archivo,MAX,Destino);
		fprintf(Destino,"%s",Texto_Archivo);
	}
	else
	{
		printf("\nProblemas para abrir el archivo destino");
	}
	fclose(Destino);
}
