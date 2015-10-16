#ifndef _LAZYSHELL
    #define _LAZYSHELL

#define TAM_DIR 30
#define TAM_BUFFER 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void lazyShell(void);
void trata_SIGCTRLC(int);


#endif
