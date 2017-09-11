#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Estructuras.h>
#include <StopWords.h>
#include <Index_ABO.h>
#include <Results_ABO.h>
#include <Results_LE.h>
#include <Index.h>

// FUNCIONES PRINCIPALES
Index* createIndex(char* pathDocumentsFile, StopWords* sw, code*statusCode)
{
	if (sw == NULL)
	{
		*statusCode = ERR_STOPWORDS_NOT_FOUND;
		return NULL;
	}

	FILE* archivoEntrada;
	Index* index = NULL;
	IndexListID* resultID = NULL;
	char* textID = NULL;
	Title* textTitulo = NULL;
	Author* textAutor = NULL;
	char* palabra = NULL;
	
	archivoEntrada = fopen(pathDocumentsFile, "rb");

	if (archivoEntrada != NULL)
	{
		printf("Creando index...");
		while (feof(archivoEntrada) == 0)
		{
			textID = leerTextID(archivoEntrada);
			if (textID != NULL)
			{
				textTitulo = leerTextTitulo(archivoEntrada);
				textAutor = leerTextAutor(archivoEntrada);
				resultID = insertarResultsID(resultID, textID, textTitulo, textAutor);
			}
		}
		rewind(archivoEntrada);

		int textosIndexados = 0;
		while (feof(archivoEntrada) == 0)
		{
			palabra = LeerPalabra(archivoEntrada);
			if (strcmp(palabra, ".I") == 0)
			{
				textID = LeerPalabra(archivoEntrada);
				index = indexarPalabra(textID, textID, index, sw, resultID);
				textosIndexados++;
			}
			index = indexarPalabra(palabra, textID, index, sw, resultID);
		}

		// Indexo clave para guardar textos.
		index = indexarPalabra("save_index_text_docs", "-1", index, sw, resultID);
		Index* saveIndexText = BuscarPalabraIndex(index, "save_index_text_docs");
		saveIndexText->textosIndexados = textosIndexados;
		saveIndexText->saveTextDocs = resultID;

		//inOrdenResults(resultID); //muestra los documentos indexados.
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	/*
	//Para probar el indice 
	indexPalabra = BuscarPalabraIndex(index, "viscosity");
	printf("Palabra: viscosity\n");
	MostrarIndex(indexPalabra->resultsID);
	// lo siguiente muestra todas la palabras indexadas. 
	//postOrden(index);
	*/
	fclose(archivoEntrada);
	*statusCode = OK;
	return index;
}

void saveIndex(Index*i, int* id, code*statusCode)
{
	printf("Guardando index...\n");
	if (i == NULL)
	{
		*statusCode = ERR_INDEX_NOT_FOUND;
	}
	else
	{
		Index* saveIndexText = NULL;
		*id = obtenerID();
		char* fecha = obtenerFecha(id);
		char* saveID = generarNombreSave(id, 0);
		FILE *archivoSalida;
		archivoSalida = fopen(saveID, "wb");
		// funcion que guarda el texto.
		if (archivoSalida != NULL)
		{
			// Guardar los textos.
			saveIndexText = BuscarPalabraIndex(i, "save_index_text_docs");
			fprintf(archivoSalida, "%d\n", saveIndexText->textosIndexados);
			escribirTextDocs(archivoSalida, saveIndexText->saveTextDocs);

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

Index* loadIndex(int id, code* statusCode)
{
	Index* cargarIndex = NULL;
	IndexListID* indiceDocs = NULL;
	int numDocumentosIndexados = 0;
	
	char* loadID = generarNombreSave(&id, 0);
	FILE* archivoEntrada;
	
	archivoEntrada = fopen(loadID, "rb");
	if (archivoEntrada != NULL)
	{
		indiceDocs = cargarTextos(&numDocumentosIndexados, archivoEntrada);		
		cargarIndex = cargarPalabras(archivoEntrada, indiceDocs);

		// Indexo clave para guardar.
		Index* saveIndexText = BuscarPalabraIndex(cargarIndex, "save_index_text_docs");
		saveIndexText->textosIndexados = numDocumentosIndexados;
		saveIndexText->saveTextDocs = indiceDocs;
		*statusCode = OK;
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	
	fclose(archivoEntrada);
	*statusCode = OK;
	return cargarIndex;
}

// FUNCIONES EXTRAS

void saveRanking(Ranking *r, int *id, code *statusCode)
{
	printf("Guardando ranking...\n");
	*id = obtenerID();
	char* fecha = obtenerFecha(id);
	char* saveID = generarNombreSave(id, 1);
	FILE *archivoSalida;
	archivoSalida = fopen(saveID, "wb");
	// funcion que guarda el texto.
	if (archivoSalida != NULL && r != NULL)
	{
		fprintf(archivoSalida, "%s\n", r->text);
		fprintf(archivoSalida, "%d\n", r->numTextos);
		escribirRankingDocs(archivoSalida, r->busqueda);
        fprintf(archivoSalida, "%d\n", r->numTextos);
        escribirResults(archivoSalida, r->busqueda);
		fprintf(archivoSalida, "%s\n", fecha);
		*statusCode = OK;
	}
	else
	{
		*statusCode = ERR_FILE_NOT_PERMISSION;
	}
	fclose(archivoSalida);
}

Ranking* loadRanking(int id, code *statusCode)
{
	Ranking* ranking = (Ranking*)malloc(sizeof(Ranking));
	ranking->numTextos = 0;
	ranking->busqueda = NULL;

	IndexListID* indiceDocs = NULL;
	Results* result = NULL;
	char* text = NULL;
	int numDocumentosIndexados = 0;
	int numPalabras = 0;
	
	char* loadID = generarNombreSave(&id, 1);
	FILE* archivoEntrada;
	
	archivoEntrada = fopen(loadID, "rb");
	if (archivoEntrada != NULL)
	{
		text = obtenerTextLoad(archivoEntrada);
		indiceDocs = cargarTextos(&numDocumentosIndexados, archivoEntrada);
		int i = 0;
		fscanf(archivoEntrada, "%d", &numPalabras);
		char* id = NULL;
		while(i < numPalabras)
		{
			id = (char*)malloc(sizeof(char)*256);
			fscanf(archivoEntrada, "%s", id);
			result = insertarIndexOrdenado(result, indiceDocs, id);
			i++;
		}
		// Indexo clave para guardar.
		ranking->text = text;
		ranking->numTextos = numDocumentosIndexados;
		ranking->busqueda = result;
		*statusCode = OK;
	}
	else
	{
		*statusCode = ERR_FILE_NOT_FOUND;
		return NULL;
	}
	
	fclose(archivoEntrada);
	*statusCode = OK;
	return ranking;	

}

// FUNCIONES EXTRAS CREATEINDEX
char* leerTextID(FILE* archivoEntrada)
{
	char* textID = NULL;
	char* palabra = LeerPalabra(archivoEntrada);
	if (strcmp(palabra, ".I") == 0)
	{
		textID = LeerPalabra(archivoEntrada);
	}
	else
	{
		return NULL;
	}
	return textID;
}

Title* leerTextTitulo(FILE* archivoEntrada)
{
	Title* textTitulo = NULL;
	char* palabra = NULL;
	
	palabra = LeerPalabra(archivoEntrada);
	if (strcmp(palabra, ".T") == 0)
	{
		textTitulo = InsertarTitulo(textTitulo, ".T");
		do
		{
			palabra = LeerPalabra(archivoEntrada);
			textTitulo = InsertarTitulo(textTitulo, palabra);

		}while (strcmp(palabra, ".") != 0);
	}
	else
	{
		return NULL;
	}
	//MostrarTitulo(textTitulo);
	return textTitulo;
}

Author* leerTextAutor(FILE* archivoEntrada)
{
	Author* textAutor = NULL;
	char* palabra = LeerPalabra(archivoEntrada);
	if (strcmp(palabra, ".A") == 0)
	{
		textAutor = InsertarAutor(textAutor, ".A");
		do
		{
			palabra = LeerPalabra(archivoEntrada);
			textAutor = InsertarAutor(textAutor, palabra);	
		}while((strcmp(palabra, ".B") != 0) && (strcmp(palabra, ".W") != 0)
		 	&& (strcmp(palabra, ".I") != 0) && (strcmp(palabra, ".") != 0));
	}
	else
	{
		return NULL;
	}
	//MostrarAutor(textAutor);
	return textAutor;
}

Index* indexarPalabra(char* palabra, char* textID, Index* index ,StopWords* sw, IndexListID* resultID)
{
	Index* indexPalabra = NULL;
	Results* listaID = NULL;

	int noEsStopWord = FALSE;
	int palabraNoRepetida = FALSE;
	int idRepetida = FALSE;
	
	noEsStopWord = QuitarStopWords(palabra, sw);
	palabraNoRepetida = QuitarPalabraRepetida(index, palabra);

	if (noEsStopWord == TRUE)
	{
		// Si la palabra no existe en el indice.
		if (palabraNoRepetida == TRUE)
		{
			index = InsertarPalabra(index, palabra);
            if (listaID == NULL)
            {
                listaID = InsertarIndex(listaID, resultID, 0, textID);
                indexPalabra = BuscarPalabraIndex(index, palabra);
                indexPalabra->resultsID = listaID;
                listaID = NULL;
            }
            else
            {
                listaID = NULL;
                listaID = InsertarIndex(listaID, resultID, 0, textID);
                indexPalabra = BuscarPalabraIndex(index, palabra);
                indexPalabra->resultsID = listaID;
                listaID = NULL;
            }				
        }			
		else
		{
			// si la palabra esta en el indice.
			indexPalabra = BuscarPalabraIndex(index, palabra);
			listaID = indexPalabra->resultsID;
			//verifico la id
			idRepetida = VerificarIDRepetida(listaID, textID);
			// Si la id no se encuentra en la indexacion.
			if (idRepetida == TRUE)
			{
				listaID = InsertarIndex(listaID, resultID, 0, textID);
				indexPalabra->resultsID = listaID;
				listaID = NULL;
			}
		}
	}
	return index;
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

int QuitarPalabraRepetida(Index* index, char* palabra)
{
	Index* palabraInIndex = BuscarPalabraIndex(index, palabra);
	// Si la palabra no existe en el indice
	if (palabraInIndex == NULL)
	{
		return TRUE;
	}
	return FALSE;
}

int VerificarIDRepetida(Results* resultsID, char* textID)
{
	int i = 0;
	int Largo = LargoIndex(resultsID);
	char* textInID = NULL;
	while(i < Largo)
	{
		textInID = ObtenerIndexID(resultsID, i);
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

// FUNCIONES EXTRAS SAVEINDEX
int obtenerID()
{
    return (int)time(NULL);
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

char* generarNombreSave(int *id, int opcion)
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
		if (opcion == 0)
		{
			strcat(saveID, ".index");
		}
		if (opcion == 1)
		{
			strcat(saveID, ".ranking");
		}
		return saveID;
	}
	return NULL;
}

void escribirTextDocs(FILE* archivoSalida, IndexListID* resultID)
{
	if (resultID != NULL)
	{ 
		escribirTextDocs(archivoSalida, resultID->hijoIzquierdo);
		fprintf(archivoSalida, ".I %s\n", resultID->id);
		escribirTitulo(archivoSalida, resultID->titulo);
		escribirAutor(archivoSalida, resultID->autor);
	 	escribirTextDocs(archivoSalida, resultID->hijoDerecho);
 	}
}

void escribirTitulo(FILE* archivoSalida, Title* title)
{
	if(title != NULL)
	{
        Title* auxiliar = crearNodoTitulo();
        auxiliar = title;
        while(auxiliar != NULL)
        {
            fprintf(archivoSalida, "%s ", auxiliar->titulo);
            auxiliar = auxiliar->siguiente;
        }
	}
	fprintf(archivoSalida, "\n");
}

void escribirAutor(FILE* archivoSalida, Author* author)
{
	if(author != NULL)
	{
        Author* auxiliar = crearNodoAutor();
        auxiliar = author;
        while(auxiliar != NULL)
        {
            fprintf(archivoSalida, "%s ", auxiliar->autor);
            auxiliar = auxiliar->siguiente;
        }
	}
	fprintf(archivoSalida, "\n");
}

void EscribirPalabra(FILE* archivoSalida, Index* index)
{
	if (index != NULL)
	{ 
		EscribirPalabra(archivoSalida, index->hijoIzquierdo);
	 	EscribirPalabra(archivoSalida, index->hijoDerecho);
	 	fprintf(archivoSalida, "%s\n", index->palabra);
	 	EscribirIndicePalabra(archivoSalida, index->resultsID);
 	}
}

void EscribirIndicePalabra(FILE* archivoSalida, Results* result)
{
	int largo = LargoIndex(result);
	fprintf(archivoSalida, "Largo_ %d ", largo);
	if (result != NULL)
	{
		Results* auxiliar = CrearNodoIndex();
        auxiliar = result;
        while(auxiliar != NULL)
        {
        	fprintf(archivoSalida, "%s ", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
        fprintf(archivoSalida, "\n");
	}
}

// FUNCIONES EXTRAS LOADINDEX
int LeerNmoPalabra(FILE* archivoEntrada)
{
	int NmoPalabra = 0;
	fscanf(archivoEntrada, "%d", &NmoPalabra);
	return NmoPalabra;	
}

IndexListID* cargarTextos(int* numDocumentosIndexados, FILE* archivoEntrada)
{
	IndexListID* indiceDocs = NULL;
	char* textID = NULL;
	Title* textTitulo = NULL;
	Author* textAutor = NULL;
	int i = 0;
	
	fscanf(archivoEntrada, "%d", numDocumentosIndexados);
	//printf("indexados: %d\n", *numDocumentosIndexados);

	while (i < *numDocumentosIndexados) // Leo los documentos guardados.
	{
		textID = leerTextID(archivoEntrada);
		if (textID != NULL)
		{
			//printf("%s\n", textID);
			textTitulo = leerTextTitulo(archivoEntrada);
			textAutor = leerTextAutor(archivoEntrada);
			indiceDocs = insertarResultsID(indiceDocs, textID, textTitulo, textAutor);
			i++;
		}
	}
	return indiceDocs;
}

Index* cargarPalabras(FILE* archivoEntrada, IndexListID* indiceDocs)
{
	Index* cargarIndex = NULL;
	Index* indicePalabra = NULL;
	Results* listaID = NULL;
	char* palabra = NULL;
	int numPalabras = 0;
	int contListaPalabras = 0;
	int numListaPalabras = 0;

	int i = 0;
	fscanf(archivoEntrada, "%d", &numPalabras);

	while(i < numPalabras)
	{	
		// Funcion que lee la palabra.
		palabra = LeerPalabra(archivoEntrada);
		// Insertar la palabra en el index.
		cargarIndex = InsertarPalabra(cargarIndex, palabra);
		// Obtener el index de la palabra.
		indicePalabra = BuscarPalabraIndex(cargarIndex, palabra);
		// Leo Largo_
		palabra = LeerPalabra(archivoEntrada);
		if (strcmp(palabra, "Largo_") == 0)
		{
			contListaPalabras = 0;
			numListaPalabras = LeerNmoPalabra(archivoEntrada);

			while(contListaPalabras < numListaPalabras)
			{
				palabra = LeerPalabra(archivoEntrada);
				//printf(" %s ", palabra);
				listaID = InsertarIndex(listaID, indiceDocs, 0, palabra);
				contListaPalabras++;
			}
			indicePalabra->resultsID = listaID;
			listaID = NULL;
		}
		i++;
	}
	return cargarIndex;
}


// FUNCIONES EXTRAS - SAVE RANKING
void escribirRankingDocs(FILE* archivoSalida, Results* result)
{
	IndexListID* indiceDoc = NULL;
	if(result != NULL)
	{
        Results* auxiliar = CrearNodoIndex();
        auxiliar = result;
        while(auxiliar != NULL)
        {
        	indiceDoc = obtenerIndexID(result->textDocs, auxiliar->id);
        	fprintf(archivoSalida, ".I %s\n", auxiliar->id);
            escribirTitulo(archivoSalida, indiceDoc->titulo);
            escribirAutor(archivoSalida, indiceDoc->autor);
            auxiliar = auxiliar->siguiente;
        }
	}
}

void escribirResults(FILE* archivoSalida, Results* result)
{
	if(result != NULL)
	{
        Results* auxiliar = CrearNodoIndex();
        auxiliar = result;
        while(auxiliar != NULL)
        {
        	fprintf(archivoSalida, "%s ", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
	}
	fprintf(archivoSalida, "\n");
}

// FUNCIONES EXTRAS - LOAD RANKING
char* obtenerTextLoad(FILE* archivoEntrada)
{
	char *newText = NULL;
	char* text = (char*)malloc(sizeof(char)*256);
	fgets(text, 256, archivoEntrada);

	// Quitamos saltos de linea.
	newText = strtok(text, "\n");
	return newText;
}

// FUNCIONES UTILITARIAS
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