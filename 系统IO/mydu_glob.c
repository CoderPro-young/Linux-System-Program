#include<stdio.h>
#include<stdlib.h>
#include<glob.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define PATHSIZE 128

long long du_glob(char *path); 

int main(int argc,char *argv[])
{
	long long res = 0; 
	if(argc == 1){
		res = du_glob("."); 
	}
	if(argc == 2){
		res = du_glob(argv[1]); 
	}
	printf("%lld KB\n",res/2); 
	return 0; 
	
}

long long du_glob(char *path)
{
//	printf("path = %s,len = %d\n",path,strlen(path)); 
	//get file type
	static struct stat buf; 
	glob_t globres; 
	if(lstat(path,&buf) < 0){
		perror("lstat error");  
	}
	long long sum = 0;  
	
	//regular file,return disk blocks allocated directly	
	if(S_ISREG(buf.st_mode))
		sum =  buf.st_blocks;
//		printf("path = %s,sum = %d\n",path,sum);  

	//directory file,
	if(S_ISDIR(buf.st_mode)){
		char nextpath[PATHSIZE];
		strcpy(nextpath,path); 
		//search file 
		strcat(nextpath,"/*"); 
		glob(nextpath,0,NULL,&globres); 
		for(size_t i = 0;i < globres.gl_pathc;i++){
			sum += du_glob(globres.gl_pathv[i]); 
//			printf("gl_path = %s,sum = %lld\n",globres.gl_pathv[i],sum); 
		}

		//search hidden file
		strcpy(nextpath,path); 
		strcat(nextpath,"/.*"); 
		glob(nextpath,0,NULL,&globres);
		printf("hidden pathc = %d, sum = %d\n",globres.gl_pathc,sum);  
		for(size_t i = 0;i<globres.gl_pathc;i++){ 
			char* ret = strrchr(globres.gl_pathv[i],'/'); 
			if(strcmp(ret+1,".") == 0 || strcmp(ret+1,"..") == 0){
				continue; 
			}
			printf("here\n"); 
			sum += du_glob(globres.gl_pathv[i]);//get all children block num 
		}
		printf("buf,st_block = %d\n",buf.st_blocks); 
		sum += buf.st_blocks; 
		printf("sum = %d\n",sum); 
	}
	return sum; 
}













