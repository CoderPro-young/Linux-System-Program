#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define BUFSIZE 128

struct lineMsg{
	int front; 
	int rear; 
}; 
typedef struct lineMsg linemsg; 

int linePos(int n,linemsg* lm,FILE* stream){
	/* getline 

	size_t len = 0; 
	char* buf = NULL;
	int cnt = 0; 
	ssize_t read = 0; 
	for(int i = 0 ;i < n;i++){
	        read = getline(&buf,&len,stream); 
		if(read > 0){
			cnt += read; 
		}
		else{
			cnt = -1; 
		}
	}
	lm -> front = cnt - read; 
	lm -> rear = cnt ;
	
	*/ 
	int pos = -1; //pos is the position of last line when entering loop 
	for(int i = 0 ;i < n;i++){
		if(i == n-1){
			lm -> front = pos; 
		}
		int read = 0; 
		while(1){
			read = fgetc(stream);
			pos++;  
			if(read == EOF){
				return -1; 
			}
			else if(read == '\n'){
				break; 
			}
		}
	}
	lm -> rear = pos; 
	return 1; 
}

int main(int argc,char* argv[])
{
	if(argc < 3){
		fprintf(stderr,"Usage...\n"); 
	}
	int n = atoi(argv[2]); 
  	FILE* fp = fopen(argv[1],"r+"); 
	if(fp == NULL){
		perror("open failed"); 
		exit(1); 
	}
	linemsg lsg; 
	if(linePos(n,&lsg,fp) > 0){
		printf("begin = %d,end = %d\n",lsg.front,lsg.rear); 
	}
	else{
		fprintf(stderr,"wrong row\n"); 
		exit(1); 
	}
	char buf[BUFSIZE]; 
	int fpos = lsg.front+1; 
	int rpos = lsg.rear+1; 
	while(1){
		fseek(fp,rpos,SEEK_SET); 
		char *c; 
		if((c = fgets(buf,BUFSIZE,fp)) == NULL){
			break; 
		} 
		fseek(fp,fpos,SEEK_SET); 
		int len = fputs(buf,fp); 
		if(len < 0){
			perror("write failed"); 
			exit(1); 
		}
		fpos += strlen(buf);//note that fpos should add len of buf to append the moved row 
		rpos += strlen(buf);//to read the moved row 
		//rpos++; 
	}
	if(truncate(argv[1],fpos) < 0){
		perror("truncate failed"); 
		exit(1); 
	}
 //	free(&lsg); 
	exit(0);
}


