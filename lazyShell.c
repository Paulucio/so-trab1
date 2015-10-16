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

void trata_SIGUSR2 (int sig)
{
    static int i = 0;
    printf("Fim do SIGUSR2.\n");
}
