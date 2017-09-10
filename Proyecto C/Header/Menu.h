#ifndef _FUNC_MENU_H_
#define _FUNC_MENU_H_

// Funciones del Menu.
void MostrarMenu(int ultimaID, int id);
void ValidarOpcionIngresada(int* opcionIngresada, int Min, int Max);
void LimpiarConsola();
void PresionarContinuar();
void MostrarStatusCode(code statusCode);
char* obtenerNombre();
char* obtenerText();
int obtenerIDArchivo();
void AcercaDe();
#endif