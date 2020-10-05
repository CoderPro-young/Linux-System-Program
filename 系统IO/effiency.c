#include<stdlib.h>
#include<unistd.h>

int main()
{
	int fd1 = open(); 
	int fd2 = open(); 
	int BUFSIZE = 1; 	
	while(1){
		BUFSIZE *= 2 ; 
	}
}
