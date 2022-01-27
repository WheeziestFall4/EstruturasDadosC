/* Nome: Vinicius Rodrigues da Costa Almeida RA:254843
   DESCRICAO: Programa que dado uma musica, retorna as 50 palavras mais usadas e a frequencia com que
   elas aparecem.
   ENTRADA: Estimativa da quantidade de palavras que a musica tem, Qtd de palavras consideradas inuteis
   de significado (StopWords), todas as palavras StopWords, letra da musica inteira
   SAIDA: 50 palavras mais usadas na musica com a frequencia com que elas aparecem*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

typedef struct noTabela   /* No de cada posicao da tabela*/
{
  char palavra[30];
  int frequencia;
  struct noTabela *prox;
} NoTabela;

typedef struct hash   /* Guarda o vetor que representa a tabela Hash sendo o indice calculado por metodo*/
{                     /* de multiplicacao*/
  int tamanhoRealVetor;
  NoTabela **vetor;
} Hash;

typedef struct noStopWords /* Nos da Arvore StopWords que possue filhos direito e esquerdo*/
{
  char palavra[30];
  struct noStopWords *esq;
  struct noStopWords *dir;
} NoStopWords;

typedef struct arvoreStopWords  /* Guarda a raiz da arvore StopWord*/
{
  NoStopWords *raiz;
} ArvoreStopWords;

int ConverteHash(char palavra[], int tamanhoTabela) /* Calcula o indice que a palavra dada ira ocupar*/
{                                 /* baseado nas letras da palavra e o tamanho da tabela*/
  int i, numHash = 0;

  for (i = 0; i < strlen(palavra); i++)
  {
    numHash = (256 * numHash + palavra[i]) % tamanhoTabela;
  }

  return numHash;
}

NoTabela *inserirLista(NoTabela *atual, Hash *tabela, char palavra[])
{                                 /* Inseri Nos dado determinado vetor[n] de posicao n*/
  NoTabela *novo;

  if (atual == NULL) /* Se o vetor[n] ainda tiver vazio de NO*/
  {
    novo = malloc(sizeof(NoTabela));
    novo->frequencia = 1;
    strcpy(novo->palavra, palavra);
    novo->prox = NULL;

    tabela->tamanhoRealVetor++;

    atual = novo;
  }
  else    /* Se o vetor[n] nao tiver vazio, pode significar que */
  {
    NoTabela *auxiliar = atual;

    while (auxiliar != NULL)  /* Surgiu palavras iguais e deve aumentar a variavel frequencia*/
    {
      if (strcmp(auxiliar->palavra, palavra) == 0)
      {
        auxiliar->frequencia++;

        return atual;
      }

      auxiliar = auxiliar->prox;
    }

    auxiliar = atual;

    while (auxiliar->prox != NULL) /* Surgiu palavras que sao diferentes mas possui o mesmo indice = colisao*/
    {
       auxiliar = auxiliar->prox; /* Acha o ultimo NO no final da lista*/
    }                             /* que comeca no ponteiro guardado em v[n]*/

    novo = malloc(sizeof(NoTabela));
    novo->frequencia = 1;
    strcpy(novo->palavra, palavra);
    novo->prox = NULL;
    auxiliar->prox = novo;

    tabela->tamanhoRealVetor++;
  }

  return atual; /*retorna o inicio da lista*/
}

void inserirTabela(Hash *tabela, char palavra[], int tamanhoTabela)
{                                               
  int n = ConverteHash(palavra, tamanhoTabela);

  tabela->vetor[n] = inserirLista(tabela->vetor[n], tabela, palavra); 
}                                           /* Guarda inicio de uma lista no vetor de posicao n*/

int verificaStopWords(NoStopWords *atual, char palavra[])
{                                 /* verifica se a palavra dada eh uma StopWord*/
  if (atual == NULL || strcmp(atual->palavra, palavra) == 0)
  {
    if (atual != NULL)
    {
      return 1; /* Se a palavra eh uma StopWord, retorna 1*/
    }
    else
    {
      return 0; /* Se a palavra nao eh, retorna 0*/
    }
  }
  else
  {
    if (strcmp(atual->palavra, palavra) > 0) /* Se a palavra dada for menor que a palavra atual,*/
    {
      return verificaStopWords(atual->esq, palavra); /* procura na esquerda da arvore*/
    }
    else
    {
      return verificaStopWords(atual->dir, palavra);  /* Se for maior, procura na direita*/
    }
  }
}

NoStopWords *inserirArvoreStopWords(NoStopWords *atual, char palavra[])
{                     /* Insere todas as palavras StopWords dado pelo usuario em uma arvore binaria de busca*/
  NoStopWords *no;

  if (atual == NULL) /* Se o no em questao tiver vazio, pode adicionar a nova palavra nele*/
  {
    no = malloc(sizeof(NoStopWords));
    strcpy(no->palavra, palavra);
    no->dir = NULL;
    no->esq = NULL;

    return no;
  }
  else
  {
    if (strcmp(atual->palavra, palavra) > 0) /* Se a palavra for menor que a palavra atual, entao*/
    {
      atual->esq = inserirArvoreStopWords(atual->esq, palavra); /* adiciona na esquerda*/
    }
    else /* Se for maior, coloca na direita*/
    {
      atual->dir = inserirArvoreStopWords(atual->dir, palavra);
    }

    return atual;
  }
}

void troca(NoTabela *objeto1, NoTabela *objeto2) /* Troca dois nos de lugar*/
{
  NoTabela auxiliar = *objeto1;
  *objeto1 = *objeto2;
  *objeto2 = auxiliar;
}

