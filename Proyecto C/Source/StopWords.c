#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
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
    		listaSW = InsertarStopWord(listaSW, 0, ObtenerPalabra(archivoEntrada));		
		}
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
	}
	return listaSW;
}

StopWords* CrearNodo()
{
	StopWords* listaSW = (StopWords*)malloc(sizeof(StopWords));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(listaSW != NULL)
	{
	    listaSW->palabra = NULL;
		listaSW->siguiente = NULL;
		return listaSW;
	}
	else{
		return NULL;
	}
}

StopWords* InsertarStopWord(StopWords* listaSW, int pos, char* palabra)
{
	int i;
	if(pos < 0)
	{
		return listaSW;
	}
	if(pos == 0)
	{
		StopWords* nuevaSW = CrearNodo();
		nuevaSW->palabra = palabra;
		nuevaSW->siguiente = listaSW;
		return nuevaSW;
	}
	i = 0;
	StopWords* indice = CrearNodo();
	indice = listaSW;
	while (indice != NULL && i < pos -1)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice != NULL)
	{
		StopWords* nuevaSW = CrearNodo();
		nuevaSW->palabra = palabra;
		nuevaSW->siguiente = indice->siguiente;
		indice->siguiente = nuevaSW;
	}
	return listaSW; 
}

void MostrarStopWords(StopWords* listaSW)
{
	if(listaSW != NULL)
	{
        StopWords* auxiliar = CrearNodo();
        auxiliar = listaSW;
        while(auxiliar != NULL)
        {
            printf("Elemento: %s\n", auxiliar->palabra);
            auxiliar = auxiliar->siguiente;
        }
	}
}

char* ObtenerPalabra(FILE* archivoEntrada)
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