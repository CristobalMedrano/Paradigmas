#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <buscador.h>
#include <Menu.h>

void MostrarMenu(int ultimaID, int id)
{
	printf("***----------------------***\n");
	printf("**                        **\n");
	printf("*         PaDSearch        *\n");
	printf("*        Version 1.0       *\n");
	printf("**                        **\n");
	printf("***----------------------***\n");
	printf("\n");
	if(ultimaID == ULTIMA_ID_ON)printf("Ultima ID cargada: %d\n\n", id);
	if(ultimaID == SAVE_ID_ON)printf("Ultima ID guardada: %d\n\n", id);
	printf("1.- Cargar StopWords.\n");
	printf("2.- Crear Index.\n");
	printf("3.- Guardar Index.\n");
	printf("4.- Cargar Index.\n");
	printf("5.- Consultar(Query).\n");
	printf("6.- Mostrar Resultados.\n");
	printf("7.- Guardar Ranking.\n");
	printf("8.- Cargar Ranking.\n");
	printf("9.- Acerca de.\n");
	printf("10.- Salir.\n\n");
	printf("Ingrese la opcion deseada: ");

}

void ValidarOpcionIngresada(int* opcionIngresada, int Min, int Max)
{
	do
	{
		fflush(stdin); // Limpiamos buffer de entrada.
		if ((scanf("%d", opcionIngresada) == 0) || (*opcionIngresada < Min || *opcionIngresada > Max))
		{
		    while (getchar() != '\n');
		    printf("Error. Ingrese una opcion valida: ");
		    fflush(stdin); // Limpiamos buffer.
		}
		
	} while (*opcionIngresada < Min || *opcionIngresada > Max);
}

void LimpiarConsola()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void PresionarContinuar()
{
	fflush(stdin);
	printf("\nPresione intro para continuar...");
	while (getchar() != '\n');	
}

void MostrarStatusCode(code statusCode)
{
	printf("\n");
	switch(statusCode)
	{
		case OK: 
			printf("statusCode: OK\n" );
			break;
		case NO_MEMORY: 
			printf("statusCode: NO_MEMORY\n" );
			break;
		case ERR_FILE_NOT_FOUND: 
			printf("statusCode: ERROR_FILE_NOT_FOUND\n");
			break;
		case ERR_FILE_NOT_PERMISSION: 
			printf("statusCode: ERR_FILE_NOT_PERMISSION\n");
			break;
		case FAIL: 
			printf("statusCode: FAIL\n" );
			break;
		case ERR_STOPWORDS_NOT_FOUND:
			printf("statusCode: ERR_STOPWORDS_NOT_FOUND\n");
			break;
		case ERR_INDEX_NOT_FOUND:
			printf("statusCode: ERR_INDEX_NOT_FOUND\n");
			break;
		case ERR_RANKING_NOT_FOUND:
			printf("statusCode: ERR_RANKING_NOT_FOUND\n");
			break;
		case NO_SEARCH_RESULTS:
			printf("statusCode: NO_SEARCH_RESULTS\n");
			break;
		case ERR_TEXT_INPUT_NOT_FOUND:
			printf("statusCode: ERR_TEXT_INPUT_NOT_FOUND\n");
	}
}

char* obtenerNombre()
{
	printf("Ingrese el nombre del archivo: ");
	char* nombreArchivo = (char*)malloc(sizeof(char)*256);
	char nombreLeido[256];
	fflush(stdin);
	scanf("%s", nombreLeido);
	fflush(stdin);
	strcpy(nombreArchivo, nombreLeido);
	return nombreArchivo;
}

char* obtenerText()
{
	char* nombreText = NULL;
	char temporalNombreText[256];
	printf("Consultar: ");
	fflush(stdin);
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        getchar();
    #endif
	if( fgets(temporalNombreText, 256, stdin) != NULL)
	{
		fflush(stdin);
		if (strlen(temporalNombreText) != 1)
		{
			nombreText = (char*)malloc(sizeof(char)*256);
			strcpy(nombreText, temporalNombreText);
			return nombreText;
		}
		else
		{
			nombreText = NULL;
			return nombreText;
		}
	    
	}
	return nombreText;
}

int obtenerIDArchivo()
{
	printf("Ingrese el nombre del archivo: ");
	int idArchivo = 0;
	fflush(stdin);
	scanf("%d", &idArchivo);
	fflush(stdin);
	return idArchivo;
}
int resultadosAMostrar()
{
	int cantidad;
	printf("Ingrese la cantidad de resultados a mostrar: ");
	if(scanf("%d", &cantidad) == 0)
	{
		return 0;
	}
	return cantidad;
}

void AcercaDe()
{
	LimpiarConsola();
	printf("Proyecto perteneciente a Paradigmas de Programacion 2-2017.\n\n");
	printf("Nombre: Cristobal Nicolas Medrano Alvarado.\n");
	printf("Rut: 19.083.864-1\n");
	printf("Correo: cristobal.medrano@usach.cl\n");

}
