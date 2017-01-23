CC = gcc

LIBS = -lm
CCFLAGS = -Wall -ggdb

EXECS = analyseur_lexical analyseur_syntaxique compilateur

.c.o :
				$(CC) -c $(CCFLAGS) $*.c

help ::
				@echo "Options du make : help all clean distclean"

all :: $(EXECS)

$(EXECS) : %: %.o
				$(CC) -o $@ $@.o $(LIBS)

clean ::
				\rm -f *.o core

distclean :: clean
				\rm -f *% $(EXECS)
