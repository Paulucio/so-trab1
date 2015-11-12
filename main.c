#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lazyShell.h"

Celula cel_PID = NULL, cel_CMD = NULL, cel_ZOMBIE = NULL;                                 //Variaveis globais para a criacao das filas

void trataSIGINT(int sig)
{
    static int numCtrlC = 0;
    int stats, *vetor;

    //waitpid() retorna pid do filho defunct ou -1 para o caso de nao existirem filhos ativos nem defuncts
    if(numCtrlC == 0)
    {
        if(getNumElem(cel_CMD))                             //Se existirem comandos na primeira vez q aperta Ctrl-C
            execComandos(cel_PID, cel_CMD, cel_ZOMBIE);
        numCtrlC++;                                         //Incremente flag para saber se e a primeira vez q aperta Ctrl-C
        return;
    }

    while((stats = waitpid(-1,NULL,WNOHANG)) > 0)
    {
      addElemIntCelula(cel_ZOMBIE, stats);
    }

    if(waitpid(-1,NULL,WNOHANG) == 0) //Enquanto tiver filhos em execucao
    {
        // printf("Processo %d", stats);
        printf("\n\nNão posso morrer... sou mãe de família!!!\n");
        // if(stats > 0)
        //     printf("\nProcesso filho %d saiu do estado ZOMBIE\n", stats);
        if(getNumElem(cel_CMD))
            execComandos(cel_PID, cel_CMD, cel_ZOMBIE);
    }
    else
    {
        printf("\nOk... você venceu! Adeus!\n");
        liberaCelula(&cel_PID);
        liberaCelula(&cel_CMD);
        liberaCelula(&cel_ZOMBIE);
        exit(EXIT_SUCCESS);
    }
}

int main (void) {

        signal(SIGINT,trataSIGINT);              //Declarando tratador para o sinal SIGINT

        cel_PID = criaCelula();                  //Criação das celulas para as filas
        cel_CMD = criaCelula();
        cel_ZOMBIE = criaCelula();
        lazyShell(cel_PID, cel_CMD);             //Chama a lazyShell
        liberaCelula(&cel_PID);                  //Libera a memoria alocada
        liberaCelula(&cel_CMD);
        liberaCelula(&cel_ZOMBIE);

        return EXIT_SUCCESS;
}
