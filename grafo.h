//
// Created by Leonardo Fuso on 19/03/19.
//

#ifndef GRAFO_H
#define GRAFO_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct _TNo {
    unsigned int vertice;
    struct _TNo *proximo;
} TNo;

typedef struct {
    unsigned int qtd_vertices;
    int qtd_arestas;
    TNo **lista_adjacencias;
} TGrafo;

/*
 * Cria e devolve uma nova estrutura
 * TGrafo, inicializa os atributos da estrutura,
 * cria uma matriz de matriz de adjacências para
 * [ unsigned int ] vértices e zera os valores para arestas.
 */
TGrafo *produce_grafo (unsigned int);

/*
 * Para uma estrutura TGrafo existente, acrescenta
 * uma quantidade [ unsigned int ] de vértices.
 */
TGrafo *grow (TGrafo *, unsigned int);

/*
 * Cria uma aresta [ unsigned int a - unsigned int b] na
 * estrutura TGrafo.
 * A função supõe que [ unsigned int a ] e [ unsigned int b ]
 * são distintos, positivos e menores que [ g -> qtd_vertices ].
 * Se o grafo já tem a aresta [ unsigned int a - unsigned int b ],
 * a função não faz nada e retorna '1'. Caso a inserção seja
 * bem sucedida, retorna '0'.
 * A função também atualiza a quantidade
 * de arestas na estrutura  TGrafo.
 */
int insert_aresta (TGrafo *, unsigned int, unsigned int);

/*
 * Calcula o grau de entrada para uma estrutura
 * TGrafo para um vértice de valor [ unsigned int ],
 * se sucedida, retorna o seu grau de entrada.
 */
unsigned int grau_de_entrada (TGrafo *, unsigned int);

/*
 * Verifica se uma sequência de vértices
 * na forma de um array é um caminho
 * válido na estrutura TGrafo criada.
 */
int is_caminho (TGrafo *, const int *, unsigned int);

/*
 * Para cada vértice  [ g->vertice ] do grafo, esta função
 * imprime, em uma linha, todos os vértices
 * adjacentes à [ g->vertice ].
 */
void show (TGrafo *);

void busca_profundidade (TGrafo *);

int busca_ciclos (TGrafo *);

void busca_largura(TGrafo *, unsigned int);

void free_graph (TGrafo *);

#endif //GRAFO_H
