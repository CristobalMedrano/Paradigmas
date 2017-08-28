#ifndef _FUNC_INDEX_H_
#define _FUNC_INDEX_H_

#define TRUE 1
#define FALSE 0
#define TEXT_SC 0
#define TEXT_ID 1
#define TEXT_TITLE 2
#define TEXT_AUTHOR 3
#define TEXT_BODY 4
 
// Creando IndexInvertido
Index* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode);

int QuitarStopWords(char* palabra, StopWords* listaSW);
int QuitarPalabraRepetida(Index* index, char* palabra);
int VerificarIDRepetida(Result* indexListID, char* textID);
int LeerTexto(char* palabra);
char* LeerPalabra(FILE* archivoEntrada);
void leerTitulo(FILE* archivoEntrada);

void leerTextoContiguo(char* palabra, char* textoContiguo);
Index* indexarID(Index* index, char** textID, FILE* archivoEntrada);
Index* indexarPalabra(char* palabra,char* textID, Index* index,StopWords* sw);
int leerTipoClasificacion(char* palabra);

// Guardando IndexInvertido
void saveIndex(Index*i, int*id, code*statusCode);

char* generarNombreSave(int *id);
char* obtenerFecha(int *id);
int obtenerID();
void EscribirPalabra(FILE* archivoSalida, Index* index);
void EscribirIndicePalabra(FILE* archivoSalida, Result* result);

// Cargando IndexInvertido
Index* loadIndex(int id, code*statusCode);
int LeerNmoPalabra(FILE* archivoEntrada);


#endif