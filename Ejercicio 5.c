#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//declaro los tipo de datos estructura que voy a usar//

struct BaseDeSensores
{
	char MarcaSensor[MAX];
	char TipoSensor[MAX];
	char UnidadMedida[MAX];
}SensorTipo[2];

struct Mediciones
{
	char Fecha[15];
	char Hora[15];
	struct BaseDeSensores Sensor;
	float ValorMedido;
	char Comentarios[150];
}MedidasLaboratorio[MAX]; //maximo 50 medidas//


//declaracion de funciones//

void AgregarMedicion(struct Mediciones *);
void EliminarMedicion(struct Mediciones *);
void ImprimirMedicion(struct Mediciones *);
void ModificarMedicion(struct Mediciones *);
int BuscarPorFecha(struct Mediciones *,char *);
int BuscarPorSensor(struct Mediciones *,int);
int BuscarPorValorMedido(struct Mediciones *,float);
void CargarBaseDeDatos(void);
void MostrarBaseDeDatos(void);
void GuardarEnArchivo(FILE *,int);
void LeerDeArchivo(FILE *, int);


//programa principal//

int main(int argc, char *argv[]) 
{
	
	// algunas variables auxiliares dentro del programa//
	
	int selector,salir=0,control=0,i,cantidad=0,NroMedicion,buscador,control1,buscar_sensor;
	char buscar_fecha[15];
	float buscar_valor_medido;
	FILE *Archivo;
	
	//creo una pequeña base de datos con los 3 sensores que voy a tener disponible//
	
	CargarBaseDeDatos();
	
	//funcionamiento del programa principal//
	
	printf("\nEl siguiente programa es para anotar mediciones meteorologicas, utilizando 3 sensores, uno de lluvia, uno de temperatura y otro de presion\n\n");
	system("pause");
	
	while(salir!=1)
	{
		system("cls");
		printf("\n\nMENU PRINCIPAL DE MEDICIONES\n\n1-Agregar una nueva medicion\n2-Eliminar mediciones existentes\n3-Modificar mediciones existentes\n4-Búsquedas por fecha, sensor o valor medido\n5-Mostrar todas las mediciones\n6-Guardar las mediciones en un archivo\n7-Leer los datos guardados en el archivo\n8-Salir\n\n");
		scanf("%d",&selector);
		switch(selector)
		{
		case 1:	fflush(stdin);
				cantidad=1;
				for(i=control;i<control+cantidad;i++)
				{
					AgregarMedicion(&MedidasLaboratorio[i]);
				}
				control=control+cantidad;
				break;
		
		case 2:	printf("\nSE MUESTRAN TODAS LAS MEDICIONES\n\n");
				for(i=0;i<control;i++)
				{
					printf("\n\n---------------------------------------\n\n");
					printf("MEDICION NRO: %d",i+1);
					ImprimirMedicion(&MedidasLaboratorio[i]);
					printf("\n\n---------------------------------------\n\n");
				}
				printf("\n\nINGRESE EL NUMERO DE LA MEDICION A ELIMINAR: ");
				scanf("%d",&NroMedicion);
				EliminarMedicion(&MedidasLaboratorio[NroMedicion-1]);
				system("pause");
				break;
		
		case 3:	printf("\nSE MUESTRAN TODAS LAS MEDICIONES\n\n");
				for(i=0;i<control;i++)
				{
					printf("\n\n---------------------------------------\n\n");
					printf("MEDICION NRO: %d",i+1);
					ImprimirMedicion(&MedidasLaboratorio[i]);
					printf("\n\n---------------------------------------\n\n");
				}
				printf("\n\nINGRESE EL NUMERO DE LA MEDICION A MODIFICAR: ");
				scanf("%d",&NroMedicion);
				ModificarMedicion(&MedidasLaboratorio[NroMedicion-1]);
				system("pause");
				break; 
		
		case 4: printf("\nComo desea buscar?\n\n1-Por Fecha\n2-Sensor\n3-ValorMedido\n");
				scanf("%d",&buscador);
				switch(buscador)
				{
				case 1:	fflush(stdin);
						printf("\nIngrese la fecha: ");
						gets(buscar_fecha);
						fflush(stdin);
						control1=0;
						for(i=0;i<control;i++)
						{
							if((BuscarPorFecha(&MedidasLaboratorio[i],buscar_fecha))==1)
							{
								printf("\n\n---------------------------------------\n\n");
								printf("MEDICION NRO: %d",i+1);
								ImprimirMedicion(&MedidasLaboratorio[i]);
								printf("\n\n---------------------------------------\n\n");
								control1=1;
								
							}
						}
						if(control1==0)
						{
							printf("\nNo se encontraron mediciones con esa fecha especificada\n");
							
						}
						system("pause");
						break;	
		
				case 2: control1=0;
		
						MostrarBaseDeDatos(); //muestro los sensores que tengo en el sistema//
						
						printf("\nIngrese el sensor a buscar: ");
						scanf("%d",&buscar_sensor);
						for(i=0;i<control;i++)
						{
							if(BuscarPorSensor(&MedidasLaboratorio[i],buscar_sensor) == 1)
							{
								printf("\n\n---------------------------------------\n\n");
								printf("MEDICION NRO: %d",i+1);
								ImprimirMedicion(&MedidasLaboratorio[i]);
								printf("\n\n---------------------------------------\n\n");
								control1=1;
								
							}
						}
						if(control1==0)
						{
							printf("\nNo se encontraron mediciones con ese sensor especificado\n");
							
						}
						system("pause");
						break;
		
				case 3: control1=0;
						printf("\nIngrese el valor medido de la medicion que desea buscar: ");
						scanf("%f",&buscar_valor_medido);
						for(i=0;i<control;i++)
						{
							if(BuscarPorValorMedido(&MedidasLaboratorio[i],buscar_valor_medido) == 1)
							{
								printf("\n\n---------------------------------------\n\n");
								printf("MEDICION NRO: %d",i+1);
								ImprimirMedicion(&MedidasLaboratorio[i]);
								printf("\n\n---------------------------------------\n\n");
								control1=1;
								
							}
						}
						if(control1==0)
						{
							printf("\nNo se encontraron mediciones con ese valor medido especificado\n");
							
						}
						system("pause");
						break;
						
				default: break;
				}
		break;
		
		case 5: for(i=0;i<control;i++)
				{
					printf("\n\n---------------------------------------\n\n");
					printf("MEDICION NRO: %d",i+1);
					ImprimirMedicion(&MedidasLaboratorio[i]);
					printf("\n\n---------------------------------------\n\n");
					
				}
				system("pause");
				break;
		
		case 6: GuardarEnArchivo(Archivo,control);	
				break;
				
		case 7: LeerDeArchivo(Archivo,control);
				break;
			
		case 8: salir=1;
				break;
		
		default: break;
		}
	}
	return 0;
}


