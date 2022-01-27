
# Printando na tela (Saida) ################################

# printando em C:

printf("Printar");

# Printando int:

int x = 10;

printf("%d",x);

# Printando Double:

double y = 10.3;

printf("%lf",y);

# Printando Char:

char l = 'c';

printf("%c",l);

# Lendo (Entrada)

# Scanf
- Para ignorar espaço em branco entre só colocar espaço entre &;

scanf("%d %d",variavel1, variavel2); 

# Laços de Repetição ##############################################3

# For

for(int x = 0; x < 10; x++)

# While

while( x < 10)
{
    continue;
}

# Vetores ############################################################

# Como declarar vetores

int lista[10]; 

# Passar vetor em uma funcao

void funcao(int lista[], int n)

# Passar uma matriz em uma funcao
- Obs: A primeira linha eh ignorada

void funcao(int lista[][tamanho1], int tamanho2)

# Registro (STRUCT) em C #################################################
- Usado quando queremos criar tipo de algo novo 

struct identificador{
    tipo nome1;
    tipo nome2;
    ...
};

# Inicializacao e chamada
- o tipo sempre vai ser struct nome

struct Identificador variavel = {inicializa};

Identificador.nome1 = "Vinicius";

printf("%s",identificador.nome1);

# typedef para dar apelido para um tipo independente se
for int, struct etc

typedef struct identificador ident;

typedef struct novamente
{

} nomenovo;

# TAD: Interface, Implementacao e Cliente ######################

- Interface = conjunto de operacoes (nome das operacoes)
  possui a struct e os nomes das funcoes e seus parametros

- Implementacao = implementacao das funcoes/operacoes

#include "nomedainterface.h"

- Cliente = as chamadas de variaveis e passadas de funcoes

#include "nomedainterface.h"

- O que eh um TAD? R: Tipo Abstrado de Dados,

# Ponteiro #######################################################
- quando queremos passar um valor fixo 
- & retorna o endereço de memoria de uma variavel
- * retorna o conteudo do endereço indicado pelo ponteiro = valor
- quando soma ou subtrai um ponteiro, o endereco ira ser somado com o tamanho do tipo 
da variavel

# Para chamar um ponteiro

double *p;
double nota;

# Para guardar um endereco

p = &nota;

# Para atribui conteudo para a variavel que o apontador esta apontando

*p = 10;

# Para imprimir um ponteiro

variavel = 10;
int *ponteiro;
ponteiro = &variavel;

printf("Variavel: %d", variavel);
printf("Variavel: %d",*ponteiro);
printf("Endereco: %p",ponteiro);
printf("Endereco: %p",&variavel);

# Alocacao dinamica (sem tamanho definido) ##############################
- sizeof(tipo) = devolve o tamanho de um tipo
- malloc aloca dinamicamente a qtd de bytes

variavelponteiro = malloc(tamanhodovetor * sizeof(tipo));

- free = libera espaco alocado de uma variavel que foi alocada
- stdlib.h --- biblioteca para usar ponteiro, malloc etc.

double media, *notas;
int i, n;
scanf("%d",&n);
notas = malloc(n * sizeof(double));
if(notas == NULL)
  printf("Nao ha memoria suficiente");
  exit(1);

# Funcao com ponteiro
- Como retornar algo alocado

int * funcao(

  return variavelponteiro;
)

# Struct com alocacao 

struct data *p = malloc(sizeof(struct data));

(*p).variaveldastruct = 1;
p -> variaveldastruct = 1;  /* A mesma coisa */

####### Lista Ligada ###########################################

- Nó: elemento alocado dinamicamente que contem 
      os dados da questao 
      um ponteiro para outro nó

- necessita de um ponteiro que guarda o inicio 
da lista. 

### Versao 1 #############

typedef struct no *p_no;

struct no{
    int dado;
    p_no prox;
};

p_no criar_lista()
{
  return NULL;
}

/* Adiciona novos elementos no INICIO da lista*/
p_no adicionar_elemento(p_no lista, int x)
{
  p_novo novo = malloc(sizeof(struct no));

  novo->dado = x;
  novo->prox = lista; /* Se refere a lista, por que a lista guarda o endereço do primeiro no da lista*/

  return novo;
}

p_no copiar_lista(p_no lista)
{
  if(lista == NULL)
  {
    novo = NULL;
  }
  else
  {
    novo = malloc(sizeof(struct no));
    novo-> dado = lista ->dado;
    p_no menor = copiar_lista(lista->prox); /* Pega os prox nos da lista*/
    novo -> prox = menor;
  }

  return lista; 

}

p_no inverter(p_no lista)
{
  p_no atual, ant, invertida = NULL;
  atual = lista;

  while(atual != NULL)
  {
    ant = atual;
    atual = ant -> prox;
    ant -> prox = invertida;
    invertida = ant;
  }

  return invertida;
}

p_no concatenar_lista(p_no primeiro, p_no segunda)
{
  if(primeira == NULL)
  {
    return segunda;
  }
  else
  {
    primeira -> prox = concatenar_lista(primeira->prox, segunda)

    /* Falta terminar */
  }
}

