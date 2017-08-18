#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Estructuras.h>
#include <Procesamiento.h>
/*


InvertedIndex* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode)
{
	FILE* archivoEntrada;
	archivoEntrada = fopen(pathDocumentsFile, "rb");
}

InvertedIndex* loadIndex(int id, code*statusCode){}

Result** query(InvertedIndex*i, StopWords*sw, char*q, code*statusCode){}

void showResults(Result*r, int TopK, code*statusCode){}*/

/*

char* obtenerFecha(int *id)
{
	static char hora[128];
	time_t tiempo = *id;
    struct tm *tlocal = localtime(&tiempo);
    hora[0] = '\0';
    strftime(hora, 128, "Fecha: %d/%m/%y Hora: %H:%M:%S", tlocal);
    return hora;
}
*/
int obtenerID()
{
    return (int)time(NULL);
}
void ProbarEnumCode(code* statusCode)
{
	*statusCode = OK;
}
