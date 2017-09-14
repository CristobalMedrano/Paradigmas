#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Estructuras.h>
#include <Index.h>
#include <Index_ABO.h>
#include <Results_LE.h>
#include <Results_ABO.h>
#include <Results.h>

Ranking* query(Index*i, StopWords*sw, char* text, code*statusCode)
{
	Ranking* ranking = inicializarRanking();

	if (i == NULL)
	{
		*statusCode = ERR_INDEX_NOT_FOUND; 
		return ranking;
	}
	if (sw == NULL)
	{
		*statusCode = ERR_STOPWORDS_NOT_FOUND; 
		return ranking;
	}
	if (text == NULL)
	{
		*statusCode = ERR_TEXT_INPUT_NOT_FOUND;
		return ranking;
	}
	
	IndexListID* textDocs = NULL;
	Palabra* frase = NULL;
	Results* nuevoResultado = NULL;
	frase = obtenerFrase(text, sw);
	int* listaCoincidencias = NULL;
	int largoTotal = 0;
	int largoBase = 0;
	if(frase != NULL)
	{
		listaCoincidencias = obtenerListaCoincidencias(frase, i, &largoTotal, &textDocs);
		if (listaCoincidencias != NULL)
		{
			listaCoincidencias = obtenerListaResults(listaCoincidencias, largoTotal, &largoBase);
			nuevoResultado = generarResultado(listaCoincidencias, largoBase - 1, textDocs);
			ranking->numTextos = largoBase-1;
			ranking->text = text;
			ranking->busqueda = nuevoResultado;
			*statusCode = OK;
			/*int res = solicitarVerResultados();
			if (res == 1)
			{
				displayResults(ranking, largoBase-1, statusCode);
			}*/
			return ranking;
		}
		else
		{
			*statusCode = NO_SEARCH_RESULTS;
			return ranking;
		}
		
	}
	*statusCode = NO_SEARCH_RESULTS;
	return ranking;
}

void displayResults(Ranking *r, int TopK, code *statusCode)
{
	if(r != NULL)
	{   
		IndexListID* indiceDoc = NULL;
		Results* result = r->busqueda;
		if(result != NULL)
		{
	        Results* auxiliar = CrearNodoIndex();
	        auxiliar = result;
       		int i = 0;
       		printf("\nSu consulta: '%s', genero %d coincidencias.\n", r->text, r->numTextos);

       		if (TopK > r->numTextos)
	        {
   		        printf("Resultados a mostrar (%d de %d).\n",  r->numTextos, r->numTextos);
	        }
	        else
	        {
	        	printf("Resultados a mostrar (%d de %d).\n",  TopK, r->numTextos);
	        }
       		printf("\nListado de documentos que cumplen con su busqueda: \n\n");

	        while(auxiliar != NULL && i < TopK)
	        {
	        	indiceDoc = obtenerIndexID(result->textDocs, auxiliar->id);
	            printf(".-- Documento(ID): %s --.\n", auxiliar->id);
	            printf("\n");
	            MostrarTitulo(indiceDoc->titulo);
	            MostrarAutor(indiceDoc->autor);
	            printf("\n'--------------------------------------'\n\n");
	            auxiliar = auxiliar->siguiente;
	            i++;
	        }
	        printf("Fin de la busqueda...\n\n");
	        *statusCode = OK;
		}
		else
		{
			*statusCode = NO_SEARCH_RESULTS;
		}
	
	}
	else
	{
		*statusCode = NO_SEARCH_RESULTS;
	}
}