void imprimir_lista(p_no lista)
{
  p_no atual = lista;

  for(atual = lista; atual != NULL; atual = atual -> prox)
  {
      printf("%d\n", atual->dado);
    atual = atual -> prox;
  }

}

int main()
{
  p_no lista;

  lista = criar_lista();

  lista = adicionar_elemento(lista, 13);
  lista = adicionar_elemento(lista, 13);
  lista = adicionar_elemento(lista, 13);
  lista = adicionar_elemento(lista, 13);

  imprimir_lista(lista);

}

#### Versao 2 ##########

typedef struct No{
  int valor;
  struct No *proximo;
}No;

typedef struct{
  No *inicio;
  int tam;
} Lista;

void inserirInicio(Lista *list, int valor)
{
  No *novo = malloc(sizeof(No));
  novo -> valor = valor;
  novo -> proximo = list -> inicio;
  list -> inicio = novo;
  list -> tam++;
}

void inserirFim(Lista *list, int valor)
{
  No *novo = malloc(sizeof(No));
  No *no = malloc(sizeof(No));

  novo -> valor = valor;
  novo -> proximo = NULL;

  if(lista -> inicio == NULL)
  {
    list->inicio = novo;
    list->tam++;
  }
  else
  {
    no = list -> inicio;

    while(no ->proximo != NULL)
    {
      no = no -> proximo;
    }

    no->proximo = novo;
    lista-> tam++;

  }
}

void adicionar_elementofinal(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{
    No *novo = malloc(sizeof(No));
    No *atual = lista->inicio;

    novo->prox = NULL;
    novo->lanterna = 1;
    novo->numdocumento = numdocumento;
    strcpy(novo->nomeprofissao, nomeprofissao);
    strcpy(novo->estadovacinacao, estadovacinacao);

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->tam++;
    }
    else
    {
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = novo;
        atual->lanterna = 0;
        lista->tam++;
    }
}

void adicionar_elemento_inicio(Lista *lista, int numdocumento, char nomeprofissao[], char estadovacinacao[])
{
    if (lista->inicio != NULL)
    {
        No *noantigo = lista->inicio;
        noantigo->lanterna = 0;
    }

    No *novo = malloc(sizeof(No));

    novo->lanterna = 1;
    novo->numdocumento = numdocumento;
    strcpy(novo->nomeprofissao, nomeprofissao);
    strcpy(novo->estadovacinacao, estadovacinacao);
    novo->prox = lista->inicio; /* Se refere a lista, por que a lista guarda o endereço do primeiro no da lista*/
    lista->inicio = novo;
    lista->tam++;
}

void imprimir(Lista *list)
{
  No *inicio = list-> inicio;

  while(inicio != NULL)
  {
    printf("%d", inicio -> valor);
    inicio = inicio -> proximo;
  }

  printf("\n\n");
}

int main()
{
  Lista list;
  int opcao, valor;

  list.inicio = NULL;
  list.tam = 0;

  do{
    printf("1 - Inserir no inicio\n2 - Imprimir\n5 - Sair\n");
    scanf("%d",&opcao);

    if(opcao == 1)
    {
      inserirInicio(&list, valor);
    }
    else if(opcao == 2)
    {
      imprimir(&list);
    }
    else
    {
      inserirFim(&list, valor);
    }

  } while(opcao != 5);


}





####### Lista Circular ######################
- Lista guarda o primeiro elemento


p_no inserir_circular(p_no lista, int x)
{
  p_no novo;
  novo = malloc(sizeof(struct no));

  novo-> dado = x;

  if(lista == NULL)
  {
    novo-> prox = novo; /* Aponta para ele mesmo*/
    lista = novo;
  }else /* Inseri no inicio da lista*/
  {
    novo -> prox = lista -> prox;
    lista -> prox = novo;
  }

  return lista;
}

p_no remover_circular(p_no lista, p_no no)
{
  p_no ant;

  if(no -> prox == no)
  {
    free(no);
    return NULL;
  }

  for(ant = no -> prox; ant -> prox != no; ant = ant -> prox);
  ant-> prox = no -> prox;

  if(lista == no)
    lista = ant;
  
  free(no);

  return lista;

    /* Terminar */
}

void imprimir_lista_circular(p_no lista)
{
  p_no p;
  p = lista -> prox;

  do{

    printf("%d\n",p->dado);
    p = p->prox;

  }while(p != lista -> prox);


}

# Lista circular com cabeca
- Sempre vai haver um no como lider da Lista

p_no inserir_circular(p_no lista, int x)
{
  p_no novo;
  novo = malloc(sizeof(struct no));
  novo->dado = x;
  novo->prox = lista->prox;
  lista->prox = novo;
  return lista;
}

###### FILA ######################
- Remove primeiro objetos colocados primeiro
- adiciona novos objetos no final = primeiro a entrar eh o primeiro a sair 
- Enfileira e Desenfileira

## Com alocacao ####

