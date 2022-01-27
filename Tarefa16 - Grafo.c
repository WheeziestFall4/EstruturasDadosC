/* NOME: Vinicius Rodrigues da Costa Almeida RA: 254843
   DESCRICAO: Programa simula um RPG no qual eh dado um numero de celas e o numero de jogadores.
   Cada cela possui pontos de habilidades unicos. As celas sao simulados como um grafo sendo os vertices
   as celas em questao e as arestas os caminhos possiveis a ser feitas pelos jogadores.
   ENTRADA: numero de celas, cada cela com nome, forca, destreza, constituicao, inteligencia, sabedoria e carisma
    num de jogadores e pontos de habilidades iniciais com forca, destreza, constituicao, inteligencia, sabedoria
    e carisma. 
   SAIDA: numero de celas possiveis que podem reunir os jogadores juntos apos duas rodadas.
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogadores 
{
    int celaInicial; /* Armazena a cela inicial que ele comeca no grafo*/
    char nome[30];
    int forca;
    int destreza;
    int constituicao;
    int inteligencia;
    int sabedoria;
    int carisma;
} Jogadores;

typedef struct cela 
{
    int numIndice; /* indica qual indice eh correspondente a cela*/
    char nome[30];
    int forca;
    int destreza;
    int constituicao;
    int inteligencia;
    int sabedoria;
    int carisma;
} Cela;

typedef struct grafo
{
    Cela *vertices;  /* Guarda as celas */
    int **matrizAdjacencia; /* Guarda as conexoes, linha ou coluna representa os vertices celas*/
    int tamanho;
} Grafo;

void imprimiCelasPossiveis(Grafo *grafo, Jogadores jogadores[], int numJogadores)
{
    int linha = 0, passou = 0;
    int x = 0;

    for (int j = 0; j < grafo->tamanho; j++) /* Percorre as linhas da matriz com num de cada cela*/
    {
        for (int i = 0; i < numJogadores; i++) /* Percorre as colunas da matriz com cela inicial de cada jogador*/
        {
            linha = jogadores[i].celaInicial;

            if (grafo->matrizAdjacencia[j][linha] == 1) /* Se naquela posicao for igual a 1, entao ha conexao*/
            {
                x++;
            }

            if (x == numJogadores) /* Se todas as colunas tiverem igual a 1, entao significa que todos os jogadore*/
            {                       /* podem se reunir naquela sala apos duas rodadas*/
                passou = 1;         /* Marca que houve ao menos 1 cela que pode reunir o final*/
                printf("%s\n", grafo->vertices[j].nome);
            }
        }

        x = 0;
    }

    if (passou == 0) /* Se for igual a 0, significa que nao houve cela que reunisse todos no final de duas rodadas*/
    {
        printf("\nImpossivel terminar em duas rodadas.");
    }
}

void adicionaJogadoresCela(Grafo *grafo, Jogadores jogadores[], int numJogadores)
{
    for (int i = 0; i < numJogadores; i++) /* Percorre todos os jogadores*/
    {
        for (int j = 0; j < grafo->tamanho; j++)
        {
            if (jogadores[i].forca == grafo->vertices[j].forca && jogadores[i].destreza == grafo->vertices[j].destreza)
            {
                if (jogadores[i].constituicao == grafo->vertices[j].constituicao && jogadores[i].inteligencia == grafo->vertices[j].inteligencia)
                {
                    if (jogadores[i].sabedoria == grafo->vertices[j].sabedoria && jogadores[i].carisma == grafo->vertices[j].carisma)
                    {                                       /* Todos if verifica qual cela inicial eh correspondente do jogador em questao*/
                        jogadores[i].celaInicial = j;
                    }
                }
            }
        }
    }
}

