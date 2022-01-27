/* Nome: Vinicius Rodrigues da Costa Almeida RA:254843
   DESCRICAO: Programa distribui carregamentos e descarregamentos de pilhas de conteiners de acordo
   com uma fila de navios. Só termina apos todas as operacoes forem feitas ou quando nao ha como distri
   bui os conteiners nas docas.
   ENTRADA: numero de docas, capacidade de cada doca, numero de navios, dado de cada navio com nome 
   funcao (carrega ou descarrega), tipo de mercadoria e quantidade de conteiners.
   SAIDA: todas as operacoes feitas entre a fila e as docas no formato 
   nome do navio, funcao feita, tipo de mercadoria e quantidade de conteiners trocados*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct navio
{
    char nome[20];
    char funcao[11];
    char tipoMercadoria[20];
    int qtdConteiners;
    struct navio *prox;
} Navio;

typedef struct filaNavios /* Guarda a fila de Navios numa lista ligada. */
{                           /* Inicio da lista = final da fila*/
    Navio *inicio;          /* Fim da lista = inicio da fila*/
    Navio *fim;
    int tamanho;
} filaNavios;

typedef struct conteiner
{
    char nomeMercadoria[20];
    struct conteiner *prox;
} Conteiner;

typedef struct pilhaDocas   /* Guarda a pilha de conteiners numa lista ligada*/
{                           /* Inicio da lista = topo da pilha*/
    Conteiner *topo;        /* Fim da lista = fundo da pilha*/
    int capacidadeDisponivel;

} pilhaDocas;

void colocaNavioFinalFila(filaNavios *fila, Navio *navio) /* Retorna o navio do final da fila para o comeco*/ 
{                                               /* na lista, representa colocar no final da lista*/
    fila->inicio = navio->prox;
    fila->fim->prox = navio;
    fila->fim = navio;
    navio->prox = NULL;
}

void enfileiraNavios(filaNavios *filaNavios) /* Adiciona novos navios no final da lista*/
{
    Navio *novo = malloc(sizeof(Navio));

    scanf("%s %s %s %d", novo->nome, novo->funcao, novo->tipoMercadoria, &novo->qtdConteiners);

    if (filaNavios->inicio == NULL) /*Caso a fila tiver vazia ainda, coloca navio como inicio e fim da lista*/
    {
        filaNavios->inicio = novo;
        filaNavios->fim = novo;
        novo->prox = NULL;
    }
    else
    {
        filaNavios->fim->prox = novo;
        filaNavios->fim = novo;
    }

    filaNavios->tamanho++;
}

int desempilhaConteiners(Navio *navio, Conteiner *conteiner, pilhaDocas *pilhaDocas, char nomeMercadoria[])
{                                   /*Desempilha uma quantidade variavel de conteiners que estejam juntamente empilhados*/
    Conteiner *atual = conteiner;
    int qtdDesempilha = 0;
    int auxiliar = 0;

    do
    {
        pilhaDocas->topo = atual->prox;
        free(atual);

        atual = pilhaDocas->topo;

        pilhaDocas->capacidadeDisponivel++;
        qtdDesempilha++;

        if (atual != NULL)
        {
            if (strcmp(navio->tipoMercadoria, atual->nomeMercadoria) == 0)
            {
                auxiliar = 0;
            }
            else    /* O proximo conteiner eh de outro tipo e portanto nao deve ser retirado da pilha*/
            {
                auxiliar = 1;
            }
        }
        else    /* Não existe mais conteiners e portanto deve parar a retirada*/
        {
            auxiliar = 1;
        }
                /* A qtd de desempilhamento nao pode ultrapassar a capacidade maxima do navio*/
    } while ((auxiliar != 1) && (qtdDesempilha < navio->qtdConteiners));

    return qtdDesempilha;
}

void empilhaConteiners(pilhaDocas *pilhaDocas, char nomeMercadoria[], int qtdPilha)
{ /* Empilha novos conteiners no inicio da lista*/
    for (int i = 0; i < qtdPilha; i++)
    {
        Conteiner *novo = malloc(sizeof(Conteiner));

        strcpy(novo->nomeMercadoria, nomeMercadoria);
        novo->prox = pilhaDocas->topo;
        pilhaDocas->topo = novo;
        pilhaDocas->capacidadeDisponivel--;
    }
}

Navio *carrega(filaNavios *fila, Navio *navio, pilhaDocas pilhaDocas[], int numdocas)
{                           /* Carrega conteiners das pilhas para os navios*/
    Conteiner *conteiner;
    int qtdDesempilha = 0;

    for (int i = 0; i < numdocas; i++)
    {
        conteiner = pilhaDocas[i].topo;

        if (conteiner != NULL)  /* Caso a pilha de posicao i nao tiver vazia*/
        {
            if (strcmp(navio->tipoMercadoria, conteiner->nomeMercadoria) == 0)
            {   /* Se a mercadoria do topo da pilha for igual a do navio, pode comecar a desempilhar*/
                qtdDesempilha = desempilhaConteiners(navio, conteiner, &pilhaDocas[i], navio->tipoMercadoria);

                printf("\n%s carrega %s doca: %d conteineres: %d", navio->nome, navio->tipoMercadoria, i, qtdDesempilha);

                if (qtdDesempilha == navio->qtdConteiners)
                {
                    fila->inicio = navio->prox;
                    free(navio);
                    fila->tamanho--;
                }
                else    /* Se a qtd de pilhas desempilhadas for menor que a capacidade do navio*/
                {       /* navio deve ir para o inicio da fila*/
                    navio->qtdConteiners = navio->qtdConteiners - qtdDesempilha;
                    colocaNavioFinalFila(fila,navio);
                }

                return fila->inicio;
            }
        }
    }

    colocaNavioFinalFila(fila,navio); /* Se não houver desempilhamento, entao o navio deve voltar */
                                      /* para o inicio da fila*/
    return fila->inicio;
}

