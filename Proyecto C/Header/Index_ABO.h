#ifndef INDEX_ABO
#define INDEX_ABO

InvertedIndex* InsertarPalabra(InvertedIndex* index, char* palabra);
InvertedIndex* CrearHoja(char* palabra, InvertedIndex* arbol_izquierdo, InvertedIndex* arbol_derecho);
InvertedIndex* hijo_IZQUIERDO(InvertedIndex* index);
InvertedIndex* hijo_DERECHO(InvertedIndex* index);
char* ObtenerPalabraIndex(InvertedIndex* index);
InvertedIndex* BuscarPalabraIndex(InvertedIndex* index, char* palabra);
void preOrden(InvertedIndex* index);
void inOrden(InvertedIndex* index);
void postOrden(InvertedIndex* index);
int nElementos(InvertedIndex* index);
void obtenerElemento(InvertedIndex* index, int* n);

#endif