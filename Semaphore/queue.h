/*
  
  Anno Accademico: 2012-2013
  Corso di Studio: Scienze Informatiche - Sistemi Operativi
  Titolo: Progetto2 - Threads: Encrypter
  Autori: Bergamo Federico 151736, Martintoni Davide 151712, Passerini Luca 15

*/

// Definisco l'header di queue
#ifndef QUEUE_H
#define QUEUE_H

// Includo le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definisco la struttura della Queue
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        char ** elements;
}Queue;

// Definisco la firma delle varie funzioni e procedure presenti in queue.c
Queue * createQueue(int maxElements);
void Dequeue(Queue *Q);
char * front(Queue *Q);
void Enqueue(Queue *Q,char * element);
bool isEmpty(Queue * Q);

#endif