Navio *descarrega(filaNavios *fila, Navio *navio, pilhaDocas pilhaDocas[], int numdocas)
{                           /* Descarrega conteiners do navio para as pilhas*/
    int qtdPilha = 0;

    for (int i = 0; i < numdocas; i++)
    {
        if (pilhaDocas[i].capacidadeDisponivel > 0)
        {   /* Se tiver capacidade na pilha i, entao pode comecar o empilhamento*/
            if (pilhaDocas[i].capacidadeDisponivel >= navio->qtdConteiners)
            {                                       /* Caso em que o navio descarregou tudo*/
                qtdPilha = navio->qtdConteiners;

                empilhaConteiners(&pilhaDocas[i], navio->tipoMercadoria, qtdPilha);

                printf("\n%s descarrega %s doca: %d conteineres: %d", navio->nome, navio->tipoMercadoria, i, qtdPilha);

                fila->inicio = navio->prox;
                free(navio);
                fila->tamanho--;

                return fila->inicio;
            }
            else                                    /* Caso em que navio nao descarrega tudo*/
            {
                qtdPilha = pilhaDocas[i].capacidadeDisponivel;
                navio->qtdConteiners = navio->qtdConteiners - qtdPilha;

                empilhaConteiners(&pilhaDocas[i], navio->tipoMercadoria, qtdPilha);

                printf("\n%s descarrega %s doca: %d conteineres: %d", navio->nome, navio->tipoMercadoria, i, qtdPilha);

                colocaNavioFinalFila(fila,navio);

                return fila->inicio;
            }
        }
    }

    colocaNavioFinalFila(fila,navio);   /* Caso nao houver empilhamento, entao o navio deve
                                        voltar pro inicio da fila*/

    return fila->inicio;
}

int verificaCarregamentoNavios(filaNavios *filaNavios, pilhaDocas pilhaDocas[], int numdocas, int capacidadeMaxima)
{                   /* verifica se nao tem mais como empilhar/desempilhar nas pilhas*/
    Navio *atual;

    if (filaNavios->inicio != NULL)
    {
        for (atual = filaNavios->inicio; atual != NULL; atual = atual->prox)
        {
            if (strcmp(atual->funcao, "carrega") != 0) /* verifica se ha alguma descarregamento a ser feito*/
            {                                   /* se nao houver, entao pode ser sinal de que a fila nao vai ser mais esvaziada*/
                return 0;
            }
        }

        for (atual = filaNavios->inicio; atual != NULL; atual = atual->prox)
        {
            for (int i = 0; i < numdocas; i++)
            {
                if (pilhaDocas[i].capacidadeDisponivel < capacidadeMaxima)
                {
                    if (strcmp(atual->tipoMercadoria, pilhaDocas[i].topo->nomeMercadoria) == 0)
                    {                           /*Se nao houve pilhas com topo do mesmo tipo dos navios, entao*/
                        return 0;               /* pode ser sinal de que a fila nao vai ser esvaziada*/
                    }
                }
            }
        }
    }
    else
    {
        return 0;
    }

    printf("\nALERTA: impossivel esvaziar fila, restam %d navios.", filaNavios->tamanho);

    return 1;
}

void processoDocas(filaNavios *filaNavios, pilhaDocas pilhaDocas[], int numdocas, int capacidadeMaxima)
{
    Navio *atual = filaNavios->inicio;
    int verifica = 0;

    while ((atual != NULL) && (verifica == 0)) /* se a o inicio da fila nao for vazio ou se a verificacao der errado*/
    {                                
        if (strcmp(atual->funcao, "carrega") == 0) /* Se o navio no final da fila for do tipo carrega*/
        {
            atual = carrega(filaNavios, atual, pilhaDocas, numdocas);
            verifica = verificaCarregamentoNavios(filaNavios, pilhaDocas, numdocas, capacidadeMaxima);
        }
        else    /* Se o navio no final da fila for do tipo descarrega*/
        {
            atual = descarrega(filaNavios, atual, pilhaDocas, numdocas);
        }
    }
}

void desalocaFila(Navio *navio)
{
    if (navio != NULL)
    {
        desalocaFila(navio->prox);
        free(navio);
    }
}

int main()
{
    int numDocas = 0, capacidadeDoca = 0, numNavios = 0;

    filaNavios filaNavios;
    filaNavios.inicio = NULL;
    filaNavios.fim = NULL;
    filaNavios.tamanho = 0;

    pilhaDocas pilhas[1000]; /* Vetor estatico que armazena todas as pilhas*/

    scanf("%d", &numDocas);
    scanf("%d", &capacidadeDoca);
    scanf("%d", &numNavios);

    for (int i = 0; i < numDocas; i++) /* Inicializa todas as pilhas*/
    {
        pilhas[i].topo = NULL;
        pilhas[i].capacidadeDisponivel = capacidadeDoca;
    }

    for (int i = 0; i < numNavios; i++) 
    {
        enfileiraNavios(&filaNavios);
    }

    processoDocas(&filaNavios, pilhas, numDocas, capacidadeDoca);
    desalocaFila(filaNavios.inicio);
}