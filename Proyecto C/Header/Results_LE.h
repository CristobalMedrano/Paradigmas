#ifndef _FUNC_RESULTS_LE_H_
#define _FUNC_RESULTS_LE_H_

Result* CrearNodoIndex();
Result* InsertarIndex(Result* result, int pos, char* id);
void MostrarIndex(Result* listaID);
int LargoIndex(Result* listaID);
char* ObtenerIndexID(Result* listaID, int pos);

#endif