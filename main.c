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
TGrafo *grow (TGrafo *G, int V);
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
  int seq[] = {0, 2, 4, 5, 1};

  grafo = init (6);
  insertA (grafo, 0, 2);
  insertA (grafo, 0, 4);
  insertA (grafo, 0, 3);
  insertA (grafo, 2, 1);
  insertA (grafo, 2, 4);
  insertA (grafo, 3, 4);
  insertA (grafo, 3, 5);
  insertA (grafo, 4, 1);
  insertA (grafo, 4, 5);
  insertA (grafo, 5, 1);
  show (grafo);

  printf ("\nisPath = %d", isPath (grafo, seq, 4));

  int vertice = 1;
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
  g->lista_adjacencias = (TNo **) calloc (V, sizeof (TNo *));
  return g;
}

TGrafo *grow (TGrafo *G, int V)
{
  /* Aloca um vetor de lista de adjacências */
  G->lista_adjacencias = (TNo **) realloc (G->lista_adjacencias, sizeof (TNo *) * (G->V + V));
  G->V += V;
  return G;
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
  aux = G->lista_adjacencias[v];

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
    G->lista_adjacencias[v] = novo;
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
    aux = G->lista_adjacencias[i];
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
    TNo *aux = G->lista_adjacencias[v];
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
    aux = G->lista_adjacencias[i];

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
  int qtdVertices = (G->V) + 1;

  /* Primeiro índice será ignorado */
  int visitado[qtdVertices];

  int i;
  for (i = 0; i < qtdVertices; i++)
  {
    visitado[i] = 0;
  }

  TNo *root = NULL;
  root = G->lista_adjacencias[0];
  visitado[0] = 1;
  printf (" %d", 0);
  while (root != NULL)
  {
    busca_profundidade (G, root, visitado);
    root = root->proximo;
  }

  printf ("\nVisitado -> [ ");
  for (i = 0; i < qtdVertices - 1; i++)
  {
    printf ("%d ", visitado[i]);
  }
  printf ("]");
}
void busca_profundidade (TGrafo *G, TNo *V, int visitado[])
{
  int vertice = V->vertice;
  int isVisitado = visitado[vertice];
  if (isVisitado)
  {
    return;
  }

  /* Imprime o Vértice */
  printf (" %d", vertice);

  /* Marca o Vértice como visitado */
  visitado[vertice] = 1;

  /* Desce mais uma camada no Grafo */
  TNo *proximo = NULL;
  proximo = G->lista_adjacencias[vertice];
  while (proximo != NULL)
  {
    busca_profundidade (G, proximo, visitado);
    /* Não há mais como se aprofundar, busca o próximo Vértice */
    proximo = proximo->proximo;
  }
}

void freeGraph (TGrafo *G)
{
  int i;
  for (i = 0; i < G->V; i++)
  {
    TNo *aux;
    TNo *proximo;
    aux = G->lista_adjacencias[i];
    do
    {
      proximo = aux->proximo;
      free (aux);
    }
    while (proximo != NULL);
  }
}
