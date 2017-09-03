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
char* generarNombreSave(int *id);
void EscribirPalabra(FILE* archivoSalida, Index* index);
void EscribirIndicePalabra(FILE* archivoSalida, Results* result);

// Funciones extras loadIndex
int LeerNmoPalabra(FILE* archivoEntrada);

// Funciones utilitarias
char* LeerPalabra(FILE* archivoEntrada);

#endif