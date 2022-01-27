/* Nome: Vinicius Rodrigues da Costa Almeida RA: 254843
   DESCRICAO: Programa le nomes de certa qtd de estudantes e retorna quais nomes possuem
   o primeiro nome homonimo e quais nomes possuem os sobrenomes iguais dependendo da escolha do usuario.
   O usuario pode escolher homonimo ou parentes.

   - Entrada: numeroestudante, opcaodeorganizacao, nomes          
   - Saida: nomes com primeiro nome homonimos, nomes com sobrenome homonimos*/

#include <stdio.h>
#include <string.h>
#define TAM 100
#define TAMSTRING 31

void lenomes(char nomeestudantes[][TAMSTRING], int numestudantes)
{
    for (int x = 0; x < numestudantes; x++)
    {
        scanf("%s", nomeestudantes[x]);
    }
}

void separanomeesobrenome(char nomeestudantes[][TAMSTRING], char primeironome[][TAMSTRING], char sobrenome[][TAMSTRING], int numestudantes)
{ /* Separanome os nomes em primeironome, sobrenome */
    int condicao;

    for (int x = 0; x < numestudantes; x++)
    {
        condicao = 0;
        int z = 0;

        for (int y = 0; y <= strlen(nomeestudantes[x]); y++) /*verifica qual parte do nome possue a separacao _*/
        {
            if ((nomeestudantes[x][y] != '_') && condicao == 0)
            {
                primeironome[x][y] = nomeestudantes[x][y]; /* guarda os primeiros caracteres do nome ate chegar no _*/
            }
            else if ((nomeestudantes[x][y] == '_') && condicao == 0) /* Atribui \0 ao primeironome */
            {
                primeironome[x][y] = '\0';
                condicao++;
            }
            else
            {
                sobrenome[x][z] = nomeestudantes[x][y];
                z++;
                condicao++;
            }
        }
    }
}

void colocaemordem(char resultado[][TAMSTRING], int tamanhoresultado) /* Coloca o resultado em ordem alfabetica*/
{
    char reserva[TAMSTRING];

    for (int x = 0; x < tamanhoresultado; x++)
    {
        for (int y = 1; y < tamanhoresultado; y++)
        {
            for (int k = 0; k < TAMSTRING; k++) /* Percorre os caracteres da string resultado[x];*/
            {
                if ((resultado[x][k] != resultado[y][k]) && (strlen(resultado[x]) >= k) && (strlen(resultado[y]) >= k) && (y > x))
                {
                    if (resultado[x][k] > resultado[y][k])
                    {
                        strcpy(reserva, resultado[x]);
                        strcpy(resultado[x], resultado[y]);
                        strcpy(resultado[y], reserva);
                    }

                    break;
                }
            }
        }
    }
}

