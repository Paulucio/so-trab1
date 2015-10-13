#include "fila.h"

/////////////////////////////// FILA //////////////////////////////////////////

struct tFila                //Definindo a estrutura da Fila
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

Fila criaElemFila(char *elem)          //Cria um novo elemento na fila
{
    Fila novo = (Fila) malloc(sizeof(struct tFila));   //Aloca memoria para o novo elemento
    novo->buffer = (char*) copia_string(elem);         //Insere o elemento
    novo->prox = NULL;                                 //Inicializa o ponteiro do proximo

    return novo;
}

int filaVazia(Fila f) //Verifica se a fila esta vazia
{
    return f == NULL;
}

void liberaFila(Fila *fila) //Libera a memoria alocada pela fila
{
    if(*fila == NULL)   //Verifica se a fila esta vazia
        return;

    Fila f, aux;         //Libera a memoria percorrendo a fila
    f = aux = *fila;

    while(aux != NULL)
    {
        free(aux->buffer);
        aux = aux->prox;
        free(f);
        f = aux;
    }
}

void insereFinalFila(Fila *fila, char *str) //Insere no final da fila
{
    if(*fila == NULL)     //Verifica se a fila esta vazia
    {
        *fila = criaElemFila(str);
        return;
    }

    Fila aux = *fila;

    while(aux->prox != NULL)            //Percorre a fila e insere no final
        aux = aux->prox;

    aux->prox = criaElemFila(str);
}

void imprimeFila(Fila fila)  //Funcao de imprimir os elementos da fila
{
    if(fila == NULL)   //Se estiver vazia
    {
        printf("Fila Vazia\n");
        return;
    }

    while(fila != NULL)  //Percorre a fila imprimindo os elementos
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
    Celula novo = (Celula) malloc(sizeof(struct tCelula)); //Aloca memoria para uma celula
    novo->primeiro = NULL;  //Inicia ponteiros com NULL
    novo->ultimo = NULL;
    return novo;
}

void liberaCelula(Celula *cel) //Libera a memoria alocada pela celula
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

void imprimeCelula(Celula cel) //Imprime os elementos da celula
{
    Fila f = cel->primeiro;
    imprimeFila(f);
}