int testagemDePontos(Cela *cela1, Cela *cela2)
{
    int somaPontos = 0;

    if (cela1->forca - cela2->forca > 0) /* Todos if verifica se a subtracao eh negativa e se for ignora*/
    {
        somaPontos += cela1->forca - cela2->forca;
    }
    if (cela1->destreza - cela2->destreza > 0)
    {
        somaPontos += cela1->destreza - cela2->destreza;
    }
    if (cela1->constituicao - cela2->constituicao > 0)
    {
        somaPontos += cela1->constituicao - cela2->constituicao;
    }
    if (cela1->inteligencia - cela2->inteligencia > 0)
    {
        somaPontos += cela1->inteligencia - cela2->inteligencia;
    }
    if (cela1->sabedoria - cela2->sabedoria > 0)
    {
        somaPontos += cela1->sabedoria - cela2->sabedoria;
    }
    if (cela1->carisma - cela2->carisma > 0)
    {
        somaPontos += cela1->carisma - cela2->carisma;
    }

    return somaPontos;
}

void verificaArestas(Grafo *grafo, Jogadores jogadores[], int numJogadores)
{                           /* verifica as possiveis conexoes baseado nas duas rodadas e no aumento do atributos*/
    int posicao = 0;

    for (int i = 0; i < numJogadores; i++)
    {
        posicao = jogadores[i].celaInicial;

        for (int j = 0; j < grafo->tamanho; j++)
        {
            if (testagemDePontos(&grafo->vertices[j], &grafo->vertices[posicao]) <= 2)
            {   /* Se a soma de ponto for maior que 2, significa que mesmo apos duas rodadas, nao poderia termina na cela j*/
                grafo->matrizAdjacencia[j][posicao] = 1;
                grafo->matrizAdjacencia[posicao][j] = 1; /* Atribui a conexao*/
            }
        }
    }
}

int main()
{
    int numCelas = 0;
    int numJogadores = 0;

    Grafo grafo;

    char nome[30];
    int forca = 0, destreza = 0, constituicao = 0, inteligencia = 0, sabedoria = 0, carisma = 0;

    scanf("%d", &numCelas);

    grafo.tamanho = numCelas;
    grafo.matrizAdjacencia = malloc(numCelas * sizeof(int *));

    for (int i = 0; i < numCelas; i++)
    {
        grafo.matrizAdjacencia[i] = malloc(numCelas * sizeof(int));
    }

    for (int i = 0; i < numCelas; i++) /* Inicializa a matrizAdjacencia com 0 ou seja sem arestas*/
    {
        for (int j = 0; j < numCelas; j++)
        {
            grafo.matrizAdjacencia[i][j] = 0;
        }
    }

    grafo.vertices = malloc(numCelas * sizeof(Cela));

    for (int i = 0; i < numCelas; i++) /* Inicializa o vetor de vertices com cada atributos*/
    {
        scanf("%s           %d %d %d %d %d %d", nome, &forca, &destreza, &constituicao, &inteligencia, &sabedoria, &carisma);
        grafo.vertices[i].numIndice = i;
        strcpy(grafo.vertices[i].nome, nome);
        grafo.vertices[i].forca = forca;
        grafo.vertices[i].destreza = destreza;
        grafo.vertices[i].constituicao = constituicao;
        grafo.vertices[i].inteligencia = inteligencia;
        grafo.vertices[i].sabedoria = sabedoria;
        grafo.vertices[i].carisma = carisma;
    }

    scanf("%d", &numJogadores);

    Jogadores *vetorJogadores = malloc(numJogadores * sizeof(Jogadores));

    for (int i = 0; i < numJogadores; i++)
    {
        scanf("\t%s %d %d %d %d %d %d", vetorJogadores[i].nome, &vetorJogadores[i].forca, &vetorJogadores[i].destreza, &vetorJogadores[i].constituicao, &vetorJogadores[i].inteligencia, &vetorJogadores[i].sabedoria, &vetorJogadores[i].carisma);
    }

    adicionaJogadoresCela(&grafo, vetorJogadores, numJogadores);
    verificaArestas(&grafo, vetorJogadores, numJogadores);

    imprimiCelasPossiveis(&grafo, vetorJogadores, numJogadores);

    /* desaloca o que foi alocado anteriormente*/

    for (int i = 0; i < numCelas; i++)
    {
        free(grafo.matrizAdjacencia[i]);
    }

    free(grafo.matrizAdjacencia);
    free(grafo.vertices);
    free(vetorJogadores);
}