#ifndef ESTRUCTURAS
#define ESTRUCTURAS

typedef struct InvertedIndex
{
	//Palabra
	//ListaEnlazada Indice de doc donde se encuentra.
	//Hijoizquierdo
	//Hijoderecho
} InvertedIndex;

typedef struct Result
{

} Result;

typedef struct Ranking
{

} Ranking;

typedef struct StopWords
{
	char *palabra;
	struct StopWords *siguiente;

} StopWords;

typedef enum code { OK, NO_MEMORY, ERR_FILE_NOT_FOUND, ERR_FILE_NOT_PERMISSION, FAIL } code;

#endif