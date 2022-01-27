/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   LAB 07
   DESCRICAO: Jogo do arranha ceus no qual o jogador deve colocar o tam n de uma matriz e as possiveis
   dicas ao redor dessa matriz de maneira que não haja numeros repetidos tanto em fileiras ou colunas.
   As dicas devem ser numeros de arranha ceus que podem ser vistos de determinado lado.
   ENTRADA: Tamanho n da matriz, matriz n+2*n+2 que possue as dicas laterais e matriz central nula.
   SAIDA: Somente matriz central com a unica disposicao de arranha ceus disponivel.*/


#include <stdio.h>
#include <stdlib.h>

int verificalinhas(int **matriz, int tamreal, int linha, int coluna) /* Verifica se as dicas dadas nas linhas*/
{                                                       /* corresponde a linha ocupado em questao*/
    int maiortorre = 0, qtdesquerda = 0, qtddireita = 0;

    if (coluna / (tamreal - 2) == 1) /* Se nao for a ultima coluna, entao ainda nao eh necessario testar*/
    {
        for (int i = 1; i < tamreal - 1; i++)
        {
            if (matriz[linha][i] > maiortorre) /* Se a posicao atual for maior do que a maior torre salva*/
            {                                   /* logo, ela eh a mais alta e pode ser vista mais pela esquerda*/
                maiortorre = matriz[linha][i];
                qtdesquerda++;
            }

            if (qtdesquerda > matriz[linha][0])
            {
                matriz[linha][coluna] = 0;
                return 0;
            }
        }

        maiortorre = 0;

        for (int i = tamreal - 2; i >= 1; i--) /* Percorre agora olhando da direita pra esquerda*/
        {
            if (matriz[linha][i] > maiortorre)
            {
                maiortorre = matriz[linha][i];
                qtddireita++;
            }

            if (qtddireita > matriz[linha][tamreal - 1])
            {
                matriz[linha][coluna] = 0;
                return 0;
            }
        }

        if (qtdesquerda != matriz[linha][0]) /* Se no final, a qtddeesquerda nao for igual a da dica*/
        {                                     /* da esquerda, entao esta incorreta a linha em questao*/
            matriz[linha][coluna] = 0;
            return 0;
        }

        if (qtddireita != matriz[linha][tamreal - 1]) /* O mesmo vale para dica da direita*/
        {
            matriz[linha][coluna] = 0;
            return 0;
        }
    }

    return 1;
}

int verificacolunas(int **matriz, int tamreal, int linha, int coluna)/* Verifica se as dicas dadas nas linhas*/
{                                                       /* corresponda a coluna ocupada em questao*/
    int maiortorre = 0, qtdcima = 0, qtdbaixo = 0;

    for (int i = 1; i < tamreal - 1; i++)
    {
        if (matriz[i][coluna] > maiortorre)
        {
            maiortorre = matriz[i][coluna];
            qtdcima++;
        }

        if (qtdcima > matriz[0][coluna])
        {
            matriz[linha][coluna] = 0;
            return 0;
        }
    }

    maiortorre = 0;

    for (int i = tamreal - 2; i >= 1; i--)
    {
        if (matriz[i][coluna] > maiortorre)
        {
            maiortorre = matriz[i][coluna];
            qtdbaixo++;
        }

        if (qtdbaixo > matriz[tamreal - 1][coluna])
        {
            matriz[linha][coluna] = 0;
            return 0;
        }
    }

    if (qtdcima != matriz[0][coluna])
    {
        matriz[linha][coluna] = 0;
        return 0;
    }

    if (qtdbaixo != matriz[tamreal - 1][coluna])
    {
        matriz[linha][coluna] = 0;
        return 0;
    }

    return 1;
}

int disposicao_valida(int **matriz, int tamreal, int linha, int coluna) /* Verifica se ha valores repetidos nas linhas*/
{                                                   /* e colunas ja ocupadas*/
    for (int i = coluna; i >= 1; i--)
    {
        if ((matriz[linha][i] == matriz[linha][coluna]) && (i != coluna))
        {
            matriz[linha][coluna] = 0;
            return 0;
        }
    }

    for (int i = linha; i >= 1; i--)
    {
        if ((matriz[i][coluna] == matriz[linha][coluna]) && (i != linha))
        {
            matriz[linha][coluna] = 0;
            return 0;
        }
    }

    return 1;
}

int preenche_matriz(int **matriz, int tamreal, int linha, int coluna) /* Funcao Recursiva que faz o backtracking */
{                                                       /* para os valores da matriz*/
    int valido = 0, i = 0, valor = 0;

    if ((linha == tamreal - 2) && (coluna == tamreal - 2)) /* Caso base: quando a posicao da matriz esta na ultima posicao da matriz central*/
    {
        i = 1;

        while ((valido != 1) && (i <= tamreal - 2)) /* Enquanto nao retornar que o valor colocado na ultima posicao*/
        {                                   /* eh valido, entao continue ate chegar em n*/
            matriz[linha][coluna] = i;

            valido = disposicao_valida(matriz, tamreal, linha, coluna);

            i++;
        }

        if (valido == 0) /* Se no final, valido for igual a 0, significa que nao achou numero para a ultima posi*/
        {
            return 0;
        }
        else /* Se achar, retorna 1*/
        {
            return 1;
        }
    }
    else /* Se nao for o caso base*/
    {
        i = 1;

        while (i <= tamreal - 2) /* Dispoe possiveis valores de 1 a n em cada posicao e depois verifica */
        {                        /* se eh possivel esses valores são possiveis*/
            matriz[linha][coluna] = i;      

            valido = disposicao_valida(matriz, tamreal, linha, coluna);

            if (valido == 1)
            {
                if (verificalinhas(matriz, tamreal, linha, coluna) == 0)
                {
                    return 0;
                }

                if (linha ==  tamreal - 2) /* Quando comecar a ocupar a ultima linha pode comecar a testar colunas*/
                {
                    if (verificacolunas(matriz, tamreal, linha, coluna) == 0)
                    {
                        return 0;
                    }
                }

                if (coluna < tamreal - 2) /* Se nao for a ultima coluna ainda, entao continue incrementando coluna*/
                {
                    valor = preenche_matriz(matriz, tamreal, linha, coluna + 1);
                }
                else /* Se chegar na ultima posicao de coluna, entao deve incrementar linha*/
                {
                    valor = preenche_matriz(matriz, tamreal, linha + 1, 1);
                }

                if (valor == 1) 
                {
                    return 1;
                }
            }

            valido = 0;
            i++;
        }

        matriz[linha][coluna] = 0; /* Se nao encontrou nenhuma valor para a posicao atual, entao deve retorna*/
        return 0;                   /* para a anterior e zerar novamente a posicao atual*/
    }
}

int main()
{
    int tam = 0, valor = 0;
    int **matriz;

    scanf("%d", &tam);

    tam = tam + 2; /* Logo, a matriz real sera a matriz central mais as laterais*/

    matriz = malloc(tam * sizeof(int *));

    for (int i = 0; i < tam; i++)
    {
        matriz[i] = malloc(tam * sizeof(int));
    }

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }

    valor = preenche_matriz(matriz, tam, 1, 1);

    if (valor == 1) /* Se valor eh igual a 1, entao a recursao foi ate o final*/
    {
        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                if ((i != 0) && (j != 0) && (i != tam - 1) && (j != tam - 1))
                    printf("%d ", matriz[i][j]);
            }

            printf("\n");
        }
    }

    /* Desalocando matriz*/
    for (int i = 0; i < tam; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}