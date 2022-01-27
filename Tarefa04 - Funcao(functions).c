#include "planejar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

int registrar(Voo voos[])
{
    int numvoo, dia, mes, ano;
    double valor;
    char origem[30], destino[30];

    scanf("%d", &numvoo);
    scanf("%s %s", origem, destino);
    scanf("%d/%d/%d", &dia, &mes, &ano);
    scanf("%lf", &valor);

    for (int x = 0; x < TAM; x++)
    {
        if (voos[x].numvoo == 0) /* Se o numero de voo for igual a 0, chegou na parte do vetor que nao foi ocupada*/
        {
            voos[x].numvoo = numvoo;
            strcpy(voos[x].origem, origem);
            strcpy(voos[x].destino, destino);
            voos[x].data = ler_data(dia, mes, ano);
            voos[x].valor = valor;

            return x + 1;
        }
    }

    return 0;
}

Data ler_data(int dia, int mes, int ano)
{
    Data data;

    data.dia = dia;
    data.mes = mes;
    data.ano = ano;

    return data;
}

int compara_data(Data datavoo, Data data2)
{
    if (datavoo.ano != data2.ano)
    {
        if (datavoo.ano > data2.ano) /* Se o ano for maior que o outro, entao retorna 1 (a datavoo eh maior)*/
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else /* Mesmo ano*/
    {
        if (datavoo.mes > data2.mes)
        {
            return 1;
        }
        else if (datavoo.mes == data2.mes)
        {
            if (datavoo.dia > data2.dia)
            {
                return 1;
            }
            else if (datavoo.dia == data2.dia) /*Condicao especial que pode ocorrer em comparacoes em que */
            {                                  /* A data de voo eh maior que a data dada ou menor, mas ambos no mesmo mes*/
                return 2;
            }
            else
            {
                return 0;
            }
        }
        else /* Se o mes do voo for menor do que o mes da data dada*/
        {
            return 0;
        }
    }
}

int diferenca_data(Data data1, Data data2)
{
    int diferenca, numerodediasdomes;

    if ((data1.mes == data2.mes) && (data1.ano == data2.ano))
    {
        if (abs(data1.dia - data2.dia) + 1 >= 4) /* Calcula a diferenca entre as datas e adiciona 1 para que possa contar */
        {                                        /* o dia da partida que foi retirado no momento da conta*/
            if (data1.dia > data2.dia)
            {
                return 2; /* Retornar 2 significa que data2 eh a data de voo de partida (menor data)*/
            }
            else
            {
                return 1; /* Retornar 1 significa que data1 eh a data de voo de partida (menor data)*/
            }
        }
        else
        {
            return 0; /* Retorna 0 significa que a diferenca eh baixa e nao pode ser considerada as datas dadas*/
        }
    }
    else if ((data1.mes != data2.mes) && (data1.ano == data2.ano))
    {
        if (data1.mes > data2.mes) /* Se os meses forem diferentes, entao deve se levar em conta a diferenca de dias de cada um*/
        {
            if ((data2.mes == 1) || (data2.mes == 3) || (data2.mes == 5) || (data2.mes == 7) || (data2.mes == 8) || (data2.mes == 10) || (data2.mes == 12))
            {
                numerodediasdomes = 31;
            }
            else if ((data2.mes == 4) || (data2.mes == 6) || (data2.mes == 9) || (data2.mes == 11))
            {
                numerodediasdomes = 30;
            }
            else
            {
                numerodediasdomes = 28;
            }

            diferenca = numerodediasdomes - data2.dia;
            diferenca += data1.dia + 1;

            if (diferenca >= 4)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }
        else /* Quando o mes da data2 eh maior que o mes da data1 */
        {
            if ((data1.mes == 1) || (data1.mes == 3) || (data1.mes == 5) || (data1.mes == 7) || (data1.mes == 8) || (data1.mes == 10) || (data1.mes == 12))
            {
                numerodediasdomes = 31;
            }
            else if ((data1.mes == 4) || (data1.mes == 6) || (data1.mes == 9) || (data1.mes == 11))
            {
                numerodediasdomes = 30;
            }
            else
            {
                numerodediasdomes = 28;
            }

            diferenca = numerodediasdomes - data1.dia;
            diferenca += data2.dia + 1;

            if (diferenca >= 4)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else /* Quando os anos sao diferentes as contas devem ser diferentes*/
    {
        if (data1.mes > data2.mes)
        {
            if ((data2.mes == 1) || (data2.mes == 3) || (data2.mes == 5) || (data2.mes == 7) || (data2.mes == 8) || (data2.mes == 10) || (data2.mes == 12))
            {
                numerodediasdomes = 31;
            }
            else if ((data2.mes == 4) || (data2.mes == 6) || (data2.mes == 9) || (data2.mes == 11))
            {
                numerodediasdomes = 30;
            }
            else
            {
                numerodediasdomes = 28;
            }

            diferenca = numerodediasdomes - data1.dia;
            diferenca += data2.dia + 1;

            if (diferenca >= 4)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else /* Quando o mes da data1 eh menor do que a data2*/
        {
            if ((data2.mes == 1) || (data2.mes == 3) || (data2.mes == 5) || (data2.mes == 7) || (data2.mes == 8) || (data2.mes == 10) || (data2.mes == 12))
            {
                numerodediasdomes = 31;
            }
            else if ((data2.mes == 4) || (data2.mes == 6) || (data2.mes == 9) || (data2.mes == 11))
            {
                numerodediasdomes = 30;
            }
            else
            {
                numerodediasdomes = 28;
            }

            diferenca = numerodediasdomes - data2.dia;
            diferenca += data1.dia + 1;

            if (diferenca >= 4)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }
    }
}

int cancelar(Voo voos[], int qtd_voos, int numero_voo)
{
    int posicaovoo;

    for (int x = 0; x < qtd_voos; x++)
    {
        if (voos[x].numvoo == numero_voo) /* Procura numvoo dado para que ele seja cancelado (ou seja) zerado*/
        {
            voos[x].numvoo = 0;
            strcpy(voos[x].origem, "");
            strcpy(voos[x].destino, "");
            voos[x].data = ler_data(00, 0, 0);
            voos[x].valor = 0;

            posicaovoo = x;
        }
    }

    for (int x = posicaovoo; x < qtd_voos; x++) /* Coloca os voos registrados apos a posicao do voo cancelado*/
    {                                           /* para posicoes mais a frente*/
        voos[x].numvoo = voos[x + 1].numvoo;
        strcpy(voos[x].origem, voos[x + 1].origem);
        strcpy(voos[x].destino, voos[x + 1].destino);
        voos[x].data = ler_data(voos[x + 1].data.dia, voos[x + 1].data.mes, voos[x + 1].data.ano);
        voos[x].valor = voos[x + 1].valor;
    }

    return qtd_voos - 1; /* Retorna a nova qtd_voos sem o voo cancelado*/
}

void alterar(Voo voos[], int qtd_voos, int numero_voo, double novo_valor)
{
    for (int x = 0; x < qtd_voos; x++)
    {
        if (voos[x].numvoo == numero_voo)
        {
            voos[x].valor = novo_valor;
        }
    }
}

int verificaregistro(Voo voosinicio[], Voo voosfim[], Voo valor1, Voo valor2, int qtd_voos)
{
    for (int x = 0; x < qtd_voos; x++) /* Verifica se ja houve registro do par de voos nos vetores de vooinicio e voofim*/
    {
        if (voosinicio[x].numvoo == valor1.numvoo)
        {
            if (voosfim[x].numvoo == valor2.numvoo)
            {
                return 1; /* Se achar, entao retorna 1*/
            }
        }
    }

    return 0; /* Se nao achar, retorna 0*/
}

int verificaaeroporto(char codigovoo[], char codigo_origem[])
{
    if (strcmp(codigovoo, codigo_origem) == 0) /* Verifica se codigo de origem ou destino eh igual ao codigo dado*/
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[])
{
    Voo possiveisvoos[TAM], possiveisvoosinicio[10000], possiveisvoosfim[10000];
    Voo resultadofinalinicio, resultadofinalfim;
    int tamanho = 0, tamanho2 = 0;
    double somax = 0, somatotal = 0;

    for (int x = 0; x < qtd_voos; x++) /* For que analisa se os voos estao entre as datas de inicio e fim de ferias*/
    {
        if (compara_data(voos[x].data, data_inicio) != 0)
        {
            if ((compara_data(voos[x].data, data_fim) == 0) || (compara_data(voos[x].data, data_fim) == 2))
            {
                possiveisvoos[tamanho] = voos[x];
                tamanho++; /* Guarda o tamanho do vetor de voos que estao dentro do prazo de ferias*/
            }
        }
    }

    for (int x = 0; x < tamanho; x++)
    {
        for (int y = 0; y < tamanho; y++)
        {
            if (y != x)
            {
                if (diferenca_data(possiveisvoos[x].data, possiveisvoos[y].data) != 0)
                { /* Analisa as datas possuem diferenca de no minimo 4 dias para aproveitas as ferias*/
                    if (diferenca_data(possiveisvoos[x].data, possiveisvoos[y].data) == 1)
                    { /* Analisa o retorno da funcao, se retorna 1 entao a primeiradata dada eh o voo de inicio*/
                        if (verificaregistro(possiveisvoosinicio, possiveisvoosfim, possiveisvoos[x], possiveisvoos[y], tamanho2) == 0)
                        { /* Verifica se o registro do par de voos existem ja*/
                            if ((verificaaeroporto(possiveisvoos[x].origem, codigo_origem) == 1) && (verificaaeroporto(possiveisvoos[y].destino, codigo_origem) == 1))
                            { /* Verifica se o aeroporto de origem ou de destino sao validos de acordo com o que o usuario colocou*/
                                possiveisvoosinicio[tamanho2] = possiveisvoos[x];
                                possiveisvoosfim[tamanho2] = possiveisvoos[y];
                                tamanho2++; /*Tamanho dos vetores que guardam os pares de voos que sao validos*/
                            }
                        }
                    }
                    else /* Se o retorna da funcao for igual a 2, entao o 2 voo (y) eh o voo de inicio*/
                    {
                        if (verificaregistro(possiveisvoosinicio, possiveisvoosfim, possiveisvoos[y], possiveisvoos[x], tamanho2) == 0)
                        {
                            if ((verificaaeroporto(possiveisvoos[y].origem, codigo_origem) == 1) && (verificaaeroporto(possiveisvoos[x].destino, codigo_origem) == 1))
                            {
                                possiveisvoosinicio[tamanho2] = possiveisvoos[y];
                                possiveisvoosfim[tamanho2] = possiveisvoos[x];
                                tamanho2++;
                            }
                        }
                    }
                }
            }
        }
    }

    somatotal = possiveisvoosinicio[0].valor + possiveisvoosfim[0].valor; /*Guarda a primeira posicao como a soma de valor mais cara*/
    resultadofinalinicio = possiveisvoosinicio[0];                        /*Atribui o primeiro par de voos como o resultado*/
    resultadofinalfim = possiveisvoosfim[0];

    for (int x = 0; x < tamanho2; x++) /* Para descobrir a menor soma de precos*/
    {
        somax = possiveisvoosinicio[x].valor + possiveisvoosfim[x].valor;

        if (somatotal > somax) /* Se a soma do novo par for menor, entao a variavel somatotal sera o novo parametro de comparacao*/
        {
            resultadofinalinicio = possiveisvoosinicio[x];
            resultadofinalfim = possiveisvoosfim[x];
            somatotal = somax;
        }
    }

    printf("\n%d", resultadofinalinicio.numvoo);
    printf("\n%d", resultadofinalfim.numvoo);
}
