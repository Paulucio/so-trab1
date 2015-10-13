#include "lazyShell.h"

void lazyShell(void)
{
    char *dir;
    char buffer[TAM_BUFFER];

    // dir = getcwd(0,0);

    //---------cd wait exit

    for(;;)
    {
        dir = getcwd(0,0);

        printf("lsh> ~%s $ ",dir);
        // scanf("%s", buffer);
        fgets(buffer,TAM_BUFFER, stdin);
        sscanf(buffer,"%s",buffer);

        if(chdir(buffer))
            printf("Diretorio nao encontrado\n");
        // printf("buffer:%s\n", buffer);



    }

}
