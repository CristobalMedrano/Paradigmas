#ifndef _FUNC_INDEX_LE_H_
#define _FUNC_INDEX_LE_H_

Results* CrearNodoIndex();
Title* crearNodoTitulo(); 
Author* crearNodoAutor();

Results* InsertarIndex(Results* result, IndexListID* resultID, int pos, char* id);

//Results* InsertarFinal(Results* L, char* id);
Title* InsertarTitulo(Title* L, char* titulo);
Author* InsertarAutor(Author* L, char* autor);

void MostrarIndex(Results* result);
void MostrarTitulo(Title* title);
void MostrarAutor(Author* author);
int LargoIndex(Results* listaID);
char* ObtenerIndexID(Results* listaID, int pos);

#endif