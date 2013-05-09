#ifndef CRIPTER_H
#define CRIPTER_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include <sys/stat.h>

/*Funzione che permette di far partire il cripter. 
il programma crea un thread di lettura, uno che genera stringhe a caso,
uno che cripta e decripta e un ultimo che stampa. */
void boot(int argc, char **argv);

#endif
