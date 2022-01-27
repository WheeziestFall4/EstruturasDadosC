/* NOME: Vinicius Rodrigues da Costa Almeida    RA: 254843
   TAREFA 12
   DESCRICAO: Tarefa simula um aplicativo que permite buscar ofertas de acordo com o produto e
   o preço dado pelo usuario. Programa cria uma arvore binaria de todos os produtos nas respectivas lojas
   e os preços de venda. Apos isso, dado o preço de oferta acrescido de 10%, ele procura em quais
   lojas o produto em questões esta com preco em oferta
   ENTRADA: numero de produtos cadastrados, cada produto com nome da loja, codigo do produto e preco a ser vendido,
    qtd de busca que serao feitas na arvore e cada busca com o codigo do produto e o preco de oferta a ser buscado
   SAIDA: impressao por Codigo de produto de todos os produtos em Lojas que vendem o preco de oferta, caso
   nao houve produtos dentro da oferta, imprimi ofertas nao disponivel*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noSubArvore /* Nos das Arvores que estao armazenadas dentro da arvore principal*/
{                          /* Guarda as informacoes do produto*/
    char nomeLoja[20];
    double valor;
    int codigoArvore;
    struct noSubArvore *esq;
    struct noSubArvore *dir;

} NoSubArvore;

typedef struct noArvore /* No da Arvore principal, guarda por codigo de Produto e as raizes */
{                       /*das subarvores de cada codigo, alem do tamanho da subarvore*/
    NoSubArvore *raizSubArvore;
    int codigoProduto;    /* Arvore de busca binaria*/
    int tamanhoSubArvore; /* esquerdas = valores menore do que o no*/
    struct noArvore *esq; /* direitas = valores maiores do que no*/
    struct noArvore *dir;
} NoArvore;

typedef struct arvore /* Guarda a raiz da arvore principal*/
{
    NoArvore *raizArvore;
} Arvore;

int adicionaNoEsquerdoVetor(NoSubArvore *raiz, NoSubArvore vetor[], int tamanhoAtual)
{ /* Adiciona todo os nos que estao a esquerda de determinado no em um vetor dinamico*/
    if (raiz != NULL)
    {
        strcpy(vetor[tamanhoAtual].nomeLoja, raiz->nomeLoja);
        vetor[tamanhoAtual].valor = raiz->valor;
        tamanhoAtual++;

        tamanhoAtual = adicionaNoEsquerdoVetor(raiz->esq, vetor, tamanhoAtual);
        tamanhoAtual = adicionaNoEsquerdoVetor(raiz->dir, vetor, tamanhoAtual);
    }

    return tamanhoAtual;
}

