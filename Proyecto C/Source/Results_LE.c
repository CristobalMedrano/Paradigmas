#include <stdio.h>
#include <stdlib.h>
#include <Estructuras.h>
#include <Results_LE.h>

Results* CrearNodoIndex()
{
	Results* result = (Results*)malloc(sizeof(Results));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(result != NULL)
	{
	    result->id = NULL;
	    result->textDocs = NULL;
		result->siguiente = NULL;
		return result;
	}
	else
	{
		return NULL;
	}
}
Title* crearNodoTitulo()
{
	Title* nuevoTitulo = (Title*)malloc(sizeof(Title));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(nuevoTitulo != NULL)
	{
	    nuevoTitulo->titulo = NULL;
		nuevoTitulo->siguiente = NULL;
		return nuevoTitulo;
	}
	else
	{
		return NULL;
	}
}
Author* crearNodoAutor()
{
	Author* nuevoAutor = (Author*)malloc(sizeof(Author));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(nuevoAutor != NULL)
	{
	    nuevoAutor->autor = NULL;
		nuevoAutor->siguiente = NULL;
		return nuevoAutor;
	}
	else
	{
		return NULL;
	}
}

Palabra* crearNodoPalabra()
{
	Palabra* nuevaPalabra = (Palabra*)malloc(sizeof(Palabra));
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if(nuevaPalabra != NULL)
	{
	    nuevaPalabra->palabra = NULL;
		nuevaPalabra->siguiente = NULL;
		return nuevaPalabra;
	}
	else
	{	
		return NULL;
	}
}

Results* InsertarIndex(Results* result, IndexListID* resultID, int pos, char* id)
{
	int i;
	if(pos < 0)
	{
		return result;
	}
	if(pos == 0)
	{
		Results* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->textDocs = resultID;
		nuevaID->siguiente = result;
		return nuevaID;
	}
	i = 0;
	Results* indice = CrearNodoIndex();
	indice = result;
	while (indice != NULL && i < pos -1)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice != NULL)
	{
		Results* nuevaID = CrearNodoIndex();
		nuevaID->id = id;
		nuevaID->textDocs = resultID;
		nuevaID->siguiente = indice->siguiente;
		indice->siguiente = nuevaID;
	}
	return result; 
}

Title* InsertarTitulo(Title* L, char* titulo)
{
	//Se crea una nueva lista
	Title *nuevo = crearNodoTitulo();
	Title *aux = crearNodoTitulo();
	//Se comprueba si se realiza con exito
	//Si la lista es creada con exito
	if(nuevo!=NULL){
        //Se ve si L esta vacia
        if (L==NULL){
            //En ese caso, L sera igual a la nueva lista que creamos
        	L = nuevo;
            nuevo->titulo = titulo;
            nuevo->siguiente = NULL;
            return L;
        }
        else
        { 
        	// Aux sera igual a L.
        	aux = L;
        	// Ubicamos el puntero en el ultimo nodo.
        	while(aux->siguiente != NULL)
        	{
        		aux = aux->siguiente;
        	}
        	// Asignamos la ultima posicion al nuevo nodo.
        	aux->siguiente = nuevo;
        	nuevo->titulo = titulo;
        	nuevo->siguiente = NULL;
        	// Retornamos la lista.
        	return L;
        }

	}
	//En caso que la asignacion de memoria falle, se avisa del error y se retorna la lista L
	else{
        printf("Error en la asignacion de memoria\n");
        return L;
    }
}

