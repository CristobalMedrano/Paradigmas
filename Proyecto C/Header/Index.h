#ifndef _FUNC_INDEX_H_
#define _FUNC_INDEX_H_

#define TRUE 1
#define FALSE 0
#define TEXT_SC 0
#define TEXT_ID 1
#define TEXT_TITLE 2
#define TEXT_AUTHOR 3
#define TEXT_BODY 4
 
// Funciones Principales
Index* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode);
void saveIndex(Index*i, int*id, code*statusCode);
Index* loadIndex(int id, code*statusCode);

// FUNCIONES EXTRAS

void saveRanking(Ranking *r, int *id, code *statusCode);
void escribirRankingDocs(FILE* archivoSalida, Results* result);
void escribirResults(FILE* archivoSalida, Results* result);
Ranking* loadRanking(int id, code *statusCode);
char* obtenerTextLoad(FILE* archivoEntrada);


// Funciones extras createIndex
char* leerTextID(FILE* archivoEntrada);
Title* leerTextTitulo(FILE* archivoEntrada);
Author* leerTextAutor(FILE* archivoEntrada);
Index* indexarPalabra(char* palabra, char* textID, Index* index ,StopWords* sw, IndexListID* resultID);
int QuitarStopWords(char* palabra, StopWords* listaSW);
int QuitarPalabraRepetida(Index* index, char* palabra);
int VerificarIDRepetida(Results* resultsID, char* textID);

// Funciones extras saveIndex
int obtenerID();
char* obtenerFecha(int *id);
void escribirTextDocs(FILE* archivoSalida, IndexListID* resultID);
void escribirTitulo(FILE* archivoSalida, Title* title);
void escribirAutor(FILE* archivoSalida, Author* author);
void EscribirPalabra(FILE* archivoSalida, Index* index);
void EscribirIndicePalabra(FILE* archivoSalida, Results* result);

// Funciones extras loadIndex
int LeerNmoPalabra(FILE* archivoEntrada);
IndexListID* cargarTextos(int* numDocumentosIndexados, FILE* archivoEntrada);
Index* cargarPalabras(FILE* archivoEntrada, IndexListID* indiceDocs);

// Funciones utilitarias
char* LeerPalabra(FILE* archivoEntrada);
char* generarNombreSave(int *id, int opcion);

#endif