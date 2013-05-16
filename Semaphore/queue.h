#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        char ** elements;
}Queue;

Queue * createQueue(int maxElements);
void Dequeue(Queue *Q);
char * front(Queue *Q);
void Enqueue(Queue *Q,char * element);
bool isEmpty(Queue * Q);

#endif
