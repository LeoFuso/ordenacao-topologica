#include <stdio.h>
#include <stdlib.h>
#include "ordenacao_topologica.h"
/* Cliente */
int
main (int argc, char *argv[])
{
  /*
   *  Tenta ler o documento 'entrada'
   */
  if (argc != 2)
  {
    printf ("Sintaxe: main [documento] (qualquer extensão é implícita) \n");
    printf ("Nenhum arquivo de entrada encontrado especificado. Encerrando o programa... \n");
    exit (0);
  }

  ordenar (argv[1]);

  return 0;
}

/*
int main ()
{

  TGrafo *grafo;
  int seq[] = {0, 2, 4, 5, 1};

  grafo = init (6);
  insertA (grafo, 0, 2);
  insertA (grafo, 0, 4);
  insertA (grafo, 0, 3);
  insertA (grafo, 2, 1);
  insertA (grafo, 2, 4);
  insertA (grafo, 3, 4);
  insertA (grafo, 3, 5);
  insertA (grafo, 4, 1);
  insertA (grafo, 4, 5);
  insertA (grafo, 5, 1);
  show (grafo);

  printf ("\nisPath = %d", isPath (grafo, seq, 4));

  int vertice = 1;
  int result = indeg (grafo, vertice);
  printf ("\nGrau de entrada [ %d ] -> %d ", vertice, result);

  printf ("\nBusca ->");
  busca (grafo);

  return 0;
}
*/

