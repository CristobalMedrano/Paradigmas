#ifndef _ESTRUCTURAS_H
#define _ESTRUCTURAS_H

typedef struct Result
{
	char* id;
	char* Titulo;
	char* Author;
	struct Result* siguiente;

} Result;

typedef struct Index
{
	char* palabra;
	Result* indexListID;
	struct Index* hijoIzquierdo;
	struct Index* hijoDerecho;

} Index;

typedef struct Ranking
{

} Ranking;

typedef struct StopWords
{
	char* palabra;
	struct StopWords* siguiente;

} StopWords;



typedef enum code { OK, NO_MEMORY, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERMISSION, FAIL
	, ERR_STOPWORDS_NOT_FOUND, ERR_INDEX_NOT_FOUND, NO_SEARCH_RESULTS} code;

#endif