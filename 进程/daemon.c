#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void deamonize()
{
	pid_t pid; 
	if((pid = fork()) < 0){
		perror("fork"); 
		exit(1); 
	}
	if(pid){
		exit(0); 
	}
	/* create a new session by child process */
	int fd ; 
	fd = open("dev/null",O_RDWR); 
	dup2(fd,0);
	dup2(fd,1); 
	dup2(fd,2); 

	if(setsid() < 0){
		exit(1); 
	}
	
	chdir("/"); 
	umask(0); 
	
	
}

int main()
{
	deamonize();

	FILE* fp = NULL;
	time_t t;  
	while(1){
		if((fp = fopen("../tmp/time.log","a")) < 0){
			perror("fopen"); 
			exit(1); 
		}
		t = time(0); 
		fprintf(fp, "current time is: %s", asctime(localtime(&t)));
		fflush(fp);  
		fclose(fp);
		sleep(1);  
	}
	exit(0); 
}
