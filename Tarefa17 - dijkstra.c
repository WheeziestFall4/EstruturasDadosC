/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   DESCRICAO: programa calcula cidades capazes de serem consideradas capitais de um estado, baseado
   nos aspectos de centralidade. As cidades sao vertices de um grafo e as arestas as conexoes entre eles.
   ENTRADA: num de cidades, cada cidade com o nome e a populacao respectiva. Apos isso, recebe as conexoes
   entre as cidades existentes no formato cidade1 cidade2 e distancia entre elas.
   SAIDA: Todas as cidades que podem ser consideradas capitais e seu fator de centralidade do lado*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_ESQ(i) (2 * i + 1) /*Guarda a relacao que os vetores tem entre si*/
#define F_DIR(i) (2 * i + 2) /* de acordo com o MINHEAP*/
#define PAI(i) ((i - 1) / 2)
#define INTMAX 200000 

typedef struct cidades
{
    int indice;     /* Guarda o indice correspondente ao vetor da lista de Adjacencia*/
    char nome[30];
    double centralidade;
    int somaPopulacaoLigadas;   /* Soma todas as populacoes das cidades que sao ligadas com a atual*/
    int populacao;
    double peso;
    struct cidades *prox;
} Cidades;

typedef struct grafo
{
    int tamanho;
    Cidades **listaAdjacencia;
} Grafo;

typedef struct
{
    double prioridade;  /* Prioridade nesse caso seria a distancia minima entre as cidades*/
    int vertice;           /* Guarda os indices de cada cidade registrada*/
} Item;

typedef struct filaPrioridade
{
    Item *vetor;
    int *indice;
    int n, tamanho;
} FilaPrioridade;

Cidades *insereNaLista(Cidades *lista, char nome[], int populacao, int indice, double peso)
{
    Cidades *nova = malloc(sizeof(Cidades));
    strcpy(nova->nome, nome);
    nova->indice = indice;
    nova->populacao = populacao;
    nova->peso = peso;
    nova->prox = lista; /* Insere no inicio da lista em questao*/

    return nova;
}

void adicionaAresta(Grafo *grafo, Cidades vetorCidades[], char nome1[], char nome2[], double peso)
{
    int indiceDaLista = 0, indiceDaAdicao = 0;

    for (int i = 0; i < grafo->tamanho; i++)
    {
        if (strcmp(vetorCidades[i].nome, nome1) == 0) /* Descobre o indice correspondente a cidade de nome1*/
        {
            indiceDaLista = i;
        }

        if (strcmp(vetorCidades[i].nome, nome2) == 0) /* Descobre o indice correspondente a cidade de nome2*/
        {
            indiceDaAdicao = i;
        }
    }

    /* Salva na lista correspondente ao indice em questao. No caso, como eh uma conexao, deve salvar nas duas listas diferentes*/
    grafo->listaAdjacencia[indiceDaLista] = insereNaLista(grafo->listaAdjacencia[indiceDaLista], nome2, vetorCidades[indiceDaAdicao].populacao, indiceDaAdicao, peso);
    grafo->listaAdjacencia[indiceDaAdicao] = insereNaLista(grafo->listaAdjacencia[indiceDaAdicao], nome1, vetorCidades[indiceDaLista].populacao, indiceDaLista, peso);
}

/* Comeca o algoritmo de caminho minimo */

FilaPrioridade *criarFilaPrioridade(int tam)
{
    FilaPrioridade *fila = malloc(sizeof(FilaPrioridade));

    fila->tamanho = tam;
    fila->n = 0; /* marca quantos posicoes dos vetores esta ocupado*/
    fila->vetor = malloc(tam * sizeof(Item));

    return fila;
}

int vazia(FilaPrioridade *fprio)
{
    if (fprio->n == 0)
    {
        return 0;
    }

    return 1;
}

void trocar(Item *a, Item *b)
{
    Item t = *a;
    *a = *b;
    *b = t;
}

/* Sobe o elemento do indice k ate a posicao correta, no MINHEAP, os vetores com valores menores ficam na posicao PAI*/
void sobeNoHeap(FilaPrioridade *fila, int indice)
{
    if (indice > 0 && fila->vetor[PAI(indice)].prioridade > fila->vetor[indice].prioridade)
    {
        trocar(&fila->vetor[indice], &fila->vetor[PAI(indice)]);
        sobeNoHeap(fila, PAI(indice));
    }
}