typedef struct fila *p_fila;

struct fila{
  p_no ini, fim, prox;
};

p_fila criar_fila()
{
  p_fila f;
  f = malloc(sizeof(struct fila));
  f -> ini = NULL;
  f -> fim = NULL;
  return f;
}

void destruir_fila(p_fila f)
{
  destruir_lista(f -> ini);
  free(f);
}

void enfileira(p_fila f, int x)
{
  p_no novo;
  novo = malloc(sizeof(struct no));
  novo -> dado = x;
  novo -> prox = NULL;

  if(f -> ini == NULL)
    f -> ini = novo;
  else
    f-> fim -> prox = novo;

  f->fim = novo;
}

int desenfileira(p_fila f)
{
  p_no primeiro = f->ini;
  int x = primeiro->dado;
  f->ini = f->ini->prox;

  if(f->ini == NULL)
  {
    f->fim = NULL;
  }

  free(primeiro);
  return x;
}

## Com vetor dinamico ############

typedef struct fila *p_fila;

struct fila{
  int *v;
  int ini, fim, N, tamanho;
};

p_fila criar_fila(int N) /* Criando o dummy*/
{
  p_fila f;
  f = malloc(sizeof(struct fila)); /*alocando o tipo fila no heap*/

  f->v = malloc(N * sizeof(int));
  f->ini = 0;
  f->fim = 0;
  f->N = N;
  f-> tamanho = 0;
}

void enfileira (p_fila f, int x)
{
  f->v[f->fim] = x;
  f->fim = (f->fim + 1)%f->N;
  f->tamanho++;
}

int desenfileira(p_fila f)
{
  int x = f->v[f->ini];
  f->ini = (f->ini + 1)%f->N;
  f->tamanho--;
  return x;
}

int main()
{
  int n,x, i;
  p_fila f;
  f = criar_fila(100);
  scanf("%d",&n);

  for(i = 0; i < n; i++)
  {
    scanf("%d",&x);
    enfileira(f,x);
  }

  while(!file_vazia(f))
  {
    x = desenfileira(f);
    printf("%d", x);
  }

  printf("\n");
  destroi_file(f);
  return 0;
}

## Segunda versao com lista ligada ##
- OBS: o ultimo elemento adicionado esta no inicio da lista

typedef struct no{
  int valor;
  struct no *proximo;
}

void inserir_na_fila(No **fila, int num)
{
  No *novo = malloc(sizeof(No));

  if(novo)
  {
    novo -> valor = num;
    novo -> proximo = NULL;

    if(*fila == NULL)
    {
      *fila = novo;
    }
    else
    {
      aux = *fila;

      while(aux -> proximo)
      {
        aux = aux-> proxima;
      }

      aux->proximo = novo;
    }
  }
  
}

void remover_da_fila(No **fila)
{
  No *remover = NULL;

  if(*fila)
  {
    remover = *fila;
    *fila = remover ->proximo;
  }

  free(remover);
}

void imprimir(No *fila)
{
  prinf("\t-------- FILA ------\n");

  while(fila)
  {
    printf("%d ", fila->valor);
    fila = fila->proximo;
  }

  printf("\t------ FIM -------\n");
}

### PILHA #################################
- os primeiros sao os ultimos a sair 
- empilha e desempilha

# Com lista ligada ##########

typedef struct pilha *p_pilha;

struct pilha{
  p_no topo;
};

typedef struct No{
  int dado;
  no *prox;
}no;

void empilhar(p_pilha pilha, int x)
{
  no novo = malloc(sizeof(struct no));
  novo -> dado = x;
  novo -> prox = pilha -> topo;
  pilha -> topo = novo;
}

int desempilhar(p_pilha pilha)
{
  no topo = pilha->topo;
  int x = topo->dado;
  pilha->topo = pilha -> topo -> prox;
  free(topo);
  return x;
}


# Com vetor dinamico #####

typedef struct pilha *p_pilha;

struct pilha{
  int *v;
  int topo;
};

void empilhar(p_pilha p, int i)
{
  p->v[p->topo] = i;
  p->topo++;
}

int desempilhar(p_pilha p)
{
  p->topo--;
  return p->v[p->topo];
}








#### Balanceamento de delimitadores #######
- Abrir parenteses = empilhar
- fecha parenteses = desempilha
- Somente equacoes balanceadas podem empilhar 
e desempilhar corretamente sem haver erro

typedef struct pilha *p_pilha;

/* Cria uma pilha
   para cada caractere:
   - leu ( ou [ , empilha caractere
   - se leu ), desempilha e verifica se eh (
   - se leu ], desempilha e verifica se eh [ */

int eh_balanceada(char *exp)
{
  p_pilha pilha;
  int ok = 1;

  pilha = criar_pilha(pilha);

  for(int i = 0; ok && exp[i] != '\0'; i++)
  {
    if(exp[i] == "(" || exp[i] == "[")
    {
      empilhar(pilha, exp[i]);
    }
    else if(pilha_vazia(pilha))
    {
      ok = 0;
    }
    else if( exp[i] == ")")
    {
      char par = desempilhar(pilha);

      if(par != "(")
      {
        ok = 0;
      }
    }
    else
    {
      char par = desempilhar(pilha);

      if(par != "[")
      {
        ok = 0;
      }
    }
  }

  if(!pilha_vazia(pilha))
  {
    ok = 0;
  }
  
  destruir_pilha(pilha);
  return ok;
}

