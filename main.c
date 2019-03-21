#include "ordenacao_topologica.h"

int
main (int argc, char *argv[])
{

  /*Tenta ler o documento 'entrada'*/
  if (argc != 2)
  {
    printf ("Sintaxe: main [entrada] (qualquer extensão é implícita) \n");
    printf ("Nenhum arquivo de entrada encontrado especificado. Encerrando o programa... \n");
    exit (0);
  }

  ordenar (argv[1]);

  return 0;
}
