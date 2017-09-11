#ifndef _ESTRUCTURAS_H
#define _ESTRUCTURAS_H

typedef struct Palabra
{
	char* palabra;
	struct Palabra* siguiente;
} Palabra;

typedef struct Title
{
	char* titulo;
	struct Title* siguiente;
} Title;

typedef struct Author
{
	char* autor;
	struct Author* siguiente;
} Author;

typedef struct IndexListID
{
	char* id;
	struct Title* titulo;
	struct Author* autor;
	struct IndexListID* hijoIzquierdo;
	struct IndexListID* hijoDerecho;
} IndexListID;

typedef struct Results
{
	char* id;
	struct IndexListID* textDocs;
	struct Results* siguiente;

} Results;

typedef struct Index
{
	char* palabra;
	Results* resultsID;
	int textosIndexados;
	IndexListID* saveTextDocs;
	struct Index* hijoIzquierdo;
	struct Index* hijoDerecho;

} Index;

typedef struct Ranking
{
	int numTextos;
	char* text;
	struct Results* busqueda;
} Ranking;

typedef struct StopWords
{
	char* palabra;
	struct StopWords* siguiente;

} StopWords;



typedef enum code { OK, NO_MEMORY, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERMISSION, FAIL
	, ERR_STOPWORDS_NOT_FOUND, ERR_INDEX_NOT_FOUND, NO_SEARCH_RESULTS} code;

#endif