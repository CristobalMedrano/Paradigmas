#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Index_LE.h>
#include <Index.h>

Index* CrearNodoIndex()
{
	Index* index = (Index*)malloc(sizeof(Index));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(index != NULL)
	{
	    index->id = 0;
		index->siguiente = NULL;
		return index;
	}
	else
	{
		return NULL;
	}
}

Index* InsertarIndex(Index* index, int pos, int id)
{
	int i;
	if(pos < 0)
	{
		return index;
	}
	if(pos == 0)
	{
		Index* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->siguiente = index;
		return nuevaID;
	}
	i = 0;
	Index* indice = CrearNodoIndex();
	indice = index;
	while (indice != NULL && i < pos -1)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice != NULL)
	{
		Index* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->siguiente = indice->siguiente;
		indice->siguiente = nuevaID;
	}
	return index; 
}

void MostrarIndex(Index* index)
{
	if(index != NULL)
	{
        Index* auxiliar = CrearNodoIndex();
        auxiliar = index;
        while(auxiliar != NULL)
        {
            printf("Elemento: %d\n", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
	}
}

int LargoIndex(Index* index)
{
	int i = 0;
	Index* indice = index;
	while(indice != NULL)
	{
		indice = indice->siguiente;
		i++;
	}
	return i;
}

int ObtenerIndexID(Index* listaID, int pos)
{
	int i;
	if(pos < 0)
	{
		return 0;
	}
	i = 0;
	Index* indice = listaID;
	while(indice != NULL && i < pos)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice == NULL)
	{
		return 0;
	}
	return indice->id;
}