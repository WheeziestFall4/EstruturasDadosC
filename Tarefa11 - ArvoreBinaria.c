/* NOME: Vinicius Rodrigues da Costa Almeida RA: 254843
   TAREFA 11
   DESCRICAO: A tarefa simula o esquema de Piramide (golpe) no qual os participantes investem dinheiro
   em conjunto formando uma piramide de lucros e pagamentos. Essa piramide eh guardada em uma arvore binaria.
   A raiz eh o topo e os outros participantes sao as folhas.
   ENTRADA: primeira linha - topo Nomedoparticipante investimento
            outras linhas - NomedoParticipante recruta NovoParticipante investimento
   SAIDA:   mostra os niveis da piramide de acordo com a adicao de um novo participante e de
            acordo com a distribuicao de juros e lucros.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noArvore /*Nos que compoe a arvore binaria*/
{
    char nome[20];
    double valorInvest;
    int nivel;
    struct noArvore *dir;
    struct noArvore *esq;
    struct noArvore *pai;
} NoArvore;

typedef struct noFila   /*Nos que compoe uma fila para impressao por niveis da arvore*/
{                           
    NoArvore *no;
    struct noFila *prox;
} NoFila;

typedef struct fila     /* Guarda as informacoes da fila*/
{
    NoFila *inicio;     /* inicio da fila = fim da lista ligada*/
    NoFila *fim;        /* Fim da fila = inicio da lista ligada*/
} Fila;

typedef struct arvore
{
    NoArvore *raiz;
} Arvore;

NoArvore *criaNo(char nome[], double valor, int nivel)
{
    NoArvore *novo = malloc(sizeof(NoArvore));
    strcpy(novo->nome, nome);
    novo->valorInvest = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->nivel = nivel;

    return novo;
}

void acertoRenumeracao(NoArvore *noDireita) /*Apos completar dois ramos de participante no no, faz */
{                                       /* a distribuicao de lucro para os nos-pai e de juros para os nos-filho*/
    double desconto = 0.06;
    double valor = 0, montante1 = 0, montante2 = 0;
    NoArvore *novoPai = noDireita->pai; /*Guarda o pai dos dois ramos filhos*/
    NoArvore *anterior;

    montante1 = novoPai->dir->valorInvest;
    montante2 = novoPai->esq->valorInvest;
    novoPai->dir->valorInvest = montante1 * (1 - desconto); /* atualiza o valor de investimento dos nos-filho*/
    novoPai->esq->valorInvest = montante2 * (1 - desconto); /* subtraindo os juros para o no-pai*/

    valor = (montante1 + montante2) * desconto;         /*recalcula o valor investimento adicionando*/
    novoPai->valorInvest = novoPai->valorInvest + valor; /* os juros dos nos-filho para o pai*/

    anterior = novoPai;
    novoPai = novoPai->pai;

    while (novoPai != NULL) /* Se o pai for nulo, significa que chegou na raiz*/
    {
        valor = 0;
        desconto = desconto - 0.01; /* Cada novo nivel, subtrai 1%*/

        valor = anterior->valorInvest * desconto;                       /* atualiza o valor investimento do no-filho*/
        anterior->valorInvest = anterior->valorInvest * (1 - desconto); /* subtraindo a porcentagem do investimento*/

        novoPai->valorInvest = novoPai->valorInvest + valor; /* adiciona a porcentagem tirada no no-filho para o investimento*/
                                                                /* do pai*/
        anterior = novoPai;
        novoPai = novoPai->pai; /*atualiza o anterior, o pai passa ser filho*/
    }
}

void adicionaNoArvore(NoArvore *recrutador, NoArvore *novo, NoArvore *raiz, int nivel)
{
    double valorDescontado = novo->valorInvest * 0.1;

    if (recrutador != NULL)
    {
        if (recrutador->esq == NULL) /*Se o recrutador tiver o no-filho esquerdo vazio, entao adiciona o no*/
        {
            nivel = recrutador->nivel + 1;
            novo->nivel = nivel;

            novo->valorInvest = novo->valorInvest + valorDescontado;
            recrutador->valorInvest = recrutador->valorInvest - valorDescontado;

            novo->pai = recrutador;
            recrutador->esq = novo;
        }
        else /*Se o recrutador tiver o no-filho esquerdo nao vazio, entao adiciona o no no espaco da direita*/
        {
            nivel = recrutador->nivel + 1;
            novo->nivel = nivel;

            novo->valorInvest = novo->valorInvest + valorDescontado;
            recrutador->valorInvest = recrutador->valorInvest - valorDescontado;

            novo->pai = recrutador;
            recrutador->dir = novo;

            acertoRenumeracao(novo); /*Faz o acerto de lucros e juros apos completar os dois espacos nos-filho*/
        }
    }
}