void insereNaFila(FilaPrioridade *fila, int vertice, double maxPrioridade)
{

    fila->vetor[fila->n].vertice = vertice;
    fila->vetor[fila->n].prioridade = maxPrioridade;
    fila->n++;

    sobeNoHeap(fila, fila->n - 1);
}

void desceNoHeap(FilaPrioridade *fprio, int k)
{
    int maior_filho;

    if (F_ESQ(k) < fprio->n)
    {
        maior_filho = F_ESQ(k);

        if (F_DIR(k) < fprio->n &&
            fprio->vetor[F_ESQ(k)].prioridade > fprio->vetor[F_DIR(k)].prioridade)
        {
            maior_filho = F_DIR(k);
        }
        if (fprio->vetor[k].prioridade > fprio->vetor[maior_filho].prioridade)
        {
            trocar(&fprio->vetor[k], &fprio->vetor[maior_filho]);
            desceNoHeap(fprio, maior_filho);
        }
    }
}

Item extraiMinimo(FilaPrioridade *fila) /* Extrai o minimo do MINHEAP, nesse caso sera a propria raiz com indice 0*/
{
    Item item = fila->vetor[0];

    trocar(&fila->vetor[0], &fila->vetor[fila->n - 1]);
    fila->n--;
    desceNoHeap(fila, 0);

    return item;
}

void diminuiPrioridade(FilaPrioridade *fprio, int k, double valor)
{                           /*Diminui a prioridade do vetor que tem vertice igual k. Muda para valor valor*/
    int i = 0;

    for (i = 0; i < fprio->n; i++)
    {
        if (fprio->vetor[i].vertice == k) /* Se encontrar o vertice dado dentro de um vetor de posicao i, entao muda sua prioridade*/
        {
            fprio->vetor[i].prioridade = valor;
            break;
        }
    }

    sobeNoHeap(fprio, i);
}

double prioridade(FilaPrioridade *fila, int vertice)
{                           /* Devolve a prioridade dado um vertice*/
    double prioridade = 0;

    for (int i = 0; i < fila->n; i++)
    {
        if (fila->vetor[i].vertice == vertice) /* Procura se o vertice em questao esta no vetor*/
        {
            prioridade = fila->vetor[i].prioridade; /* retorna a prioridade da posicao i que esta o vertice vertice*/
            return prioridade;
        }
    }

    return prioridade;
}

FilaPrioridade *dijkstra(Grafo *grafo, int s)
{                   /* Algoritmo especifico que calcula as distancias minimas entre o vertice s e os outros do grafo*/
    Item item;

    Cidades *cidade;
    FilaPrioridade *fila = criarFilaPrioridade(grafo->tamanho);

    for (int i = 0; i < grafo->tamanho; i++)
    {
        insereNaFila(fila, i, INTMAX); /* Insere na fila de prioridade todos com prioridade MAXIMA*/
    }

    diminuiPrioridade(fila, s, 0); /* diminui a prioridade do vertice s para 0, ja que a distancia dele propria eh 0*/

    while (vazia(fila) == 1) /* Percorre as cidades conectadas ao vertice s e diminui suas prioridades*/
    {
        item = extraiMinimo(fila);

        if (item.prioridade != INTMAX)
        {
            for (cidade = grafo->listaAdjacencia[item.vertice]; cidade != NULL; cidade = cidade->prox)
            {
                if (item.prioridade + cidade->peso < prioridade(fila, cidade->indice))
                {
                    diminuiPrioridade(fila, cidade->indice, item.prioridade + cidade->peso);
                }
            }
        }
    }

    return fila; /* retorna a fila que contem o vetor com as distancias de s ate cada vertice do grafo*/
}

