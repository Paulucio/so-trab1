#  Makefile

CC = gcc

DEBUG = -g

CFLAGS = -Wall $(DEBUG)
LIBS = -lm

OBJETOS	= lazyShell.o fila.o main.o

TEMPORARIOS = *.o

EXECUTAVEL = lazyShell

all: compila

compila: $(OBJETOS)
	$(CC) $(OBJETOS) $(LIBS) $(CFLAGS) -o $(EXECUTAVEL)

main.o:
	$(CC) -c main.c

lazyShell.o:
	$(CC) -c lazyShell.c

fila.o: fila.c
	$(CC) -c fila.c

clean:
	rm -f $(TEMPORARIOS)
