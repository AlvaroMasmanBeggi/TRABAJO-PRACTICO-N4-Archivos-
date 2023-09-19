#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 150

//declaracion de las funciones a utilizar//

int  VerificarNombredeArchivo(char *);


//programa principal//

int main(int argc, char *argv[]) 
{
	
	FILE *Archivo;
	char NombreDeArchivo[MAX];
	char TextoArchivo[MAX];
	int selecionador,salir=0;
	
	
	do
	{
	printf("Ingrese el nombre del Archivo: ");
	gets(NombreDeArchivo);
	fflush(stdin);
	}
	while(VerificarNombredeArchivo(&NombreDeArchivo[0])!=1);
	
	printf("\nEl archivo se creo correctamente\n");	
	
	while(salir!=1)
	{
		printf("\nQue desea hacer ? \n1-Ingresar texto\n2-Mostrar su contenido\n3-Salir\n");
		scanf("%d",&selecionador);
		fflush(stdin);
		
		switch(selecionador)
		{
		case 1:
				if((Archivo=fopen(NombreDeArchivo,"a"))!=NULL)
				{
					printf("\nIngrese el texto a escribir en el Archivo''%s'': ",NombreDeArchivo);
					gets(TextoArchivo);
					fprintf(Archivo,TextoArchivo);
				}
				fclose(Archivo);
				break;
				
		case 2:
				if((Archivo=fopen(NombreDeArchivo,"r"))!=NULL)
				{
					printf("\nEl texto leido desde''%s'': ",NombreDeArchivo);
					fgets(TextoArchivo,100,Archivo);
					puts(TextoArchivo);
				}
				fclose(Archivo);
				break;
		case 3: 
				salir=1;
				break;
		default: 
				break;
		}
	
	}
	return 0;
}



//codigo de las funciones //


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


