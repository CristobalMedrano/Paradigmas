#ifndef ESTRUCTURAS
#define ESTRUCTURAS


typedef struct Index
{
	int id;
	struct Index* siguiente;

} Index ;

typedef struct InvertedIndex
{
	char* palabra;
	Index* index;
	struct InvertedIndex* hijoIzquierdo;
	struct InvertedIndex* hijoDerecho;

} InvertedIndex;

typedef struct Result
{

} Result;

typedef struct Ranking
{

} Ranking;

typedef struct StopWords
{
	char* palabra;
	struct StopWords* siguiente;

} StopWords;



typedef enum code { OK, NO_MEMORY, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERMISSION, FAIL, ERR_STOPWORDS_NOT_FOUND } code;

#endif