#ifndef _FUNC_INDEX_LE_H_
#define _FUNC_INDEX_LE_H_

Results* CrearNodoIndex();
Title* crearNodoTitulo(); 
Author* crearNodoAutor();
Palabra* crearNodoPalabra();

Results* InsertarIndex(Results* result, IndexListID* resultID, int pos, char* id);
Results* insertarIndexOrdenado(Results* result, IndexListID* resultID ,char* id);

//Results* InsertarFinal(Results* L, char* id);
Title* InsertarTitulo(Title* L, char* titulo);
Author* InsertarAutor(Author* L, char* autor);
Palabra* InsertarPalabraFrase(Palabra* L, char* palabra);

void MostrarIndex(Results* result);
void MostrarTitulo(Title* title);
void MostrarAutor(Author* author);
void MostrarFrase(Palabra* palabra);

int largoFrase(Palabra* frase);

int LargoIndex(Results* listaID);
char* ObtenerIndexID(Results* listaID, int pos);

#endif