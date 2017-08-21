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
	InvertedIndex* indexPalabra = NULL;
	Index* listaID = NULL;
	char* palabra = NULL;
	int palabraValida = FALSE;
	int palabraNoRepetida = FALSE;
	int idRepetida = FALSE;
	int leerTexto = FALSE;
	char* textID = NULL;
	
	archivoEntrada = fopen(pathDocumentsFile, "rb");

	if (archivoEntrada != NULL)
	{
		printf("Creando index...\n");
		while (feof(archivoEntrada) == 0)
		{
			palabra = LeerPalabra(archivoEntrada);
			leerTexto = LeerTexto(palabra);
			if(leerTexto == TRUE)
			{
				textID = LeerPalabra(archivoEntrada);
				index =	InsertarPalabra(index, textID);
				listaID = InsertarIndex(listaID, 0, textID);
				indexPalabra = BuscarPalabraIndex(index, textID);
				indexPalabra->indexListID = listaID;
				listaID = NULL;

				//index = AgregarIndice(index, palabra, textID);
				//printf("Text(%s)\n", textID);
			}
			palabraValida = QuitarStopWords(palabra, sw);
			palabraNoRepetida = QuitarPalabraRepetida(index, palabra);

			if (palabraValida == TRUE)
			{
				// Si la palabra no existe en el indice.
				if (palabraNoRepetida == TRUE)
				{
					index = InsertarPalabra(index, palabra);
					listaID = InsertarIndex(listaID, 0, textID);
					indexPalabra = BuscarPalabraIndex(index, palabra);
					indexPalabra->indexListID = listaID;
					//printf("-------------- %s ----------------\n", textID);
					//MostrarIndex(indexPalabra->indexListID);
					//printf("-------------------------------\n");
					listaID = NULL;
				}			
				else
				{
					// si la palabra esta en el indice.
					indexPalabra = BuscarPalabraIndex(index, palabra);
					listaID = indexPalabra->indexListID;
					//verifico la id
					idRepetida = QuitarIDRepetida(listaID, textID);
					// Si la id no se encuentra en la indexacion.
					if (idRepetida == TRUE)
					{
						listaID = InsertarIndex(listaID, 0, textID);
						indexPalabra->indexListID = listaID;
						//printf("-------------- %s ----------------\n", textID);
						//MostrarIndex(indexPalabra->indexListID);
						//printf("-------------------------------\n");
						listaID = NULL;
					}
				}
			}
		}

	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	/* Para probar el indice --> servira para buscar.
	indexPalabra = BuscarPalabraIndex(index, "incompressible");
	printf("Palabra: incompressible\n");
	MostrarIndex(indexPalabra->indexListID); */
	//preOrden(index);
	fclose(archivoEntrada);
	*statusCode = OK;
	return index;
}

void saveIndex(InvertedIndex*i, int*id, code*statusCode)
{
	*id = obtenerID();
	printf("Soy la ID: %d\n", *id);
}

InvertedIndex* loadIndex(int id, code*statusCode)
{
	return NULL;
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

int QuitarPalabraRepetida(InvertedIndex* index, char* palabra)
{
	InvertedIndex* palabraInIndex = BuscarPalabraIndex(index, palabra);
	// Si la palabra no existe en el indice
	if (palabraInIndex == NULL)
	{
		return TRUE;
	}
	return FALSE;
}

int QuitarIDRepetida(Index* indexListID, char* textID)
{
	int i = 0;
	int Largo = LargoIndex(indexListID);
	char* textInID = NULL;
	while(i < Largo)
	{
		textInID = ObtenerIndexID(indexListID, i);
		if (textInID != NULL)
		{
			// Si encuentra la id del texto en la lista.
			if (strcmp(textInID, textID) == 0)
			{
				return FALSE;
			}
			else
			{
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}
		i++;
	}
	return TRUE;
}

int LeerTexto(char* palabra)
{
	if (strcmp(palabra, ".I") == 0)
	{
		return TRUE;
	}	
	return FALSE;
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

