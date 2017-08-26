#ifndef _FUNC_INDEX_ABO_H_
#define _FUNC_INDEX_ABO_H_

Index* InsertarPalabra(Index* index, char* palabra);
Index* CrearHoja(char* palabra, Index* arbol_izquierdo, Index* arbol_derecho);
Index* hijo_IZQUIERDO(Index* index);
Index* hijo_DERECHO(Index* index);
char* ObtenerPalabraIndex(Index* index);
Index* BuscarPalabraIndex(Index* index, char* palabra);
void preOrden(Index* index);
void inOrden(Index* index);
void postOrden(Index* index);
int nElementos(Index* index);
void obtenerElemento(Index* index, int* n);

#endif