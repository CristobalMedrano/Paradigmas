#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Index_ABO.h>

InvertedIndex* InsertarPalabra(InvertedIndex* index, char* palabra)
{
	InvertedIndex* hoja = CrearHoja(palabra, NULL, NULL);
	if (index == NULL)
	{
		return hoja;
	}
	if (hijo_IZQUIERDO(index) == NULL && strcmp(ObtenerPalabraIndex(hoja),ObtenerPalabraIndex(index)) < 0)
	{
		index->hijoIzquierdo = hoja;
		return index;
	}
	if (hijo_DERECHO(index) == NULL && strcmp(palabra,ObtenerPalabraIndex(index)) >= 0)
	{
		index->hijoDerecho = hoja;
		return index;
	}
	if (strcmp(palabra,ObtenerPalabraIndex(index)) < 0)
	{
		index->hijoIzquierdo = InsertarPalabra(hijo_IZQUIERDO(index), palabra);
		return index;
	}
	else
	{
		index->hijoDerecho = InsertarPalabra(hijo_DERECHO(index), palabra);
		return index;
	}
	return index;
}

InvertedIndex* CrearHoja(char* palabra, InvertedIndex* index_izquierdo, InvertedIndex* index_derecho)
{
	InvertedIndex* nuevaHoja = (InvertedIndex*)malloc(sizeof(InvertedIndex)); 
	if(nuevaHoja!=NULL){ 
	    nuevaHoja->palabra = palabra;
		nuevaHoja->hijoIzquierdo = index_izquierdo;
		nuevaHoja->hijoDerecho = index_derecho;

		return nuevaHoja;
	} 
	else{
		printf("No es posible asignar memoria para crearHoja");
		return NULL; 
	} 
}

InvertedIndex* hijo_IZQUIERDO(InvertedIndex* index)
{
	if (index == NULL)
	{
		return NULL;
	}
	else
	{
		return index->hijoIzquierdo;
	}
}

InvertedIndex* hijo_DERECHO(InvertedIndex* index)
{
	if (index == NULL)
	{
		return NULL;
	}
	else
	{
		return index->hijoDerecho;
	}
	return index;
}

char* ObtenerPalabraIndex(InvertedIndex* index)
{
	if (index == NULL)
	{
		return NULL;
	}
	else
	{
		return index->palabra;
	}
}

InvertedIndex* BuscarPalabraIndex(InvertedIndex* index, char* palabra)
{
	InvertedIndex* indice = index;
	while (indice != NULL)
	{
		char* palabraActual = ObtenerPalabraIndex(indice);
		if (strcmp(palabra, palabraActual) == 0)
		{
			return indice;
		}
		if (strcmp(palabra, palabraActual) < 0)
		{
			indice = hijo_IZQUIERDO(indice);
		}
		else
		{
			indice = hijo_DERECHO(indice);
		}
	}
	return NULL;
}

void preOrden(InvertedIndex* index)
{
	if (index != NULL)
	{ 
 	printf("%s\n", index->palabra);
 	preOrden(index->hijoIzquierdo);
 	preOrden(index->hijoDerecho);
	}
}