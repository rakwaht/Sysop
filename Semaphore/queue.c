/*
  
  Anno Accademico: 2012-2013
  Corso di Studio: Scienze Informatiche - Sistemi Operativi
  Titolo: Progetto2 - Threads: Encrypter
  Autori: Bergamo Federico 151736, Martintoni Davide 151712, Passerini Luca 15

*/

// Questo codice ci permette di definire la struttura della coda e le varie funzioni ad essa associate.

#include "queue.h"

/* 
   Questa funzione inizializza la queue e i vari parametri:
   - elements: è un puntatore a stringa;
   - size: è la grandezza attuale della coda;
   - capacity: è la capacità massima della coda;
   - font/rear: sono rispettivamente la testa e la coda;
*/
Queue * createQueue(int maxElements){
  Queue *Q;
  Q = (Queue *)malloc(sizeof(Queue));
  Q->elements = (char **)malloc(sizeof(char *)*maxElements);
  Q->size = 0;
  Q->capacity = maxElements;
  Q->front = 0;
  Q->rear = -1;
  return Q;
}

// Dequeue toglie l'elemento in coda
void Dequeue(Queue *Q){
  if(Q->size==0)
    {
      return;
    }
  else
    {
      Q->size--;
      Q->front++;
      if(Q->front==Q->capacity)
	{
	  Q->front=0;
	}
    }
  return;
}

// Front restituisce l'elemento in coda
char * front(Queue *Q)
{
  if(Q->size==0)
    {
      return NULL;
    }
  return Q->elements[Q->front];
}

// Enqueue aggiunge un elemento alla coda
void Enqueue(Queue *Q,char * element)
{
  if(Q->size == Q->capacity)
    {
      return NULL;
    }
  else
    {
      Q->size++;
      Q->rear = Q->rear + 1;
      if(Q->rear == Q->capacity)
	{
	  Q->rear = 0;
                }
      Q->elements[Q->rear] = element;
    }
  return;
}

// isEmpty controlla se la coda è vuota
bool isEmpty(Queue * Q){
	if(Q->size == 0){
		return true;
	}
	else return false;
}
