#ifndef HELPER_H
#define HELPER_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_SIZE 51

typedef struct {
    unsigned int tarefa_par;
    unsigned int tarefa_impar;
} TPar;

typedef struct _TEntrada {
    unsigned int qtd_tarefas;
    unsigned int qtd_pares;
    char **tarefas;
    TPar **pares;
} TEntrada;

TEntrada *read_file (FILE *, unsigned int);

FILE *_open_file (char *);

unsigned int _count_lines (FILE *);

#endif //HELPER_H
