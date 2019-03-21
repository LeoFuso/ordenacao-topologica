//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

struct ComparisonNode {
    unsigned int vertice;
    unsigned int grau_de_entrada;
};

TGrafo *organiza_grafo (TEntrada *entrada);
struct ComparisonNode **ordena_tarefas (TGrafo *);
int comparator (const void *, const void *);

void ordenar (char *filename)
{
  FILE *filePtr;
  unsigned int line_count = 0;
  TGrafo *grafo = NULL;

  filePtr = _open_file (filename);
  if (filePtr == NULL)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 13 - Encerrando...");
    exit (1);
  }
  else
    printf ("\nDocumento [ '%s' ] aberto com sucesso.\n", filename);

  line_count = _count_lines (filePtr);
  TEntrada *entrada = read_file (filePtr, line_count);

  if (!entrada)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 24 - Encerrando...");
    exit (1);
  }

  int i;
  printf ("\nTAREFAS\n");
  for (i = 0; i < entrada->qtd_tarefas; ++i)
    printf ("[ %d ] %s\n", i + 1, entrada->tarefas[i]);

  printf ("\nPARES\n");
  for (i = 0; i < entrada->qtd_pares; ++i)
    printf ("[ %d - %d ]\n", entrada->pares[i]->tarefa_par, entrada->pares[i]->tarefa_impar);

  grafo = organiza_grafo (entrada);
  show (grafo);

  printf ("%d", grau_de_entrada (grafo, 12));

  struct ComparisonNode **tarefasOrdenadas = ordena_tarefas (grafo);

  for (i = 0; i < entrada->qtd_tarefas; ++i)
  {
    printf ("Tarefa [ %d ]\n", tarefasOrdenadas[i]->vertice + 1);
  }
}

int
comparator (const void *c1, const void *c2)
{
  struct ComparisonNode *o1 = *(struct ComparisonNode **) c1;
  struct ComparisonNode *o2 = *(struct ComparisonNode **) c2;

  if (o1->grau_de_entrada > o2->grau_de_entrada)
    return 1;
  else if (o1->grau_de_entrada < o2->grau_de_entrada)
    return -1;
  else if ((o1->grau_de_entrada = o2->grau_de_entrada) && (o1->vertice > o2->vertice))
    return 1;
  else if ((o1->grau_de_entrada = o2->grau_de_entrada) && (o1->vertice < o2->vertice))
    return -1;
  else
    return 0;
}

struct ComparisonNode **
ordena_tarefas (TGrafo *g)
{
  unsigned int qtdTarefas = g->qtd_vertices;

  struct ComparisonNode *aux = NULL;
  struct ComparisonNode **nodes = NULL;
  nodes = (struct ComparisonNode **) calloc (qtdTarefas, sizeof (struct ComparisonNode *));

  unsigned int grau_aux = 0;
  unsigned int i;
  for (i = 0; i < qtdTarefas; ++i)
  {
    aux = (struct ComparisonNode *) calloc (1, sizeof (struct ComparisonNode));
    aux->vertice = i;
    aux->grau_de_entrada = grau_de_entrada (g, i);
    nodes[i] = aux;
  }

  qsort (nodes, qtdTarefas, sizeof (struct ComparisonNode *), comparator);

  return nodes;
}

TGrafo *organiza_grafo (TEntrada *entrada)
{
  TGrafo *g = NULL;
  unsigned int qtdTarefas = 0;
  unsigned int qtdPares = 0;

  qtdTarefas = entrada->qtd_tarefas;
  qtdPares = entrada->qtd_pares;

  g = produce_grafo (qtdTarefas);

  int i;
  for (i = 0; i < qtdPares; ++i)
  {
    unsigned int par = entrada->pares[i]->tarefa_par;
    unsigned int impar = entrada->pares[i]->tarefa_impar;

    insert_aresta (g, par, impar);
  }

  return g;
}
