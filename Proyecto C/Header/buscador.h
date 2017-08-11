#ifndef INICIO
#define INICIO

#define SIN_INGRESO -1
#define CARGAR_STOPWORDS 1
#define CREAR_INDEX 2
#define GUARDAR_INDEX 3
#define CARGAR_INDEX 4
#define BUSCAR 5
#define MOSTRAR_RESULTADOS 6
#define ACERCA_DE 7
#define SALIR 8

// Funciones del Menu.
void MostrarMenu();
void LimpiarConsola();
void ValidarOpcionIngresada(int* opcionIngresada, int Min, int Max);
void AcercaDe();
void PresionarContinuar();

#endif