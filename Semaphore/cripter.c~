#include"cripter.h"
#include "queue.h"

#define MAX_STRING_SIZE 100
#define QUEUE_MAX_SIZE 20

struct thread_args{    /* Used as argument to thread functions */
	char * s;
	char * r;
	char * Se;
	char * Sd;    
};

sem_t te_mutex,tw_mutex,td_mutex;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t Tr,Te,Td,Tw;
time_t timer;
FILE *Trlog,*Telog,*Twlog,*Tdlog;

int dim;
char buf[30];
bool debugFlag = false;
struct thread_args stringhe;
Queue * Q;

void* reader(void* arg);
void* randomize(void* args);
void* decript(void* args);
void* print_string(void* args);
void initDebugMode();
void openLogFile();
void quitLog();
void printHelp();
void shutDown();	
char * time_to_string();

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
	
	Q = createQueue(QUEUE_MAX_SIZE);
		
	sem_init(&te_mutex, 0, 0);
	sem_init(&td_mutex, 0, 0);
	sem_init(&tw_mutex, 0, 0);
	
	pthread_create(&Tr,NULL,&reader,NULL);
	pthread_create(&Te,NULL,&randomize,NULL);
	pthread_create(&Td,NULL,&decript,NULL);
	pthread_create(&Tw,NULL,&print_string,NULL);
	

	if(pthread_join(Tr,NULL)){
		fprintf (Trlog, "%s - Aborted.\n",time_to_string());
		quitLog();
		exit(-1);
		}

	if(pthread_join(Te,NULL)){
		fprintf (Telog, "%s - Aborted.\n",time_to_string());
		quitLog();
		exit(-1);
		}

	if(pthread_join(Td,NULL)){
		fprintf (Tdlog, "%s - Aborted.\n",time_to_string());
		quitLog();
		exit(-1);
		}

	if(pthread_join(Tw,NULL)){
		fprintf (Twlog, "%s - Aborted.\n",time_to_string());
		quitLog();
		exit(-1);
		}
	
}

void* reader(void* arg){
	while(true){	
		int i =0;
        	//accept user input until hit enter or end of file
		int len_max = 10;
		char *buffer = (char*)malloc(sizeof(char)*(len_max));
		int current_size = len_max;
		char c;    		
		while (( c = getchar() ) != '\n')
    			{
        			buffer[i++]=(char)c;
        			//if i reached maximize size then realloc size
        			if(i == current_size)
        			{
                        		current_size = i+len_max;
            				buffer = realloc(buffer, sizeof(char)*(current_size+1));
        			}
    			}
		buffer[i+1] = '\0';
		if(strcmp(buffer,"quit")==0){
			shutDown();
		}
		else{
		//critical section start
		pthread_mutex_lock(&mutex);		
		//enqueue
		Enqueue(Q,buffer);		
		if(debugFlag) fprintf (Trlog, "%s - Read string: %s\n",time_to_string(),stringhe.s);
		//critical section end
		pthread_mutex_unlock(&mutex);			
		sem_post (&te_mutex);
		}
	}
	return NULL;
}

void* randomize(void* args){
	while(true){
	//critical section start	
	sem_wait (&te_mutex);
	//dequeue
	if(!isEmpty(Q)){
	printf("dio\n");
	char * buffer;
	pthread_mutex_lock(&mutex);
	buffer = front(Q);
	Dequeue(Q);
	pthread_mutex_unlock(&mutex);
	stringhe.s = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
	stringhe.r = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
	stringhe.Se = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
	stringhe.Sd = (char*)malloc(sizeof(char)*(strlen(buffer)+1));		
	strcpy(stringhe.s,buffer);
	dim = strlen(stringhe.s);
	int i=0;
	int myrandomint;
	int data = open("/dev/random");
	while(i<dim){
		char temp;
		read(data, &temp, sizeof(char));
		temp = (temp % 25) + 100;
		stringhe.r[i] = temp;
		i++;
	}
	close(data);
	i=0;
	while(i<dim){
		stringhe.Se[i] = stringhe.r[i] ^ stringhe.s[i];
		i++;
	}
	
	time(&timer);
	if(debugFlag) fprintf (Telog, "%s - Create random string:\n %s \n and XOR with:\n %s \n result: \n %s \n",time_to_string(),stringhe.s,stringhe.r,stringhe.Se);
	//critical section end
	sem_post (&td_mutex);
	}
	}
	return NULL;
}

void* decript(void* args){
	while(true){
	//critical section start	
	sem_wait (&td_mutex);
	int i=0;
	while(i<dim){
		stringhe.Sd[i] = stringhe.r[i] ^ stringhe.Se[i];
		i++;
	}

	time(&timer);
	if(debugFlag) fprintf (Tdlog, "%s - Last operation: \n %s XOR %s \n result: %s\n",time_to_string(), 	stringhe.r,stringhe.Se,stringhe.Sd);
	//critical section end
	sem_post (&tw_mutex);
	}	
	return NULL;
}

void* print_string(void* args){
	while(true){	
	sem_wait (&tw_mutex);
	//critical section start
	time(&timer);
	if(debugFlag) fprintf (Twlog, "%s - Print strings\n",time_to_string());
	printf("s: %s \n",stringhe.s);
	printf("r: %s \n",stringhe.r);
	printf("se: %s \n",stringhe.Se);
	printf("sd: %s \n",stringhe.Sd);
	//critical section end
	//free(stringhe.s);
	//free(stringhe.r);
	//free(stringhe.Se);
	//free(stringhe.Sd);
	sem_post (&te_mutex);
	}
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

void shutDown(){
	pthread_cancel(Tr);
	pthread_cancel(Td);
	pthread_cancel(Te);
	pthread_cancel(Tw);
	quitLog();
	fclose(Trlog);
	fclose(Telog);
	fclose(Tdlog);
	fclose(Twlog);
}
