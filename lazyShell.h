#ifndef _LAZYSHELL
    #define _LAZYSHELL

#define TAM_DIR 30
#define TAM_BUFFER 50
#define EVER ;;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "fila.h"

/////////////////////////////////////////// LAZYSHELL ///////////////////////////////////////////////////////////////

void lazyShell(Celula, Celula);        //Executa a LazyShell

/////////////////////////////////////////// COMANDOS ///////////////////////////////////////////////////////////////
void execComandos(Celula, Celula);                              //Executa comandos do buffer

/////////////////////////////////////// COMANDOS INTERNOS //////////////////////////////////////////////////////////////
int cmdInt(char*);                                              //Verifica se e um comando interno
void execCMDInt(int, char*, Celula, Celula);                    //Executa o comando interno passando os parametros
void CD(char*);                                                 //Comando interno cd
void WAIT(Celula);                                              //Comando interno wait
void EXIT(Celula, Celula);                                      //Comando interno exit

/////////////////////////////////////// COMANDOS EXTERNOS //////////////////////////////////////////////////////////////
void execCMDExt(Celula, Celula, const char*, char *const[]);            //Executa comando externo

#endif
