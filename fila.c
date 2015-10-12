#include "fila.h"
#define TAM 50

/////////////////////////////// FILA //////////////////////////////////////////

struct tFila                //Estrutura da Fila
{
  char *buffer;
  struct tFila *prox;
};

char* copia_string(char *str)  //Funcao para copia de string
{
    char *p;
    p = (char*) malloc(1+strlen(str));
    strcpy(p, str);

    return p;
}

Fila criaElemFila(char *elem)          //Cria um novo elemento fila
{
    Fila novo = (Fila) malloc(sizeof(struct tFila));
    novo->buffer = (char*) copia_string(elem);
    novo->prox = NULL;

    return novo;
}

int filaVazia(Fila f)
{
    return f == NULL;
}

void liberaFila(Fila *fila)
{
    if(*fila == NULL)
        return;

    Fila f, aux;
    f = aux = *fila;

    while(aux != NULL)
    {
        free(aux->buffer);
        aux = aux->prox;
        free(f);
        f = aux;
    }
}

void insereFinalFila(Fila *fila, char *str)
{
    if(*fila == NULL)
    {
        *fila = criaElemFila(str);
        return;
    }

    Fila aux = *fila;

    while(aux->prox != NULL)
        aux = aux->prox;

    aux->prox = criaElemFila(str);
}

void imprimeFila(Fila fila)
{
    if(fila == NULL)
    {
        printf("Fila Vazia\n");
        return;
    }

    while(fila != NULL)
    {
        printf("%s\n", fila->buffer);
        fila = fila->prox;
    }
}

//////////////////////////////////////// CELULA ////////////////////////////////

struct tCelula              //Estrutura da Celula
{
  struct tFila *primeiro;
  struct tFila *ultimo;
};

Celula criaCelula(void)         //Cria uma celula
{
    Celula novo = (Celula) malloc(sizeof(struct tCelula));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    return novo;
}

void liberaCelula(Celula *cel)
{
    Celula c = (*cel);
    liberaFila(&c->primeiro);
    //liberaFila(c->ultimo);
    free(*cel);
}

int celulaVazia(Celula c) //Verifica se a celula esta vazia
{
  return c->primeiro == NULL;
}

void addElemCelula(Celula cel, char *str)  //Insere elemento na fila
{
    if(celulaVazia(cel))  //Se a fila estiver vazia insere o primeiro elemento
    {
        cel->primeiro = criaElemFila(str);
        cel->ultimo = cel->primeiro;
        return;
    }
    // Se nao insere no final

    Fila f = cel->ultimo;
    f->prox = criaElemFila(str);          //insere o novo elemento no final
    cel->ultimo = f->prox;             //atualiza o ultimo elemento da celula
}

void imprimeCelula(Celula cel)
{
    Fila f = cel->primeiro;
    imprimeFila(f);
}