int main()
{
  char *exp =  "([()([])])";

  if(eh_balanceada(exp))
  {
    printf("Beleza\n");
  }
  else
  {
    printf("Num deu\n");
  }
}

######## Arvore Binaria ################
- Formado por Nos
- Altura = numero de niveis
- filho = no abaixo do no do nivel anterior
- folha = ultimo no da arvore que remete a NULL

typedef struct no *p_no;

struct no{
  int dado;
  /*struct no *pai;*/
  struct no *dir;
  struct no *esq;
};

p_no criar_arvore_vazia()
{
  return NULL;
}

p_no criar_arvore(int dado, p_no esq, p_no dir) /* Cria No ou folha dependendo do parametro*/
{
  p_no novo = malloc(sizeof(no));
  novo ->dado = dado;
  novo->esq = esq;
  novo->dir = dir;

  return novo;
}

p_no procurar_no(p_no raiz, int num)
{
  if(raiz == NULL || raiz->dado == num)
  {
    return raiz;
  }
  else
  {
    p_no no = procurar_no(raiz->esq, num);

    if(no != NULL)
    {
      return no;
    }

     no = procurar_no(raiz->dir, num);

    if(no != NULL)
    {
      return no;
    }

    return NULL;
  }
}

int numero_nos(p_no raiz)
{
  if(raiz == NULL)
  {
    return 0;
  }

  return numero_nos(raiz->esq) + numeros_nos(raiz->dir) + 1;
}

int altura(p_no raiz)
{
  int h_esq, h_dir;

  if(raiz == NULL)
  {
    return 0;
  }

  h_esq = altura(raiz->esq);
  h_dir = altura(raiz->dir);

  return 1+(h_esq > h_dir ? h_esq: h_dir);
}

void liberar_arvore(p_no raiz)
{
  if(raiz != NULL)
  {
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
  }
}

int main()
{
  p_no folha4 = criar_arvore(4, NULL, NULL);

  p_no no = procurar_no(raiz, num);
  printf("\nO lado esquerdo do filho do no eh:");

  if(no == NULL)
  {
    printf("\nNao encontrei");
  }
  else if(no->esq != NULL)
  {
    printf("%d\n", no->esq->dado);
  }
  else
  {
    printf("Nao ha no esquerdo\n");
  }


}

# Percurso em Profundidade - maneiras ##

void pre_ordem(p_no raiz)
{
  if(raiz != NULL)
  {
    printf("%d", raiz->dado);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
  }
}

void pos_ordem(p_no raiz)
{
  if(raiz != NULL)
  {
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d", raiz->dado);
  }
}

void inordem(p_no raiz)
{
  if(raiz != NULL)
  {
    inordem(raiz->esq);
    printf("%d", raiz->dado);
    inordem(raiz->dir); 
  }
}

# Sem recursao

void pre_ordem(p_no raiz)
{
  p_pilha p;
  p = criar_pilha();
  empilhar(p, raiz);

  while(!pilha_vazia(p))
  {
    raiz = desempilhar(p);
    if(raiz != NULL)
    {
      empilhar(p, raiz->dir);
      empilhar(p, raiz->esq);
      printf("%d", raiz->dado);
    }
  }

  destruir_pilha(p);
}

# Percorrendo em largura
- Usa fila

void percurso_em_largura(p_no raiz)
{
  p_fila f;

  f = criar_fila();
  enfileirar(f, raiz);

  while(!fila_vazia(f))
  {
    raiz = desenfileirar(f);

    if(raiz != NULL)
    {
      enfileirar(f, raiz->esq);
      enfileirar(f, raiz->dir);
      printf("%d ", raiz->dado);
    }
  }

  destruir_fila(f);
}

####### Arvores Binarias de Busca ######
- Guarda um conjunto que pode ser ordenado
- Todo elemento a esquerda da raiz eh menor que a raiz
- Todo elemento a direita da raiz eh maior que a raiz.
- As subraizes tambem devem ser menores ou maiores que a raiz.

p_no buscar(p_no raiz, int chave)
{
  if(raiz == NULL || raiz->valor == chave)
  {
    return raiz;
  }
  else
  {
    if(raiz->valor > chave)
    {
       return buscar(raiz->esq, chave);
    }
    else
    {
      return buscar(raiz->dir, chave);
    }
  }
 
}

p_no inserir(p_no r, int x)
{
  p_no nova;

  if(r == NULL)
  {
    nova = malloc(sizeof(struct no));
    nova->chave = x;
    nova->esq = NULL;
    nova->dir = NULL;
  }
  else
  {
    nova = r;

    if(x < r->valor)
    {
      r->esq = inserir(r->esq, x);
    }
    else
    {
      r->dir = inserir(r->di, x);
    }
  }

  return nova;
}

