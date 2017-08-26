#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Index_ABO.h>
#include <Results_LE.h>
#include <Results.h>

Ranking* query(Index*i, StopWords*sw, char* text, code*statusCode)
{
	if (i == NULL)
	{
		*statusCode = ERR_INDEX_NOT_FOUND; 
		return NULL;
	}
	if (sw == NULL)
	{
		*statusCode = ERR_STOPWORDS_NOT_FOUND; 
		return NULL;
	}

	printf("Buscando palabra... %s\n", text);
	i = BuscarPalabraIndex(i, text);
	if (i != NULL)
	{
		// Encontramos la palabra
		// Recorremos la list enlazada asociada
		showResults(i->indexListID, 10, statusCode);
		// Un result sera:
		//  ID: del txt (.I)
		//  Author (.A) // Falta modificar la lectura
		//				   para que lee esta linea y la guarde.
		// Guardamos en ranking la lista enlazada de results.
		//MostrarIndex(i->indexListID);
		*statusCode = OK;
	}
	else
	{
		printf("No esta su palabra.\n");
	}
	return NULL;
}
void showResults(Result* r, int TopK, code*statusCode)
{
	if(r != NULL)
	{
        Result* auxiliar = CrearNodoIndex();
        auxiliar = r;
        int i = 0;
        while(auxiliar != NULL && i < TopK)
        {
        	// Aca lo que sera una id.
        	printf("*********************************************\n");
            printf("ID: %s\n", auxiliar->id);
            printf("Title: Insert title here\n");
            printf("Author: Insert author here\n");
            printf("\n");
            auxiliar = auxiliar->siguiente;
            i++;
        }
		printf("*********************************************\n");

	}
	// a Result, le debe ingresar el indice de la palabra.
}