Author* InsertarAutor(Author* L, char* autor)
{
	//Se crea una nueva lista
	Author *nuevo = crearNodoAutor();
	Author *aux = crearNodoAutor();
	//Se comprueba si se realiza con exito
	//Si la lista es creada con exito
	if(nuevo!=NULL){
        //Se ve si L esta vacia
        if (L==NULL){
            //En ese caso, L sera igual a la nueva lista que creamos
        	L = nuevo;
            nuevo->autor = autor;
            nuevo->siguiente = NULL;
            return L;
        }
        else
        { 
        	// Aux sera igual a L.
        	aux = L;
        	// Ubicamos el puntero en el ultimo nodo.
        	while(aux->siguiente != NULL)
        	{
        		aux = aux->siguiente;
        	}
        	// Asignamos la ultima posicion al nuevo nodo.
        	aux->siguiente = nuevo;
        	nuevo->autor = autor;
        	nuevo->siguiente = NULL;
        	// Retornamos la lista.
        	return L;
        }

	}
	//En caso que la asignacion de memoria falle, se avisa del error y se retorna la lista L
	else{
        printf("Error en la asignacion de memoria\n");
        return L;
    }
}

Palabra* InsertarPalabraFrase(Palabra* L, char* palabra)
{
	//Se crea una nueva lista
	Palabra *nuevo = crearNodoPalabra();
	Palabra *aux = crearNodoPalabra();
	//Se comprueba si se realiza con exito
	//Si la lista es creada con exito
	if(nuevo!=NULL){
        //Se ve si L esta vacia
        if (L==NULL){
            //En ese caso, L sera igual a la nueva lista que creamos
        	L = nuevo;
            nuevo->palabra = palabra;
            nuevo->siguiente = NULL;
            return L;
        }
        else
        { 
        	// Aux sera igual a L.
        	aux = L;
        	// Ubicamos el puntero en el ultimo nodo.
        	while(aux->siguiente != NULL)
        	{
        		aux = aux->siguiente;
        	}
        	// Asignamos la ultima posicion al nuevo nodo.
        	aux->siguiente = nuevo;
        	nuevo->palabra = palabra;
        	nuevo->siguiente = NULL;
        	// Retornamos la lista.
        	return L;
        }

	}
	//En caso que la asignacion de memoria falle, se avisa del error y se retorna la lista L
	else{
        printf("Error en la asignacion de memoria\n");
        return L;
    }
}

void MostrarIndex(Results* result)
{
	if(result != NULL)
	{
        Results* auxiliar = CrearNodoIndex();
        auxiliar = result;
        while(auxiliar != NULL)
        {
            printf("- %s -", auxiliar->id);
            auxiliar = auxiliar->siguiente;
        }
	}
	printf("\n");
}

void MostrarTitulo(Title* title)
{
	if(title != NULL)
	{
        Title* auxiliar = crearNodoTitulo();
        auxiliar = title;
        while(auxiliar != NULL)
        {
            printf("%s ", auxiliar->titulo);
            auxiliar = auxiliar->siguiente;
        }
	}
	printf("\n");
}

void MostrarAutor(Author* author)
{
	if(author != NULL)
	{
        Author* auxiliar = crearNodoAutor();
        auxiliar = author;
        while(auxiliar != NULL)
        {
            printf("%s ", auxiliar->autor);
            auxiliar = auxiliar->siguiente;
        }
	}
	printf("\n");
}

void MostrarFrase(Palabra* palabra)
{
	if(palabra != NULL)
	{
		Palabra* auxiliar = crearNodoPalabra();
		auxiliar = palabra;
		while(auxiliar != NULL)
		{
		    printf("%s ", auxiliar->palabra);
		    auxiliar = auxiliar->siguiente;
		}
	}
	printf("\n");
}

int largoFrase(Palabra* frase)
{
	int i = 0;
	Palabra* indice = frase;
	while(indice != NULL)
	{
		indice = indice->siguiente;
		i++;
	}
	return i;
}

int LargoIndex(Results* result)
{
	int i = 0;
	Results* indice = result;
	while(indice != NULL)
	{
		indice = indice->siguiente;
		i++;
	}
	return i;
}

char* ObtenerIndexID(Results* listaID, int pos)
{
	int i;
	if(pos < 0)
	{
		return NULL;
	}
	i = 0;
	Results* indice = listaID;
	while(indice != NULL && i < pos)
	{
		indice = indice->siguiente;
		i++;
	}
	if(indice == NULL)
	{
		return NULL;
	}
	return indice->id;
}
