#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Menu.h>

void MostrarMenu()
{
	printf("***----------------------***\n");
	printf("**                        **\n");
	printf("*         PaDSearch        *\n");
	printf("*        Version 0.5       *\n");
	printf("**                        **\n");
	printf("***----------------------***\n");
	printf("\n");
	printf("1.- Cargar StopWords.\n");
	printf("2.- Crear Index.\n");
	printf("3.- Guardar Index.\n");
	printf("4.- Cargar Index.\n");
	printf("5.- Buscar.\n");
	printf("6.- Mostrar Resultados.\n");
	printf("7.- Acerca de.\n");
	printf("8.- Salir.\n\n");
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
	getchar();
	
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        	getchar();
    #endif	
}

void MostrarStatusCode(code statusCode)
{
	printf("\n");
	switch(statusCode)
	{
		case OK: 
			printf("statusCode: OK\n");
			break;
		case NO_MEMORY: 
			printf("statusCode: NO_MEMORY\n");
			break;
		case ERR_FILE_NOT_FOUND: 
			printf("statusCode: ERROR_FILE_NOT_FOUND\n");
			break;
		case ERR_FILE_NOT_PERMISSION: 
			printf("statusCode: ERR_FILE_NOT_PERMISSION\n");
			break;
		case FAIL: 
			printf("statusCode: FAIL\n");
			break;
		case ERR_STOPWORDS_NOT_FOUND:
			printf("statusCode: ERR_STOPWORDS_NOT_FOUND\n");
			break;
	}
}

char* obtenerNombreArchivo()
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

void AcercaDe()
{
	LimpiarConsola();
	printf("Proyecto perteneciente a Paradigmas de Programacion 2-2017.\n\n");
	printf("Nombre: Cristobal Nicolas Medrano Alvarado.\n");
	printf("Rut: 19.083.864-1\n");
	printf("Correo: cristobal.medrano@usach.cl\n");

}
