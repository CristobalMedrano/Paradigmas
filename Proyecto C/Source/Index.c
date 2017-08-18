#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Estructuras.h>
#include <Index.h>

InvertedIndex* createIndex(char* pathDocumentsFile, StopWords* sw, code*statusCode)
{
	FILE* archivoEntrada;
	archivoEntrada = fopen(pathDocumentsFile, "rb");
}

void saveIndex(InvertedIndex*i, int*id, code*statusCode)
{
	*id = obtenerID();
	printf("Soy la ID: %d\n", *id);
}

InvertedIndex* loadIndex(int id, code*statusCode)
{

}







int obtenerID()
{
    return (int)time(NULL);
}