NoArvore *procuraNoArvore(NoArvore *atual, char nomeRecrutador[], NoArvore *novo) /* Procura o nome de um recrutador na arvore*/
{
    if (atual == NULL || strcmp(atual->nome, nomeRecrutador) == 0)
    {
        return atual; 
    }
    else
    {
        NoArvore *no = procuraNoArvore(atual->esq, nomeRecrutador, novo);

        if (no != NULL)
        {
            return no;
        }

        no = procuraNoArvore(atual->dir, nomeRecrutador, novo);

        if (no != NULL)
        {
            return no;
        }

        return NULL;
    }
}

void enfileirar(Fila *fila, NoArvore *novo) /* Enfileira os Nos numa fila para imprimir em niveis*/
{
    NoFila *noFila = malloc(sizeof(NoFila));
    noFila->no = novo;

    if (fila->inicio == NULL) /* Se a fila tiver vazia*/
    {
        fila->inicio = noFila;
        fila->fim = noFila;
        noFila->prox = NULL;
    }
    else        /* Se a fila nao tiver vazia, coloca o novo NO no fim*/
    {
        fila->fim->prox = noFila;
        fila->fim = noFila;
        fila->fim->prox = NULL;
    }
}

NoArvore *desenfileirar(Fila *fila) /* Desenfileira a fila*/
{
    NoFila *primeiro = fila->inicio;
    NoArvore *conteudo = fila->inicio->no;

    fila->inicio = fila->inicio->prox; /* Atualiza o inicio da lista, agora sera o prox da lista que estava antes*/
                                        /* = retira um no do fim da fila*/
    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    free(primeiro); 

    return conteudo;
}

void imprimi_em_largura(NoArvore *raiz) /* Imprimi em niveis da arvore binaria*/
{
    Fila f;
    int nivel = 0;

    NoArvore *no;

    f.inicio = NULL;
    f.fim = NULL;

    enfileirar(&f, raiz); /*enfileira primeiro a raiz*/

    while (f.inicio != NULL) /* enquanto a fila nao tiver vazia, continua */
    {
        no = desenfileirar(&f); /* desenfileira para poder imprimir*/
                                /* atualiza o no para adicionar os filhos da fila*/
        if (no != NULL)
        {
            enfileirar(&f, no->esq); /* enfileira os dois filhos do no atual*/
            enfileirar(&f, no->dir);

            if (no->nivel != nivel) /* Se mudar de nivel, entao pula linha e escreve o nivel novo*/
            {
                printf("\nNivel %d:", no->nivel);
                printf(" [%s %.2lf]", no->nome, no->valorInvest);
                nivel = no->nivel;
            }
            else
            {
                printf(" [%s %.2lf]", no->nome, no->valorInvest);
            }
        }
    }
}

void liberar_arvore(NoArvore *raiz) /*Desaloca os nos das arvores partindo das folhas para a raiz*/
{
  if(raiz != NULL)
  {
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
  }
}

int main()
{
    char tipo[20], nome[20], nomeRecrutador[20], acao[20];
    double valor = 0;
    int nivel = 0;

    Arvore arvore;
    arvore.raiz = NULL;

    scanf("%s %s %lf", tipo, nome, &valor);

    if (strcmp(tipo, "Topo") == 0)
    {
        arvore.raiz = criaNo(nome, valor, 1);

        printf("Nivel %d: [%s %.2lf]", arvore.raiz->nivel, arvore.raiz->nome, arvore.raiz->valorInvest);
    }

    while (scanf("%s %s %s %lf", nomeRecrutador, acao, nome, &valor) != EOF)
    {
        NoArvore *novo = criaNo(nome, valor, nivel);
        NoArvore *recrutador = procuraNoArvore(arvore.raiz, nomeRecrutador, novo);

        adicionaNoArvore(recrutador, novo, arvore.raiz, 0); /* Procura o recrutador e adiciona o novo no num dos espacos nos-filhos (esq ou dir)*/

        printf("\n");
        imprimi_em_largura(arvore.raiz); /* Imprimi os niveis existentes com os participantes*/
    }

    liberar_arvore(arvore.raiz); 
}
