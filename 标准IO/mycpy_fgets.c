#include<stdio.h>
#include<stdlib.h> 

#define BUFSIZE 1024
 
int main(int argc,char *argv[])
{
	if(argc<2){
		fprintf(stderr,"Usage %s:",argv[0]); 
		exit(1); 
	}

	FILE* fp1 = NULL; 
	FILE* fp2 = NULL;
 
	fp1 = fopen(argv[1],"r");

	if(fp1 == NULL){
		perror("fopen src");
		exit(1);  
	}
 
	fp2 = fopen(argv[2],"w");

	if(fp2 == NULL){
		perror("fopen dest"); 
		exit(1); 
	}

	char tmp[BUFSIZE];
 	 
	while((fgets(tmp,BUFSIZE,fp1)) != NULL){
		if(fputs(tmp,fp2) < 0){
			perror("fputs failed.");
			fclose(fp2); 
			fclose(fp1);  
			exit(1); 
		}
		else{
			printf("write str: %s",tmp); 
		} 
	}
	fclose(fp2); 
	fclose(fp1); 
	exit(0); 
}
