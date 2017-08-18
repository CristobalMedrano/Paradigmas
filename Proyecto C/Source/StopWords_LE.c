#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <StopWords_LE.h>

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

int LargoStopWords(StopWords* listaSW)
{
	int i = 0;
	StopWords* indice = listaSW;
	while(indice != NULL)
	{
		indice = indice->siguiente;
		i++;
	}
	return i;
}

char* ObtenerStopWord(StopWords* listaSW, int pos)
{
	int i;
	if(pos < 0)
	{
		return NULL;
	}
	i = 0;
	StopWords* indice = listaSW;
	while(indice != NULL && i < pos)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice == NULL)
	{
		return NULL;
	}
	return indice->palabra;
}