int verificarregistro(char nome[], int tamanhoresultado, char resultado[][TAMSTRING]) /* Verifica se ha o nome inserido ja no resultado, se tiver retorna 1*/
{
    for (int x = 0; x < tamanhoresultado; x++)
    {
        if (strcmp(nome, resultado[x]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void colocaemordemsobrenome(char resultado[][TAMSTRING], int tamanhoresultado)
{ /* Faz a organizacao alfabetica de sobrenomes e depois coloca em ordem alfabetica de primeiro nome */
    char guardanomes[TAM][TAMSTRING], novoresultado[TAM][TAMSTRING];
    char primeironome[TAM][TAMSTRING], sobrenome[TAM][TAMSTRING], parentes[TAM][TAMSTRING];
    int z, tamanho = 0;

    separanomeesobrenome(resultado, primeironome, sobrenome, tamanhoresultado); /* Descobrir sobrenomes dos nomes resultados*/

    for (int x = 0; x < tamanhoresultado; x++)
    {
        strcpy(parentes[x], sobrenome[x]);
    }

    colocaemordem(parentes, tamanhoresultado); /* Coloca os sobrenomes armazenas em parentes em ordem alfabetica*/

    for (int x = 0; x < tamanhoresultado; x++) /* Percorre os sobrenomes do resultado e compara com a ordem alfabetica dos sobrenomes armazenado em parentes*/
    {
        z = 0;

        for (int y = 0; y < tamanhoresultado; y++)
        {
            if (strcmp(sobrenome[y], parentes[x]) == 0)
            {
                if ((verificarregistro(resultado[y], z, guardanomes) == 0) && (verificarregistro(resultado[y], tamanho, novoresultado) == 0))
                { /* Verifica se um dos nomes ja esta armazenado em resultado*/
                    strcpy(guardanomes[z], resultado[y]);
                    z++;
                }
            }
        }

        colocaemordem(guardanomes, z);

        for (int x = 0; x < z; x++)
        {
            strcpy(novoresultado[x + tamanho], guardanomes[x]);
        }

        tamanho += z;

        for (int y = 0; y < z; y++) /* Guardanomes eh um vetor de string temporario para armazenas os nomes */
        {                           /* organizados alfabeticamente pelo sobrenome, depois do uso ele eh zerado novamente*/
            strcpy(guardanomes[y], "");
        }
    }

    for (int x = 0; x < tamanho; x++)
    {
        strcpy(resultado[x], novoresultado[x]);
    }
}

int main()
{
    char opcao[TAMSTRING];
    int numestudantes, tamanhoresultado = 0;
    char nomeestudantes[TAM][TAMSTRING], primeironome[TAM][TAMSTRING], sobrenome[TAM][TAMSTRING];
    char resultado[TAM][TAMSTRING];

    scanf("%d", &numestudantes);
    scanf("%s", opcao);

    if (strcmp(opcao, "homonimos") == 0)
    {
        lenomes(nomeestudantes, numestudantes);
        separanomeesobrenome(nomeestudantes, primeironome, sobrenome, numestudantes);

        for (int x = 0; x < numestudantes; x++)
        {
            for (int y = 1; y < numestudantes; y++)
            {
                if ((strcmp(primeironome[x], primeironome[y]) == 0) && y > x) /* Compara os primeiros nomes dos nomes inseridos*/
                {
                    if (verificarregistro(nomeestudantes[y], tamanhoresultado, resultado) == 0)
                    {
                        strcpy(resultado[tamanhoresultado], nomeestudantes[y]);
                        tamanhoresultado++;
                    }

                    if (verificarregistro(nomeestudantes[x], tamanhoresultado, resultado) == 0)
                    {
                        strcpy(resultado[tamanhoresultado], nomeestudantes[x]);
                        tamanhoresultado++;
                    }
                }
            }
        }

        colocaemordem(resultado, tamanhoresultado);
    }
    else
    {
        lenomes(nomeestudantes, numestudantes);
        separanomeesobrenome(nomeestudantes, primeironome, sobrenome, numestudantes);

        for (int x = 0; x < numestudantes; x++)
        {
            for (int y = 0; y < numestudantes; y++)
            {
                if ((strcmp(sobrenome[x], sobrenome[y]) == 0) && (x != y))
                {
                    if (verificarregistro(nomeestudantes[y], tamanhoresultado, resultado) == 0)
                    {
                        strcpy(resultado[tamanhoresultado], nomeestudantes[y]);
                        tamanhoresultado++;
                    }

                    if (verificarregistro(nomeestudantes[x], tamanhoresultado, resultado) == 0)
                    {
                        strcpy(resultado[tamanhoresultado], nomeestudantes[x]);
                        tamanhoresultado++;
                    }
                }
            }
        }

        colocaemordemsobrenome(resultado, tamanhoresultado);
    }

    printf("\n");

    for (int x = 0; x < tamanhoresultado; x++) /* Imprimi resultado ja em ordem*/
    {
        printf("%s\n", resultado[x]);
    }

    return 0;
}