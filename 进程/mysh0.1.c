#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<glob.h>

void display(){
	printf("mysh0.1@: "); 
}

void parse(char *str,glob_t* globres){
	int len = strlen(str); 
	str[len-1] = '\0';  //删除末尾换行符 
	char *pch;
	pch = strtok(str," ");
//	printf("arg = %s\n",pch);  
	glob(pch,GLOB_NOCHECK,NULL,globres);
	while(1){
//		printf("argc = %d",globres->gl_pathc); 
		pch = strtok(NULL," "); 
//		printf("arg = %s\n",pch);  
		if(pch){
			glob(pch,GLOB_NOCHECK|GLOB_APPEND,NULL,globres); 
		}
		else{
			break; 
		}
	}	
	//globres->gl_pathv[globres->gl_pathc] = '\0'; 
}
void Print(glob_t *globres){
	printf("Print argc = %d \n",globres->gl_pathc); 
	for(int i = 0;i < globres->gl_pathc;i++){
		printf("arg: %s\n",globres->gl_pathv[i]); 
	}
	printf("End\n"); 
}
int main()
{
	while(1){
		display(); 
		char *str; 
		size_t len = 0; 
		ssize_t read; 
		read = getline(&str,&len,stdin); 
		glob_t globres; 
		if(read != -1){
			parse(str,&globres); 		
		}

		pid_t pid; 
		if((pid = fork()) < 0){
			perror("fork"); 
			exit(1); 
		}
		else if(pid == 0){
	//		printf("child\n"); 
	//		Print(&globres); 
			execvp(globres.gl_pathv[0],globres.gl_pathv); 	
			perror("execvp"); 
		}
		else{
			wait(NULL); 
		}
	}
	
	exit(0); 
}
