#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Estructuras.h>
#include <buscador.h>
#include <Menu.h>
#include <StopWords.h>
#include <Index.h>
#include <Results.h>

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int opcion;
	int id = 0;
	int ultimaID = ULTIMA_ID_OFF;
	char* pathStopWordsFile = NULL;
	char* pathDocumentsFile = NULL;
	char* searchWord = NULL;
	StopWords* listaSW = NULL;
	InvertedIndex* index = NULL;
	Ranking* ranking = NULL;
	code statusCode;
	
	do
	{
		opcion = SIN_INGRESO;
		statusCode = FAIL;
		LimpiarConsola();
		MostrarMenu(ultimaID, id);
		ValidarOpcionIngresada(&opcion, 1,8);

		switch(opcion)
		{
			case CARGAR_STOPWORDS: 
				pathStopWordsFile = obtenerNombre(ARCHIVO);
				listaSW = loadStopWords(pathStopWordsFile, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CREAR_INDEX:
				pathDocumentsFile = obtenerNombre(ARCHIVO);
				index = createIndex(pathDocumentsFile, listaSW, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case GUARDAR_INDEX:
				printf("Guardando Index...\n");
				saveIndex(index, &id, &statusCode);
				printf("ID del Index creado: %d\n", id);
				ultimaID = SAVE_ID_ON;
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CARGAR_INDEX:
				printf("Cargando Index...\n");
				id = obtenerIDArchivo();
				index = loadIndex(id, &statusCode);
				ultimaID = ULTIMA_ID_ON;
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case BUSCAR:
				searchWord = obtenerNombre(BUSCAR_PALABRA);
				ranking = query(index, listaSW, searchWord, &statusCode);
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