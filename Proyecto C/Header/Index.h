#ifndef INDEX
#define INDEX

#define TRUE 1
#define FALSE 0

InvertedIndex* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode);
void saveIndex(InvertedIndex*i, int*id, code*statusCode);
InvertedIndex* loadIndex(int id, code*statusCode);

int QuitarStopWords(char* palabra, StopWords* listaSW);
int QuitarPalabraRepetida(InvertedIndex* index, char* palabra);
int QuitarIDRepetida(Index* indexListID, char* textID);
int LeerTexto(char* palabra);
char* LeerPalabra(FILE* archivoEntrada);
int obtenerID();

#endif