p_no minimo(p_no raiz)
{
  if(raiz == NULL || raiz->esq == NULL)
    return raiz;
  
  return minimo(raiz->esq);
}

p_no maximo(p_no raiz)
{
  if(raiz == NULL || raiz->esq == NULL)
    return raiz;
  
  return minimo(raiz->dir);
}

p_no remover_rec(p_no raiz, int chave)
{
  if(raiz == NULL)
  {
    return NULL;
  }

  if(chave < raiz->valor)
    raiz->esq = remover_rec(raiz->esq, chave);
  else if(chave > raiz->valor)
    raiz->dir = remover_rec(raiz->dir, chave);
  else if(raiz->esq == NULL)
    return raiz->dir;
  else if(raiz->dir == NULL)
    return raiz->esq;
}

############## Arvores Balanceada ##################

########## Arvore rubro-Negras Esquerdistas #####
- Nos podem ser preto ou vermelho
- Raiz sempre eh preta
- Folhas sao NULL e tem cor preta
- Se um no eh vermelho, os dois filhos sao pretos 
- Todo no vermelho esta a esquerda do pai
- Altura negra do no = caminho da folha descendente ate o no

enum cor {VERMELHO, PRETO}

struct no
{
  int chave;
  enum cor cor;
  p_no esq, dir;
};

int ehVermelho(p_no x)
{
  if(x == NULL)
    return 0;

  return x->cor == VERMELHO;
}

int ehPreto(p_no x)
{
  if(x == NULL)
    return 0;

  return x->cor == PRETO;
}

p_no rotaciona_para_esquerda(p_no raiz)
{     /*Muda a direita para a esquerda*/
  p_no x = raiz->dir;
  raiz->dir = x->esq;
  x->esq = raiz;
  x->cor = raiz->cor;
  raiz_cor = VERMELHO;
  return x;
}

p_no rotaciona_para_direita(p_no raiz)
{
  p_no x = raiz->esq;
  raiz->esq = x->dir;
  x->dir = raiz;
  x->cor = raiz->cor;
  raiz->cor = VERMELHO;
  return x;
}

void sobe_vermelho(p_no raiz)
{   /* Troca as cores do no-pai com as dos filhos*/
  raiz->cor = VERMELHO;
  raiz->esq->cor = PRETO;
  raiz->dir->cor = PRETO;
}

