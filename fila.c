#include "fila.h"
#define TAM 30

struct tFila
{
  char buffer[];
  struct tFila *prox;
};

struct tCelula
{
  Fila *primeiro;
  Fila *ultimo;
};

Fila* criaFila(void)
{
  Fila *novo = (Fila*) malloc(sizeof(Fila));
  return novo;
}

int filaVazia(Fila* f)
{
  return buffer == NULL;
}

Celula addPrimeiro(Celula cel, Fila *prim)
{
  cel.primeiro = cel.ultimo = prim;
}

Fila* insereFila(char *buffer, Celula cel)
{
  Fila *novo = criaFila();
  novo->buffer = buffer;
}
