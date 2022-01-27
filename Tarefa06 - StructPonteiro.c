/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   Descricao: Programa cria um mundo do minecraft atraves do numero de x(largura) e z(profundidade).
   Alem disso, com o numero de seeds o programa calcula o numero de blocos vazios e de outros tipos nesse
   mundo.
   Entrada: largura(x), profundidade(z), seed, tempo de mineracao para cada bloco.
   Saida: retorna o numero total de blocos no mundo, o tempo total usada para minerar e a qtd de diamante, ouro e ferro. */

#include "minecraft.h"
#include <stdio.h>
#include <stdlib.h>

int **calcularAltitudes(int tamanhox, int tamanhoz, int seed) /* Aloca dinamicamente uma matriz de altitudes*/
{                                                             /* e calcula a altitude de cada parte*/
    int **matrizaltitude;

    matrizaltitude = malloc(tamanhox * sizeof(int *));

    for (int i = 0; i < tamanhox; i++)
    {
        matrizaltitude[i] = malloc(tamanhoz * sizeof(int));
    }

    for (int i = 0; i < tamanhox; i++) /* Conta especifica para calcular a altitude em cada coordenada*/
    {
        for (int j = 0; j < tamanhoz; j++)
        {
            matrizaltitude[i][j] = (((seed * (202 + i + j)) + 12345 + i + j) % 256); /* Armazena a altura real de cada coordenada*/
        }
    }

    return matrizaltitude;
}

void defineqtdblocos(Bloco *bloco, int contatipominerio) /* Define qual tipo de bloco dependendo da altitude y*/
{
    if (contatipominerio == 0)
    { /* Para que seja bloco de diamente*/
        bloco->blocoDiamante = 1;
        bloco->blocoDisponivel = 1;
    }
    else if ((contatipominerio == 1) || (contatipominerio == 2))
    { /* Para que seja bloco de ouro*/
        bloco->blocoOuro = 1;
        bloco->blocoDisponivel = 1;
    }
    else if ((contatipominerio == 3) || (contatipominerio == 4) || (contatipominerio == 5))
    { /* Para que seja bloco de ferro*/
        bloco->blocoFerro = 1;
        bloco->blocoDisponivel = 1;
    }
    else if ((contatipominerio >= 6) && (contatipominerio <= 20)) /* Outros tipos de blocos: terra, pedra*/
    {
        bloco->blocoOutros = 1;
        bloco->blocoDisponivel = 1;
    }
}

Bloco ***criarMundo(int tamanhox, int tamanhoz, int **altitudes, int seed) /* Cria matriz de blocos de acordo com as coordenadas x, y e z*/
{
    Bloco ***matrizblocos;
    int contatipominerio = 0;
    int tamanhoy = 256;

    matrizblocos = malloc(tamanhox * sizeof(int **));

    if (matrizblocos == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < tamanhox; i++)
    {
        matrizblocos[i] = malloc(tamanhoz * sizeof(int *));

        if (matrizblocos[i] == NULL)
        {
            exit(1);
        }
    }

    for (int i = 0; i < tamanhox; i++)
    {
        for (int j = 0; j < tamanhoz; j++)
        {
            matrizblocos[i][j] = malloc(tamanhoy * sizeof(Bloco));

            if (matrizblocos[i][j] == NULL)
            {
                exit(1);
            }

            for (int k = 0; k < tamanhoy; k++) /* Percorre y = 0 ate y = 255*/
            {
                matrizblocos[i][j][k].blocoDiamante = 0;
                matrizblocos[i][j][k].blocoOuro = 0;
                matrizblocos[i][j][k].blocoFerro = 0;
                matrizblocos[i][j][k].blocoOutros = 0;
                matrizblocos[i][j][k].blocoDisponivel = 0;

                if (k > altitudes[i][j]) /* Se for maior, contatipominerio nao tera numero valido para algum bloco*/
                {
                    contatipominerio = 21;
                }
                else
                {
                    contatipominerio = (((seed * (202 + i + j + k)) + i + j + k) % 33);
                }

                defineqtdblocos(&matrizblocos[i][j][k], contatipominerio); /* Analise qual tipo de bloco eh apos a conta*/
            }
        }
    }

    return matrizblocos;
}

double explorarMundo(Bloco ***mundo, int tamanhox, int tamanhoz, int **altitudes, double tempoPorBloco,
                     int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos)
{ /* Funcao que retorna a qtdtotaldetempogasto*/
    double tempototal = 0;
    int tamanhoy = 256;

    for (int i = 0; i < tamanhox; i++)
    {
        for (int j = 0; j < tamanhoz; j++)
        {
            for (int k = 0; k < tamanhoy; k++) /* Somatoria de todos os blocos, blocos de diamante, ouro e ferro*/
            {
                *qtdDiamante += mundo[i][j][k].blocoDiamante;
                *qtdOuro += mundo[i][j][k].blocoOuro;
                *qtdFerro += mundo[i][j][k].blocoFerro;
                *qtdBlocos += mundo[i][j][k].blocoDisponivel;
            }
        }
    }

    tempototal = tempoPorBloco * (*qtdBlocos); /* Calcula tempo total de mineracao*/

    return tempototal;
}

int main()
{
    int seed = 0, tamanhox = 0, tamanhoz = 0, **matrizaltitude;
    double tempoPorBloco = 0;
    Bloco ***matrizblocos;
    double tempototal = 0;
    int qtdBlocos = 0, qtdDiamante = 0, qtdOuro = 0, qtdFerro = 0;

    scanf("%d %d", &tamanhox, &tamanhoz);
    scanf("%d", &seed);
    scanf("%lf", &tempoPorBloco);

    matrizaltitude = calcularAltitudes(tamanhox, tamanhoz, seed);

    matrizblocos = criarMundo(tamanhox, tamanhoz, matrizaltitude, seed);

    tempototal = explorarMundo(matrizblocos, tamanhox, tamanhoz, matrizaltitude, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    printf("Total de Blocos: %d", qtdBlocos);
    printf("\nTempo total: %.2lfs", tempototal);
    printf("\nDiamantes: %d", qtdDiamante);
    printf("\nOuros: %d", qtdOuro);
    printf("\nFerros: %d\n", qtdFerro);

    for (int i = 0; i < tamanhox; i++)
    {
        free(matrizaltitude[i]);
    }

    for (int i = 0; i < tamanhox; i++)
    {
        for (int j = 0; j < tamanhoz; j++)
        {
            free(matrizblocos[i][j]);
        }
    }

    for (int i = 0; i < tamanhox; i++)
    {
        free(matrizblocos[i]);
    }

    free(matrizblocos);
    free(matrizaltitude);
}
