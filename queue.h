//
// Created by Leonardo Fuso on 20/03/19.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct {
    unsigned int size;
    unsigned int first_position;
    unsigned int last_position;
    int *elements;
} TQueue;

TQueue *produce_queue (unsigned int);
void queue (TQueue *, int);
int dequeue (TQueue *);
unsigned int size (TQueue *);
int is_empty (TQueue *);
int is_full (TQueue *);

#endif //QUEUE_H