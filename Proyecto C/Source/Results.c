#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Index_ABO.h>
#include <Index_LE.h>
#include <Results_ABO.h>
#include <Results.h>

Ranking* query(Index*i, StopWords*sw, char* text, code*statusCode)
{
	Ranking* ranking = inicializarRanking();

	if (i == NULL)
	{
		*statusCode = ERR_INDEX_NOT_FOUND; 
		return ranking;
	}
	if (sw == NULL)
	{
		*statusCode = ERR_STOPWORDS_NOT_FOUND; 
		return ranking;
	}

	printf("Buscando palabra... %s\n", text);
	i = BuscarPalabraIndex(i, text);
	if (i != NULL)
	{
		ranking->busqueda = i->resultsID;
		// Encontramos la palabra
		// Recorremos la list enlazada asociada
		//showResults(ranking->busqueda, 10, statusCode);
		// Guardamos en ranking la lista enlazada de results.
		*statusCode = OK;
		return ranking;
	}
	
	*statusCode = NO_SEARCH_RESULTS;
	return ranking;
}
void showResults(Results* r, int TopK, code*statusCode)
{
	if(r != NULL)
	{
		IndexListID* indice = NULL;
        Results* auxiliar = CrearNodoIndex();
        auxiliar = r;
        int i = 0;
        while(auxiliar != NULL && i < TopK)
        {
            indice = obtenerIndexID(r->textDocs, auxiliar->id);

        	// Aca lo que sera una id.
        	printf("*********************************************\n");
            printf("ID: %s\n", auxiliar->id);
            printf("Title: ");
            MostrarTitulo(indice->titulo);
            printf("Author: ");
            MostrarAutor(indice->autor);
            printf("\n");
            auxiliar = auxiliar->siguiente;
            i++;
        }
		printf("*********************************************\n");
		*statusCode = OK;
	}
	else
	{
		*statusCode = NO_SEARCH_RESULTS;
	}
}

Ranking* inicializarRanking()
{
	Ranking* ranking = (Ranking*)malloc(sizeof(Ranking));
	ranking->busqueda = NULL;
	return ranking;
}