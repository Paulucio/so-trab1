#include "lazyShell.h"
#include "fila.h"
#define EVER ;;

void lazyShell(void)
{
    char *dir;
    char buffer[TAM_BUFFER];
    // Celula cel = criaCelula();

    for(EVER)
    {
        dir = getcwd(0,0);

        printf("lsh> ~%s $ ",dir);
        // scanf("%s", buffer);
        fgets(buffer,TAM_BUFFER, stdin);
        // addElemCelula(cel, buffer);
        sscanf(buffer,"%s",buffer);
        //printf("buffer: %s\nteste: %s\n", buffer, teste);
        if(chdir(buffer))
            printf("Diretorio nao encontrado\n");
        // printf("buffer:%s\n", buffer);
    }
}

int cmdInt(char* comando)   //Verifica se o comando e interno
{
    if(!strcmp("cd", comando))
        return 1;                 //Retorna 1 se for o CD
    if(!strcmp("wait", comando))
        return 2;                 //Retorna 2 se for o WAIT
    if(!strcmp("exit", comando))
        return 3;                 //Retorna 3 se for o EXIT

    return 0;                     //Retorna 0 se nao for comando interno
}

void CD(char* parametro) //Comando CD
{
    if(chdir(parametro)) //Verifica o parametro e realiza o cd
        printf("Diretorio passado para o comando cd nao encontrado\n");
}

void WAIT(void) //Comando WAIT
{
    int process;
    while(process = wait() != -1) //Enquanto nao liberar todos os filhos
    {
        printf("Encontrado filho %d\n", process); //Imprime filhos encontrados
    }

    printf("Não existem mais processos filhos no estado ZOMBIE\n");
}

void EXIT(void) //Comando EXIT
{
    WAIT();  //Espera todos os filhos serem liberados do estado zombie
    exit(EXIT_SUCESS);  //Encerra o programa
}

void execCMDInt(int cmd, char* parametro)             //Executa o comando interno
{
    if(cmd == 1)                                         //Se for o comando CD
    {
        CD(parametro);                                   //Chama a funcao CD
        return;
    }

    if(cmd == 2)                                         //Se for o comando WAIT
    {
        WAIT();                                          //Chama a funcao wait
        return;
    }

    if(cmd == 3)                                        //Se for o comando EXIT
    {
        EXIT();                                         //Chama a funcao EXIT
        return;
    }
}
