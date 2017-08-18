#ifndef INDEX_LE
#define INDEX_LE

Index* CrearNodoIndex();
Index* InsertarIndex(Index* index, int pos, int id);
void MostrarIndex(Index* listaID);
int LargoIndex(Index* listaID);
int ObtenerIndexID(Index* listaID, int pos);

#endif