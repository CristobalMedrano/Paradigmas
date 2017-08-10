#Makefile para Windows y Linux del codigo Laboratorio_5_19083864-1.c por Cristobal Medrano.

#Comprobamos el Sistema Operativo.
ifeq ($(OS),Windows_NT)
    OS_detected := Windows
else
    OS_detected := $(shell uname -s)
endif

#Seleccionamos las variables a cambiar dependiendo del OS.
ifeq ($(OS_detected), Windows)
	EJECUTABLE = buscador.exe
    REMOVE = -del
endif
ifeq ($(OS_detected), Linux)
	EJECUTABLE = buscador.out
    REMOVE = -rm -f
endif

#Carpeta de modulos y cabeceras
SOURCES = Source/
HEADERS = Header/

#Variables
CCDebug = gcc -Wall
CC = gcc -Wall
INCLUDE = -I $(HEADERS)
OBJECTS = Indexacion.o buscador.o

.SILENT: clean all
all: $(OBJECTS)
	$(CC) -o $(EJECUTABLE) $(OBJECTS)
	echo Compilacion Completa. Ejecutable: $(EJECUTABLE)

buscador.o: buscador.c $(HEADERS)buscador.h
	$(CC) $(INCLUDE) -c buscador.c -o buscador.o

Indexacion.o: $(SOURCES)Indexacion.c $(HEADERS)Indexacion.h
	$(CC) $(INCLUDE) -c $(SOURCES)Indexacion.c -o Indexacion.o

#file.o: $(SOURCES)file.c $(HEADERS)file.h
#	$(CC) $(INCLUDE) -c $(SOURCES)file.c -o file.o

.PHONY: clean
clean:
	$(REMOVE) $(OBJECTS) $(EJECUTABLE)
	echo Limpieza Completa.