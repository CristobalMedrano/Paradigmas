#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Results_LE.h>
#include <Results_ABO.h>


IndexListID* insertarResultsID(IndexListID* resultID, char* id, Title* titulo, Author* autor)
{
	IndexListID* hoja = crearHojaResults(id, titulo, autor, NULL, NULL);
	if (resultID == NULL)
	{
		return hoja;
	}
	if (hijoIzquierdoResults(resultID) == NULL && strcmp(obtenerResultsID(hoja),obtenerResultsID(resultID)) < 0)
	{
		resultID->hijoIzquierdo = hoja;
		return resultID;
	}
	if (hijoDerechoResults(resultID) == NULL && strcmp(id,obtenerResultsID(resultID)) >= 0)
	{
		resultID->hijoDerecho = hoja;
		return resultID;
	}
	if (strcmp(id,obtenerResultsID(resultID)) < 0)
	{
		resultID->hijoIzquierdo = insertarResultsID(hijoIzquierdoResults(resultID), id, titulo, autor);
		return resultID;
	}
	else
	{
		resultID->hijoDerecho = insertarResultsID(hijoDerechoResults(resultID), id, titulo, autor);
		return resultID;
	}
	return resultID;
}

IndexListID* crearHojaResults(char* id, Title* titulo, Author* autor, 
						IndexListID* index_izquierdo, IndexListID* index_derecho)
{
	IndexListID* nuevaHoja = (IndexListID*)malloc(sizeof(IndexListID)); 
	if(nuevaHoja!=NULL){ 
	    nuevaHoja->id = id;
	    nuevaHoja->titulo = titulo;
	    nuevaHoja->autor = autor;
		nuevaHoja->hijoIzquierdo = index_izquierdo;
		nuevaHoja->hijoDerecho = index_derecho;

		return nuevaHoja;
	} 
	else{
		printf("No es posible asignar memoria para crearHoja");
		return NULL; 
	} 
}

IndexListID* hijoIzquierdoResults(IndexListID* resultID)
{
	if (resultID == NULL)
	{
		return NULL;
	}
	else
	{
		return resultID->hijoIzquierdo;
	}
}

IndexListID* hijoDerechoResults(IndexListID* resultID)
{
	if (resultID == NULL)
	{
		return NULL;
	}
	else
	{
		return resultID->hijoDerecho;
	}
	return resultID;
}

char* obtenerResultsID(IndexListID* resultID)
{
	if (resultID == NULL)
	{
		return NULL;
	}
	else
	{
		return resultID->id;
	}
}

IndexListID* buscarResultsID(IndexListID* resultID, char* id)
{
	IndexListID* indice = resultID;
	while (indice != NULL)
	{
		char* palabraActual = obtenerResultsID(indice);
		if (strcmp(id, palabraActual) == 0)
		{
			return indice;
		}
		if (strcmp(id, palabraActual) < 0)
		{
			indice = hijoIzquierdoResults(indice);
		}
		else
		{
			indice = hijoDerechoResults(indice);
		}
	}
	return NULL;
}

void inOrdenResults(IndexListID* resultID)
{
	if (resultID != NULL)
	{ 
	inOrdenResults(resultID->hijoIzquierdo);
	printf("%s\n", resultID->id);
	MostrarTitulo(resultID->titulo);
	MostrarAutor(resultID->autor);
 	inOrdenResults(resultID->hijoDerecho);
 	}
}

char* obtenerIDdesdeIndex(IndexListID* index)
{
	if (index == NULL)
	{
		return NULL;
	}
	else
	{
		return index->id;
	}
}

IndexListID* obtenerIndexID(IndexListID* index, char* id)
{
	IndexListID* indice = index;
	while (indice != NULL)
	{
		char* palabraActual = obtenerIDdesdeIndex(indice);
		if (strcmp(id, palabraActual) == 0)
		{
			return indice;
		}
		if (strcmp(id, palabraActual) < 0)
		{
			indice = hijoIzquierdoResults(indice);
		}
		else
		{
			indice = hijoDerechoResults(indice);
		}
	}
	return NULL;
}