p_no inserir_rec(p_no raiz, int chave)
{
  p_no novo;

  if(raiz == NULL)
  {
    novo = malloc(sizeof(struct no));
    novo->esq = novo->dir = NULL;
    novo->chave = chave;
    novo->cor = VERMELHO;
    return novo;
  }

  if(chave < raiz->chave)
  {
      raiz->esq = inserir_rec(raiz->esq, chave);
  }
  else
  {
    raiz->dir = inserir_rec(raiz->dir, chave);
  }

  /* Nao queremos que so o filho direito seja vermelho*/
  if(ehVermelho(raiz->dir) && ehPreto(raiz->esq))
    raiz = rotaciona_para_esquerda(raiz);

  /* Nao queremos que o no vermelho seja filho esquerdo de no vermelho*/
  if(ehVermelho(raiz->esq) && ehPreto(raiz->esq->esq))
    raiz = rotaciona_para_direita(raiz);

  /*Nao queremos que ambos filhos sejam vermelhos*/
  if(ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
    sobe_vermelho(raiz);

  return raiz;
}

p_no inserir(p_no raiz, int chave)
{
  raiz = inserir_rec(raiz, chave);
  raiz->cor = PRETO;
  return raiz;
}


######### FILA DE PRIORIDADE #######################
- duas operacoes basicas: 
- Inserir um novo elemento 
- remover um elemento com maior chave (prioridade)
- Pilhas e filas sao tipo de fila de prioridade

# Usando vetores

typedef struct{
  char nome[20];
  int chave;
}item;

typedef struct{
  item *v;
  int n, tamanho.
}FP;

typedef FP *p_pf;

p_fp criar_filaprio(int tam)
{
  p_fp fila = malloc(sizeof(FP));

  fila->tamanho = tam;
  fila->n = 0;        /* marca quantos posicoes dos vetores esta ocupado*/
  fila->v = malloc(tam * sizeof(Item));

  return fila;
}

int vazia(p_fp fprio)
{
   if(fprio.n == 0)
   {
     return 0;
   }

   return 1;
}

int cheia(p_fp fila)
{
  if(fila->n == fila->tam)
  {
    return 1;
  }

  return 0;
}

void inserir(p_fp fila, Item item)
{
  fila->v[fila->n] = item;
  fila->n += 1;
}

Item extrai_maximo(p_fila fila)
{
  int maior = 0;

  for(int i = 1; i < fila-> n; i++)
  {
    if(fila->v[i].chave > fila->v[maior].chave)
    {
      maior = i;
    }
  }

  Item item = fila->v[maior];

  fila->v[maior] = fila->v[fila->n-1];
  fila->n--;

  return item;
}


# MAX HEAP: Tipo de arvore que guarda vetores #######################
- Todos os pais sao maiores que os filhos

- Filhos: v[2*i + 1] e v[2*i+2]
- Pai: v[(i-1)/2]

typedef struct{
  char nome[20];
  int chave;
}item;

typedef struct{
  item *v;
  int n, tamanho.
}FP;

typedef FP *p_pf;

p_fp criar_filaprio(int tam)
{
  p_fp fila = malloc(sizeof(FP));

  fila->tamanho = tam;
  fila->n = 0;        /* marca quantos posicoes dos vetores esta ocupado*/
  fila->v = malloc(tam * sizeof(Item));

  return fila;
}

int vazia(p_fp fprio)
{
   if(fprio.n == 0)
   {
     return 0;
   }

   return 1;
}

int cheia(p_fp fila)
{
  if(fila->n == fila->tam)
  {
    return 1;
  }

  return 0;
}

void trocar(Item *a, Item *b)
{
  Item t = *a;
  *a = *b;
  *b = t;
}

/* Sobe o elemento do indice k ate a posicao correta*/
void sobe_no_heap(fila, indice)
{
   if(indice > 0 && fila->v[pai(indice)].chave < fila->v[indice].chave)
   {
     troca(v[indice], v[pai(indice)]);
     sobe_no_heap(fila, pai(indice));
   }
}

void inserir(p_fp fila, Item item)
{
  fila->v[fila->n] = item;
  fila->n++;

  sobe_no_heap(fila, fila->n-1);
}

# define F_ESQ(i) (2 * i + 1);
# define F_DIR(i) (2 * i + 2)

void desce_no_heap(p_fp fprio, int indice)
{
  int maior_filho;

  if(F_ESQ(k) < fprio-> n)
  {
     maior_filho = F_ESQ(k);

     if(F_DIR(k) < fprio->n &&
       fprio->v[F_ESQ(k)].chave < fprio->v[F_DIR(k)].chave)
       {
           maior_filho = F_DIR(k);
       }
     if(fprio->v[k].chave < fprio->v[maior_filho].chave)
     {
       troca(&fprio->v[k], &fprio->v[maior_filho]);
       desce_no_heap(fprio, maior_filho);
     }
  }
}

Item extrai_maximo(p_fila fila)
{
   Item item = fila->v[0];
   troca(&fila->v[0], &fila->v[n-1]);
   fila->n--;
   desce_no_heap(fila, 0);
   return item;

}

void muda_prioridade(p_fp fprio, int k, int valor)
{
  if(fprio->v[k].chave < valor)
  {
    fprio->v[k].chave = valor;
    sobe_no_heap(fprio, k);
  }
  else
  {
    fprio->v[k].chave = valor;
    desce_no_heap(fprio, k);
  }
}

void mostra_heap(p_fp fila)
{
  for(int i = 0; i < fila->n; i++)
  {
    printf("fila[%d] = %d %s",i, fila->v[i].chave, fila->v[i].nome);
  }
}

int main()
{
  p_fp fila = criar_filaprio(10);
  Item joao = {"Joao", 7};
  inserir(fila, joao);



}

#### Algoritmo de Ordenacao ###############################

#### Bubble Sort ####
- do fim para o inicio, trocando os pares invertidos
- encontramos o elemento mais leve 
- ele sera trocado com elementos que estao antes 

void bubblesort(int *v, int n)
{
  int i, j, trocou = 1;

  for(i = 0; i < n - 1 && trocou; i++)
  {
    trocou = 0;

    for(j = n - 1; j > i; j--)
    {
      if(v[j] < v[j-1])
      {
        troca(&v[j-1], &v[j]);
        trocou = 1;
      }
    }
  }
}

###### Insertion Sort #######

void insertionSort(int *v, int n)
{
  int i,j,t;

  for(i = 1; i < n; i++)
  {
    t = v[i];

    for(j = 1; j > 0 && t < v[j - 1]; j--)
    {
        v[j] = v[j - 1];
    }

    v[j] = t;
  }
}

###### Selection Sort ####

void selectionSort(int *v, int n)
{
  int i,j, max;

  for(i = n - 1; i > 0; i--)
  {
    max = i;

    for(j = i-1; j >= 0; j--)
    {
      if(v[j] > v[max])
      {
        max = j;
      }
    }

    troca(&v[i], &v[max]);
  }
}

##### HEAPSORT: Ordenacao usando fila de prioridades ##########

void fpsort(Item *v, int n)
{
  int i;
  p_fp fprio = criar_fprio(n);

  for(i = 0; i < n; i++)
  {
    insere(fprio, v[i]);
  }

  for(i = n - 1; i >= 0; i--)
  {
    v[i] = extrai_maximo(fprio);
  }

  destroi(fprio);
}

void desceHeap(int *vetor, int n, int k)
{
  int maior_filho;

  if(F_ESQ(k) < n)
  {
    maior_filho = F_ESQ(k);

    if(F_DIR(k) < n && vetor[F_ESQ(k)] < vetor[F_DIR(K)])
    {
      maior_filho = F_DIR(k);
    }

    if(vetor[k] < vetor[maior_filho])
    {
      troca(&vetor[k], &vetor[maior_filho]);
      desceHeap(vetor, n, maior_filho);
    }
  }
}

void heapSort(int *v, int n)
{
  int k;

  for(k = n/2; k >= 0; k--) /*transforma em heap*/
  {
    desce_no_heap(v, n, k);
  }

  while(n > 1) /* extrai o maximo*/
  {
    troca(&v[0], &v[n - 1]);
    n--;
    desce_no_heap(v, n, 0);
  }
}

### MergeSort ##################

void merge(int *v, int l, int m, int r)
{
  int aux[MAX];
  int  i = 1, j = m + 1, k = 0;

  while( i <= m && j <= r)
  {
    if(v[i] <= v[j])
    {
      aux[k++] = v[i++];
    }
    else
    {
      aux[k++] = v[j++];
    }
  }

  while(i <= m)
  {
    aux[k++] = v[i++];
  }

  while(j <= r)
  {
    aux[k++] = v[j++];
  }
}

void mergeSort(int *v, int l, int r)
{
  int m = (l + r)/2;

  if(l < r)
  {
    mergeSort(v, l, m);
    mergeSort(v, m+1, r);

    merge(v, l, m, r);
  }
}

####### QuickSort ################

int partition(int *v, int l, int r)
{
  int i, pivo = v[l], pos = r + 1;

  for(i = r; i >= l; i--)
  {
    if(v[i] >= pivo)
    {
      pos--;
      troca(&v[i], &v[pos]);
    }
  }

  return pos; 
}

void quickSort(int *v, int l, int r)
{
  int i;

  if(r <= l)
  {
    return;
  }

  i = partition(v, l, r);

  quickSort(v, l, i-1);
  quickSort(v, i+1, r);
}

 #### TABELA DE ESPALHAMENTO(HASHING) ################

- Metodo da divisao: soma de bits de uma string / tamanho M do hashing
  pegar o resto da divisao.

 # define MAX 1783

 typedef struct no *p_no;

 struct no
 {
   char chave[10];
   int dado;
   p_no prox;
 }

 typedef struct hash *p_hash;

 struct hash{
   p_no vetor[MAX];
 };

 int hash(char *chave)
 {
   int i, n = 0;

   for(i = 0; i < strlen(chave); i++)
   {
     n = (256 * n + chave[i]) % MAX;
   }

   return n;
 }

 void inserir(p_hash t, char *chave, int dado)
 {
   int n = hash(chave);
   t-> vetor[n] = inserir_lista(t->vetor[n], chave, dado);
 }

 void remover(p_hash t, char *chave)
 {
   int n = hash(chave);
   t->vetor[n] = remover_lista(t->vetor[n], chave);
 }

############ Grafo #############

- Objetos sao os vertices dos grafos.
- Conexoes entre os objetos sao as arestas do grafo
- (V,E) sendo V os vertices e E as arestas

- Adjacencia: dois vertices adjacentes sao 
que possuem arestas entre ele ou seja conexao
Obs: Nao precisa ficar lado a lado 
- Matriz de adjacencia: matriz em q 
a linha eh um vertice e a coluna eh outro vertice
e se for igualada a :
  1 - significa que ha conexao
  2 - siginifica que nao ha conexao


#### Com matriz de adjacencia #############

typedef grafo *p_grafo;

struct grafo{
  int **adj;
  int n;
}

p_grafo criar_grafo(int n)
{
  int i, j;

  p_grafo g = malloc(sizeof(struct grafo));

  g->n = n;
  g->adj = malloc(n * sizeof(int *));

  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      g->adj[i][j] = 0;
    }
  }

  return g;
}

