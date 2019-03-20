#include <stdio.h>
#include <stdlib.h>
#include "ordenacao_topologica.h"
/* Cliente */
/*
int
main (int argc, char *argv[])
{
  *//*
   *  Tenta ler o documento 'entrada'
   *//*
  if (argc != 2)
  {
    printf ("Sintaxe: main [documento] (qualquer extensão é implícita) \n");
    printf ("Nenhum arquivo de entrada encontrado especificado. Encerrando o programa... \n");
    exit (0);
  }

  ordenar (argv[1]);

  return 0;
}
 */

int main ()
{

  TGrafo *grafo;

  grafo = init (6);
  insert_aresta (grafo, 0, 2);
  insert_aresta (grafo, 0, 4);
  insert_aresta (grafo, 0, 3);
  insert_aresta (grafo, 2, 1);
  insert_aresta (grafo, 2, 4);
  insert_aresta (grafo, 3, 4);
  insert_aresta (grafo, 3, 5);
  insert_aresta (grafo, 4, 1);
  insert_aresta (grafo, 4, 5);
  insert_aresta (grafo, 5, 1);

  busca_largura (grafo, 1);

  return 0;
}

