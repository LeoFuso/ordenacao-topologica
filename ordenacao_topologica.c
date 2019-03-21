//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

TGrafo *organiza_grafo (TEntrada *entrada);
int *ordena_tarefas (TGrafo *);
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

  int * tarefasOrdenadas = ordena_tarefas (grafo);

  for (i = 0; i < entrada->qtd_tarefas; ++i)
  {
    printf ("Tarefa [ %d ]\n", tarefasOrdenadas[i] + 1);
  }
}

int
comparator (const void *c1, const void *c2)
{
  int o1 = *(int*) c1;
  int o2 = *(int*) c2;

  if (o1 > o2)
    return 1;
  else if (o1 < o2)
    return -1;
  else
    return 0;
}

int *ordena_tarefas (TGrafo *g)
{

  unsigned int qtdTarefas = g->qtd_vertices;

  int *tarefas = NULL;
  tarefas = (int *) calloc (qtdTarefas, sizeof (int));

  unsigned int grau_aux = 0;
  unsigned int i;
  for (i = 0; i < qtdTarefas; ++i)
    tarefas[i] = grau_de_entrada (g, i);

  qsort (tarefas, qtdTarefas, sizeof (int), comparator);

  return tarefas;
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
