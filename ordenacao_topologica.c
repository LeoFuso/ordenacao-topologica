//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

/* Usado para organizar os vértices
 * e seu grau de entrada.
 *
 * Como é de uso interno, não faz sentido
 * colocar no ordenacao_topologica.h
 */
typedef struct ComparisonNode {
    unsigned int vertice;
    unsigned int grau_de_entrada;
} ComparisonNode;

/* Funções de uso interno */
TGrafo *organiza_grafo (TEntrada *entrada);
ComparisonNode **ordena_tarefas (TGrafo *);
int comparator (const void *, const void *);

void
ordenar (char *filename)
{
  FILE *filePtr;
  unsigned int line_count = 0;
  TGrafo *grafo = NULL;

  filePtr = _open_file (filename);
  if (filePtr == NULL)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 31 - Encerrando...");
    exit (1);
  }
  else
    printf ("\nDocumento [ '%s' ] aberto com sucesso.\n", filename);

  line_count = _count_lines (filePtr);
  TEntrada *entrada = read_file (filePtr, line_count);

  if (!entrada)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 42 - Encerrando...");
    exit (1);
  }

  grafo = organiza_grafo (entrada);

  if (!grafo)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 50 - Encerrando...");
    exit (1);
  }

  ComparisonNode **tarefasOrdenadas = NULL;
  tarefasOrdenadas = ordena_tarefas (grafo);

  if (!tarefasOrdenadas)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 59 - Encerrando...");
    exit (1);
  }

  int i;
  for (i = 0; i < entrada->qtd_tarefas; ++i)
  {
    unsigned int tarefa = tarefasOrdenadas[i]->vertice;
    printf ("TAREFA [ %d ]: %s\n", tarefa + 1, entrada->tarefas[tarefa]);

  }
  free_graph (grafo);
}

/*
 * Baseado na TEntrada produzida pelo helper.c
 * Itera pelos pelos pares e insere as arestas.
 */
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

/*
 * Ordena um conjunto de tarefas baseado no seu grau de entrada,
 * e retorna uma ordem de execução de tarefas.
 */
ComparisonNode **
ordena_tarefas (TGrafo *g)
{
  unsigned int qtdTarefas = g->qtd_vertices;

  ComparisonNode *aux = NULL;
  ComparisonNode **nodes = NULL;
  nodes = (ComparisonNode **) calloc (qtdTarefas, sizeof (ComparisonNode *));

  unsigned int i;
  for (i = 0; i < qtdTarefas; ++i)
  {
    aux = (ComparisonNode *) calloc (1, sizeof (ComparisonNode));
    aux->vertice = i;
    aux->grau_de_entrada = grau_de_entrada (g, i + 1);
    nodes[i] = aux;
  }

  qsort (nodes, qtdTarefas, sizeof (ComparisonNode *), comparator);

  return nodes;
}

/*
 * Função de comparação utilizada pela
 * implementação do QuickSort.
 *
 * Realiza a comparação entre os graus de
 * entrada de um dois vértices distintos.
 */
int
comparator (const void *c1, const void *c2)
{
  ComparisonNode *o1 = *(ComparisonNode **) c1;
  ComparisonNode *o2 = *(ComparisonNode **) c2;

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