int partition(NoTabela v[], int l, int r) /* Funcao utilizada no QuickSort*/
{
  int i = l;

  for (int j = l; j < r; j++)
  {
    if (v[j].frequencia < v[r].frequencia) 
    {
      troca(&v[i++], &v[j]);
    }
    else if (v[j].frequencia == v[r].frequencia)
    {
      if (strcmp(v[r].palavra, v[j].palavra) < 0) /* Se as frequencias sao iguais e as palavra de r for menor*/
      {                             /* ou seja, antes alfabeticamente da palavra j, entao troca de lugar*/
        troca(&v[r], &v[j]);
      }
    }
  }
  troca(&v[i], &v[r]);

  return i;
}

void quickSort(NoTabela v[], int indiceInicial, int indiceFinal)
{                 /* Metodo eficiente de ordenacao QUICK SORT*/
  int i = 0;

  if (indiceFinal <= indiceInicial)
  {
    return;
  }

  i = partition(v, indiceInicial, indiceFinal);

  quickSort(v, indiceInicial, i - 1);
  quickSort(v, i + 1, indiceFinal);
}

void organizaMostraTabela(Hash *tabela, NoTabela vetor[], int tamanhoTabela)
{                 /* Passa todos as posicoes da tabela que seja diferente de NULO para um novo vetor*/
  int t = 0;      /* ordena esse novo vetor e imprimi as 50 palavras com frequencia mais alta*/

  for (int i = 0; i < tamanhoTabela; i++)
  {
    if (tabela->vetor[i] != NULL) /* Se a posicao na tabela nao tiver vazia*/
    {
      strcpy(vetor[t].palavra, tabela->vetor[i]->palavra);
      vetor[t].frequencia = tabela->vetor[i]->frequencia;
      t++;

      if (tabela->vetor[i]->prox != NULL) /* Se na posicao i da tabela tiver uma lista com mais de 1 item*/
      {
        NoTabela *auxiliar = tabela->vetor[i]->prox;

        while (auxiliar != NULL)
        {
          strcpy(vetor[t].palavra, auxiliar->palavra);
          vetor[t].frequencia = auxiliar->frequencia;
          t++;

          auxiliar = auxiliar->prox; /* Percorre a lista e faz a copia para o vetor novo*/
        }
      }
    }
  }

  quickSort(vetor, 0, tabela->tamanhoRealVetor - 1); /*Organiza o novo vetor*/

  for (int i = tabela->tamanhoRealVetor - 1; i >= tabela->tamanhoRealVetor - 50; i--)
  {                                                              /* Faz impressao ao contrario do vetor ate completar 50 itens*/
    printf("%s %d\n", vetor[i].palavra, vetor[i].frequencia);
  }
}

void desalocaArvoreStopWords(NoStopWords *raiz)
{
  if(raiz != NULL)
  {
    desalocaArvoreStopWords(raiz->esq);
    desalocaArvoreStopWords(raiz->dir);
    free(raiz);
  }
}

void desalocaLista(NoTabela *atual)
{
    if (atual != NULL)
    {
        desalocaLista(atual->prox);
        free(atual);
    }
}

int main()
{
  int tamanhoTabela = 0, n = 0;
  char stopWords[50], palavra[50];

  ArvoreStopWords arvore;
  arvore.raiz = NULL;

  Hash tabela;

  scanf("%d", &tamanhoTabela);

  tabela.vetor = malloc(tamanhoTabela * sizeof(NoTabela *));
  tabela.tamanhoRealVetor = 0;

  for (int i = 0; i < tamanhoTabela; i++)
  {
    tabela.vetor[i] = NULL; /* Inicializa todas posicoes da tabela com NULL*/
  }

  scanf("\t%d", &n); /* n eh qtd de StopWords*/

  for (int i = 0; i < n; i++)
  {
    scanf("\t%s", stopWords);

    arvore.raiz = inserirArvoreStopWords(arvore.raiz, stopWords);
  }

  while (scanf("\t%s", palavra) != EOF)
  {
    int i = 0;

    for (i = 0; i < strlen(palavra); i++)
    {
      if (!isalpha(palavra[i])) /* Se a letra da palavra for diferente de letras ou seja simbolos etc*/
      {
        for (int j = i; j < strlen(palavra); j++)
        {
          if (j + 1 <= strlen(palavra))
          {
            palavra[j] = palavra[j + 1]; /* Todas as letras depois sao ajustadas para uma posicao a menos*/
          }
        }

        i--; /* Diminui i pois uma nova letra ocupou a posicao antiga e ela deve ser testada novamente*/
      }
      else
      {
        palavra[i] = tolower(palavra[i]); /* coloca em minuscula*/
      }
    }

    palavra[i] = '\0'; 

    if (strcmp(palavra, "") != 0) /* Se a palavra estiver vazia devido as alteracoes feitas*/
    {
      if (strlen(palavra) != 1) /* Se a palavra for de apenas 1 letra, nao deixe passar*/
      {
        if (verificaStopWords(arvore.raiz, palavra) == 0) 
        {
          inserirTabela(&tabela, palavra, tamanhoTabela);
        }
      }
    }
  }

  NoTabela *vetor = malloc(tabela.tamanhoRealVetor * sizeof(NoTabela)); /* Aloca o novo vetor com o tamanho real*/
                                                                      /* ou seja, com todas as posicoes ocupadas*/
  organizaMostraTabela(&tabela, vetor, tamanhoTabela);

  /* Desaloca todas as etapas que foram alocadas */

  desalocaArvoreStopWords(arvore.raiz);

  for(int i = 0; i < tamanhoTabela; i++)
  {
     desalocaLista(tabela.vetor[i]);
  }

  free(tabela.vetor);
  free(vetor);
}