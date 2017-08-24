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
                    if (listaID == NULL)
                    {
                        listaID = InsertarIndex(listaID, 0, textID);
                        indexPalabra = BuscarPalabraIndex(index, palabra);
                        indexPalabra->indexListID = listaID;
                        listaID = NULL;
                    }
                    else
                    {
                        listaID = NULL;
                        listaID = InsertarIndex(listaID, 0, textID);
                        indexPalabra = BuscarPalabraIndex(index, palabra);
                        indexPalabra->indexListID = listaID;
                        listaID = NULL;
                    }				
                }			
				else
				{
					// si la palabra esta en el indice.
					indexPalabra = BuscarPalabraIndex(index, palabra);
					listaID = indexPalabra->indexListID;
					//verifico la id
					idRepetida = VerificarIDRepetida(listaID, textID);
					// Si la id no se encuentra en la indexacion.
					if (idRepetida == TRUE)
					{
						listaID = InsertarIndex(listaID, 0, textID);
						indexPalabra->indexListID = listaID;
						listaID = NULL;
					}
				}
			}
			//MostrarIndex(indexPalabra->indexListID);

		}

	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	//Para probar el indice --> servira para buscar.
	/*indexPalabra = BuscarPalabraIndex(index, "viscosity");
	printf("Palabra: viscosity\n");*/
	//MostrarIndex(indexPalabra->indexListID);
	//postOrden(index);
	fclose(archivoEntrada);
	*statusCode = OK;
	return index;
}

void saveIndex(InvertedIndex*i, int*id, code*statusCode)
{
	if (i == NULL)
	{
		*statusCode = ERR_INDEX_NOT_FOUND;
	}
	else
	{
		*id = obtenerID();
		char* saveID = generarNombreSave(id);
		char* fecha = obtenerFecha(id);
		FILE *archivoSalida;
		archivoSalida = fopen(saveID, "w");
		if (archivoSalida != NULL)
		{
			// guardar Palabra, luego su lista con el largo de ella.
			fprintf(archivoSalida, "%d\n", 	nElementos(i));
			EscribirPalabra(archivoSalida, i);
			fprintf(archivoSalida, "%s", fecha);
			*statusCode = OK;
		}
		else
		{
			*statusCode = ERR_FILE_NOT_PERMISSION;
		}
		fclose(archivoSalida);
		*statusCode = OK;
	}	
}

InvertedIndex* loadIndex(int id, code* statusCode)
{
	InvertedIndex* load_Index = NULL;
	InvertedIndex* indicePalabra = NULL;
	Index* listaID = NULL;
	int n_Palabras = 0;
	int n_Lista_Palabras = 0;
	int cont_Lista_Palabras = 0;
	int i = 0;
	char* palabra = NULL;

	char* loadID = generarNombreSave(&id);
	FILE* archivoEntrada;
	archivoEntrada = fopen(loadID, "rb");
	if (archivoEntrada != NULL)
	{
		fscanf(archivoEntrada, "%d", &n_Palabras);
		//printf("Numero de palabras: %d\n", n_Palabras);
		while(i < n_Palabras)
		{	
			// Funcion que lee la palabra.
			palabra = LeerPalabra(archivoEntrada);
			// Insertar la palabra en el index.
			load_Index = InsertarPalabra(load_Index, palabra);
			// Obtener el index de la palabra.
			indicePalabra = BuscarPalabraIndex(load_Index, palabra);
			// Leo Largo_
			palabra = LeerPalabra(archivoEntrada);
			if (strcmp(palabra, "Largo_") == 0)
			{
				cont_Lista_Palabras = 0;
				n_Lista_Palabras = LeerNmoPalabra(archivoEntrada);

				while(cont_Lista_Palabras < n_Lista_Palabras)
				{
					palabra = LeerPalabra(archivoEntrada);
					//printf(" %s ", palabra);
					listaID = InsertarIndex(listaID, 0, palabra);
					cont_Lista_Palabras++;
				}
				indicePalabra->indexListID = listaID;
				listaID = NULL;
			}
			i++;
		}
		// retorno el indice invertido cargado.
		*statusCode = OK;
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	
	fclose(archivoEntrada);
	*statusCode = OK;
	return load_Index;
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

int VerificarIDRepetida(Index* indexListID, char* textID)
{
	int i = 0;
	int Largo = LargoIndex(indexListID);
	char* textInID = NULL;
	while(i < Largo)
	{
		textInID = ObtenerIndexID(indexListID, i);
		if (textInID != NULL)
		{
			// Si la id existe en la lista.
			if (strcmp(textInID, textID) == 0)
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
		i++;
	}
	// TRUE indica que no esta en la lista
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

int LeerNmoPalabra(FILE* archivoEntrada)
{
	int NmoPalabra = 0;
	fscanf(archivoEntrada, "%d", &NmoPalabra);
	return NmoPalabra;	
}

char* generarNombreSave(int *id)
{
	char* saveID = (char*)malloc(sizeof(char)*256);
	if (saveID != NULL)
	{
		// Convertimos la id en string.
		char strID[128];
		sprintf(strID, "%d", *id);

		// Concatenamos el nombre del archivo.
		strcpy(saveID, "save_");
		strcat(saveID, strID);
		strcat(saveID, ".index");
		return saveID;
	}
	return NULL;
}

char* obtenerFecha(int *id)
{
	char* fecha = (char*)malloc(sizeof(char)*256);
	if (fecha != NULL)
	{
		char hora[128];
		time_t tiempo = *id;
	    struct tm *tlocal = localtime(&tiempo);
	    strftime(hora, 128, "Fecha: %d/%m/%y Hora: %H:%M:%S", tlocal);
	    strcpy(fecha, hora);
	    return fecha;
	}
	return NULL;
}

int obtenerID()
{
    return (int)time(NULL);
}

void EscribirPalabra(FILE* archivoSalida, InvertedIndex* index)
{
	if (index != NULL)
	{ 
		EscribirPalabra(archivoSalida, index->hijoIzquierdo);
	 	EscribirPalabra(archivoSalida, index->hijoDerecho);
	 	fprintf(archivoSalida, "%s\n", index->palabra);
	 	EscribirIndicePalabra(archivoSalida, index->indexListID);
 	}
}

void EscribirIndicePalabra(FILE* archivoSalida, Index* index)
{
	int largo = LargoIndex(index);
	fprintf(archivoSalida, "Largo_ %d ", largo);
	if (index != NULL)
	{
		Index* auxiliar = CrearNodoIndex();
        auxiliar = index;
        while(auxiliar != NULL)
        {
        	fprintf(archivoSalida, "%s ", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
        fprintf(archivoSalida, "\n");
	}
}


