#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	if(argc<2){
		fprintf(stderr," Usage %s: <src name> <dest name>\n",argv[0]); 
		exit(1); 
	}
	FILE* src_fp = NULL;
	FILE* dest_fp = NULL; 
	src_fp = fopen(argv[1],"r");
	if(src_fp == NULL){
		perror("fopen src"); 
	//	fclose(src_fp); 
		exit(1); 
	} 
	dest_fp = fopen(argv[2],"w");
	if(dest_fp == NULL){
		perror("fopen dest");
	//	fclose(dest_fp);
		exit(1);   
	}
	int c;  
	while((c = fgetc(src_fp))!=-1){
		printf("current char: %c\n",c); 
		int c_ = fputc(c,dest_fp);
		printf("write %c\n",c_);  
	}
	fclose(dest_fp); 
	fclose(src_fp); 
	exit(0); 
}
