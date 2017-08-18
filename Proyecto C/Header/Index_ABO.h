#ifndef INDEX_ABO
#define INDEX_ABO

InvertedIndex* InsertarPalabra(InvertedIndex* index, char* palabra);
InvertedIndex* CrearHoja(char* palabra, InvertedIndex* arbol_izquierdo, InvertedIndex* arbol_derecho);
InvertedIndex* hijo_IZQUIERDO(InvertedIndex* index);
InvertedIndex* hijo_DERECHO(InvertedIndex* index);
char* ObtenerPalabraIndex(InvertedIndex* index);
void preOrden(InvertedIndex* index);

#endif