//codigo de las funciones a utilizar//

void AgregarMedicion(struct Mediciones *A)
{
	int TipoDeSensorUsado=0;
	
	
	fflush(stdin);
	printf("\nIngrese la fecha de la medicion (dia/mes/año): ");
	gets(A->Fecha);
	fflush(stdin);
	printf("\nIngrese la hora de la medicion (hora:minutos): ");
	gets(A->Hora);
	fflush(stdin);
	
	
	printf("\n--DATOS DEL SENSOR--\n");
	printf("\nLOS SENSORES REGISTRADOS SON: \n");
	printf("\nSENSOR 1:\n");
	printf("Marca: ");
	puts(SensorTipo[0].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[0].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[0].UnidadMedida);
	
	printf("\nSENSOR 2:\n");
	printf("Marca: ");
	puts(SensorTipo[1].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[1].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[1].UnidadMedida);
	
	printf("\nSENSOR 3:\n");
	printf("Marca: ");
	puts(SensorTipo[2].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[2].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[2].UnidadMedida);
	
	printf("\n\nIngrese el tipo de sensor usado: ");
	scanf("%d",&TipoDeSensorUsado);
	switch(TipoDeSensorUsado)
	{
	case 1: strcpy(A->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[0].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida);
	break;
	
	case 2: strcpy(A->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[1].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida);
	break;
	
	case 3: strcpy(A->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[2].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida);
	break;
	
	default: break;
	}
	
	printf("\nIngrese el valor medido: ");
	scanf("%f",&A->ValorMedido);
	fflush(stdin);
	
	printf("\nIngrese algun comentario sobre la medicion: ");
	gets(A->Comentarios);
	fflush(stdin);
	
}

