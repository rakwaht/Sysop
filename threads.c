#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_STRING_SIZE 100

int dim;
char s[MAX_STRING_SIZE];
char r[MAX_STRING_SIZE];
char Se[MAX_STRING_SIZE];
char Sd[MAX_STRING_SIZE];

void* reader(void* arg);
void* randomize(void* args);
void* decript(void* args);

int main(){

pthread_t Tr;
pthread_create(&Tr,NULL,&reader,NULL);

if(pthread_join(Tr,NULL)){
	printf("Aborted \n");
	exit(-1);
}

printf("Done \n");

return 0;
}

void* reader(void* arg){
	printf("Dammi una stringa! \n");	
	gets(s);
	dim=0;
	while(s[dim]!='\0'){
		dim++;
	}
	pthread_t Te;
	pthread_create(&Te,NULL,&randomize,NULL);
	
	if(pthread_join(Te,NULL)){
		printf("Aborted \n");
		exit(-1);
	}

	return NULL;
}

void* randomize(void* args){
	int i=0;
	int data = open("/dev/random");
	int myrandomint;
	while(i<dim){
		read(data, &myrandomint, sizeof myrandomint);
		myrandomint = myrandomint%63;
		if(myrandomint<0) myrandomint = -myrandomint;
		myrandomint += 64;		
		//printf("random int: %d  %c\n", myrandomint,(char) myrandomint);		
		r[i] = myrandomint;
		i++;
	}
	printf("R: %s\n",r);
	i=0;
	while(i<dim){
		Se[i] = r[i] ^ s[i];
		i++;
	}
	printf("Se: %s\n",Se);
	
	pthread_t Td;
	pthread_create(&Td,NULL,&decript,NULL);
	
	if(pthread_join(Td,NULL)){
		printf("Aborted \n");
		exit(-1);
	}
	
	return NULL;
}

void* decript(void* args){
	int i=0;
	while(i<dim){
		Sd[i] = r[i] ^ Se[i];
		i++;
	}
	printf("Sd: %s \n",Sd);
	return NULL;
}
