#include "lazyShell.h"
#include "fila.h"

void lazyShell(Celula cel_PID, Celula cel_CMD)
{
    if(cel_PID == NULL || cel_CMD == NULL)
    {
        fprintf(stderr, "Problema nas filas");
        exit(1);
    }

    char *dir;                                              //Variavel para salvar o diretorio atual
    char buffer[TAM_BUFFER];                                //Buffer de leitura da Shell

    for(EVER)                                               //LOOP INFINITO
    {
        dir = getcwd(0,0);                                  //Obtem o diretorio atual
        printf("lsh> ~%s $ ",dir);                          //Formato da Shell
        free(dir);
        // scanf("%s", buffer);
        fgets(buffer,TAM_BUFFER, stdin);                    //Le o comando
        // printf("<%s>", buffer);
        if(strcmp(buffer,"\n"))                             //Se nao for um enter insere na fila de comandos
            addElemCelula(cel_CMD, buffer);

        //imprimeCelula(cel_CMD);
        // printf("Comando: %s\n", buffer);

        // if(strcmp(buffer,"exit\n") == 0)
        // break;
    }
}

/////////////////////////////////////////// COMANDOS ///////////////////////////////////////////////////////////////

void execComandos(Celula cel_PID, Celula cel_CMD, Celula cel_ZOMBIE)
{
    const int NUM_PARAMETROS = 5;     //Constante delimitadora do numero de parametros
    int i = 0;                        //Indice
    char *buffer = NULL;              //Ponteiro para pegar o buffer da fila
    char *string = NULL;              //Ponteiro para pegar cada palavra do buffer
    char *argv[NUM_PARAMETROS];       //Vetor que contem os parametros

    while(getNumElem(cel_CMD))                                  //Enquanto existirem comandos na fila
    {
        buffer = getElemTopoCelula(cel_CMD);                    //Pega o primeiro comando digitado

        ///////////////////////////////////////// GERA LISTA DE PARAMETROS ///////////////////////////////////////////

        string = strtok(buffer," \n");                          //Aponta para o inicio da string buffer
        while(string != NULL && i < NUM_PARAMETROS)             //Enquanto nao verificar todo o buffer e nao ultrapassar o limite de parametros
        {
            argv[i] = string;                                   //Pega o parametro i do buffer atual
            // printf("String:%s\n",string);
            string = strtok(NULL," \n");                        //Localiza o proximo parametro
            i++;                                                //Incrementa o indice
        }
        argv[i]=NULL;                                           //Ultimo valor tem q ser nulo

        // for(i=0;i<NUM_PARAMETROS;i++)
        //     printf("Parametro i = %d\n -%s-\nn", i, argv[i]);
        // //////////////////////////////////////////// FIM DA LISTA DE PARAMETROS ////////////////////////////////////////
        // printf("parametro passado =-%s-\n", argv[0]);
        // printf("Numero: %d", cmdInt(argv[0]));
        if(i = cmdInt(argv[0]))                                    //Verifica se e comando interno
        {
            // printf("Comando interno\n");
            switch(i)                                             //Realiza o comando interno
            {
                case 1:                                            //CD
                    execCMDInt(i, argv[1], cel_PID, cel_CMD, cel_ZOMBIE);
                    break;

                case 2:                                            //WAIT
                    execCMDInt(i, argv[1], cel_PID, cel_CMD, cel_ZOMBIE);
                    break;

                case 3:                                            //EXIT
                    execCMDInt(i, argv[1], cel_PID, cel_CMD, cel_ZOMBIE);
                    break;
            }

            pop(cel_CMD);                                          //Retira o comando da fila

        }//FIM_IF
        else                                                       //Comando externo
        {
            execCMDExt(cel_PID, cel_CMD, argv[0], argv);           //Executa comando externo
        }
        i=0;                                                       //Reinicia indice
    }//FIM_WHILE

}//FIM COMANDOS

/////////////////////////////////////// COMANDOS INTERNOS //////////////////////////////////////////////////////////////

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

