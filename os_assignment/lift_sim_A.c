#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define BSIZE 6
#define NUMITEMS 35



typedef struct {
	int *lift_no;
}arguments;



typedef struct
{
 char buf[BSIZE];
 int occupied;
 int nextin, nextout;
 pthread_mutex_t mutex;
 pthread_cond_t more;
 pthread_cond_t less;
} buffer_t;
buffer_t buffer;
void * request(void *);
void * lift(void *);
char item[NUMITEMS];
int request1 = 0;
int liftrequest  = 0;
int liftnum =0;
pthread_mutex_t file_mutex;

char proarray[2];
int proarr[2];

char liftarray[2];
int liftarr[2];

#define NUM_THREADS 4
pthread_t tid[NUM_THREADS];


void print(char a[], int b[]){

FILE *fp = fopen ("sim_out.txt","a");

fprintf(fp,"Lift- %d Operation ",b[0]);

fprintf(fp," Go from Floor %c to Floor  %c\n", a[0] ,a[1]);
fprintf(fp,"#request: %d\n",b[1]);
fprintf(fp,"Current position: %c\n",a[1]);

  fprintf (fp,"Go from Floor  to Floor  \n");
  fclose (fp);



}


void produceprint(char a[], int b[])
{


FILE *fp = fopen ("sim_out.txt","a");
fprintf(fp,"New Lift Request From Floor %c to Floor %c\n", a[0] ,a[1]);
fprintf(fp,"Request No:  %d\n", b[0]);
fclose (fp);

}


void add(){
int z = 0; 
FILE *f; 
char *buffer[100];
char *token;
f = fopen("sim_input.txt","r");

while( fgets( buffer,20,f ) != NULL)
{ 
       token = strtok(buffer, " ");

while( token != NULL )
 {
     item[z++] = token[0]; 
      token = strtok(NULL, " ");

 	 }

}

}


int main(int argc,char* argv[])
{
add();

arguments *args = malloc(sizeof  *args);
 int i;

 pthread_cond_init(&(buffer.more), NULL);
 pthread_cond_init(&(buffer.less), NULL);



		
 pthread_create(&tid[0], NULL, request, NULL);

 for(int p=1;p<4;p++){
args->lift_no = &p;
			

if(pthread_create(&tid[p], NULL,lift,args)) {
            free(args);
        }
}
 for ( i = 0; i < NUM_THREADS; i++)
 pthread_join(tid[i], NULL);

return 0;

} 


void * request(void * parm)
{


 int i;

 for(i=0;i<NUMITEMS;i++)
 {
 if (item[i] == '\0') break;

 pthread_mutex_lock(&(buffer.mutex));
 if (buffer.occupied >= BSIZE)

 while (buffer.occupied >= BSIZE)
 pthread_cond_wait(&(buffer.less),& (buffer.mutex) );

if( i == 0 || i%2 == 0)
{

proarray[0] = item[i] ;
proarray[1] = item[i+1];
proarr[0] = ++liftrequest;

pthread_mutex_lock(&file_mutex);
produceprint(proarray, proarr);
pthread_mutex_unlock(&file_mutex);
printf("New Lift Request From Floor %c to Floor %c\n", item[i], item[i+1]);
printf("Request No:  %d\n", liftrequest);
}

 buffer.buf[buffer.nextin++] = item[i];
 buffer.nextin %= BSIZE;
 buffer.occupied++;

 pthread_cond_signal(&(buffer.more));
 pthread_mutex_unlock(&(buffer.mutex));
 }

 pthread_exit(0);
}

void * lift(void *args)
{

int timer;
arguments *actual_args = args;
 char item,item1,requestNo;
 int i;

 for(i=0;i<NUMITEMS;i++){
 pthread_mutex_lock(&(buffer.mutex) );
 if (buffer.occupied <= 0)
 
 while(buffer.occupied <= 0)
 pthread_cond_wait(&(buffer.more),&(buffer.mutex) );


 item = buffer.buf[buffer.nextout++];
 item1 = buffer.buf[buffer.nextout++];

liftnum++;

if(liftnum == 4)
{
liftnum = 1;
}


liftarray[0] = item ;
liftarray[1] = item1;

liftarr[0] = liftnum;
liftarr[1] = ++request1;

pthread_mutex_lock(&file_mutex);
print(liftarray, liftarr);
pthread_mutex_unlock(&file_mutex);
printf("Lift- %d Operation ",liftnum);

printf(" Go from Floor %c to Floor  %c\n", item ,item1);
printf("#request: %d\n",request1);
printf("Current position: %c\n",item1);


 


 buffer.nextout %= BSIZE;
 buffer.occupied--;
 buffer.occupied--;

 pthread_cond_signal(&(buffer.less));
 pthread_mutex_unlock(&(buffer.mutex));
timer = item - '0';
sleep(timer);

 }
 
 pthread_exit(0);
}
