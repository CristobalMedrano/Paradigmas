#ifndef STOPWORDS
#define STOPWORDS

StopWords* loadStopWords(char* pathStopWordsFile, code*statusCode);
StopWords* CrearNodo();
StopWords* InsertarStopWord(StopWords* listaSW, int pos, char* palabra);
void MostrarStopWords(StopWords* listaSW);
char* ObtenerPalabra(FILE* archivoEntrada);

#endif