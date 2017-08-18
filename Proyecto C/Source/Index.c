#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Estructuras.h>
#include <StopWords.h>
#include <Index_ABO.h>
#include <Index_LE.h>
#include <Index.h>

InvertedIndex* createIndex(char* pathDocumentsFile, StopWords* sw, code*statusCode)
{
	if (sw == NULL)
	{
		*statusCode = ERR_STOPWORDS_NOT_FOUND;
		return NULL;
	}

	FILE* archivoEntrada;
	InvertedIndex* index = NULL;
	char* palabra = NULL;
	int palabraValida = 0;
	
	archivoEntrada = fopen(pathDocumentsFile, "rb");

	if (archivoEntrada != NULL)
	{
		while (feof(archivoEntrada) == 0)
		{
			palabra = LeerPalabra(archivoEntrada);
			palabraValida = QuitarStopWords(palabra, sw);
			if (palabraValida == TRUE)
			{
				//Falta condicion para que no agregue palabras repetidas...!!
				//Falta funcion que agregue el id a la palabra
				// La idea es encontrar la palabra que no sea stopwords y agregar el indice.
				// texto2- tomo la palabra, la busco en el texto, si está, añado el indice a la lista.

				// Primero termino funcion que evite palabras repetidas.
				// Segundo creo funcion que almacene un texto.
				// Tercero busco en ese texto mi palabra.
				// Cuarto si la palabra está, agrego la id del texto a la palabra.
				// Tambien puedo agregar la cantidad de veces que aparece en el texto.
				index = InsertarPalabra(index, palabra);
			}
		}
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
	}
	preOrden(index);
	fclose(archivoEntrada);
	*statusCode = OK;
}

void saveIndex(InvertedIndex*i, int*id, code*statusCode)
{
	*id = obtenerID();
	printf("Soy la ID: %d\n", *id);
}

InvertedIndex* loadIndex(int id, code*statusCode)
{

}

int QuitarStopWords(char* palabra, StopWords* listaSW)
{
	int i = 0;
	int Largo = LargoStopWords(listaSW);
	char* stopWord = NULL;
	while(i < Largo)
	{
		stopWord = ObtenerStopWord(listaSW, i);
		if (strcmp(palabra, stopWord) == 0 || (strcmp(palabra, ".I") == 0) 
			|| (strcmp(palabra, ".T") == 0) || (strcmp(palabra, ".A") == 0)
			|| (strcmp(palabra, ".B") == 0) || (strcmp(palabra, ".W") == 0)
			|| (strcmp(palabra, ".") == 0))
		{
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

char* LeerPalabra(FILE* archivoEntrada)
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



int obtenerID()
{
    return (int)time(NULL);
}

