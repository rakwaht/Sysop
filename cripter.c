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
void printHelp();
char * time_to_string();
char buf[30];
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
	     printHelp();
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
		fprintf (Trlog, "%s - Aborted.\n",ctime (&timer));
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
		dim = strlen(stringhe.s);
		if(strcmp(stringhe.s,"quit")==0){
			attivo=0;
		}
		else{
			time(&timer);
			if(debugFlag) fprintf (Trlog, "%s - Read string: %s\n",time_to_string(),stringhe.s);
			
			pthread_t Te;
			pthread_create(&Te,NULL,&randomize,&stringhe);
		
			if(pthread_join(Te,NULL)){
				fprintf (Telog, "%s - Aborted.\n",time_to_string());
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
	if(debugFlag) fprintf (Telog, "%s - Create random string:\n %s \n and XOR with:\n %s \n result: \n %s \n",time_to_string(),stringhe->s,stringhe->r,stringhe->Se);

	pthread_t Td;
	pthread_create(&Td,NULL,&decript,stringhe);
	
	if(pthread_join(Td,NULL)){
		fprintf (Tdlog, "%s - Aborted.\n",time_to_string());
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
	if(debugFlag) fprintf (Tdlog, "%s - Last operation: \n %s XOR %s \n result: %s\n",time_to_string(),stringhe->r,stringhe->Se,stringhe->Sd);

	pthread_t Tw;
	pthread_create(&Tw,NULL,&print_string,stringhe);
	
	if(pthread_join(Tw,NULL)){
		fprintf (Twlog, "%s - Aborted.\n",time_to_string());
		quitLog();
		exit(-1);
	}
	return NULL;
}

void* print_string(void* args){
	struct thread_args * stringhe = (struct thread_args *) args;

	time(&timer);
	if(debugFlag) fprintf (Twlog, "%s - Print strings\n",time_to_string());

	printf("s: %s \n",stringhe->s);
	printf("r: %s \n",stringhe->r);
	printf("se: %s \n",stringhe->Se);
	printf("sd: %s \n",stringhe->Sd);
	return NULL;
}

void initDebugMode(){
	time(&timer);
	fprintf (Trlog, "%s - Debug Mode On\n",time_to_string());
	fprintf (Telog, "%s - Debug Mode On\n",time_to_string());
	fprintf (Tdlog, "%s - Debug Mode On\n",time_to_string());
	fprintf (Twlog, "%s - Debug Mode On\n",time_to_string());
}

void openLogFile(){
	Trlog = fopen ("/var/log/threads/tr.log","a");
	Telog = fopen ("/var/log/threads/te.log","a");
	Tdlog = fopen ("/var/log/threads/td.log","a");
	Twlog = fopen ("/var/log/threads/tw.log","a");
	time(&timer);
	fprintf (Trlog, "%s - Program Start\n",time_to_string());
	fprintf (Telog, "%s - Program Start\n",time_to_string());
	fprintf (Tdlog, "%s - Program Start\n",time_to_string());
	fprintf (Twlog, "%s - Program Start\n",time_to_string());
}

void quitLog(){
	time(&timer);
	fprintf (Trlog, "%s - Program Quit\n",time_to_string());
	fprintf (Telog, "%s - Program Quit\n",time_to_string());
	fprintf (Tdlog, "%s - Program Quit\n",time_to_string());
	fprintf (Twlog, "%s - Program Quit\n",time_to_string());
}

void printHelp(){
  	printf("\n\nEncrypter\n\n");
	printf("Description: \n");
	printf("The program read a string ( given by the user ) and encrypt it, then after some XOR operations return the original string.\n\n");
	printf("Usage: \n");
	printf("encrypter [arguments]    		starts the program \n \n");
	printf("Arguments: \n");
	printf("-d	Run the program in debug mode ( logs are more detailed ) \n");
	printf("-h	Show help (this message) and exit \n\n");
}
 
char * time_to_string(){
	char* tmp = ctime (&timer);
	strcpy(buf, tmp);
	char* p = strchr(buf,'\n');
	if (p)
	{
    	*p = '\0';
	}
	return buf;
}