#ifndef INDEX
#define INDEX

InvertedIndex* createIndex(char* pathDocumentsFile, StopWords*sw, code*statusCode);
void saveIndex(InvertedIndex*i, int*id, code*statusCode);
InvertedIndex* loadIndex(int id, code*statusCode);
int obtenerID();

#endif