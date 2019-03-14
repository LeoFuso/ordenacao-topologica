#include <stdio.h>
#include <stdlib.h>

// site para API C
//http://www.cplusplus.com/

/* Estrutura TNo */
typedef struct _TNo {
    int vertice;
    struct _TNo *proximo;
} TNo;

/* Estrutura TGrafo */
typedef struct {
    int V;
    int A;
    TNo **adj;
} TGrafo;

/* Declaração de funções */
TGrafo *init (int V);
void insertA (TGrafo *G, int v, int w);
void show (TGrafo *G);
int isPath (TGrafo *G, const int *seq, int k);
int indeg (TGrafo *G, int w);
void busca (TGrafo *G);
void busca_profundidade (TGrafo *G, TNo *, int visitado[]);
void freeGraph (TGrafo *);

/* Cliente */
int main ()
{

  TGrafo *grafo;
  int seq[] = {0, 2, 4, 1, 2};

  grafo = init (6);
  insertA (grafo, 0, 2);
  insertA (grafo, 0, 3);
  insertA (grafo, 0, 4);
  insertA (grafo, 2, 1);
  insertA (grafo, 2, 4);
  insertA (grafo, 3, 4);
  insertA (grafo, 3, 5);
  insertA (grafo, 4, 1);
  insertA (grafo, 4, 5);
  insertA (grafo, 5, 1);
  show (grafo);

  printf ("\nisPath = %d", isPath (grafo, seq, 4));

  int vertice = 3;
  int result = indeg (grafo, vertice);
  printf ("\nGrau de entrada [ %d ] -> %d ", vertice, result);

  printf ("\nBusca ->");
  busca (grafo);

  return 0;
}

/*
 * Cria e devolve uma nova estrutura
 * TGrafo, inicializa os atributos da estrutura,
 * cria uma matriz de matriz de adjacências para
 * [ V ] vértices e zera os valores para arestas.
 */
TGrafo *init (int V)
{
  TGrafo *g;

  g = (TGrafo *) calloc (1, sizeof (TGrafo));
  g->V = V;
  g->A = 0;

  /* Aloca um vetor de lista de adjacências */
  g->adj = (TNo **) calloc (V, sizeof (TNo *));
  return g;
}

/*
 * Cria uma aresta [ v - w ] no grafo. A função
 * supõe que [ v ] e [ w ] são distintos, positivos e
 * menores que [ G -> V ]. Se o grafo já tem a aresta
 * [ v - w ], a função não faz nada.
 * A função também atualiza a quantidade
 * de arestas no grafo.
 */
void insertA (TGrafo *G, int v, int w)
{
  TNo *novo, *aux, *ant;

  ant = NULL;
  aux = G->adj[v];

  /* Se existe aux e aux != NULL */
  while (aux && aux->vertice <= w)
  {

    /*
     * Se o grafo já tem a aresta
     * [ v - w ], a função não faz nada.
     */
    if (aux->vertice == w)
      return;

    ant = aux; /* guarda o anterior */
    aux = aux->proximo; /* anda para frente */
  }

  novo = (TNo *) calloc (1, sizeof (TNo));
  novo->vertice = w;
  novo->proximo = aux;

  /* Se ant == NULL ou a lista está vazia ou devo inserir no início */
  if (ant == NULL)
    G->adj[v] = novo;
  else
    ant->proximo = novo;

  /* Atualiza o número de arestas */
  G->A++;

}

/*
 * Calcula grau de entrada de um vértice
 */
int indeg (TGrafo *G, int w)
{
  int i;
  TNo *aux = NULL;
  int controle = G->V;
  int grau_de_entrada = 0;

  for (i = 0; i < controle; i++)
  {
    aux = G->adj[i];
    while (aux && aux->vertice)
    {
      if (aux->vertice == w)
      {
        grau_de_entrada++;
      }
      aux = aux->proximo; /* anda para frente */
    }
  }
  return grau_de_entrada;
}

/*
 * Verifica se uma sequência de vértices é um caminho
 */
int isPath (TGrafo *G, const int *seq, int k)
{
  int i;
  for (i = 0; i < k; i++)
  {
    int v = seq[i];
    int w = seq[i + 1];

    /* a partir da entrada [ v ] verifica os seus adjacentes */
    TNo *aux = G->adj[v];
    while (aux && aux->vertice != w)
      aux = aux->proximo;

    /*
     * se  [ w ] não está na lista [ v ], não existe aresta e
     * consequentemente, não existe caminho
     */
    if (aux == NULL)
      return 0;

  }

  /* É caminho */
  return 1;
}

/*
 * Para cada vértice  [ V ] do grafo, esta função
 * imprime, em uma linha, todos os vértices
 * adjacentes à [ V ].
 */
void show (TGrafo *G)
{
  int i;
  printf ("Vértices [ %d ] e Arestas [ %d ]\n\n", G->V, G->A);
  for (i = 0; i < G->V; i++)
  {
    TNo *aux;
    printf ("Vértice [ %d ] -> ", i);

    /* para cada entrada da lista pega o início da lista */
    aux = G->adj[i];

    /* enquanto não chegar ao final da lista */
    while (aux != NULL)
    {
      printf ("%d ", aux->vertice);
      aux = aux->proximo;
    }
    printf ("\n");
  }
}

void busca (TGrafo *G)
{
  int qtdVertices = G->V;

  /* Primeiro índice será ignorado */
  int visitado[qtdVertices];

  int i;
  for (i = 0; i < qtdVertices; i++)
  {
    visitado[i] = 0;
  }

  for (i = 0; i < qtdVertices; i++)
  {
    TNo *aux = NULL;
    aux = G->adj[i];
    int debug = aux->vertice;
    busca_profundidade (G, aux, visitado);
  }
  visitado;

}
void busca_profundidade (TGrafo *G, TNo *V, int visitado[])
{
  int vertice = V->vertice;
  int visitadoAddress = vertice - 1;
  int isVisitado = visitado[visitadoAddress];
  if (isVisitado)
    return;

  /* Marca V como visitado */
  visitado[visitadoAddress] = 1;

  /* Imprime V */
  printf (" %d", vertice);

  TNo *aux = NULL;
  aux = V->proximo;
  while (aux != NULL)
  {
    busca_profundidade (G, aux, visitado);
    aux = aux->proximo;
  }
}

void freeGraph (TGrafo *G)
{

  int i;
  for (i = 0; i < G->V; i++)
  {
    TNo *aux;
    TNo *proximo;
    aux = G->adj[i];
    do
    {
      proximo = aux->proximo;
      free (aux);
    }
    while (proximo != NULL);
  }
}
