//
// Created by Leonardo Fuso on 17/03/19.
//

#include "ordenacao_topologica.h"

FILE *_open_file (char *filename);

unsigned int _count_lines (FILE *filePtr);

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
