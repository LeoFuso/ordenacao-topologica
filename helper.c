//
// Created by Leonardo Fuso on 17/03/19.
//

#include "helper.h"
TEntrada *read_file (FILE *filePtr, unsigned int line_count)
{
  /* Aloca TEntrada */
  TEntrada *entrada = (TEntrada *) calloc (1, sizeof (TEntrada));

  /* Serve como uma linha coringa para realizar a leitura do Documento */
  char *raw_line = NULL;

  /* Realiza a leitura da quantidade de tarefas */
  fgets (raw_line, MAX_LINE_SIZE, filePtr);

  /* Configura a quantidade de tarefas */
  entrada->qtd_tarefas = (unsigned int) strtol (raw_line, (char **) NULL, 10);

  /* Aloca uma coleção de tarefas */
  entrada->tarefas = (char **) calloc ((size_t) entrada->qtd_tarefas, sizeof (char *));

  unsigned int i;
  /* Aloca o espaço necessário para preencher as tarefas individuais */
  for (i = 0; i < entrada->qtd_tarefas; ++i)
    entrada->tarefas[i] = (char *) calloc (MAX_LINE_SIZE, sizeof (char));

  /* Realiza a leitura das tarefas */
  for (i = 0;
       (fgets (raw_line, MAX_LINE_SIZE, filePtr) != NULL) &&
       (i < entrada->qtd_tarefas);
       ++i)
  {
    /*
     *  Realiza a troca do character '\n' por '\0'
     */
    if (strchr (raw_line, '\n') != NULL)
      *(strchr (raw_line, '\n')) = '\0';

    stpcpy (entrada->tarefas[i], raw_line);
  }

  /* Realiza a leitura da quantidade de pares */
  fgets (raw_line, MAX_LINE_SIZE, filePtr);

  /* Configura a quantidade de pares */
  entrada->qtd_pares = (unsigned int) strtol (raw_line, (char **) NULL, 10);

  /* Aloca uma coleção de pares */
  entrada->pares = (TPar **) calloc ((size_t) entrada->qtd_pares, sizeof (TPar *));

  /* Aloca o espaço necessário para preencher os pares individuais */
  for (i = 0; i < entrada->qtd_pares; i++)
    entrada->pares[i] = (TPar *) calloc (1, sizeof (TPar *));

  /* Realiza a leitura dos pares */
  char delimiter[] = " ";
  char *pares;
  for (i = 0;
       (fgets (raw_line, MAX_LINE_SIZE, filePtr) != NULL) &&
       (i < entrada->qtd_pares);
       ++i)
  {
    /*
     *  Realiza a troca do character '\n' por '\0'
     */
    if (strchr (raw_line, '\n') != NULL)
      *(strchr (raw_line, '\n')) = '\0';

    pares = strtok (raw_line, delimiter);
    entrada->pares[i]->tarefa_par = (unsigned int) strtol (pares, (char **) NULL, 10);
    pares = strtok (NULL, delimiter);
    entrada->pares[i]->tarefa_impar = (unsigned int) strtol (pares, (char **) NULL, 10);
  }

  return entrada;
}