void execCMDInt(int cmd, char* parametro, Celula cel_PID, Celula cel_CMD, Celula cel_ZOMBIE)    //Executa o comando interno
{
    if(cmd == 1)                                         //Se for o comando CD
    {
        CD(parametro);                                   //Chama a funcao CD
        return;
    }

    if(cmd == 2)                                         //Se for o comando WAIT
    {
        WAIT(cel_PID, cel_ZOMBIE);                                          //Chama a funcao wait
        return;
    }

    if(cmd == 3)                                        //Se for o comando EXIT
    {
        EXIT(cel_PID, cel_CMD, cel_ZOMBIE);                          //Chama a funcao EXIT
        return;
    }
}

void CD(char* parametro)                                 //Comando CD
{
    if(parametro == NULL)                                //Se o parametro for NULL vai para a Raiz
    {
        chdir("/");                                      //Muda para diretoria raiz
        return;
    }

    if(chdir(parametro)) //Verifica o parametro e realiza o cd
        printf("Diretorio passado para o comando cd nao encontrado\n");
}

void WAIT(Celula cel_PID, Celula cel_ZOMBIE) //Comando WAIT
{
    int process;

    while(getNumElem(cel_ZOMBIE) != 0)     //Imprime todos os processos q estavam em defunct
    {
        printf("\nRecolhido os restos de estado ZOMBIE do processo filho %d\n", getElemIntTopoCelula(cel_ZOMBIE)); //Imprime filhos encontrados)
        pop(cel_ZOMBIE);
    }

    while(process = waitpid(-1, NULL, WNOHANG)) //Enquanto nao liberar todos os filhos que encerraram
    {
        if(process == -1)                       //Se nao encontrar processos vivos ou no estado zombie sai
            break;
        printf("\nRecolhido os restos de estado ZOMBIE do processo filho %d\n", process); //Imprime filhos encontrados
    }
    printf("\nNão existem mais processos filhos no estado ZOMBIE\n");
}

void EXIT(Celula cel_PID, Celula cel_CMD, Celula cel_ZOMBIE) //Comando EXIT
{
    int i=0, stats;
    int *vetor = NULL;
    // WAIT();  //Espera todos os filhos serem liberados do estado zombie
    vetor = geraVetorPID(cel_PID);

    for(i = 0; i < getNumElem(cel_PID); i++)                      //Mata todos filhos
    {
        kill(vetor[i], SIGABRT);
    }

    sleep(1);                                                //Delay para pegar os filhos q foram finalizados pelo kill

    while(i = waitpid(-1,NULL,WNOHANG))                      //Verifica se existem processos vivos
    {
        if(i == -1)                                          //Se nao existirem processos filhos vivos ou defunct encerra
            break;

        printf("\nProcesso %d liberado do estado ZOMBIE\n",i);
        sleep(1);                                            //Delay para pegar os filhos q foram finalizados pelo kill
    }

    free(vetor);
    liberaCelula(&cel_PID);
    liberaCelula(&cel_CMD);
    liberaCelula(&cel_ZOMBIE);
    printf("\nFinalizando Lazy Shell...\n");
    exit(EXIT_SUCCESS);  //Encerra o programa
}

/////////////////////////////////////// COMANDOS EXTERNOS //////////////////////////////////////////////////////////////

void execCMDExt(Celula cel_PID, Celula cel_CMD, const char *cmd, char *const argv[])
{
        int pid;

        pid = fork();                                           //Cria processo filho

        if(pid < 0)                                             //Verifica se ocorreu erro no fork
        {
            fprintf(stderr,"\nERRO NO FORK\n");                   //Imprime mensagem de erro
            _exit(EXIT_FAILURE);                                 //Encerra processo
        }

        if(pid == 0) //Se for o filho
        {
            signal(SIGINT,SIG_IGN);                              //Ignorar SIGINT
            if(setsid() < 0)                                            //Coloca o processo filho em background
              fprintf(stderr, "\n ERRO NO SETSIG\n");
            execvp(cmd, argv);                                   //Executa comando externo
            fprintf(stderr, "\nO COMANDO < %s > NAO FOI ENCONTRADO!!!\n",cmd); //Se der erro na execucao imprime mensagem de ERRO
            _exit(EXIT_FAILURE);                                  //Encerra processo
        }
        pop(cel_CMD);
        addElemIntCelula(cel_PID,pid);                  //Insere o PID do filho na fila de PIDs
}
