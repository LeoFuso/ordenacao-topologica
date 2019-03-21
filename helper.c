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
  raw_line = (char *) calloc (MAX_LINE_SIZE, sizeof (char));

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
       (i < entrada->qtd_tarefas) &&
       (fgets (raw_line, MAX_LINE_SIZE, filePtr) != NULL);
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
       (i < entrada->qtd_pares) &&
       (fgets (raw_line, MAX_LINE_SIZE, filePtr) != NULL);
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

FILE *_open_file (char *filename)
{
  FILE *filePtr;

  if ((filePtr = fopen (filename, "r")) == NULL)
  {
    printf ("Documento não encontrado.\n");
    exit (0);
  }

  /*
   *  Verifica se o arquivo está vazio
   */
  fseek (filePtr, 0, SEEK_END);

  if (ftell (filePtr) == 0)
  {
    printf ("Documento está vazio.\n");
    exit (0);
  }

  rewind (filePtr);
  return filePtr;
}

unsigned int _count_lines (FILE *filePtr)
{
  unsigned int line_count = 0;
  char *raw_line = NULL;

  /*
   *  Aloca o espaço de memória necessário para uma linha do documento
   */
  raw_line = (char *) malloc (MAX_LINE_SIZE * sizeof (char) + 1);

  /*
   *  Conta quantas linhas o documento possui
   */
  while (fgets (raw_line, MAX_LINE_SIZE, filePtr) != NULL)
    line_count++;

  /*
   *  Rebobina o documento
   */
  rewind (filePtr);

  free (raw_line);
  return line_count;
}