NoSubArvore *adicionaSubArvore(NoSubArvore *raiz, int codigoProduto, char nomeLoja[], double valorProduto)
{ /* Apos passar o codigo de determinado produto, funcao adiciona os produtos na subarvore destinada*/
    NoSubArvore *novo;

    if (raiz == NULL) /* Se o no em questao for vazio, coloque o produto nele*/
    {
        novo = malloc(sizeof(NoSubArvore));
        strcpy(novo->nomeLoja, nomeLoja);
        novo->valor = valorProduto;
        novo->codigoArvore = codigoProduto;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    else /* Se o no nao tiver vazio, deve percorrer um de seus ramos*/
    {
        novo = raiz;

        if (valorProduto < raiz->valor) /* Se o valor do no for menor do que do no-pai, entao coloque na esquerda*/
        {
            raiz->esq = adicionaSubArvore(raiz->esq, codigoProduto, nomeLoja, valorProduto);
        }
        else /* Se o valor for maior, entao coloque na direita*/
        {
            raiz->dir = adicionaSubArvore(raiz->dir, codigoProduto, nomeLoja, valorProduto);
        }
    }

    return novo;
}

NoArvore *adicionaArvore(NoArvore *raiz, NoArvore *raizAtual, char nomeLoja[], int codigoProduto, double valorProduto)
{                 /*Adiciona os produtos na arvore principal mas adicionando somente os codigos do Produto*/
    NoArvore *no; /* Os dados dos produtos que possuem o mesmo codigo sao colocado numa subArvore*/

    if (raizAtual == NULL) /* Se o no em questao tiver vazio, pode adicionar o novo Codigo nele*/
    {
        no = malloc(sizeof(NoArvore));
        no->codigoProduto = codigoProduto;
        no->raizSubArvore = NULL;
        no->tamanhoSubArvore = 1;
        no->dir = NULL;
        no->esq = NULL;
        no->raizSubArvore = adicionaSubArvore(no->raizSubArvore, codigoProduto, nomeLoja, valorProduto);
    }
    else
    {
        no = raizAtual;

        if (raizAtual->codigoProduto == codigoProduto) /* verifica se ja existe algum no que ja possui o mesmo codigo*/
        {                                              /* se tiver, adiciona somente na subarvore e nao mexe na arvore principal*/
            raizAtual->raizSubArvore = adicionaSubArvore(raizAtual->raizSubArvore, codigoProduto, nomeLoja, valorProduto);
            raizAtual->tamanhoSubArvore++;

            return raizAtual;
        }

        if (codigoProduto < raizAtual->codigoProduto) /* Se o novo codigoProduto for menor que o no-pai, entao ele eh colocado na esquerda*/
        {
            raizAtual->esq = adicionaArvore(raiz, raizAtual->esq, nomeLoja, codigoProduto, valorProduto);
        }
        else /* Se for maior, coloca na direita*/
        {
            raizAtual->dir = adicionaArvore(raiz, raizAtual->dir, nomeLoja, codigoProduto, valorProduto);
        }
    }

    return no;
}

void ordenaVetorOrdemAlfabetica(NoSubArvore vetor[], int tamanho)
{ /* Coloca o vetor dinamico com todos os produtos dentro da oferta em ordem alfabetica*/
    NoSubArvore auxiliar;

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 1; j < tamanho; j++)
        {
            for (int k = 0; k < 20; k++)
            {
                if (vetor[i].nomeLoja[k] != vetor[j].nomeLoja[k] && j > i)
                { /* Sendo os nomes diferentes entre si, entao pode comparar*/
                    if (vetor[i].nomeLoja[k] > vetor[j].nomeLoja[k])
                    {
                        auxiliar = vetor[i];
                        vetor[i] = vetor[j];
                        vetor[j] = auxiliar;
                    }

                    break;
                }
            }
        }
    }
}

void imprimirOfertas(NoSubArvore vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("\n%s %d %.2lf", vetor[i].nomeLoja, vetor[i].codigoArvore, vetor[i].valor);
    }
}

int buscaOferta(NoSubArvore *raiz, NoSubArvore vetor[], int tamanhoAtual, double valorOferta)
{ /* funcao que busca nas SubArvore os precos adequados da oferta*/
    if (raiz == NULL || (raiz->esq == NULL && raiz->dir == NULL))
    { /* Se ele tiver a esquerda e direita vazia, entao significa que chegou a uma folha final da subarvore*/
        if (raiz != NULL)
        {
            if (raiz->valor <= valorOferta)
            {
                strcpy(vetor[tamanhoAtual].nomeLoja, raiz->nomeLoja);
                vetor[tamanhoAtual].valor = raiz->valor;
                tamanhoAtual++;
            }
        }

        ordenaVetorOrdemAlfabetica(vetor, tamanhoAtual);
        imprimirOfertas(vetor, tamanhoAtual);

        if (vetor[0].valor != 0) /* Se o vetor tiver a primeira posicao diferente de 0, entao ele foi ocupado por um No da SubArvore*/
        {                        /* ou seja, houve ofertas encontradas*/
            free(vetor);         /* pode desalocar o vetor ja que nao sera mais usado para o codigo em questao*/
            return 1;            /* retorna 1 significa que encontrou oferta*/
        }
        else
        {
            free(vetor); /* mesmo vazio o vetor, ainda precisa desalocar sua variavel*/
            return 0;
        }
    }
    else
    {
        if (raiz->valor <= valorOferta) /* os precos devem ser menores ou iguais ao valor da oferta*1,1*/
        {
            strcpy(vetor[tamanhoAtual].nomeLoja, raiz->nomeLoja);
            vetor[tamanhoAtual].valor = raiz->valor;
            tamanhoAtual++;

            tamanhoAtual = adicionaNoEsquerdoVetor(raiz->esq, vetor, tamanhoAtual); /* Se o preco do noAtual tiver adequado, entao */
                                                                                    /* todas os nos a esquerda dele tambem esta adequado*/
            return buscaOferta(raiz->dir, vetor, tamanhoAtual, valorOferta);        /* busca Oferta as diretas no noAtual*/
        }
        else
        {
            return buscaOferta(raiz->esq, vetor, tamanhoAtual, valorOferta); /* Se noAtual nao tiver preco adequado, entao devemos percorrer a esquerda*/
        }                                                                    /* para verificar se existe um preco valido na SubArvore*/
    }
}

