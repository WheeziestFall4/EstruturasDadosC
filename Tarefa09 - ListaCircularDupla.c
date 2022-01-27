/* Nome: Vinicius Rodrigues da Costa Almeida        RA: 254843 
   DESCRICAO: Programa recebe quantidade de alturas, as alturas e separa eles em duas equipes utilizando
   estrutura de lista circular dupla. A separacao eh feita por jogada de dados
   ENTRADA: qtddealturas, alturas (na mesma linha e separado por espaco), cada jogada do dado de acordo com a qtddealturas
   SAIDA: Duas listas de alturas das equipes criadas pelo sorteio
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int altura;
    struct no *proximono;
    struct no *anteriorno;
} No;

typedef struct equipe /* Armazena o primeiro no de cada equipe, alem do tamanho dela*/
{
    int tamanhoequipe;
    No *inicio;
} Equipe;

void imprimiequipe(Equipe *equipe)
{
    No *atual = equipe->inicio;

    if (atual != NULL)
    {
        do
        {
            printf("%d ", atual->altura);
            atual = atual->proximono;

        } while (atual != equipe->inicio); /* Enquanto nao chegar no ultimo elemento que aponta novamente*/
    }                                   /* para o inicio da lista circular, entao continua printando*/
}

void inserirproximo(Equipe *equipe, int altura) /* Inserir o proximo na equipe*/
{
    No *novo = malloc(sizeof(No));
    novo->altura = altura;

    if (equipe->inicio == NULL) /* Se a equipe ainda tiver vazia*/
    {
        novo->anteriorno = novo;
        novo->proximono = novo;
        equipe->inicio = novo;
        equipe->tamanhoequipe++;
    }
    else
    {
        No *atual = equipe->inicio;

        while (atual->proximono != equipe->inicio) /* Procura o ultimo elemento da lista*/
        {
            atual = atual->proximono;
        }

        atual->proximono = novo;
        novo->anteriorno = atual;
        novo->proximono = equipe->inicio;
        equipe->inicio->anteriorno = novo;
        equipe->tamanhoequipe++;
    }
}

void colocaemordemcrescente(Equipe *equipe)
{
    No *no1, *no2, *aux;
    int menor = 0;

    no1 = equipe->inicio;
    no2 = equipe->inicio->proximono;

    do
    {
        do
        {
            if (no1->altura < no2->altura) /* Compara a altura dos dois nos em questao*/
            {                               /* Se for maior, troca somente a altura deles de posicao*/
                menor = no2->altura;
                aux = no2;
                aux->altura = no1->altura;
                no1->altura = menor;
            }

            no2 = no2->proximono;

        } while (no2 != equipe->inicio);

        no1 = no1->proximono;

    } while (no1 != equipe->inicio);
}

void removerdaequipe(Equipe *equipe, No *no) /* Remove o elemento no da equipe principal*/
{
    No *auxprox, *auxanterior;
 
    if (equipe->tamanhoequipe == 1) /* Se o tamanho for 1, entao deve desalocar o no e reiniciar o inicio da lista*/
    {
        equipe->inicio = NULL;
        free(no);   
    }
    else                          
    {                               /* Liga o anterior do no ao proximo do no e desaloca o no */
        auxprox = no->proximono;        
        auxanterior = no->anteriorno;
        no->anteriorno->proximono = auxprox;
        no->proximono->anteriorno = auxanterior;
        free(no);
    }
    
    equipe->tamanhoequipe--;
}

void separaequipes(Equipe *equipegeral, Equipe *equipe, int numerodado, char sentido[])
{                               /* Faz separacao das equipe de acordo com o sentido dado */
    No *atual = equipegeral->inicio;

    if (numerodado / equipegeral->tamanhoequipe > 1) /* Se o numrodado por maior que n, entao quer dizer que deu a volta*/
    {
        numerodado = numerodado - equipegeral->tamanhoequipe;
    }

    numerodado = numerodado - 1; /* Sempre anda 1 a menos*/

    if (atual != NULL)
    {
        if (strcmp("esquerda", sentido) == 0)
        {
            int i = 0;

            while (i != numerodado)
            {
                atual = atual->anteriorno;
                i++;
            }
        }
        else
        {
            int i = 0;

            while (i != numerodado)
            {
                atual = atual->proximono;
                i++;
            }
        }

        if (atual == equipegeral->inicio) /* Se o atual for o proprio inicio da lista*/
        {                           /* entao deve atualizar o lista inicio para o proximo da frente*/
            equipegeral->inicio = equipegeral->inicio->proximono;
        }

        inserirproximo(equipe, atual->altura); 
        removerdaequipe(equipegeral, atual);
    }
}

void desaloca(No *no, Equipe *equipe)
{
    No *inicio = equipe->inicio;

    if (no->proximono == inicio) /* Caso basico: quando o no eh o ultimo da lista antes de*/
    {                           /* retornar para o inicio novamente*/
        free(no);
    }
    else
    {
        desaloca(no->proximono, equipe);
        free(no);
    }
}

int main()
{
    int numalturas = 0, alturaatual = 0;
    int numerodado = 0;
    Equipe equipegeral;
    equipegeral.inicio = NULL;
    equipegeral.tamanhoequipe = 0;

    Equipe equipe1, equipe2;
    equipe1.inicio = NULL;
    equipe2.inicio = NULL;
    equipe1.tamanhoequipe = 0;
    equipe2.tamanhoequipe = 0;

    scanf("%d", &numalturas);

    int i = 0;

    while (i < numalturas) /* Inseri na equipe geral*/
    {
        scanf("\t%d", &alturaatual);
        inserirproximo(&equipegeral, alturaatual);
        alturaatual = 0;
        i++;
    }

    printf("\n");

    i = 0;

    while (i < numalturas)  /* Recebe as rodadas e faz a separacao das equipes*/
    {
        scanf("\t%d", &numerodado);

        if (i % 2 == 0)
        {
            separaequipes(&equipegeral, &equipe1, numerodado, "esquerda");
        }
        else
        {
            separaequipes(&equipegeral, &equipe2, numerodado, "direita");
        }

        i++;
    }

    colocaemordemcrescente(&equipe1);
    colocaemordemcrescente(&equipe2);

    printf("\n");
    imprimiequipe(&equipe1);
    printf("\n");
    imprimiequipe(&equipe2);

    desaloca(equipe1.inicio, &equipe1);
    desaloca(equipe2.inicio, &equipe2);
}