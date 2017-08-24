#ifndef RESULTS
#define RESULTS

Ranking* query(InvertedIndex*i, StopWords*sw, char* text, code*statusCode);
void showResults(Result*r, int TopK, code*statusCode);

#endif