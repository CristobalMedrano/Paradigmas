#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Results_LE.h>
#include <Index.h>

Result* CrearNodoIndex()
{
	Result* result = (Result*)malloc(sizeof(Result));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(result != NULL)
	{
	    result->id = 0;
		result->siguiente = NULL;
		return result;
	}
	else
	{
		return NULL;
	}
}

Result* InsertarIndex(Result* result, int pos, char* id)
{
	int i;
	if(pos < 0)
	{
		return result;
	}
	if(pos == 0)
	{
		Result* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->siguiente = result;
		return nuevaID;
	}
	i = 0;
	Result* indice = CrearNodoIndex();
	indice = result;
	while (indice != NULL && i < pos -1)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice != NULL)
	{
		Result* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->siguiente = indice->siguiente;
		indice->siguiente = nuevaID;
	}
	return result; 
}

void MostrarIndex(Result* result)
{
	if(result != NULL)
	{
        Result* auxiliar = CrearNodoIndex();
        auxiliar = result;
        while(auxiliar != NULL)
        {
            printf("- %s -", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
	}
	printf("\n");
}

int LargoIndex(Result* result)
{
	int i = 0;
	Result* indice = result;
	while(indice != NULL)
	{
		indice = indice->siguiente;
		i++;
	}
	return i;
}

char* ObtenerIndexID(Result* listaID, int pos)
{
	int i;
	if(pos < 0)
	{
		return NULL;
	}
	i = 0;
	Result* indice = listaID;
	while(indice != NULL && i < pos)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice == NULL)
	{
		return NULL;
	}
	return indice->id;
}