p_grafo le_grafo()
{
  int n,m, i,u,v;
  p_grafo g;
  scanf("%d %d", &n, &m);
  g = criar_grafo(n);

  for(i = 0; i < n; i++)
  {
    scanf("%d %d", &u, &v);
    insere_aresta(g, u, v);
  }

}

void destroi_grafo(p_grafo g)
{
  int i;

  for(i = 0; i < g->n; i++)
    free(g->adj[i]);
  
  free(g->adj);
  free(g);
}

void insere_aresta(p_grafo f, int u, int v)
{
  g->adj[u][v] = 1;
  g->adj[v][u] = 1;
}

void remove_aresta(p_grafo g, int u, int v)
{
  g->adj[u][v] = 0;
  g->adj[v][u] = 0;
}

int tem_aresta(p_grafo f, int u, int v)
{
  return g->adj[u][v];
}

void imprime_arestas(p_grafo g)
{
  int u, v;

  for(u = 0; u < g->n; u++)
  {
    for(v = u+1; v < g->n; v++)
    {
      if(g->adj[u][v])
      {
        printf("{%d, %d}\n", u, v);
      }
    }
  }
}

int grau(p_grafo g, int u)
{
  int v, grau = 0;

  for(v = 0; v < g->n; v++)
  {
    if(g->adj[u][v])
    {
      grau++;
    }
  }

  return grau;
}

