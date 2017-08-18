#ifndef PROCESAMIENTO
#define PROCESAMIENTO

Result** query(InvertedIndex*i, StopWords*sw, char*q, code*statusCode);
void showResults(Result*r, int TopK, code*statusCode);

// Para reconocer archivos
//char* obtenerNombreArchivo();
char* obtenerFecha(int *id);
int obtenerID();

#endif