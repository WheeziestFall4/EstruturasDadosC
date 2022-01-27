/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   Descricao: Programa pede uma serie de bases de DNA, uma serie de bases de RNA e apos le um 
   tamanho de uma sequencia de DNA digitada pelo usuario. Apos a leitura, o programa deve apresentar
   essa sequencia de DNA totalmente transcrita, a propria sequencia de DNA e a qtd de vezes em que
   cada base apareceu ao longo da sequencia.
   - Entrada: sequencia de DNA, sequencia de RNA, tamanho de um sequencia de DNA e a sequencia de DNA
   a ser transcrita.
   - Saida: id com qtd de cada base na sequencia, a sequencia de DNA e a sequencia de RNA (DNA transcrito)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 26

typedef struct transcricao 
{
    char DNA[TAM];
    char RNA[TAM];
    char *DNAusuario;
    char *resultado;
    int *IDusuario;

} transcricao;

int main()
{
    transcricao transcrever;
    int tamanhodna = 0, condicao = 0;
    char base1;

    scanf("%s", transcrever.DNA);
    scanf("%s", transcrever.RNA);

    scanf("%d", &tamanhodna);

    transcrever.DNAusuario = malloc((tamanhodna+1) * sizeof(char)); /* Aloca dinamicamente as 3 variaveis que necessitavam */
    transcrever.resultado = malloc(tamanhodna * sizeof(char));      /* do tamanho do DNA desejado*/
    transcrever.IDusuario = malloc(tamanhodna * sizeof(int));

    if ((transcrever.DNAusuario == NULL) || (transcrever.resultado == NULL) || (transcrever.IDusuario == NULL))
    { /* Verifica se a alocacao dos 3 funcionou*/
        exit(1);
    }

    scanf("%s", transcrever.DNAusuario);

    for(int i = 0; i < tamanhodna; i++)
    {
        transcrever.IDusuario[i] = 0;
    }

    for (int x = 0; x < tamanhodna; x++)
    {
        base1 = transcrever.DNAusuario[x]; /* A base a ser comparada recebe do DNA digitado pelo usuario*/
        condicao = 0; /* Condicao apos cada comparacao de base volta a ser 0 para poder ser reutilizada*/

        for (int y = 0; y < tamanhodna; y++) /* Percorre novamente as bases de DNA mas comparando com a base armazenada*/
        {                                   /* Se a base de y foi igual a de x, significa que houve repeticao de base*/
            if ((transcrever.DNAusuario[y] == base1) && (x != y) && (condicao == 0) && (transcrever.IDusuario[x] == 0))
            {                               /* Nesse if, deve ser testado quando eh a primeira vez que a base esta aparecendo na sequencia*/
                transcrever.IDusuario[x] = 0;
                transcrever.IDusuario[y] = 1;
                condicao += 2; /* Incrementa condicao significando que a base em questao ja existe na sequencia*/
            }
            else if ((transcrever.DNAusuario[y] == base1) && (x != y) && (transcrever.IDusuario[x] == 0))
            {                   /* Se a base for igual e ela ja foi vista na sequencia, apenas atribui a ela o valor da condicao e incrementa ele apos*/
                transcrever.IDusuario[y] = condicao;
                condicao += 1;
            }
        }
    }

    for (int x = 0; x < strlen(transcrever.DNA); x++)
    {
        for (int y = 0; y < tamanhodna; y++)
        {/* Se a base do DNA digitada pelo usuario for igual a sequencia de DNA de transcricao que ele digitou, entao passa*/
            if (transcrever.DNAusuario[y] == transcrever.DNA[x])
            {
                transcrever.resultado[y] = transcrever.RNA[x]; /* Nesse caso, o resultado recebe a base de RNA (transcrita do DNA)*/
            }                                                   /* que possui a mesma posicao do DNA*/
        }
    }

    /* Sequencia de for para printar de acordo com o exigido */
    printf("\nID:\t\t");

    for (int x = 0; x < tamanhodna; x++)
    {
        printf("%d\t", transcrever.IDusuario[x]);
    }

    printf("\nDNA:\t");

    for (int x = 0; x < tamanhodna; x++)
    {
        printf("%c\t", transcrever.DNAusuario[x]);
    }

    printf("\n\t\t");

    for (int x = 0; x < tamanhodna; x++)
    {
        printf("|\t");
    }

    printf("\nRNA:\t");

    for (int x = 0; x < tamanhodna; x++)
    {
        printf("%c\t", transcrever.resultado[x]);
    }

    printf("\n");

    /* Libera alocacao das 3 variaveis alocadas anteriormente */
    free(transcrever.DNAusuario);
    free(transcrever.resultado);
    free(transcrever.IDusuario);
}