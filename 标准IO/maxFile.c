#include<stdio.h>
#include<stdlib.h>

int main()
{
	int cnt = 0;
	FILE* fp = NULL; 
	while(1){
		fp = fopen("../tmp/log.txt","r"); 
		if(fp == NULL){
			break; 
		}
		cnt++; 
	}
	//fprintf(stdout,"%d",cnt);
	printf("%d\n",cnt);  
	exit(0) ; 
}
