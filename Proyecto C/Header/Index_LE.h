#ifndef INDEX_LE
#define INDEX_LE

Index* CrearNodoIndex();
Index* InsertarIndex(Index* index, int pos, char* id);
void MostrarIndex(Index* listaID);
int LargoIndex(Index* listaID);
char* ObtenerIndexID(Index* listaID, int pos);

#endif