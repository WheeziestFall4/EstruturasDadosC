/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   Descricao: Programa analisa datas entre voos e o preco deles e devolve qual eh o melhor par de voos
   custo beneficio para ter o melhor preco.
   Entrada: 4 Escolhas (registrar/4 Parametros, alterar/2 parametro, cancelar/2 parametros, planejar(faz conta))
   Saida: numero do voos de partida e de volta */

#include "planejar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

int main()
{
    Voo voos[TAM];
    Data datainicio, datafim;
    char escolha[30], aeroportosaida[30];
    double valornovo;
    int numerovoo, qtdvoos;

    for (int x = 0; x < TAM; x++)
    {
        voos[x].numvoo = 0;
    }

    while (strcmp(escolha, "planejar") != 0)
    {
        scanf("%s", escolha);

        if (strcmp(escolha, "registrar") == 0)
        {
            qtdvoos = registrar(voos);
        }
        else if (strcmp(escolha, "alterar") == 0)
        {
            scanf("%d %lf", &numerovoo, &valornovo);

            alterar(voos, qtdvoos, numerovoo, valornovo);
        }
        else if (strcmp(escolha, "cancelar") == 0)
        {
            scanf("%d", &numerovoo);

            qtdvoos = cancelar(voos, qtdvoos, numerovoo);
        }
        else if (strcmp(escolha, "planejar") == 0)
        {
            scanf("%s", aeroportosaida);
            scanf("%d/%d/%d %d/%d/%d", &datainicio.dia, &datainicio.mes, &datainicio.ano, &datafim.dia, &datafim.mes, &datafim.ano);

            planejar(voos, qtdvoos, datainicio, datafim, aeroportosaida);
        }

        printf("\n");
    }

    return 0;
}
