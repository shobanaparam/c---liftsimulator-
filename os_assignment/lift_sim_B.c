#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SEGSIZE 10

#define KEY_CODE 1598
main(int argc, char *argv[])
{
 key_t key=KEY_CODE;
 int shmid, cntr;
 char *segptr;

pid_t	pid;    
 if(argc == 1)



	if ((pid = fork()) < 0) 
	{ 
		perror("error");


		
	}

	else if (pid != 0){

if((shmid = shmget(key,SEGSIZE, IPC_CREAT|IPC_EXCL|0666)) == -1)
{
 printf("Shared memory segment already exists\n");
 if((shmid = shmget(key, SEGSIZE, 0)) == -1)
 {
 perror("shmget");
 exit(1);
 }
 }
 else
 {
printf("Creating new shared memory \n");
 }
if((segptr = shmat(shmid, 0, 0)) == -1)
{
 perror("shmat");

}
}
}



