#ifndef PROCESAMIENTO
#define PROCESAMIENTO

StopWords* loadStopWords(char*pathStopWordsFile, code*statusCode);
InvertedIndex* createIndex(char*pathDocumentsFile, StopWords*sw, code*statusCode);
void saveIndex(InvertedIndex*i, int*id, code*statusCode);
InvertedIndex* loadIndex(int id, code*statusCode);
Result** query(InvertedIndex*i, StopWords*sw, char*q, code*statusCode);
void showResults(Result*r, int TopK, code*statusCode);

// Para reconocer archivos
char* obtenerNombreArchivo();

#endif