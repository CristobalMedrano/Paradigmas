#include <stdio.h>
#include <stdlib.h>
#include "buscador.h"

int main(int argc, char const *argv[])
{
	int opcion;
	do{
		opcion = SIN_INGRESO;
		LimpiarConsola();
		MostrarMenu();
		ValidarOpcionIngresada(&opcion, 1,8);

		switch(opcion)
		{
			case CARGAR_STOPWORDS: 
				printf("Cargando StopWords...\n");
				PresionarContinuar();
				break;

			case CREAR_INDEX: 
				printf("Creando Index...\n");
				PresionarContinuar();
				break;

			case GUARDAR_INDEX:
				printf("Guardando Index...\n");
				PresionarContinuar();
				break;

			case CARGAR_INDEX:
				printf("Cargando Index...\n");
				PresionarContinuar();
				break;

			case BUSCAR:
				printf("Buscando...\n");
				PresionarContinuar();
				break;

			case MOSTRAR_RESULTADOS:
				printf("Mostrando resultados...\n");
				PresionarContinuar();
				break;

			case ACERCA_DE:
				AcercaDe();
				PresionarContinuar();
				break;

			case SALIR:
				printf("Saliendo del programa...\n");
				break;
		}
	}while(opcion != 8);
	return 0;
}

void MostrarMenu()
{
	printf("***----------------------***\n");
	printf("**                        **\n");
	printf("*         PaDSearch        *\n");
	printf("*        Version 0.1       *\n");
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

void AcercaDe()
{
	LimpiarConsola();
	printf("Proyecto perteneciente a Paradigmas de Programacion 2-2017.\n\n");
	printf("Nombre: Cristobal Nicolas Medrano Alvarado.\n");
	printf("Rut: 19.083.864-1\n");
	printf("Correo: cristobal.medrano@usach.cl\n");
}

void PresionarContinuar()
{
	fflush(stdin);
	printf("\nPresione intro para continuar...");
	getchar();
}