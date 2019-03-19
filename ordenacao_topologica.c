//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

void ordenar (char *filename)
{
  FILE *filePtr;
  unsigned int line_count = 0;

  filePtr = _open_file (filename);
  if (filePtr == NULL)
  {
    printf ("Comportamento não esperado: ordenacao_topologica.c 17 - Encerrando...");
    exit (1);
  }
  else
    printf ("\nDocumento [ '%s' ] aberto com sucesso.\n", filename);

  line_count = _count_lines (filePtr);
  TEntrada *entrada = read_file (filePtr, line_count);

  int i;

  printf("\nTAREFAS\n");
  for(i = 0; i < entrada->qtd_tarefas; ++i)
    printf("[ %d ] %s\n", i, entrada->tarefas[i]);

  printf("\nPARES\n");
  for(i = 0; i < entrada->qtd_pares; ++i)
    printf("[ %d - %d ]\n", entrada->pares[i]->tarefa_par, entrada->pares[i]->tarefa_impar);
}
