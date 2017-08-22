#ifndef INDEX
#define INDEX

#define TRUE 1
#define FALSE 0

// Creando IndexInvertido
InvertedIndex* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode);

int QuitarStopWords(char* palabra, StopWords* listaSW);
int QuitarPalabraRepetida(InvertedIndex* index, char* palabra);
int QuitarIDRepetida(Index* indexListID, char* textID);
int LeerTexto(char* palabra);
char* LeerPalabra(FILE* archivoEntrada);

// Guardando IndexInvertido
void saveIndex(InvertedIndex*i, int*id, code*statusCode);

char* generarNombreSave(int *id);
char* obtenerFecha(int *id);
int obtenerID();

// Cargando IndexInvertido
InvertedIndex* loadIndex(int id, code*statusCode);


#endif