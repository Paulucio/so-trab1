#ifndef _TFILA
  #define _TFILA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tFila* Fila;

char* copia_string(char*);          //Funcao para copia de string
Fila criaElemFila(char*);
int filaVazia(Fila);
void liberaFila(Fila*);
void insereFinalFila(Fila*, char*);
void imprimeFila(Fila);

typedef struct tCelula* Celula;
Celula criaCelula(void);
void liberaCelula(Celula*);
int celulaVazia(Celula);
void addElemCelula(Celula, char*);


#endif //Fim _TFILA
