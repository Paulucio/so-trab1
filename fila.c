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

void liberaFilaEncadeada(Fila *fila) //Libera a memoria alocada pela fila
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
    if(*fila == NULL)     //Se a fila esta vazia
    {
        *fila = criaElemFila(str);      //Cria um novo elemento na fila
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

char* getElemFila(Fila f)                     //Pega o elemento da fila
{
    if(f == NULL)
        return NULL;

    return f->buffer;
}

//////////////////////////////////////// CELULA ////////////////////////////////

struct tCelula              //Estrutura da Celula
{
  struct tFila *primeiro;
  struct tFila *ultimo;
  int n_elem;
};

Celula criaCelula(void)         //Cria uma celula
{
    Celula novo = (Celula) malloc(sizeof(struct tCelula)); //Aloca memoria para uma celula
    novo->primeiro = NULL;  //Inicia ponteiros com NULL
    novo->ultimo = NULL;
    novo->n_elem = 0;
    return novo;
}

void liberaCelula(Celula *cel) //Libera a memoria alocada pela celula
{
    Celula c = (*cel);
    liberaFilaEncadeada(&c->primeiro);
    //liberaFila(c->ultimo);
    free(*cel);
}

Fila getTopoCelula(Celula cel)            //Retorna o primeiro da celula
{
    return cel->primeiro;
}

int celulaVazia(Celula c) //Verifica se a celula esta vazia
{

    return c == NULL || c->primeiro == NULL;
}

void addElemCelula(Celula cel, char *str)  //Insere elemento na fila
{
    if(celulaVazia(cel))  //Se a fila estiver vazia insere o primeiro elemento
    {
        cel->primeiro = criaElemFila(str);
        cel->ultimo = cel->primeiro;
        cel->n_elem += 1;
        return;
    }
    // Se nao insere no final

    Fila f = cel->ultimo;
    f->prox = criaElemFila(str);          //insere o novo elemento no final
    cel->ultimo = f->prox;             //atualiza o ultimo elemento da celula
    cel->n_elem += 1;
}

void imprimeCelula(Celula cel) //Imprime os elementos da celula
{
    if(cel == NULL) //Verifica se a fila esta vazia
    {
        printf("Celula Vazia\n");
        return;
    }

    printf("Numero de elementos: %d\n", cel->n_elem);
    Fila f = cel->primeiro;      //Referencia o primeiro elemento da fila
    imprimeFila(f);              //Imprime a fila
}

void pop(Celula cel)  //Remove o primeiro elemento da celula
{
    if(celulaVazia(cel))   //Verifica se a celula e valida
        return;

    Fila topo = cel->primeiro;      //Referencia o primeiro elemento

    cel->primeiro = topo->prox;     //O segundo elemento passa a ser o primeiro
    free(topo->buffer);             //Libera o elemento retirado
    free(topo);
    cel->n_elem -= 1;
}

int getNumElem(Celula cel)  //Retorna o numero de elementos da celula
{
    return cel->n_elem;
}

char* getElemTopoCelula(Celula c)  //Retorna o elemento do topo da celula
{
    return getElemFila(c->primeiro);
}

/////////////////////////////////// OPERACOES PARA NUMEROS NA FILA //////////////////////////////////////////

char* numToString(int num) //Converte inteiro para string
{
    const int TAM = 20;
    char *string = (char*) malloc(TAM*sizeof(char));
    sprintf(string,"%d",num);
    return string;
}

void addElemIntCelula(Celula cel, int num)  //Insere numero inteiro na fila
{
    char *str = NULL;

    if(celulaVazia(cel))  //Se a fila estiver vazia insere o primeiro elemento
    {
        str = numToString(num);
        cel->primeiro = criaElemFila(str);
        cel->ultimo = cel->primeiro;
        cel->n_elem += 1;
        free(str);
        return;
    }
    // Se nao insere no final

    str = numToString(num);
    Fila f = cel->ultimo;
    f->prox = criaElemFila(str);          //insere o novo elemento no final
    cel->ultimo = f->prox;             //atualiza o ultimo elemento da celula
    cel->n_elem += 1;
    free(str);
}

int* geraVetorPID(Celula cel)                              //Retorna vetor de PIDs dos processos
{
    int tam = getNumElem(cel), i=0;
    int *vetor = (int*) malloc(tam*sizeof(int));

    Fila aux = getTopoCelula(cel);

    // printf("Tamanho %d", tam);

    while(aux != NULL)
    {
        vetor[i++] = atoi(getElemFila(aux));
        aux = aux->prox;
    }
    return vetor;
}

int getElemIntTopoCelula(Celula c)  //Retorna o elemento do topo da celula
{
    return atoi(getElemFila(c->primeiro));
}
