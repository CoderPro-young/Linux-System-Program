#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 5
#define TRUE 1
#define FALSE 0

ssize_t myGetline(char** lineptr,size_t*n,FILE* straem);

int main(int argc,char *argv[])
{
	
	if(argc<2){
		fprintf(stderr,"Usage :%s\n",argv[0]); 
	}
	FILE* fp = fopen(argv[1],"r"); 
	if(fp == NULL){
		perror("fopen"); 
		exit(1); 
	}
	char* line = NULL;
	size_t n = 0;
	int len = 0;  
	while((len = myGetline(&line,&n,fp)) > 0){
		printf("msg: %s, %d\n",line,len);
		free(line);  
	} 
	fclose(fp);
	if(line != NULL){
		free(line);
	} 
	
	exit(0); 
}

ssize_t myGetline(char** lineptr,size_t* n,FILE* straem)
{
	//*(*lineptr) = 
	int isprime = TRUE; 
	int c;
	int cnt = 0;
	int pos = 0; 
	(*lineptr) = (char*)malloc(sizeof(char)*BUFSIZE); 
	*n += BUFSIZE; 
	while(1){
		c = fgetc(straem); 
		if(c < 0){
			isprime = FALSE; 
			break; 
		}
		(*lineptr)[pos++] = c;
		cnt++;  
		/* buf is full,reallcoate */
		if(pos == BUFSIZE){
			*n += BUFSIZE; 
			(*lineptr) = (char*)realloc((*lineptr),*n);
			//(*lineptr) += BUFSIZE; 	
		//	pos += BUFSIZE;
		}
		if(c == '\n'){
			break; 
		}  
	}
	int res = cnt; 
	if(!isprime){
		res = -1; 	
	}
	else{
		res--; 
		(*lineptr)[pos++] = '\0'; 
	}
	return res; 
}








