//
// Created by Leonardo Fuso on 19/03/19.
//

#include "grafo.h"

int _is_ciclico (TGrafo *, unsigned int, unsigned int);
void _check_ciclico (TGrafo *, unsigned int, int *);

TGrafo *produce_grafo (unsigned int qrd_vertices)
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

int _is_ciclico (TGrafo *g, unsigned int par, unsigned int impar)
{
  int *visitados = NULL;
  visitados = (int *) calloc (g->qtd_vertices, sizeof (int));
  _check_ciclico (g, impar, visitados);
  return visitados[par];
}

void _check_ciclico (TGrafo *g, unsigned int v, int *visitados)
{
  TNo *aux = NULL;
  int isVisitado = 0;
  /* Marca vértice como visitado */
  visitados[v] = 1;

  aux = g->lista_adjacencias[v];
  while (aux != NULL)
  {
    isVisitado = visitados[aux->vertice];
    if(!isVisitado) {
      _check_ciclico (g, aux->vertice, visitados);
    }
    aux = aux->proximo;
  }
}

int insert_aresta (TGrafo *g, unsigned int par, unsigned int impar)
{
  TNo *novo;
  TNo *aux;
  TNo *ant;

  int parRepetido = 0;
  int verticesIguais = 0;
  int isCiclico = 0;

  ant = NULL;
  aux = g->lista_adjacencias[par];

  verticesIguais = par == impar;
  if (verticesIguais)
  {
    printf ("TAREFAS [ %d, %d ] SÃO REPETIDAS\n", par, impar);
    return 1;
  }

  /* Se existe aux e aux != NULL */
  while (aux && aux->vertice <= impar)
  {
    /*
     * Se o grafo já tem a aresta
     * [ par - impar ], a função não faz nada.
     */
    parRepetido = aux->vertice == impar;
    if (parRepetido)
    {
      printf ("TAREFAS [ %d, %d ] JÁ INSERIDAS\n", par, impar);
      return 1;
    }

    ant = aux; /* guarda o anterior */
    aux = aux->proximo; /* anda para frente */
  }

  isCiclico = _is_ciclico (g, par, impar);
  if (isCiclico)
  {
    printf ("TAREFAS [ %d, %d ] FORMAM CICLOS\n", par, impar);
    return 1;
  }

  novo = (TNo *) calloc (1, sizeof (TNo));
  novo->vertice = impar;
  novo->proximo = aux;

  /* Se ant == NULL ou a lista está vazia ou devo inserir no início */
  if (ant == NULL)
    g->lista_adjacencias[par] = novo;
  else
    ant->proximo = novo;

  /* Atualiza o número de arestas */
  g->qtd_arestas++;

  return 0;
}

unsigned int grau_de_entrada (TGrafo *g, unsigned int w)
{
  int i;
  TNo *aux = NULL;
  int controle = g->qtd_vertices;
  unsigned int grau_de_entrada = 0;

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

void busca_largura (TGrafo *g, unsigned int v)
{
  /* Aloca array para guardar os vértices visitados */
  int *visitados = NULL;
  visitados = (int *) calloc ((size_t) g->qtd_vertices, sizeof (int));

  /* Cria uma instância de TQueue para armazenar a fila utilizada na 'busca_largura' */
  TQueue *q = NULL;
  q = produce_queue (g->qtd_vertices);

  /* Marca o vértice inicial como visitado */
  visitados[v] = 1;

  /* Guarda-o na fila */
  queue (q, v);

  /* Enquanto a fila não está vazia */
  TNo *proximo = NULL;
  while (!is_empty (q))
  {
    int u = dequeue (q);
    printf ("[ %i ]\n", u);

    /* Navega pelo Grafo de adjacências enfileirando os próximos vértices */
    proximo = g->lista_adjacencias[u];
    while (proximo)
    {
      if (!visitados[proximo->vertice])
      {
        visitados[proximo->vertice] = 1;
        queue (q, proximo->vertice);
      }
      proximo = proximo->proximo;
    }
  }
}

void free_graph (TGrafo *g)
{
  int i;
  for (i = 0; i < g->qtd_vertices; i++)
  {
    TNo *aux = NULL;
    TNo *proximo = NULL;
    aux = g->lista_adjacencias[i];
    while (aux != NULL)
    {
      proximo = aux->proximo;
      free (aux);
      aux = proximo;
    };
  }
  free (g);
}
