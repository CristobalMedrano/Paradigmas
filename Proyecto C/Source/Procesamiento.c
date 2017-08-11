#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Procesamiento.h>

StopWords* loadStopWords(char* pathStopWordsFile, code*statusCode)
{
	FILE* archivoEntrada;
	archivoEntrada = fopen(pathStopWordsFile, "rb");
}

InvertedIndex* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode)
{
	FILE* archivoEntrada;
	archivoEntrada = fopen(pathDocumentsFile, "rb");
}

void saveIndex(InvertedIndex*i, int*id, code*statusCode){}

InvertedIndex* loadIndex(int id, code*statusCode){}

Result** query(InvertedIndex*i, StopWords*sw, char*q, code*statusCode){}

void showResults(Result*r, int TopK, code*statusCode){}


char* obtenerNombreArchivo()
{
	char* nombreArchivo = (char*)malloc(sizeof(char)*256);
	char nombreLeido[256];
	fflush(stdin);
	scanf("%s", nombreLeido);
	fflush(stdin);
	strcpy(nombreArchivo, nombreLeido);
	return nombreArchivo;
}


void ProbarEnumCode(code* statusCode)
{
	*statusCode = OK;
}
