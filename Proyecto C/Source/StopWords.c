#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <StopWords_LE.h>
#include <StopWords.h>

StopWords* loadStopWords(char* pathStopWordsFile, code* statusCode)
{
	FILE* archivoEntrada = NULL;
	StopWords* listaSW = NULL;
	
	archivoEntrada = fopen(pathStopWordsFile, "rb");
	
	if (archivoEntrada != NULL)
	{
		while (feof(archivoEntrada) == 0)
		{
    		listaSW = InsertarStopWord(listaSW, 0, LeerStopWord(archivoEntrada));		
		}
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	
	fclose(archivoEntrada);
	*statusCode = OK;
	return listaSW;
}

char* LeerStopWord(FILE* archivoEntrada)
{
	char* palabra = (char*)malloc(sizeof(char)* 256);
	if (palabra != NULL)
	{
		char obtenerPalabra[256];
		fscanf(archivoEntrada, "%s", obtenerPalabra);
		strcpy(palabra, obtenerPalabra);
	}
	return palabra;	
}