CC = gcc

LIBS = -lm
CCFLAGS = -Wall -ggdb

compilo: analyseur_lexical.o analyseur_syntaxique.o compilateur.o
	$(CC) analyseur_lexical.o analyseur_syntaxique.o compilateur.o -o compilateur

analyseur_lexical.o: analyseur_lexical.c
	$(CC) -c analyseur_lexical.c

analyseur_syntaxique.o: analyseur_syntaxique.c analyseur_lexical.h
	$(CC) -c analyseur_syntaxique.c

compilateur.o: analyseur_syntaxique.h compilateur.c
	$(CC) -c compilateur.c
