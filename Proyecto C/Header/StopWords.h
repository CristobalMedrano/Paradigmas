#ifndef STOPWORDS
#define STOPWORDS

StopWords* loadStopWords(char* pathStopWordsFile, code*statusCode);
StopWords* CrearNodo();
StopWords* InsertarStopWord(StopWords* listaSW, int pos, char* palabra);
void MostrarStopWords(StopWords* listaSW);
int LargoStopWords(StopWords* listaSW);
char* ObtenerStopWord(StopWords* listaSW, int pos);
char* LeerStopWord(FILE* archivoEntrada);

#endif