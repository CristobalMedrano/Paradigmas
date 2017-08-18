#ifndef MENU
#define MENU

// Funciones del Menu.
void MostrarMenu();
void ValidarOpcionIngresada(int* opcionIngresada, int Min, int Max);
void LimpiarConsola();
void PresionarContinuar();
void MostrarStatusCode(code statusCode);
char* obtenerNombreArchivo();
void AcercaDe();
#endif