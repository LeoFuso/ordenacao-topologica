//
// Created by Leonardo Fuso on 19/03/19.
//

#include "grafo.h"

void _inner_busca_profundidade (TGrafo *, TNo *, int []);
int _inner_busca_ciclos (TGrafo *, TNo *, int []);

TGrafo *init (unsigned int qrd_vertices)
{
  TGrafo *g;

  g = (TGrafo *) calloc (1, sizeof (TGrafo));
  g->qtd_vertices = qrd_vertices;
  g->qtd_arestas = 0;

  /* Aloca um vetor de lista de adjacências */
  g->lista_adjacencias = (TNo **) calloc (qrd_vertices, sizeof (TNo *));
  return g;
}

TGrafo *grow (TGrafo *G, unsigned int qtd_vertices_adicionais)
{
  /* Aloca um vetor de lista de adjacências */
  G->lista_adjacencias = (TNo **) realloc (G->lista_adjacencias,
                                           sizeof (TNo *) * (G->qtd_vertices + qtd_vertices_adicionais));
  G->qtd_vertices += qtd_vertices_adicionais;
  return G;
}

int insert_aresta (TGrafo *g, unsigned int v, unsigned int w)
{
  TNo *novo;
  TNo *aux;
  TNo *ant;

  ant = NULL;
  aux = g->lista_adjacencias[v];

  /* Se existe aux e aux != NULL */
  while (aux && aux->vertice <= w)
  {
    /*
     * Se o grafo já tem a aresta
     * [ v - w ], a função não faz nada.
     */
    if (aux->vertice == w)
      return 1;

    ant = aux; /* guarda o anterior */
    aux = aux->proximo; /* anda para frente */
  }

  novo = (TNo *) calloc (1, sizeof (TNo));
  novo->vertice = w;
  novo->proximo = aux;

  /* Se ant == NULL ou a lista está vazia ou devo inserir no início */
  if (ant == NULL)
    g->lista_adjacencias[v] = novo;
  else
    ant->proximo = novo;

  /* Atualiza o número de arestas */
  g->qtd_arestas++;

  return 0;
}

int grau_de_entrada (TGrafo *g, unsigned int w)
{
  int i;
  TNo *aux = NULL;
  int controle = g->qtd_vertices;
  int grau_de_entrada = 0;

  for (i = 0; i < controle; i++)
  {
    aux = g->lista_adjacencias[i];
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

int is_caminho (TGrafo *g, const int *seq, unsigned int k)
{
  int i;
  for (i = 0; i < k; i++)
  {
    int v = seq[i];
    int w = seq[i + 1];

    /* a partir da entrada [ v ] verifica os seus adjacentes */
    TNo *aux = g->lista_adjacencias[v];
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

void show (TGrafo *g)
{
  int i;
  printf ("Vértices [ %d ] e Arestas [ %d ]\n\n", g->qtd_vertices, g->qtd_arestas);
  for (i = 0; i < g->qtd_vertices; i++)
  {
    TNo *aux;
    printf ("Vértice [ %d ] -> ", i);

    /* para cada entrada da lista pega o início da lista */
    aux = g->lista_adjacencias[i];

    /* enquanto não chegar ao final da lista */
    while (aux != NULL)
    {
      printf ("%d ", aux->vertice);
      aux = aux->proximo;
    }
    printf ("\n");
  }
}

void busca_profundidade (TGrafo *g)
{
  /* Primeiro índice será ignorado */
  int qtdVertices = (g->qtd_vertices) + 1;
  int visitado[qtdVertices];

  int i;
  for (i = 0; i < qtdVertices; i++)
  {
    visitado[i] = 0;
  }

  /* Escolhe um Nó como Root */
  TNo *root = NULL;
  root = g->lista_adjacencias[0];

  /* Marca como visitado */
  visitado[0] = 1;
  printf (" %d", 0);

  /* Começa a busca */
  while (root != NULL)
  {
    _inner_busca_profundidade (g, root, visitado);
    root = root->proximo;
  }

  /* Imprime as visitas */
  printf ("\nVisitado -> [ ");
  for (i = 0; i < qtdVertices - 1; i++)
  {
    printf ("%d ", visitado[i]);
  }
  printf ("]");
}

void _inner_busca_profundidade (TGrafo *g, TNo *no, int visitado[])
{
  int vertice = no->vertice;
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
  proximo = g->lista_adjacencias[vertice];
  while (proximo != NULL)
  {
    _inner_busca_profundidade (g, proximo, visitado);
    /* Não há mais como se aprofundar, busca o próximo Vértice */
    proximo = proximo->proximo;
  }
}

int busca_ciclos (TGrafo *g)
{
  /* Primeiro índice será ignorado */
  int qtdVertices = (g->qtd_vertices) + 1;
  int visitado[qtdVertices];

  int i;
  for (i = 0; i < qtdVertices; i++)
  {
    visitado[i] = 0;
  }

  /* Escolhe um Nó como Root */
  TNo *root = NULL;
  root = g->lista_adjacencias[0];

  /* Marca como visitado */
  visitado[0] = 1;

  int hasCiclos = 0;
  /* Começa a busca */
  while (root != NULL)
  {
    hasCiclos = _inner_busca_ciclos (g, root, visitado);

    if (hasCiclos)
    {
      return 1;
    }

    root = root->proximo;
  }
  return 0;
}

int _inner_busca_ciclos (TGrafo *g, TNo *no, int visitado[])
{
  int hasCiclos = 0;
  int vertice = no->vertice;
  int isVisitado = visitado[vertice];

  if (isVisitado)
  {
    return 1;
  }

  /* Marca o Vértice como visitado */
  visitado[vertice] = 1;

  /* Desce mais uma camada no Grafo */
  TNo *proximo = NULL;
  proximo = g->lista_adjacencias[vertice];
  while (proximo != NULL)
  {
    hasCiclos = _inner_busca_ciclos (g, proximo, visitado);
    if (hasCiclos)
    {
      return 1;
    }
    /* Não há mais como se aprofundar, busca o próximo Vértice */
    proximo = proximo->proximo;
  }

  return 0;
}

void free_graph (TGrafo *g)
{
  int i;
  for (i = 0; i < g->qtd_vertices; i++)
  {
    TNo *aux;
    TNo *proximo;
    aux = g->lista_adjacencias[i];
    do
    {
      proximo = aux->proximo;
      free (aux);
    }
    while (proximo != NULL);
  }
}

