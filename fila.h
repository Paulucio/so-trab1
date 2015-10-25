#ifndef _TFILA
  #define _TFILA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tFila* Fila;            //Definindo um tipo fila

char* copia_string(char*);             //Funcao para copia de string
Fila criaElemFila(char*);              //Cria um elemento fila
int filaVazia(Fila);                   //Verifica se a fila esta vazia
void liberaFilaEncadeada(Fila*);       //Libera a memoria alocada para uma Fila
void insereFinalFila(Fila*, char*);    //Insere elemento no final da fila
void imprimeFila(Fila);                //Imprime os elementos de uma fila
char* getElemFila(Fila);               //Retorna o elemento da fila
typedef struct tCelula* Celula;        //Definindo um tipo celula

Celula criaCelula(void);               //Cria uma Celula
void liberaCelula(Celula*);            //Libera a memoria alocada para uma celula
Fila getTopoCelula(Celula);            //Retorna o primeiro da celula
int celulaVazia(Celula);               //Verifica se uma fila esta vazia
void addElemCelula(Celula, char*);     //Insere um elemento na fila da celula
void imprimeCelula(Celula);            //Imprime os elementos da celula
void pop(Celula);                      //Remove o primeiro elemento da celula
int getNumElem(Celula);                //Retorna o numero de elementos na celula
char* getElemTopoCelula(Celula);       //Retorna o elemento do topo da celula
char* numToString(int);                //Converte inteiro para string
void addElemIntCelula(Celula, int);    //Insere numero inteiro na fila
int* geraVetorPID(Celula);             //Gera vetor com os pids dos processos
int getElemIntTopoCelula(Celula);      //Retorna o elemento do topo da celula

#endif //FIM _TFILA
