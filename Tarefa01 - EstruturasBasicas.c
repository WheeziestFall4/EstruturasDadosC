/* NOME: VINICIUS RODRIGUES DA COSTA ALMEIRA RA:254843
   TAREFA01
   DESCRICAO: Programa pede qtd de numeros de uma lista, qtd de mudança que havera entre esses numeros
   e qual tipo de mudanca dado: 1 a b (Mudanca de ordem inversa b a) e
   2 a b (Numeros a b ficam pertos e sao invertidos) */

#include <stdio.h>

void opcao1(int n[], int tamanho, int posicaoa, int posicaob) /* Opcao que inverte a ordem dos numeros entre a e b*/
{
    int y = 0;

    if (posicaob >= posicaoa)
    {
        int novotamanho = posicaob - posicaoa, novo[10000];

        for (int x = posicaoa; x <= posicaob; x++)
        {
            novo[y] = n[x];
            y++;
        }

        y = novotamanho;

        for (int x = posicaoa; x <= posicaob; x++)
        {
            n[x] = novo[y];
            y--;
        }
    }
    else /* Caso a for maior que b, significa que deve ser invertida ao contrario*/
    {
        int novotamanho = posicaoa - posicaob, novo[10000];
        y = 0;

        for (int x = posicaob; x >= posicaoa; x--)
        {
            novo[y] = n[x];
            y++;
        }

        y = novotamanho;

        for (int x = posicaob; x >= posicaoa; x--)
        {
            n[x] = novo[y];
            y--;
        }
    }
}

void opcao2(int n[], int tamanho, int posicaoa, int posicaob) /*Opcao que coloca dois numeros pertos e inverte eles*/
{
    int novonum = n[posicaoa];

    for (int x = posicaoa; x <= posicaob; x++)
    {
        if (x != posicaob)
        {
            n[x] = n[x + 1];
        }
        else
        {
            n[x] = n[posicaob];
            n[posicaob] = novonum;
        }
    }
}

int buscaposicao(int n[], int tamanho, int valor) /*Busca posicao de um valor na lista*/
{
    for (int x = 0; x < tamanho; x++)
    {
        if (n[x] == valor)
        {
            return x;
        }
    }

    return 0;
}

int main()
{
    int n[10000], m, opcao, tamanho, x, y = 0, a, b, posicaoa, posicaob;

    scanf("%d", &tamanho);
    scanf("%d", &m);

    for (x = 0; x < tamanho; x++)
    {
        n[x] = x + 1;
    }

    while (y < m) /*Enquanto a qtd de movimentos m digitada antes nao for realizada, continue pedindo qual opcao*/
    {
        scanf("%d %d %d", &opcao, &a, &b);

        posicaoa = buscaposicao(n, tamanho, a);
        posicaob = buscaposicao(n, tamanho, b);

        if (opcao == 1)
        {
            opcao1(n, tamanho, posicaoa, posicaob);
        }
        else
        {
            opcao2(n, tamanho, posicaoa, posicaob);
        }

        y++;
    }

    for (x = 0; x < tamanho; x++)
    {
        printf("%d ", n[x]);
    }

    return 0;
}