/*
  
  Anno Accademico: 2012-2013
  Corso di Studio: Scienze Informatiche - Sistemi Operativi
  Titolo: Progetto2 - Threads: Encrypter
  Autori: Bergamo Federico 151736, Martintoni Davide 151712, Passerini Luca 15

*/

// Definisco l'header
#ifndef CRIPTER_H
#define CRIPTER_H

// Includo le librerie necessarie
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <semaphore.h>

/* Funzione che permette di far partire il cripter. 
   il programma crea un thread di lettura, uno che genera stringhe a caso,
   uno che cripta e decripta e un ultimo che stampa. */
void boot(int argc, char **argv);

#endif
