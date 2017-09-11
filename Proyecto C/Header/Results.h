#ifndef _FUNC_RESULTS_H_
#define _FUNC_RESULTS_H_

#define FALSE 0
#define TRUE 1

Ranking* query(Index*i, StopWords*sw, char* text, code*statusCode);
void displayResults(Ranking *r, int TopK, code *statusCode);


Ranking* inicializarRanking();
Palabra* obtenerFrase(char* text, StopWords* sw);
//int* obtenerListaCoincidencias(Palabra* frase, Index* i, int* largoTotal);
int* obtenerListaCoincidencias(Palabra* frase, Index* i, int* largoListaCoincidencias, IndexListID** textDocs);
int* agregarIDLista(int* count, int* listaCoincidencias, Results* result);
int* ordenarLista(int* listaCoincidencias, int largoListaCoincidencias);
int* obtenerListaResults(int* lista, int largo, int* largoBase);
int elementoEnLista(int* lista, int largo, int elemento);
int* obtenerListaSinIDRepetidas(int* lista, int* largoBase, int largo);
int** agregarContadorID(int** matrizCoincidencias, int largo);
int** obtenerMatrizCoincidencias(int* lista, int largo);
int** ordenarMatrizCoincidencias(int** matrizCoincidencias, int largo);

Results* generarResultado(int* listaCoincidencias, int largoBase, IndexListID* textDocs);
#endif