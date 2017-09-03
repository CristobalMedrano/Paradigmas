#Makefile para Windows y Linux del codigo Laboratorio_Paradigmas_19083864-1.c por Cristobal Medrano.

#Comprobamos el Sistema Operativo.
ifeq ($(OS),Windows_NT)
    OS_detected := Windows
else
    OS_detected := $(shell uname -s)
endif

#Seleccionamos las variables a cambiar dependiendo del OS.
ifeq ($(OS_detected), Windows)
	EJECUTABLE = buscador.exe
	EJECUTAR = buscador.exe
    REMOVE = -del
endif
ifeq ($(OS_detected), Linux)
	EJECUTABLE = buscador.out
	EJECUTAR = ./buscador.out
    REMOVE = -rm -f
endif

#Carpeta de modulos y cabeceras
SOURCES = Source/
HEADERS = Header/

#Variables
CC = gcc
OPTS = -Wall -g3
INCLUDE = -I $(HEADERS)
OBJECTS = Results.o Index_LE.o Results_ABO.o Index_ABO.o Index.o StopWords_LE.o StopWords.o Menu.o buscador.o

.SILENT: clean all
all: $(OBJECTS)
	$(CC) $(OPTS) -o $(EJECUTABLE) $(OBJECTS)
	echo Compilacion Completa. Ejecutable: $(EJECUTABLE)

Ejecutar: all
	$(EJECUTAR)

buscador.o: buscador.c $(HEADERS)buscador.h
	$(CC) $(OPTS) $(INCLUDE) -c buscador.c -o buscador.o

Menu.o: $(SOURCES)Menu.c $(HEADERS)Menu.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Menu.c -o Menu.o

StopWords.o: $(SOURCES)StopWords.c $(HEADERS)StopWords.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)StopWords.c -o StopWords.o

StopWords_LE.o: $(SOURCES)StopWords_LE.c $(HEADERS)StopWords_LE.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)StopWords_LE.c -o StopWords_LE.o

Index.o: $(SOURCES)Index.c $(HEADERS)Index.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Index.c -o Index.o

Index_ABO.o: $(SOURCES)Index_ABO.c $(HEADERS)Index_ABO.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Index_ABO.c -o Index_ABO.o

Index_LE.o: $(SOURCES)Index_LE.c $(HEADERS)Index_LE.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Index_LE.c -o Index_LE.o

Results_ABO.o: $(SOURCES)Results_ABO.c $(HEADERS)Results_ABO.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Results_ABO.c -o Results_ABO.o

Results.o: $(SOURCES)Results.c $(HEADERS)Results.h
	$(CC) $(OPTS) $(INCLUDE) -c $(SOURCES)Results.c -o Results.o

#file.o: $(SOURCES)file.c $(HEADERS)file.h
#	$(CC) $(INCLUDE) -c $(SOURCES)file.c -o file.o

.PHONY: clean
clean:
	$(REMOVE) $(OBJECTS) $(EJECUTABLE)
	echo Limpieza Completa.
