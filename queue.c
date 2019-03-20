//
// Created by Leonardo Fuso on 20/03/19.
//

#include "queue.h"
TQueue *produce_queue (unsigned int qtd_elements)
{
  TQueue *queue = (TQueue *) calloc (1, sizeof (TQueue));
  queue->first_position = 0;
  queue->last_position = 0;
  queue->size = qtd_elements;
  queue->elements = (int *) calloc (qtd_elements, sizeof (unsigned int));
  return queue;
}

void queue (TQueue *q, int element)
{
  q->elements[q->last_position++] = element;
}

int dequeue (TQueue *q)
{
  return q->elements[q->first_position++];
}

int is_empty (TQueue *q)
{
  return q->first_position == q->last_position;
}

int is_full (TQueue *q)
{
  return q->last_position = q->size;
}