void ImprimirMedicion(struct Mediciones *A)
{
	
	printf("\n\nFecha de la Medicion:");
	puts(A->Fecha);
	
	printf("\n\nHora de la medicion: ");
	puts(A->Hora);
	
	printf("\n--DATOS DEL SENSOR USADO--\n");
	printf("\nMarca: ");
	puts(A->Sensor.MarcaSensor);
	
	printf("\nTipo: ");
	puts(A->Sensor.TipoSensor);
	
	printf("\nUnidad de Medida: ");
	puts(A->Sensor.UnidadMedida);
	
	printf("\n\nValor Medido: %.2f",A->ValorMedido);
	
	printf("\nComentario acerca de la Medicion: ");
	puts(A->Comentarios);
	
}

void EliminarMedicion(struct Mediciones *A)
{
	strcpy(A->Fecha," ");
	strcpy(A->Hora," ");
	strcpy(A->Sensor.MarcaSensor," ");
	strcpy(A->Sensor.TipoSensor," ");
	strcpy(A->Sensor.UnidadMedida," ");
	A->ValorMedido=0.0;
	strcpy(A->Comentarios," ");
}

void ModificarMedicion(struct Mediciones *A)
{
	int TipoDeSensorUsado;
	
	fflush(stdin);
	printf("\nIngrese la fecha de la nueva medicion: ");
	gets(A->Fecha);
	fflush(stdin);
	
	printf("\nIngrese la hora de la nueva medicion: ");
	gets(A->Hora);
	fflush(stdin);
	
	printf("\n--DATOS DEL SENSOR--\n");
	printf("\nLOS SENSORES REGISTRADOS SON: \n");
	printf("\nSENSOR 1:\n");
	printf("Marca: ");
	puts(SensorTipo[0].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[0].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[0].UnidadMedida);
	
	printf("\nSENSOR 2:\n");
	printf("Marca: ");
	puts(SensorTipo[1].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[1].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[1].UnidadMedida);
	
	printf("\nSENSOR 3:\n");
	printf("Marca: ");
	puts(SensorTipo[2].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[2].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[2].UnidadMedida);
	
	printf("\n\nIngrese el nuevo tipo de sensor usado: ");
	scanf("%d",&TipoDeSensorUsado);
	switch(TipoDeSensorUsado)
	{
	case 1: strcpy(A->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[0].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida);
	break;
	
	case 2: strcpy(A->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[1].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida);
	break;
	
	case 3: strcpy(A->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor);	
	strcpy(A->Sensor.TipoSensor,SensorTipo[2].TipoSensor);
	strcpy(A->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida);
	break;
	
	default: break;
	}
	
	printf("\nIngrese el nuevo valor medido: ");
	scanf("%f",&A->ValorMedido);
	fflush(stdin);
	
	printf("\nIngrese algun comentario sobre la nueva medicion: ");
	gets(A->Comentarios);
	fflush(stdin);
	
}

int BuscarPorFecha(struct Mediciones *A,char *B)
{
	int encontrar=0;
	if(strcmp(A->Fecha,B)==0)
	{
		encontrar=1;
	}
	return(encontrar);
}


