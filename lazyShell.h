#ifndef _LAZYSHELL
    #define _LAZYSHELL

#define TAM_DIR 30
#define TAM_BUFFER 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void lazyShell(void);        //Executa a LazyShell

/////////////////////////////////////// Comandos Internos ///////////////////////////////////////
int cmdInt(char*);           //Verifica se e um comando interno e retorna 0 se nao for, caso seja, retorna o numero do comando
void execCMDInt(int, char*); //Executa o comando interno passando os parametros
void CD(char*);              //Comando interno cd
void WAIT(void);             //Comando interno wait
void EXIT(void);             //Comando interno exit

#endif
