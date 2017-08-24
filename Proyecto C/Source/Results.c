#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Index_ABO.h>
#include <Index_LE.h>
#include <Results.h>

Ranking* query(InvertedIndex*i, StopWords*sw, char* text, code*statusCode)
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

	printf("Estamos buscando su palabra: %s\n", text);
	i = BuscarPalabraIndex(i, text);
	if (i != NULL)
	{
		MostrarIndex(i->indexListID);
		*statusCode = OK;
	}
	else
	{
		printf("No esta su palabra.\n");
	}
	return NULL;
}
void showResults(Result*r, int TopK, code*statusCode){}