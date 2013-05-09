#include"cripter.h"


#define MAX_STRING_SIZE 100

struct thread_args{    /* Used as argument to thread functions */
	char * s;
	char * r;
	char * Se;
	char * Sd;    
};

int dim;
time_t timer;

void* reader(void* arg);
void* randomize(void* args);
void* decript(void* args);
void* print_string(void* args);
void initDebugMode();
void openLogFile();
void quitLog();
bool debugFlag = false;
FILE * Trlog;
FILE * Telog;
FILE * Twlog;
FILE * Tdlog;
	

void boot(int argc, char **argv){
	char a = getopt(argc,argv,"dh");
	 switch (a)
           {
           case 'd':
             debugFlag = true;
	     openLogFile();
	     initDebugMode();
             break;
           case 'h':
	     printf("Here some instructions \n");
	     exit(0);             
	     break;
           case '?':
             printf("Unknown option character. Type -h option to know how it work. \n");
             exit(1);
           default:
	     openLogFile();
             break;
           }
	
	//richiamo procedura di lettura	
	pthread_t Tr;
	pthread_create(&Tr,NULL,&reader,NULL);

	if(pthread_join(Tr,NULL)){
		fprintf (Trlog, "Aborted at %s",ctime (&timer));
		quitLog();
		exit(-1);
	}
}

void* reader(void* arg){
	int attivo=1;
	
	do{
		struct thread_args stringhe;		
		printf("Dammi una stringa! \n");
		char buffer[MAX_STRING_SIZE];
		gets(buffer);
		stringhe.s = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
		stringhe.r = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
		stringhe.Se = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
		stringhe.Sd = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
		strcpy(stringhe.s,buffer);
		dim=0;
		while(stringhe.s[dim]!='\0'){
			dim++;
		}
		if(strcmp(stringhe.s,"quit")==0){
			attivo=0;
		}
		else{
			time(&timer);
			if(debugFlag) fprintf (Trlog, "Read a string at %s",ctime (&timer));
			
			pthread_t Te;
			pthread_create(&Te,NULL,&randomize,&stringhe);
		
			if(pthread_join(Te,NULL)){
				fprintf (Telog, "Aborted at %s",ctime (&timer));
				quitLog();
				exit(-1);
			}
		}
	}while(attivo==1);
	quitLog();
	return NULL;
}

void* randomize(void* args){
	int i=0;
	int myrandomint;
	int data = open("/dev/random");
	struct thread_args * stringhe = (struct thread_args *) args;
	while(i<dim){
		char temp;
		read(data, &temp, sizeof(char));
		temp = (temp % 25) + 65;
		stringhe->r[i] = temp;
		i++;
	}
	close(data);
	i=0;
	while(i<dim){
		stringhe->Se[i] = stringhe->r[i] ^ stringhe->s[i];
		i++;
	}
	
	time(&timer);
	if(debugFlag) fprintf (Telog, "Create random string and XOR at %s",ctime (&timer));

	pthread_t Td;
	pthread_create(&Td,NULL,&decript,stringhe);
	
	if(pthread_join(Td,NULL)){
		fprintf (Tdlog, "Aborted at %s",ctime (&timer));
		quitLog();
		exit(-1);
	}
	
	return NULL;
}

void* decript(void* args){
	int i=0;
	struct thread_args * stringhe = (struct thread_args *) args;
	while(i<dim){
		stringhe->Sd[i] = stringhe->r[i] ^ stringhe->Se[i];
		i++;
	}

	time(&timer);
	if(debugFlag) fprintf (Tdlog, "Last XOR %s",ctime (&timer));

	pthread_t Tw;
	pthread_create(&Tw,NULL,&print_string,stringhe);
	
	if(pthread_join(Tw,NULL)){
		fprintf (Twlog, "Aborted at %s",ctime (&timer));
		quitLog();
		exit(-1);
	}
	return NULL;
}

void* print_string(void* args){
	struct thread_args * stringhe = (struct thread_args *) args;

	time(&timer);
	fprintf (Twlog, "Print string at %s",ctime (&timer));

	printf("s: %s \n",stringhe->s);
	printf("r: %s \n",stringhe->r);
	printf("se: %s \n",stringhe->Se);
	printf("sd: %s \n",stringhe->Sd);
	return NULL;
}

void initDebugMode(){
	time(&timer);
	fprintf (Trlog, "Debug Mode On at %s",ctime (&timer));
	fprintf (Telog, "Debug Mode On at %s",ctime (&timer));
	fprintf (Tdlog, "Debug Mode On at %s",ctime (&timer));
	fprintf (Twlog, "Debug Mode On at %s",ctime (&timer));
}

void openLogFile(){
	Trlog = fopen ("/var/log/threads/tr.log","a");
	Telog = fopen ("/var/log/threads/te.log","a");
	Tdlog = fopen ("/var/log/threads/td.log","a");
	Twlog = fopen ("/var/log/threads/tw.log","a");
	time(&timer);
	fprintf (Trlog, "Program Start at %s",ctime (&timer));
	fprintf (Telog, "Program Start at %s",ctime (&timer));
	fprintf (Tdlog, "Program Start at %s",ctime (&timer));
	fprintf (Twlog, "Program Start at %s",ctime (&timer));
}

void quitLog(){
	fprintf (Trlog, "Program Quit at %s",ctime (&timer));
	fprintf (Telog, "Program Quit at %s",ctime (&timer));
	fprintf (Tdlog, "Program Quit at %s",ctime (&timer));
	fprintf (Twlog, "Program Quit at %s",ctime (&timer));
}