void saveRanking(Ranking *r, int *id, code *statusCode)
{
	printf("Guardando ranking...\n");
	if (r == NULL)
	{
		*id = 0;
		*statusCode = ERR_RANKING_NOT_FOUND;
	}
	else
	{
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

Ranking* inicializarRanking()
{
	Ranking* ranking = (Ranking*)malloc(sizeof(Ranking));
	ranking->numTextos = 0;
	ranking->busqueda = NULL;
	return ranking;
}

Palabra* obtenerFrase(char* text, StopWords* sw)
{
	Palabra* frase = NULL;
	char *token = NULL;
	char *newText = NULL;
	int noEsStopWord = 0;
	char temporalText[256];
	char* temporalToken = NULL;

	// Quitamos saltos de linea.
	newText = strtok(text, "\n");
	// Copiamos el nuevo texto a un texto temporal.
	strcpy(temporalText, newText);

	token = strtok(temporalText, " ");
	while(token != NULL ) 
	{
		noEsStopWord = QuitarStopWords(token, sw);
		if(noEsStopWord == TRUE)
		{
			temporalToken = (char*)malloc(sizeof(char)*256);
			if (temporalToken != NULL)
			{
				strcpy(temporalToken, token);
				frase = InsertarPalabraFrase(frase, temporalToken);
			}
		}
		token = strtok(NULL," ");
	}
	//MostrarFrase(frase);
	return frase;
}

int* obtenerListaCoincidencias(Palabra* frase, Index* i, int* largoListaCoincidencias, IndexListID** textDocs)
{
	Index* searchIndex = NULL;
	int* listaCoincidencias = (int*)malloc(sizeof(int)*256);
	int count = 0;
	Palabra* auxiliar = crearNodoPalabra();
	auxiliar = frase;
	if (listaCoincidencias != NULL)
	{
		while(auxiliar != NULL)
		{
		    searchIndex = BuscarPalabraIndex(i, auxiliar->palabra);
		    if (searchIndex != NULL)
		    {
		    	*textDocs = searchIndex->resultsID->textDocs;
		    	//inOrdenResults(textDocs);
		    	//printf("%s\n", auxiliar->palabra);
		    	*largoListaCoincidencias = LargoIndex(searchIndex->resultsID) + *largoListaCoincidencias;
		    	listaCoincidencias = (int*)realloc(listaCoincidencias, sizeof(int)*(*largoListaCoincidencias+1));
		    	listaCoincidencias = agregarIDLista(&count, listaCoincidencias, searchIndex->resultsID);
		    }
		    auxiliar = auxiliar->siguiente;
		}
		// Si no existen elementos en la lista, retorna null.
		if (count == 0)
		{
			*largoListaCoincidencias = 0;
			return NULL;
		}
	}
	listaCoincidencias = ordenarLista(listaCoincidencias, *largoListaCoincidencias);
	return listaCoincidencias;
}

int* agregarIDLista(int* count, int* listaCoincidencias, Results* result)
{
	Results* indice = result;
	while(indice != NULL)
	{
		//int id = atoi(indice->id); // DESCONTINUADO...
		int id = toString(indice->id);
		listaCoincidencias[*count] = id;
		//printf("id: %d", id);
		indice = indice->siguiente;
		//printf("count: %d\n", *count);
		*count = *count + 1;
	}
	return listaCoincidencias;
}

int toString(char* a) 
{
	
	int c, sign, offset, n;

	if (a[0] == '-')
	{
		sign = -1;
	}

	if (sign == -1) 
	{
		offset = 1;
	}
	else
	{
		offset = 0;
	}

	n = 0;

	for (c = offset; a[c] != '\0'; c++)
	{
		n = n * 10 + a[c] - '0';
	}

	if (sign == -1)
	{
		n = -n;
	}
	return n;
}

int* ordenarLista(int* listaCoincidencias, int largoListaCoincidencias)
{
	int i;
	int j;
	int temp;
	for (i = 1; i < largoListaCoincidencias; ++i)
	{
		temp = listaCoincidencias[i];
		j = i - 1;
		while((listaCoincidencias[j] > temp)&&(j>=0))
		{
			listaCoincidencias[j+1] = listaCoincidencias[j];
			j--;
		}
		listaCoincidencias[j+1] = temp;
	}
	return listaCoincidencias;
}

int* obtenerListaResults(int* lista, int largo, int* largoBase)
{
	int** matrizCoincidencias = NULL;
	matrizCoincidencias = obtenerMatrizCoincidencias(lista, largo);
	if (matrizCoincidencias != NULL)
	{
		matrizCoincidencias = agregarContadorID(matrizCoincidencias, largo);
	}
	int* nuevaLista = obtenerListaSinIDRepetidas(matrizCoincidencias[0], largoBase, largo);
	return nuevaLista;
}

int** obtenerMatrizCoincidencias(int* lista, int largo)
{
	int** matrizCoincidencias = (int**)calloc(2, sizeof(int*));
	int i;
	for (i = 0; i < 2; ++i)
	{
	 	matrizCoincidencias[i] = (int*)calloc(largo, sizeof(int));
	}
	
	if (matrizCoincidencias != NULL)
	{
		int j;
		for (j = 0; j < largo; ++j)
		{
			matrizCoincidencias[0][j] = lista[j];
		}
		return matrizCoincidencias;
	}
	return NULL;
}

int** agregarContadorID(int** matrizCoincidencias, int largo)
{
	int i =0;
	int temp = 0;
	int count = 0;
	while(i < largo)
	{
		temp = matrizCoincidencias[0][i];
		count = 0;
		int j;
		for (j = 0; j < largo; ++j)
		{
			if (matrizCoincidencias[0][j] == temp)
			{
				count++;
			}
		}
		matrizCoincidencias[1][i] = count;
		i++;
	}
	matrizCoincidencias = ordenarMatrizCoincidencias(matrizCoincidencias, largo);
	return matrizCoincidencias;
}

int** ordenarMatrizCoincidencias(int** matrizCoincidencias, int largo)
{
	int i;
	int j;
	int temp;
	int temp2;
	for (i = 1; i < largo; ++i)
	{
		temp = matrizCoincidencias[1][i];
		temp2 = matrizCoincidencias[0][i];
		j = i - 1;
		while((matrizCoincidencias[1][j] > temp)&&(j>=0))
		{
			matrizCoincidencias[1][j+1] = matrizCoincidencias[1][j];
			matrizCoincidencias[0][j+1] = matrizCoincidencias[0][j];
			j--;
		}
		matrizCoincidencias[1][j+1] = temp;
		matrizCoincidencias[0][j+1] = temp2;
	}
	return matrizCoincidencias;
}

int* obtenerListaSinIDRepetidas(int* lista, int* largoBase, int largo)
{
	int* nuevaLista = (int*)calloc(1, sizeof(int));
	int k = 0;
	int p = 0;
	*largoBase = 1;
	int temp2 = 0;
	while(k < largo)
	{
		temp2 = lista[k];
		int seEncuentraEnLista = elementoEnLista(nuevaLista, *largoBase, temp2);
		if (seEncuentraEnLista == FALSE)
		{
			nuevaLista[p] = temp2;
			p++;
			*largoBase = *largoBase +1;
			nuevaLista = (int*)realloc(nuevaLista, sizeof(int)*(*largoBase));
		}
		k++;
	}
	return nuevaLista;
}

int elementoEnLista(int* lista, int largo, int elemento)
{
	int i;
	for (i = 0; i < largo; ++i)
	{
		if (lista[i] == elemento)
		{
			return TRUE;
		}
	}
	return FALSE;
}

Results* generarResultado(int* listaCoincidencias, int largoBase, IndexListID* textDocs)
{
	Results* nuevoResultado = NULL;
	int i;
	for (i = 0; i < largoBase; ++i)
	{
		char* id = (char*)malloc(sizeof(char)*256);
		sprintf(id, "%d", listaCoincidencias[i]);
		nuevoResultado = InsertarIndex(nuevoResultado, textDocs, 0, id);
	}
	return nuevoResultado;
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

int solicitarVerResultados()
{
	printf("Desea ver resultados de su busqueda: (y)/(n)\n");
	char* opcion = (char*)malloc(sizeof(char)*10);
	scanf("%c", opcion);
	if (strcmp(opcion, "y") == 0 || strcmp(opcion, "Y") == 0)
	{
		return 1;
	}
	if (strcmp(opcion, "n") == 0 || strcmp(opcion, "N") == 0)
	{
		return 0;
	}
	return 0;
}
