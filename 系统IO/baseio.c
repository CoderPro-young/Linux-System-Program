#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFSIZE 16
	
int main(int argc,char *argv[])
{
	if(argc < 3){
		fprintf(stderr,"Usage...\n"); 
	}
	
	int fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0){
		perror("src file open failed."); 
		exit(1); 
	} 
	int fd2 = open(argv[2],O_RDWR); 
	if(fd2 < 0){
		perror("dest file open failed."); 
		close(fd1); 
		exit(1); 
	}
	while(1){
		char *tmp = (char*)malloc(BUFSIZE); 
		ssize_t len = read(fd1,tmp,BUFSIZE); 
		if(len < 0){
			perror("read failed."); 
			break; 
			//close(fd1); 
			//close(fd2); 
		}
		else if(len == 0){
			break; 
		}
		printf("len = %d\n",len); 
		/*wirte process ma be terminated*/
		int pos = 0; 
		ssize_t byteswrite = 0; 
		while(len > 0 && (byteswrite = write(fd2,tmp+pos,BUFSIZE)) != 0 ){
	//		int pos = 0; 
			if(byteswrite < 0){
				perror("write failed."); 
				close(fd1); 
				close(fd2); 
				exit(1);  
			}
			len -= byteswrite; 
			pos += byteswrite; 
			printf("byteswrite = %d\n", pos); 
		}
		free(tmp); 
		
	}
	close(fd1); 
	close(fd2); 
	exit(1); 
	


	
	
}
