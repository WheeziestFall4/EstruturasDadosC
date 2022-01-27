/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   DESCRICAO: Programa calcula o imposto embutido nos rendimentos de funcionarios de uma empresa. 
   - Entrada: numero de funcionarios da empresa, rendimento mensal de cada durante 12 meses, abatimentos anuais de cada fun.
   - Saida: Impostos embutidos mensalmente a cada funcionario,Total de imposto retido, Imposto anual embutido (devido) e 
   o ajuste de imposto que o funcionario deve (pagar se for + ou receber de volta se for -) */

#include <stdio.h>
#define TAM 1000

int main()
{
    int numfuncionarios;
    double rendimentomensais[TAM][12], somarendimentos[TAM], abatimentos[TAM], soma;
    double retidoanual[TAM], retidomes[TAM][12], total[TAM], devido[TAM], ajuste[TAM];

    scanf("%d", &numfuncionarios);

    for (int x = 0; x < numfuncionarios; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            scanf("%lf", &rendimentomensais[x][y]);
            somarendimentos[x] += rendimentomensais[x][y];
        }
    }

    for (int x = 0; x < numfuncionarios; x++)
    {
        scanf("%lf", &abatimentos[x]);
    }

    for (int x = 0; x < numfuncionarios; x++) /* FOr que percorre todos os rendimentos mensais para calcular os impostos mensais*/
    {
        for (int y = 0; y < 12; y++)
        {
            if (rendimentomensais[x][y] > 1499.15)
            {
                if (rendimentomensais[x][y] > 2246.75)
                {
                    soma += 56.07;

                    if (rendimentomensais[x][y] > 2995.70)
                    {
                        soma += 112.3425;

                        if (rendimentomensais[x][y] > 3743.19)
                        {
                            soma += 168.18525;

                            soma += (rendimentomensais[x][y] - 3743.19) * 0.275;
                        }
                        else
                        {
                            soma += (rendimentomensais[x][y] - 2995.70) * 0.225;
                        }
                    }
                    else
                    {
                        soma += (rendimentomensais[x][y] - 2246.75) * 0.15;
                    }
                }
                else
                {
                    soma += (rendimentomensais[x][y] - 1499.15) * 0.075;
                }
            }

            retidoanual[x] += soma;
            retidomes[x][y] = soma;
            soma = 0;
        }

        total[x] = somarendimentos[x] - abatimentos[x]; /* Calculando o total de rendimentos anuais  */
    }

    for (int x = 0; x < numfuncionarios; x++) /* For que percorre o total de rendimentos anuais para aplicar o imposto*/
    {
        if (total[x] > 18000.00)
        {
            if (total[x] > 26400.00)
            {
                devido[x] += 630;

                if (total[x] > 36000.00)
                {
                    devido[x] += 1440;

                    if (total[x] > 44400.00)
                    {
                        devido[x] += 1890;

                        devido[x] += (total[x] - 44400) * 0.275;
                    }
                    else
                    {
                        devido[x] += (total[x] - 36000) * 0.225;
                    }
                }
                else
                {
                    devido[x] += (total[x] - 26400) * 0.15;
                }
            }
            else
            {
                devido[x] += (total[x] - 18000) * 0.075;
            }
        }

        ajuste[x] = devido[x] - retidoanual[x]; /* Calculo do ajuste de acordo com o plano*/
    }

    printf("Jan	Fev	Mar	Abr	Mai	Jun	Jul	Ago	Set	Out	Nov	Dez	Retido	Devido	Ajuste\n");

    for (int x = 0; x < numfuncionarios; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            printf("%.2lf\t", retidomes[x][y]);
        }

        printf("%.2lf\t", retidoanual[x]);
        printf("%.2lf\t", devido[x]);
        printf("%.2lf",ajuste[x]);

        printf("\n");
    }

    return 0;
}