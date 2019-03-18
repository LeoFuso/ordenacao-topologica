#ifndef ORDTOP_H
#define ORDTOP_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_SIZE 50

typedef struct _TNo {
    int vertice;
    struct _TNo *proximo;
} TNo;

typedef struct {
    int qtd_vertices;
    int qtd_arestas;
    TNo **lista_adjacencias;
} TGrafo;

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

TEntrada * read_file(FILE *, unsigned int);

#endif //ORDTOP_H
