/* NOME: Vinicius Rodrigues da Costa Almeida    RA: 254843
   DESCRICAO: Programa simula acessos de usuarios a servidores e denomina se o acesso eh negado ou nao existe ou aceito.
   Ele cria uma arvore rubro negra esquerdista de servidores de redes e outra arvore rubro negra esquerdista de usuarios 
   de acordo com o pedido de acesso.
   ENTRADA: QtdMax de consultas permitidas por usuario aos servidores, qtd de Servidores, qtd de pedidos de 
   acessos de usuarios. Depois, cada pedido no formato GET servidores FROM ip do usuario.
   SAIDA: Sao 3 possiveis: ACCEPTED, FORBIDDEN e NOTFOUND 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum cor /* Cria enum atribuido VERMELHO = 0 e PRETO = 1*/
{
    VERMELHO, 
    PRETO    
};

typedef struct no /* No da arvore que pode guardar o Servidor ou Usuario*/
{
    char dominio[100];
    char enderecoServidor[16];
    char enderecoUsuario[16];
    int qtdAcesso;
    enum cor cor;
    struct no *esq;
    struct no *dir;
} No;

typedef struct arvore /*Struct que guarda a raiz da arvore*/
{
    No *raiz;
} Arvore;

int ehVermelho(No *no) /* Verifica se o No eh vermelho*/
{
    if (no == NULL)
        return 0;

    if (no->cor == VERMELHO)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ehPreto(No *no) /* Verifica se o No eh Preto*/
{
    if (no == NULL)
        return 1;   /* Retorna 1 devido ao NULL representar PRETO*/

    if (no->cor == PRETO)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

No *rotacionaEsquerda(No *raiz) 
{ /*Rotaciona a arvore da direita para a esquerda a partir do no raiz dado*/
    No *auxiliar = raiz->dir;
    raiz->dir = auxiliar->esq;
    auxiliar->esq = raiz;
    auxiliar->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return auxiliar;
}

No *rotacionaDireita(No *raiz)
{  /*Rotaciona a arvore da esquerda para a direita a partir do no raiz dado*/
    No *auxiliar = raiz->esq;
    raiz->esq = auxiliar->dir;
    auxiliar->dir = raiz;
    auxiliar->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return auxiliar;
}

void sobeVermelho(No *raiz)
{ /* Troca as cores do no-pai com as dos filhos*/
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

No *adicionaServidor(No *raizAtual, char dominio[], char endereco[])
{               /* Adiciona cada servidor com endereco e dominio a arvore rubro negro de Servidores*/
    No *novo;

    if (raizAtual == NULL) 
    {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        strcpy(novo->dominio, dominio);
        strcpy(novo->enderecoServidor, endereco);
        novo->cor = VERMELHO; /* Sempre inicia os novos NOS Com vermelho para nao atrapalhar na verificacao*/

        return novo;
    }
    else
    {
        if (strcmp(raizAtual->dominio, dominio) > 0) /* Se for maior o dominio da raizAtual, entao adiciona o novo na esquerda*/
        {
            raizAtual->esq = adicionaServidor(raizAtual->esq, dominio, endereco);
        }
        else /*Se for menor o dominio da raizAtual, entao adiciona o novo na direita*/
        {
            raizAtual->dir = adicionaServidor(raizAtual->dir, dominio, endereco);
        }

        /* Se o lado direito for vermelho e o esquerdo nao, entao deve rotacionar para a esquerda*/
        if (ehVermelho(raizAtual->dir) == 1 && ehPreto(raizAtual->esq) == 1)
        {                                               /* Arvore rubro negra nao permite vermelho as direitas*/
            raizAtual = rotacionaEsquerda(raizAtual);
        }

        /* Se o lado esquerdo for vermelho e o filho dele for vermelho tambem entao deve rotacionar para a direita*/
        if (ehVermelho(raizAtual->esq) == 1 && ehVermelho(raizAtual->esq->esq) == 1)
        {                                               /* Arvore rubro negra nao permite que filhos de um vermelho tambem seja vermelho*/
            raizAtual = rotacionaDireita(raizAtual);
        }

        /* Se oos dois filhos forem vermelho entao devemos trocar com a raizAtual que eh preta*/
        if (ehVermelho(raizAtual->esq) == 1 && ehVermelho(raizAtual->dir) == 1)
        {
            sobeVermelho(raizAtual);
        }

        return raizAtual;
    }
}

No *adicionaServidorConverteCorRaiz(No *raiz, char dominio[], char endereco[])
{   /* Em cada adicao e apos configuracao da arvore rubro negra, fazer raiz ser da cor PRETA*/
    raiz = adicionaServidor(raiz, dominio, endereco);
    raiz->cor = PRETO;
    return raiz;
}

No *buscaDominio(No *raiz, char dominio[]) /* Busca dominio dentro da arvore rubro negra de Servidores*/
{
    if (raiz == NULL || strcmp(raiz->dominio, dominio) == 0)
    {
        return raiz;
    }
    else
    {
        if (strcmp(raiz->dominio, dominio) > 0)
        {
            return buscaDominio(raiz->esq, dominio);
        }
        else /* senao, procura a direita do no*/
        {
            return buscaDominio(raiz->dir, dominio);
        }
    }
}

No *buscaEndereco(No *usuario, char endereco[]) /* Busca endereco dentro da Arvore rubro negra de Usuarios*/ 
{
    if (usuario == NULL || strcmp(usuario->enderecoUsuario, endereco) == 0)
    {
        return usuario;
    }
    else
    {
        if (strcmp(usuario->enderecoUsuario, endereco) > 0)
        {
            return buscaEndereco(usuario->esq, endereco);
        }
        else /* senao, procura a direita do no*/
        {
            return buscaEndereco(usuario->dir, endereco);
        }
    }
}

No *adicionaUsuario(No *usuarioAtual, int *verifica, int maxConsultas, char endereco[])
{               /* Adiciona novos usuarios a arvore rubro de Usuarios*/
    No *novo;

    if (usuarioAtual == NULL)
    {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        strcpy(novo->enderecoUsuario, endereco);
        novo->qtdAcesso = 1;

        novo->cor = VERMELHO;

        return novo;
    }
    else
    {
        if (strcmp(usuarioAtual->enderecoUsuario, endereco) == 0) /* Se o usuario ja existir na arvore, entao*/
        {   
            if (usuarioAtual->qtdAcesso < maxConsultas) /* Aumenta a qtd de acesso dele se nao passar na maxima permitida*/
            {
                usuarioAtual->qtdAcesso++;
            }
            else    /* Se a qtdAcesso passar do limite, entao verifica passado por parametro tera valor 1*/
            {
                *verifica = 1; /* 1 indica que usuario esta proibido de acessar mais servidores*/
            }

            return usuarioAtual; /* Retorna e para a adicao de novo usuario*/
        }

        if (strcmp(usuarioAtual->enderecoUsuario, endereco) > 0)
        {
            usuarioAtual->esq = adicionaUsuario(usuarioAtual->esq, verifica, maxConsultas, endereco);
        }
        else
        {
            usuarioAtual->dir = adicionaUsuario(usuarioAtual->dir, verifica, maxConsultas, endereco);
        }

        /* Mesmo funcionamento da arvore rubro de Servidores*/
        if (ehVermelho(usuarioAtual->dir) == 1 && ehPreto(usuarioAtual->esq) == 1)
        {
            usuarioAtual = rotacionaEsquerda(usuarioAtual);
        }

        if (ehVermelho(usuarioAtual->esq) == 1 && ehVermelho(usuarioAtual->esq->esq) == 1)
        {
            usuarioAtual = rotacionaDireita(usuarioAtual);
        }

        if (ehVermelho(usuarioAtual->esq) == 1 && ehVermelho(usuarioAtual->dir) == 1)
        {
            sobeVermelho(usuarioAtual);
        }

        return usuarioAtual;
    }
}

No *adicionaUsuarioConverteCorRaiz(No *raiz, int *verifica, int maxConsultas, char endereco[])
{
    raiz = adicionaUsuario(raiz, verifica, maxConsultas, endereco);
    raiz->cor = PRETO;
    return raiz;
}

void liberarArvore(No *raiz) /* Desaloca os nos de cada arvore*/
{
  if(raiz != NULL)
  {
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
  }
}

int main()
{
    int maxConsultas = 0;
    int qtdDominios = 0;
    int qtdConsultas = 0;
    int verifica = 0;
    char dominio[100], endereco[16], enderecoUsuario[16];
    char texto1[4], texto2[5];

    Arvore arvoreServidores;
    arvoreServidores.raiz = NULL;

    No *resultadoServidor = NULL; /* Guarda resultado da busca pelo dominio*/

    Arvore arvoreUsuarios;
    arvoreUsuarios.raiz = NULL;

    scanf("%d", &maxConsultas);
    scanf("%d", &qtdDominios);

    for (int i = 0; i < qtdDominios; i++)
    {
        scanf("%s %s", dominio, endereco);

        arvoreServidores.raiz = adicionaServidorConverteCorRaiz(arvoreServidores.raiz, dominio, endereco);
    }

    scanf("%d", &qtdConsultas);

    for (int i = 0; i < qtdConsultas; i++)
    {
        scanf("%s %s %s %s", texto1, dominio, texto2, enderecoUsuario);

        arvoreUsuarios.raiz = adicionaUsuarioConverteCorRaiz(arvoreUsuarios.raiz, &verifica, maxConsultas, enderecoUsuario);

        resultadoServidor = buscaDominio(arvoreServidores.raiz, dominio);

        if(verifica == 1) /* Se verifica tiver valor 1, significa que usuario esta proibido de acessar mais servidores*/
        {
            printf("\nFORBIDDEN %s FROM %s", dominio, enderecoUsuario);
        }
        else if (resultadoServidor == NULL && verifica == 0) /* Se resultadoServidor for nulo, entao nao foi encontrado o dominio*/
        {
            printf("\nNOTFOUND %s FROM %s", dominio, enderecoUsuario);
        }
        else if (resultadoServidor != NULL && verifica == 0)
        {
            printf("\nACCEPTED %s FROM %s RESPOND %s", resultadoServidor->dominio, enderecoUsuario, resultadoServidor->enderecoServidor);
        }

        verifica = 0; /* Reinicia o verifica para um novo uso*/
    }

    liberarArvore(arvoreServidores.raiz);
    liberarArvore(arvoreUsuarios.raiz);
}