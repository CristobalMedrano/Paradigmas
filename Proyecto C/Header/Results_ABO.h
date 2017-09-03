#ifndef _FUNC_RESULTS_ABO_H_
#define _FUNC_RESULTS_ABO_H_

IndexListID* insertarResultsID(IndexListID* resultID, char* id, Title* titulo, Author* autor);
IndexListID* crearHojaResults(char* id, Title* titulo, Author* autor, 
						IndexListID* index_izquierdo, IndexListID* index_derecho);

IndexListID* hijoIzquierdoResults(IndexListID* resultID);
IndexListID* hijoDerechoResults(IndexListID* resultID);
char* obtenerResultsID(IndexListID* resultID);
IndexListID* buscarResultsID(IndexListID* resultID, char* id);
char* obtenerIDdesdeIndex(IndexListID* index);
IndexListID* obtenerIndexID(IndexListID* index, char* id);

void inOrdenResults(IndexListID* resultID);

#endif