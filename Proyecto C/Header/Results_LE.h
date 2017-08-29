#ifndef _FUNC_RESULTS_LE_H_
#define _FUNC_RESULTS_LE_H_

Result* CrearNodoIndex();
Result* InsertarIndex(Result* result, int pos, char* id);

//Result* InsertarFinal(Result* L, char* id);
Title* InsertarTitulo(Title* L, char* titulo);
Author* InsertarAutor(Author* L, char* autor);

void MostrarIndex(Result* result);
void MostrarTitulo(Title* title);
void MostrarAutor(Author* author);
int LargoIndex(Result* listaID);
char* ObtenerIndexID(Result* listaID, int pos);

#endif