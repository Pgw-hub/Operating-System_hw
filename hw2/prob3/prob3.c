#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_PATH 256
#define MAX_RESULT 100

void FindLargestFile(char *start_dir, char *largest, long *size);

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Usage: %s <start_dir>\n", argv[0]); return 0;
    }
    char *start_dir = argv[1];
    char largest[MAX_PATH] = "";
    long size = 0L; // the initial value of size should be zero
	FindLargestFile(start_dir, largest, &size);
    if(size > 0)
        printf("largest file = %s, size = %ld\n", largest, size);
    else
        printf("no file with size > 0.\n");
    return 0;
}


void FindLargestFile(char *start_dir, char *largest, long *size){
	DIR* dp  = NULL;
	struct dirent* entry = NULL;
	struct stat buf;
	
	if((dp = opendir(start_dir)) == NULL){
		printf("fail wandering directory at %s",start_dir);
	}
	else{
//		printf("open success at %s \n",start_dir);
	}

	while((entry = readdir(dp)) != NULL){
		char temp_dir[MAX_PATH] = ""; 
		lstat(entry -> d_name,&buf);//getting specific info into buf

		if(S_ISDIR(buf.st_mode)){
//			printf("name  = %s \n",entry ->d_name);
			if(strcmp(".",entry->d_name) != 0 && strcmp("..",entry->d_name) != 0){//not same with . , ..
	//			printf("find gereral dic = %s\n",entry -> d_name);//for test
				strcat(start_dir,"/");
				strcat(start_dir,entry -> d_name);

//				printf("next startdir = %s\n",start_dir);
				FindLargestFile(start_dir,largest,size);
			}	
		}
		else if(S_ISREG(buf.st_mode)){
			if(buf.st_size > *size){
				*size = buf.st_size;
//				printf("largest에 넣기 전 start_dir = %s\n",start_dir);
				strncpy(largest, start_dir,strlen(start_dir)-1);
				strncpy(largest,entry->d_name,strlen(entry->d_name)-1);
			}
		}
	}
}