int BuscarPorSensor(struct Mediciones *A,int BuscadorDeSensor)
{
	int encontrar=0;
	
	switch(BuscadorDeSensor)
	{
	case 1: if((strcmp(A->Sensor.MarcaSensor,SensorTipo[0].MarcaSensor))==0 && (strcmp(A->Sensor.TipoSensor,SensorTipo[0].TipoSensor))==0 && (strcmp(A->Sensor.UnidadMedida,SensorTipo[0].UnidadMedida))==0)
	{
		encontrar=1;
	}
	break;
	
	case 2:	if((strcmp(A->Sensor.MarcaSensor,SensorTipo[1].MarcaSensor))==0 && (strcmp(A->Sensor.TipoSensor,SensorTipo[1].TipoSensor))==0 && (strcmp(A->Sensor.UnidadMedida,SensorTipo[1].UnidadMedida))==0)
	{
		encontrar=1;
	}
	break;
	
	case 3:	if((strcmp(A->Sensor.MarcaSensor,SensorTipo[2].MarcaSensor))==0 && (strcmp(A->Sensor.TipoSensor,SensorTipo[2].TipoSensor))==0 && (strcmp(A->Sensor.UnidadMedida,SensorTipo[2].UnidadMedida))==0)
	{
		encontrar=1;
	}
	break;
	
	default: break;
	}
	return(encontrar);
}

int BuscarPorValorMedido(struct Mediciones *A,float BuscarValorMedido)
{
	int encontrar=0;
	if(A->ValorMedido == BuscarValorMedido)
	{
		encontrar=1;
	}
	return(encontrar);
}


void CargarBaseDeDatos(void)
{
	strcpy(SensorTipo[0].MarcaSensor,"Philips");
	strcpy(SensorTipo[0].TipoSensor,"Lluvia");
	strcpy(SensorTipo[0].UnidadMedida,"Milimetros");
	
	strcpy(SensorTipo[1].MarcaSensor,"Samsung");
	strcpy(SensorTipo[1].TipoSensor,"Temperatura");
	strcpy(SensorTipo[1].UnidadMedida,"Celsius");
	
	strcpy(SensorTipo[2].MarcaSensor,"Siemens");
	strcpy(SensorTipo[2].TipoSensor,"Presion");
	strcpy(SensorTipo[2].UnidadMedida,"Bar");
}

void MostrarBaseDeDatos(void)
{
	printf("\nLOS SENSORES REGISTRADOS SON: \n");
	printf("\nSENSOR 1:\n");
	printf("Marca: ");
	puts(SensorTipo[0].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[0].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[0].UnidadMedida);
	
	printf("\nSENSOR 2:\n");
	printf("Marca: ");
	puts(SensorTipo[1].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[1].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[1].UnidadMedida);
	
	printf("\nSENSOR 3:\n");
	printf("Marca: ");
	puts(SensorTipo[2].MarcaSensor);
	printf("Tipo: ");
	puts(SensorTipo[2].TipoSensor);
	printf("Unidad de Medida: ");
	puts(SensorTipo[2].UnidadMedida);
}

void GuardarEnArchivo(FILE *Archivo, int cant)
{
	if((Archivo=fopen("Mediciones.txt","wb"))!=NULL)
	{
		fwrite(&MedidasLaboratorio,sizeof(struct Mediciones),cant,Archivo);
		printf("\nSe guardo con exito\n");
		system("pause");
	}
	else
	{
		printf("\nProblemas al abrir el archivo");
	}
	fclose(Archivo);
}

void LeerDeArchivo(FILE *Archivo, int cant)
{
	struct Mediciones MedidasLaboratorioArchivo[MAX];
	
	if((Archivo=fopen("Mediciones.txt","rb"))!=NULL)
	{
		fread(&MedidasLaboratorioArchivo,sizeof(struct Mediciones),cant,Archivo);
		printf("\nSE LEYO DESDE EL ARCHIVO:\n\n");
		for( int i=0;i<cant;i++)
		{
			printf("\n\n---------------------------------------\n\n");
			printf("MEDICION NRO: %d",i+1);
			ImprimirMedicion(&MedidasLaboratorioArchivo[i]);
			printf("\n\n---------------------------------------\n\n");
			
		}
		system("pause");
	}
	else
	{
		printf("\nProblemas al abrir el archivo");
	}
	
	fclose(Archivo);
}

