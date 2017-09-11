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
	//srand(time(NULL));
	int opcion;
	int id = 0;
	int ultimaID = ULTIMA_ID_OFF;
	int TopK = 0;
	char* pathStopWordsFile = NULL;
	char* pathDocumentsFile = NULL;
	char* searchWord = NULL;
	StopWords* listaSW = NULL;
	Index* index = NULL;
	Ranking* ranking = NULL;
	code statusCode;
	
	do
	{
		opcion = SIN_INGRESO;
		statusCode = FAIL;
		LimpiarConsola();
		MostrarMenu(ultimaID, id);
		ValidarOpcionIngresada(&opcion, 1,10);

		switch(opcion)
		{
			case CARGAR_STOPWORDS: 
				pathStopWordsFile = obtenerNombre();
				listaSW = loadStopWords(pathStopWordsFile, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CREAR_INDEX:
				pathDocumentsFile = obtenerNombre();
				index = createIndex(pathDocumentsFile, listaSW, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case GUARDAR_INDEX:
				saveIndex(index, &id, &statusCode);
				printf("ID del Index creado: %d", id);
				ultimaID = SAVE_ID_ON;
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CARGAR_INDEX:
				printf("\nCargando Index...\n");
				id = obtenerIDArchivo();
				index = loadIndex(id, &statusCode);
				ultimaID = ULTIMA_ID_ON;
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case BUSCAR:
				searchWord = obtenerText(); 
				ranking = query(index, listaSW, searchWord, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case MOSTRAR_RESULTADOS:
				LimpiarConsola();
				TopK = resultadosAMostrar();
				displayResults(ranking, TopK, &statusCode);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case GUARDAR_RANKING:
				saveRanking(ranking, &id, &statusCode);
				printf("\nID del Ranking creado: %d\n", id);
				MostrarStatusCode(statusCode);
				PresionarContinuar();
				break;

			case CARGAR_RANKING:
				printf("\nCargando ranking...\n");
				id = obtenerIDArchivo();
				ranking = loadRanking(id, &statusCode);
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