int mais_popular(p_grafo g)
{
  int u, max, grau_max, grau_atual;
  max = 0;
  grau_max = grau(g, 0);

  for(u = 1; u < g->n; u++)
  {
    grau_atual = grau(g, u);

    if(grau_atual > grau_max)
    {
      grau_max = grau_atual;
      max = u;
    }
  }

  return max;
}

void imprime_recomendacoes(p_grafo g, int u)
{
  int v, w;

  for(v = 0; v < g->n; v++)
  {
    if(g->adj[u][v])
    {
      for(w = 0; w < g->n; w++)
      {
        if(g->adj[v][w] && w != u && !g->adj[u][w])
        {
          printf("%d\n", w);
        }
      }

    }
  }
}

## Com lista de adjacencia ############


typedef struct no *p_no;

struct no
{
  int v;
  p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo{
  p_no *adjacencia;
  int n;
}

p_grafo criar_grafo(int n)
{
  int i;
  p_grafo g = malloc(sizeof(struct grafo));

  g->n = n;

  g->adjacencia = malloc(n * sizeof(p_no));

  for(i = 0; i < n; i++)
  {
    g->adjacencia[i] = NULL;
  }

  return g;
}

void libera_lista(p_no lista)
{
  if(lista != NULL)
  {
    libera_lista(lista->prox);
    free(lista);
  }
}

void destroi_grafo(p_grafo g)
{
  int i;

  for(i = 0; i < g->n; i++)
  {
    libera_lista(g ->adjacencia[i]);
  }

  free(g->adjacencia);
  free(g);
}

void insere_na_lista(p_grafo g, int u, int v)
{
  p_no novo = malloc(sizeof(struct no));

  novo->v = v;
  novo->prox = lista;

  return novo;
}

void insere_aresta(p_grafo g, int u, int v)
{
  g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
  g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
}

void remove_aresta(p_grafo g, int u, int v)
{
  p_no proximo;

  if(lista == NULL)
  {
    return NULL;
  }
  else if(lista->v == v)
  {
    proximo = lista->proximo;
    free(lista);
    return proximo;
  }
  else
  {
    lista->prox = remove_da_lista(lista->prox, v);
    return lista;
  }
}

void tem_aresta(p_grafo g, int u, int v)
{
  p_no t;

  for(t = g->adjacencia[u]; t != NULL; t = t->prox)
  {
    if(t->v == v)
    {
      return 1;
    }
  }

  return 0;
}

void imprime_arestas(p_grafo g)
{
  int u;
  p_no t;

  for(u = 0; u < g->n; u++)
  {
    for(t = g->adjacencia[u]; t != NULL; t = t->prox)
    {
      printf("{%d, %d}\n", u, t->v);
    }
  }
}

### Caminhando em percurso pelo grafo ##########

int existe_caminho(p_grafo g, int s, int t)
{
  int *visitados = malloc(g->n * sizeof(n));

  for(int i = 0; i < g->n; i++)
  {
    visitados[i] = 0;
  }

  int resultado = return existe_caminho_rec(g, s, t, visitados);
  free(visitados);
  return resultado;
}

int existe_caminho_rec(p_grafo g, int s, int t, int *visitados)
{
  visitados[s] = 1;

  if(s == t)
  {
    return 1;
  }
  else
  {
    for(int v = 0; v < g->n; v++)
    {
      if(g->adj[s][v] && !visitados[v] && existe_caminho_rec(g, v, t, visitados))
        {
          return 1;
        }
      
    }

    return 0;
  }
}

############## Algoritmos de ordenacao em GRAFO ##############3

######## Algoritmo de Dijkstra #######

## Com lista ligada ###

typedef struct no *p_no;

struct no
{
  int v;
  int peso;
  p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo{
  int n;
  p_no *adj;
};

### Heap Binario ########

typedef struct{
  int prioridade;
  int vertice;
} Item;

typedef struct{
  Item *v;
  int *indice;
  int n, tamanho;
}FP;

typedef FP *p_fp;


int *dijkstra(p_grafo g, int s)
{
  int v, *pai = malloc(g->n * sizeof(int));
  p_no t;
  p_fp h = criar_fprio(g->n);

  for(v = 0; v < g->n; v++)
  {
    pai[v] = -1;
    insere(h, v, INT_MAX);
  }

  pai[s] = s;
  diminuiprioridade(h, s, 0);

  while(!vazia(h))
  {
    v = extrai_minimo(h);

    if(prioridade(h, v) != INT_MAX)
    {
      for(t = g->adj[v]; t != NULL; t = t->prox)
      {
        if(prioridade(h, v) + t->peso < prioridade(h, t->v))
        {
          diminuiprioridade(h, t->v, prioridade(h,v) + t->peso);
          pai[t->v] = v;
        }
      }
    }
  }

  return pai;
}