void calculaCentralidade(Grafo *grafo, Cidades vetorCidades[], int somaPopulacaoTotal)
{                           /* Calcula centralidade de cada cidade e mostra na tela organizado crescentemente e alfabeticamente*/
    double somaPeso = 0;
    int somaPopulacao = 0;

    FilaPrioridade *fila;
    Item *vetorResultado;

    for (int i = 0; i < grafo->tamanho; i++)
    {
        fila = dijkstra(grafo, i); /* Recebe a fila para o vertice i em questao*/
        vetorResultado = fila->vetor; /* Recebe o vetor que contem as distancias minimas de cada cidade ate a cidade s*/

        for (int i = 0; i < grafo->tamanho; i++)
        {
            if (vetorResultado[i].prioridade != INTMAX) /* Se a prioridade do vetor de posicao i for igual ao MAXIMO, significa que essas cidades*/
            {                           /* nao possuem ligacao entre si*/
                somaPeso += vetorCidades[vetorResultado[i].vertice].populacao * vetorResultado[i].prioridade;
                somaPopulacao += vetorCidades[vetorResultado[i].vertice].populacao;
            }
        }

        vetorCidades[i].centralidade = somaPeso / somaPopulacao; /* Calcula centralidade*/

        vetorCidades[i].somaPopulacaoLigadas = somaPopulacao;

        somaPeso = 0;
        somaPopulacao = 0;

        free(fila->vetor); /* desaloca a fila e o vetor alocados para i*/
        free(fila);
    }

    int i = 0, j = 0, max = 0;

    for (i = grafo->tamanho - 1; i > 0; i--) /* Selection Sort para organizar em ordem crescente*/
    {
        max = i;

        for (j = i - 1; j >= 0; j--)
        {
            if (vetorCidades[j].centralidade > vetorCidades[max].centralidade)
            {
                max = j;
            }
            else if (vetorCidades[j].centralidade == vetorCidades[max].centralidade)
            {       /* Se as centralidades forem iguais, devemos organizar em ordem alfabetica*/
                if (strcmp(vetorCidades[j].nome, vetorCidades[max].nome) > 0)
                {
                    max = j;
                }
            }
        }

        Cidades auxiliar = vetorCidades[i];
        vetorCidades[i] = vetorCidades[max];
        vetorCidades[max] = auxiliar;
    }

    for (int i = 0; i < grafo->tamanho; i++)
    {
        if (vetorCidades[i].centralidade != 0 && vetorCidades[i].somaPopulacaoLigadas >= (somaPopulacaoTotal / 2))
        {   /* Se a centralidade existir e a soma das populacoes ligadas for maior que a metade da populacao total, entao pode printar*/
            printf("\n%s", vetorCidades[i].nome);
            printf(" %.2lf", vetorCidades[i].centralidade);
        }
    }
}

void desalocaListas(Cidades *atual)
{
    if(atual != NULL)
    {
        desalocaListas(atual->prox);
        free(atual);
    }
}

int main()
{
    int numCidades = 0, populacao = 0, somaPopulacaoTotal = 0;
    double peso = 0;
    char nome[30], nome1[30], nome2[30];
    Grafo grafo;

    scanf("%d", &numCidades);

    grafo.tamanho = numCidades;

    grafo.listaAdjacencia = malloc(numCidades * sizeof(Cidades *));

    for (int i = 0; i < numCidades; i++)
    {
        grafo.listaAdjacencia[i] = NULL;
    }

    /* Vetor que guarda as informacoes de cada cidade e o indice que ira representar no grafo*/
    Cidades *vetorCidades = malloc(numCidades * sizeof(Cidades));

    for (int i = 0; i < numCidades; i++)
    {
        scanf("%s %d", nome, &populacao);
        strcpy(vetorCidades[i].nome, nome);
        vetorCidades[i].indice = i;
        vetorCidades[i].populacao = populacao;
        vetorCidades[i].somaPopulacaoLigadas = 0;
        vetorCidades[i].peso = 0;
        vetorCidades[i].prox = NULL;
        somaPopulacaoTotal += populacao;
    }

    while (scanf("%s %s %lf", nome1, nome2, &peso) != EOF)
    {
        adicionaAresta(&grafo, vetorCidades, nome1, nome2, peso);
    }

    calculaCentralidade(&grafo, vetorCidades, somaPopulacaoTotal);

    for(int i = 0; i < numCidades; i++)
    {
        desalocaListas(grafo.listaAdjacencia[i]);
    }

    free(grafo.listaAdjacencia);
    free(vetorCidades);
}