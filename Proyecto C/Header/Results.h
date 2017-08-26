#ifndef _FUNC_RESULTS_H_
#define _FUNC_RESULTS_H_

Ranking* query(Index*i, StopWords*sw, char* text, code*statusCode);
void showResults(Result*r, int TopK, code*statusCode);

void recorrerIndex(Result* result);

#endif