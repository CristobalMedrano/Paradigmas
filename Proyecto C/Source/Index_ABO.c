#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Index_ABO.h>

Index* InsertarPalabra(Index* index, char* palabra)
{
	Index* hoja = CrearHoja(palabra, NULL, NULL);
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

Index* CrearHoja(char* palabra, Index* index_izquierdo, Index* index_derecho)
{
	Index* nuevaHoja = (Index*)malloc(sizeof(Index)); 
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

Index* hijo_IZQUIERDO(Index* index)
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

Index* hijo_DERECHO(Index* index)
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

char* ObtenerPalabraIndex(Index* index)
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

Index* BuscarPalabraIndex(Index* index, char* palabra)
{
	Index* indice = index;
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

void preOrden(Index* index)
{
	if (index != NULL)
	{ 
 	printf("%s\n", index->palabra);
 	preOrden(index->hijoIzquierdo);
 	preOrden(index->hijoDerecho);
	}
}

void inOrden(Index* index)
{
	if (index != NULL)
	{ 
	inOrden(index->hijoIzquierdo);
	printf("%s\n", index->palabra);
 	inOrden(index->hijoDerecho);
 	}
}

void postOrden(Index* index)
{
	if (index != NULL)
	{ 
	postOrden(index->hijoIzquierdo);
 	postOrden(index->hijoDerecho);
	printf("%s\n", index->palabra);
 	}
}

int nElementos(Index* index)
{
	int n = 0;
	obtenerElemento(index, &n);
	return n;
}

void obtenerElemento(Index* index, int* n)
{
	if (index != NULL)
	{ 
		obtenerElemento(index->hijoIzquierdo, n);
		*n = *n + 1;
	 	obtenerElemento(index->hijoDerecho, n);
 	}
}