int buscaCodigo(NoArvore *raiz, int codigoProduto, double valorOferta) /* Busca se o codigo dado pelo usuario exista na arvore principal*/
{
    if (raiz == NULL || raiz->codigoProduto == codigoProduto) /* Se encontrar o codigo do produto em questao, deve*/
    {                                                         /* alocar um vetor dinamico com o tamanho da subarvore associado a esse codigo*/
        if (raiz != NULL)
        {
            NoSubArvore *vetor = malloc(raiz->tamanhoSubArvore * sizeof(NoSubArvore));

            for (int i = 0; i < raiz->tamanhoSubArvore; i++) /*Inicializa todas as posicoes do vetor*/
            {
                vetor[i].codigoArvore = codigoProduto;
                strcpy(vetor[i].nomeLoja, "");
                vetor[i].valor = 0;
            }

            return buscaOferta(raiz->raizSubArvore, vetor, 0, valorOferta); /*busca a Oferta nas subArvores passando o vetor*/
        }
        else
        {
            return 0; /*Nao encontrou o codigo do Produto na arvore principal*/
        }
    }
    else
    {
        if (raiz->codigoProduto > codigoProduto) /* Se o noAtual tiver codigo maior que o codigo dado, entao procure na esquerda do no*/
        {
            return buscaCodigo(raiz->esq, codigoProduto, valorOferta);
        }
        else /* senao, procura a direita do no*/
        {
            return buscaCodigo(raiz->dir, codigoProduto, valorOferta);
        }
    }
}

void desalocaSubArvore(NoSubArvore *raiz)
{
    if (raiz != NULL)
    {
        desalocaSubArvore(raiz->esq);
        desalocaSubArvore(raiz->dir);
        free(raiz);
    }
}

void desalocaArvore(NoArvore *raiz)
{
    if (raiz != NULL)
    {
        desalocaSubArvore(raiz->raizSubArvore); /*Antes de desalocar o no em questao, deve desalocar a subarvore associado a ele*/
        desalocaArvore(raiz->esq);
        desalocaArvore(raiz->dir);
        free(raiz);
    }
}

int main()
{
    Arvore arvore;
    arvore.raizArvore = NULL;

    int qtdAnuncios = 0, codigoProduto = 0;
    double valorProduto = 0;
    char nomeLoja[20];

    int numConsultas = 0;
    double valorOferta = 0;
    int verifica = 0;

    scanf("%d", &qtdAnuncios);

    for (int i = 0; i < qtdAnuncios; i++)
    {
        scanf("%s %d %lf", nomeLoja, &codigoProduto, &valorProduto);
        arvore.raizArvore = adicionaArvore(arvore.raizArvore, arvore.raizArvore, nomeLoja, codigoProduto, valorProduto);
    }

    scanf("%d", &numConsultas);

    for (int i = 0; i < numConsultas; i++)
    {
        scanf("%d %lf", &codigoProduto, &valorOferta);

        valorOferta = 1.1 * valorOferta;

        printf("\n\nOFERTAS para %d:", codigoProduto);

        verifica = buscaCodigo(arvore.raizArvore, codigoProduto, valorOferta);

        if (verifica == 0) /* Se retorna 0, significa que ou nao achou o codigo ou nao ha produtos abaixo ou igual a esse valor de oferta*/
        {
            printf("\nnenhuma boa oferta foi encontrada\n");
        }
    }

    desalocaArvore(arvore.raizArvore);
}