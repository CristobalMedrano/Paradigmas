#ifndef _FUNC_STOPWORDS_LE_H_
#define _FUNC_STOPWORDS_LE_H_

StopWords* CrearNodo();
StopWords* InsertarStopWord(StopWords* listaSW, int pos, char* palabra);
void MostrarStopWords(StopWords* listaSW);
int LargoStopWords(StopWords* listaSW);
char* ObtenerStopWord(StopWords* listaSW, int pos);

#endif