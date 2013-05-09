/*
Anno Accademico: 2012-2013
Corso di Studio: Scienze Informatiche - Sistemi Operativi
Progetto: Progetto2 Threads: Encrypter
Autori: Bergamo Federico 151736, Martintoni Davide 151712, Passerini Luca 151838
*/

//cripter.h: file header del nostro progetto

//Definiamo cripter.h
#ifndef CRIPTER_H
#define CRIPTER_H

//Includiamo le librerie necessarie
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include <sys/stat.h>
#include <stdbool.h>

//Funzione che permette di inizializzare il cripter. Da utilizzare in un ipotetico 'main()' 
void boot(int argc, char **argv);

#endif
