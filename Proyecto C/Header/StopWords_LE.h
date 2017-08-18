#ifndef STOPWORDS_LE
#define STOPWORDS_LE

StopWords* CrearNodo();
StopWords* InsertarStopWord(StopWords* listaSW, int pos, char* palabra);
void MostrarStopWords(StopWords* listaSW);
int LargoStopWords(StopWords* listaSW);
char* ObtenerStopWord(StopWords* listaSW, int pos);

#endif