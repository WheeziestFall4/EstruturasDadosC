/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   DESCRICAO: Programa simula um fila de uma boate em que a chegada de uma nova pessoa pode ser:
   - No final da fila: quando for pessoas normais, ela pega a lanterna pra ela e vai pro final
   - No inicio da fila: quando for pessoas VIPS, ela pega a lanterna pra ela e vai pro inicio
   - No final da fila sendo FUNCIONARIOS: nesse caso, independente de onde esteja a lanterna, ele pega 
   e vai pro final da fila.
   - FISCAl: retira aqueles atras dele que estao sem vacinacao. Contudo deve estar perto dele senao ele nao consegue
   fiscalizar (perto = um atras do outro sem vacinacao).
   ENTRADA: todas as pessoas com numero de identificao, tipo de profissao e se eh vacinado ou nao
   SAIDA: A fila (lista ligada) do inicio ao fim*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No   /* No que ira compor a lista ligada*/
{
    int lanterna;    /* guarda se o no (pessoa) em questao esta(1) ou nao(0) com a lanterna*/
    int numdocumento;
    char nomeprofissao[25];
    char estadovacinacao[25];
    struct No *prox;
} No;

typedef struct Lista
{
    No *inicio; /* Guarda o inicio da lista*/

} Lista;

void imprimiTela(Lista *lista)
{
    No *atual = lista->inicio;

    for (atual = lista->inicio; atual != NULL; atual = atual->prox)
    {
        printf("\n%d %s %s", atual->numdocumento, atual->nomeprofissao, atual->estadovacinacao);
    }
}


void fiscaliza(Lista *lista) /* Faz a fiscalizacao da fila em relacao aos nao vacinados*/
{                           /* Se tiver algum nao vacinado atras de um fiscal, deve ser retirado*/
    No *atual1;

    if (lista->inicio != NULL)
    {
        for (atual1 = lista->inicio; atual1 != NULL; atual1 = atual1->prox)
        {
            if (strcmp(atual1->nomeprofissao, "fiscal") == 0) /* Procura fiscal na lista ligada*/
            {
                No *atual2 = atual1->prox;
                No *aux;

                /* enquanto nao for NULL e for nao vacinado, entao deve ser retirado*/
                while ((atual2 != NULL) && (strcmp(atual2->estadovacinacao, "nao-vacinado") == 0))
                {
                    aux = atual2->prox;
                    free(atual2);
                    atual2 = aux;
                }

                atual1->prox = atual2;
             
            }
        }
    }
}

void adicionaVIP(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{                   /* Adiciona no inicio da lista ligada*/        
    if (lista->inicio != NULL) /* Se a lista (fila) nao tiver vazia, entao devemos reinicia todos os nos*/
    {                               /* com a lanterna = 0 e atribui para o VIP novo*/
        No *atual = lista->inicio;

        while (atual->prox != NULL)
        {
            if (atual->lanterna == 1)
            {
                atual->lanterna = 0;
            }

            atual = atual->prox;
        }

        atual->lanterna = 0;
    }

    No *novo = malloc(sizeof(No));

    novo->lanterna = 1; /* Contem a lanterna*/
    novo->numdocumento = numdocumento;
    strcpy(novo->nomeprofissao, nomeprofissao);
    strcpy(novo->estadovacinacao, estadovacinacao);
    novo->prox = lista->inicio; /* Se refere a lista, por que a lista guarda o endereço do primeiro no da lista*/
    lista->inicio = novo;

    fiscaliza(lista);
}

void adicionaNormal(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{ /* Adiciona elementos no final da lista ou depois da lanterna 1*/
    No *novo = malloc(sizeof(No));

    novo->lanterna = 1;
    novo->numdocumento = numdocumento;
    strcpy(novo->nomeprofissao, nomeprofissao);
    strcpy(novo->estadovacinacao, estadovacinacao);

    if (lista->inicio == NULL) /* Se a lista tiver vazia, significa que nao ha ninguem na fila ainda*/
    {
        lista->inicio = novo;
        novo->prox = NULL;
    }
    else
    {
        No *atual = lista->inicio;
        No *aux;

        while ((atual->lanterna != 1) && (atual->prox != NULL)) /* Percorremos a lista ate achar quem esta com a lanterna */
        {                                   /* ou ate chegar no final da lista (final da fila) */
            atual = atual->prox;
        }

        atual->lanterna = 0;

        aux = atual->prox; /* Aux pode ser NULL ou nao. Depende da posicao da lanterna*/
        atual->prox = novo;
        novo->prox = aux;
    }

   
    fiscaliza(lista);
    
}

void adicionaFuncionario(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{                                   /* Adiciona Funcionario sempre no final da lista e pega a lanterna pra ele*/
    No *novo = malloc(sizeof(No));

    novo->lanterna = 1;
    novo->numdocumento = numdocumento;
    strcpy(novo->nomeprofissao, nomeprofissao);
    strcpy(novo->estadovacinacao, estadovacinacao);

    if (lista->inicio == NULL) /* Se a lista (fila em questao) tiver vazia*/
    {
        lista->inicio = novo;
        novo->prox = NULL;
    }
    else
    {
        No *atual = lista->inicio;

        while (atual->prox != NULL) /* procura o ultimo no da fila */
        {
            atual->lanterna = 0;
            atual = atual->prox;
        }

        atual->lanterna = 0;

        atual->prox = novo; /* adiciona no final da fila atualizando o proximo do antigo no final*/
        novo->prox = NULL;
    }

    fiscaliza(lista);
}

void adicionaPessoas(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{                       /* Verifica qual tipo de profissao tem o novo individuo atraves da comparacao com o nome e adiciona*/
   
    if (strcmp(nomeprofissao, "coach") == 0 || strcmp(nomeprofissao, "ex-bbb") == 0 || strcmp(nomeprofissao, "filho-politico") == 0 || strcmp(nomeprofissao, "herdeiro") == 0 || strcmp(nomeprofissao, "youtuber-financas") == 0)
    {
        adicionaVIP(lista, numdocumento, nomeprofissao, estadovacinacao);
    }
    else if (strcmp(nomeprofissao, "funcionario") == 0)
    {
        adicionaFuncionario(lista, numdocumento, nomeprofissao, estadovacinacao);
    }
    else
    {
        adicionaNormal(lista, numdocumento, nomeprofissao, estadovacinacao);
    }
}

void desaloca(No* no)
{
   if(no != NULL)
   {
       desaloca(no->prox);
       free(no);
   }
}

int main()
{
    Lista lista;

    lista.inicio = NULL;

    int numdocumento = 0;
    char nomeprofissao[25] = "", estadovacinacao[25] = "";

    while (scanf("%d %s %s", &numdocumento, nomeprofissao, estadovacinacao) != EOF)
    {
        adicionaPessoas(&lista, numdocumento, nomeprofissao, estadovacinacao);
    }

    imprimiTela(&lista);
    printf("\n");

    desaloca(lista.inicio);
}