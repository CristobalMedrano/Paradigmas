#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Estructuras.h>
#include <buscador.h>
#include <Menu.h>
#include <StopWords.h>
#include <Index.h>
#include <Procesamiento.h>

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int opcion;
	int id = 0;
	char* pathStopWordsFile = NULL;
	char* pathDocumentsFile = NULL;
	StopWords* listaSW = NULL;
	InvertedIndex* index = NULL;
	code statusCode;
	
	do
	{
		opcion = SIN_INGRESO;
		statusCode = FAIL;
		LimpiarConsola();
		MostrarMenu();
		ValidarOpcionIngresada(&opcion, 1,8);

		switch(opcion)
		{
			case CARGAR_STOPWORDS: 
				pathStopWordsFile = obtenerNombreArchivo();
				listaSW = loadStopWords(pathStopWordsFile, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CREAR_INDEX:
				pathDocumentsFile = obtenerNombreArchivo();
				index = createIndex(pathDocumentsFile, listaSW, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case GUARDAR_INDEX:
				id = obtenerID();
				printf("Guardando Index...\n");
				saveIndex(NULL, &id, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CARGAR_INDEX:
				printf("Cargando Index...\n");
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case BUSCAR:
				printf("Buscando...\n");
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case MOSTRAR_RESULTADOS:
				printf("Mostrando resultados...\n");
				MostrarStatusCode(statusCode);
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
	}while(opcion != SALIR);
	return 0;
}