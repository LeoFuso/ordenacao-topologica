//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

TGrafo *organiza_grafo (TEntrada *entrada);
void ordenar (char *filename)
{
  FILE *filePtr;
  unsigned int line_count = 0;

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
    printf ("[ %d ] %s\n", i, entrada->tarefas[i]);

  printf ("\nPARES\n");
  for (i = 0; i < entrada->qtd_pares; ++i)
    printf ("[ %d - %d ]\n", entrada->pares[i]->tarefa_par, entrada->pares[i]->tarefa_impar);

  organiza_grafo (entrada);

}

TGrafo *organiza_grafo (TEntrada *entrada)
{
  TGrafo *g = NULL;
  unsigned int qtdTarefas = 0;
  unsigned int qtdPares = 0;
  int parRepetido = 0;
  int formouCiclo = 0;

  qtdTarefas = entrada->qtd_tarefas;
  qtdPares = entrada->qtd_pares;

  g = produce_grafo (qtdTarefas);

  int i;
  for (i = 0; i < qtdPares; ++i)
  {
    unsigned int par = entrada->pares[i]->tarefa_par;
    unsigned int impar = entrada->pares[i]->tarefa_impar;

    parRepetido = insert_aresta (g, par, impar);
    if (parRepetido)
    {
      printf ("TAREFAS [ %d, %d ] JÁ INSERIDAS\n", par, impar);
    }

    formouCiclo = busca_ciclos (g);
    if  (formouCiclo)
    {
      printf ("TAREFAS [ %d, %d ] FORMAM CICLOS\n", par, impar);
      // TODO REMOVER ARESTA QUE FORMA CICLO
      exit (1);
    }
  }

  return NULL;
}
