#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 20
#define MAX_TEXTO 1000


//declaracion de las funciones//

int VerificarNombredeArchivo(char *);
int VerificarExistenciaArchivo(FILE *,char *); 
void ReemplazarPalabra(char *, char *,char *,char *);


//programa principal//

int main(int argc, char *argv[]) 
{
	FILE *Origen,*Destino;
	char Nombre_Origen[MAX_NAME],Nombre_Destino[MAX_NAME];
	char Texto_Leido[MAX_TEXTO],Texto_Modificado[MAX_TEXTO],Texto_Destino[MAX_TEXTO];
	char PalabraReemplazar[MAX_NAME],PalabraReemplazo[MAX_NAME];
	int Cantidad_Caracteres=0;
	
	do
	{
		printf("\nIngrese el nombre del archivo origen: ");
		gets(Nombre_Origen);
		fflush(stdin);
		
	} while(((VerificarExistenciaArchivo(Origen,Nombre_Origen))!=1)  ||  ((VerificarNombredeArchivo(Nombre_Origen))!=1));
	
	
	do
	{
		printf("\nIngrese el nombre del archivo destino: ");
		gets(Nombre_Destino);
		fflush(stdin);
		
	} while(((VerificarExistenciaArchivo(Destino,Nombre_Destino))!=1)  ||  ((VerificarNombredeArchivo(Nombre_Destino))!=1));
	
	
	if((Origen=fopen(Nombre_Origen,"rb"))!=NULL)
	{
		Cantidad_Caracteres=fread(Texto_Leido,sizeof(char),MAX_TEXTO,Origen);
		Texto_Leido[Cantidad_Caracteres]='\0';
		printf("\nDEL ARCHIVO ORIGEN SE LEE: \n\n");
		puts(Texto_Leido);
	}
	fclose(Origen);
	
	printf("\n\nIngrese la palabra a reemplazar: ");
	gets(PalabraReemplazar);
	printf("\n\nIngrese la palabra reemplazo: ");
	gets(PalabraReemplazo);
	
	ReemplazarPalabra(Texto_Leido,PalabraReemplazar,PalabraReemplazo,Texto_Modificado);
	
	
	if((Destino=fopen(Nombre_Destino,"wb"))!=NULL)
	{
		fwrite(Texto_Modificado,sizeof(char),strlen(Texto_Modificado),Destino);
	}
	fclose(Destino);
	
	if((Destino=fopen(Nombre_Destino,"rb"))!=NULL)
	{
		Cantidad_Caracteres=fread(Texto_Destino,sizeof(char),strlen(Texto_Modificado),Destino);
		Texto_Destino[Cantidad_Caracteres]='\0';
		printf("\nDEL ARCHIVO DESTINO SE LEE: \n\n");
		puts(Texto_Destino);
	}
	fclose(Destino);
	return 0;
}

//codigo de las funciones//

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


int VerificarExistenciaArchivo(FILE *Archivo,char *NombreDelArchivo)
{
	int Existe=0;
	
	if((Archivo=fopen(NombreDelArchivo,"r"))!=NULL)
	{
		Existe=1;
	}
	
	return(Existe);
}


void ReemplazarPalabra(char *Texto, char *PalabraBuscada,char *PalabraReemplazo,char *TextoModificado)
{
	char Nuevo_Texto[MAX_TEXTO];
	char *posicion,*posicion_aux;
	int indice=0,contador=0;
	
	posicion=strstr(Texto,PalabraBuscada); //buscamos la primer ocurrecia de la palabra a  buscar//
	
	while(posicion!=NULL)
	{
		strncpy(Nuevo_Texto+indice,Texto,posicion-Texto);	//Copio en la nueva cadena la parte de lacadena original hasta la ocurrencia encontrada para reemplazarla//
		indice=indice+(posicion-Texto);						//actualizo el indice porque con él me muevo en la cadena donde almaceno el texto modificado//
		
		strcpy(Nuevo_Texto+indice,PalabraReemplazo);		//copio en la cadena nueva que voy creando la palabra reemplazante//
		indice=indice+strlen(PalabraReemplazo);				//vuelvo a actualizar el indice agregandole la longitud de la palbra reemplazante//
		
		Texto=posicion+strlen(PalabraBuscada);				//actualizo la posicion del puntero de la cadena original,llevandolo al siguiente lugar de la ocurrencia encontrada para buscar la segunda orcurrencia//
		
		posicion_aux=posicion;								//guardo la direccion del puntero posicion porque en el paso siguiente puede darme que no existen mas ocurrencias, es decir, NULL y no lo puedo usar en el while de mas abajo//
		posicion=strstr(Texto,PalabraBuscada);				//busco la siguiente ocurencia, luego de la ya encontrada arriba para verificar en el while y repetir en caso positivo//
	}
	while(*posicion_aux!='\0')
	{
		contador++;				//voy contando cuantos caracteres hay desde la ultima ocurrencia hasta el fin de cadena//
		posicion_aux++;
	}
	strncpy(Nuevo_Texto+indice,Texto,contador);  //concateno la ultima parte de la cadena original en la nueva, a partir de la ultima ocurrencia// 
	strcpy(TextoModificado,Nuevo_Texto);         //guardo todo en textomodificado para devolverle al usuario la cadena con la nuevas palabras cambiadas//
}
