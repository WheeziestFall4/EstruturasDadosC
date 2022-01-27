/* NOME: Vinicius Rodrigues da Costa Almeida    RA: 254843
   DESCRICAO: Programa simula um roteador e o trafego que recebe uma serie de pacotes identificado por id, 
   prioridade e incremento. Apos a adicao dos pacotes, o 0 0 0 indica que o roteador desocupou uma qtd x de 
   pacotes de acordo com a prioridade. 
   ENTRADA: qtd maxima de pacotes que pode esvazir por tick, qtd maxima de pacotes guardados pelo roteador,
   cada pacote com id, prioridade e incremento, 0 0 0 - sinaliza o tick para esvaziar a fila.
   SAIDA: imprimi cada tick ou seja, todos os pacotes que foram esvaziados por ordem de prioridade*/

#include <stdio.h>
#include <stdlib.h>

#define F_ESQ(i) (2 * i + 1) /*Guarda a relacao que os vetores tem entre si*/
#define F_DIR(i) (2 * i + 2) /* de acordo com o MAXHEAP*/
#define PAI(i) ((i - 1) / 2)

typedef struct pacote
{
    int id;
    int prioridade;
    int incremento;
} Pacote;

typedef struct filaPrioridade /* Guarda a fila de prioridade com o vetor MAXHEAP*/
{
    Pacote *v;
    int n, tamanhoFila;
} FilaPrioridade;

FilaPrioridade *criarFilaPrioridades(int tamanho)
{
    FilaPrioridade *fila = malloc(sizeof(FilaPrioridade));

    fila->tamanhoFila = tamanho;
    fila->n = 0; /* marca quantos posicoes dos vetores esta ocupado*/
    fila->v = malloc(tamanho * sizeof(Pacote));

    return fila;
}

void troca(Pacote *objeto1, Pacote *objeto2) /* Troca dois pacotes de lugar*/
{
    Pacote auxiliar = *objeto1;
    *objeto1 = *objeto2;
    *objeto2 = auxiliar;
}

void desceHeap(FilaPrioridade *fila, int indice) /* desce o pacote no vetor de acordo com a prioridade dos filhos*/
{                                                /* No MAXHEAP, todo vetor filho dir e esq possue prioridade menor que o pai*/
    int maiorFilho;

    if (F_ESQ(indice) < fila->n)
    {
        maiorFilho = F_ESQ(indice);

        if (F_DIR(indice) < fila->n && fila->v[F_ESQ(indice)].prioridade < fila->v[F_DIR(indice)].prioridade)
        {
            maiorFilho = F_DIR(indice);
        }
        if (fila->v[indice].prioridade < fila->v[maiorFilho].prioridade)
        {
            troca(&fila->v[indice], &fila->v[maiorFilho]);
            desceHeap(fila, maiorFilho);
        }
    }
}

/* Sobe o elemento do indice indice ate a posicao correta de acordo com a prioridade*/
void sobeHeap(FilaPrioridade *fila, int indice)
{
    if (indice > 0 && fila->v[PAI(indice)].prioridade < fila->v[indice].prioridade)
    {
        troca(&fila->v[indice], &fila->v[PAI(indice)]);
        sobeHeap(fila, PAI(indice));
    }
}

/* Inserir o pacote e sobe ele no HEAP de acordo com a prioridade*/
void inserirPacote(FilaPrioridade *fila, Pacote pacote, int tamanhoMaximoPermitido)
{
    if (fila->n < tamanhoMaximoPermitido) /* Se n for igual a tamanho maximo permitido, entao roteador esta*/
    {                                     /* com a fila cheia e nao pode receber mais pacotes*/
        fila->v[fila->n] = pacote;
        fila->n++;

        sobeHeap(fila, fila->n - 1);
    }
}

void EsvaziaFila(FilaPrioridade *fila, int tamanhoFila, int tick)
{
    printf("\n\nTICK %d", tick);

    for (int i = 0; i < tamanhoFila; i++)
    {
        if (fila->n > 0) /* Se houve pelo menos um pacote*/
        {
            Pacote pacote = fila->v[0];

            fila->v[0].prioridade = 0; /* Zera todas as caracteristicas do pacote*/
            fila->v[0].id = 0;
            fila->v[0].incremento = 0;

            troca(&fila->v[0], &fila->v[fila->n - 1]); /* Troca de lugar o primeiro com o ultimo*/
            fila->n--;
            desceHeap(fila, 0); /* desce no HEAP no v[0] para ocupar a correta posicao*/

            printf("\n%d   %d   %d", pacote.id, pacote.prioridade, pacote.incremento);
        }
    }
}

void mudaPrioridade(FilaPrioridade *fila) /* Incrementa as propriedades de cada pacote e ordena o MAXHEAP*/
{
    if (fila->n > 0)
    {

        for (int i = fila->n - 1; i >= 0; i--)
        {
            fila->v[i].prioridade = fila->v[i].prioridade + fila->v[i].incremento;
        }

        for (int i = fila->n - 1; i >= 0; i--) /* Percorre do fim do MAXHEAP ate o inicio e sobe aqueles*/
        {                                       /* que estavam no lugar errado apos o incremento*/
            sobeHeap(fila, i);
        }
    }
}

int main()
{
    int qtdPacotesEnviados = 0, qtdMaxPacotes = 0;
    FilaPrioridade *fila;

    int id = 0, prioridade = 0, incremento = 0, tick = 1;

    scanf("%d %d", &qtdPacotesEnviados, &qtdMaxPacotes);

    fila = criarFilaPrioridades(qtdMaxPacotes);

    while (scanf("%d %d %d", &id, &prioridade, &incremento) != EOF)
    {
        if (id >= 0)
        {
            if (id == 0 && prioridade == 0 && incremento == 0) /* Se for 0 0 0, entao eh TICK*/
            {
                EsvaziaFila(fila, qtdPacotesEnviados, tick);
                mudaPrioridade(fila);

                tick++;
            }
            else if (id != 0)
            {
                Pacote pacote = {id, prioridade, incremento};
                inserirPacote(fila, pacote, qtdMaxPacotes);
            }
        }
    }

    free(fila->v);
    free(fila);
}
