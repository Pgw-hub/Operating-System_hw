#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_PATH 500
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

	//previous code
	/*
	DIR* dp  = NULL;
	struct dirent* entry = NULL;
	struct stat buf;
	
	if((dp = opendir(start_dir)) == NULL){
		printf("fail wandering directory at %s",start_dir);
	}
	else{
	//	printf("open success at %s \n",start_dir);
	}

	while((entry = readdir(dp)) != NULL){
		char temp_dir[MAX_PATH] = ""; 
		lstat(entry -> d_name,&buf);//getting specific info into buf

		if(S_ISDIR(buf.st_mode)){
	//	printf("name  = %s \n",entry ->d_name);
			if(strcmp(".",entry->d_name) != 0 && strcmp("..",entry->d_name) != 0){//not same with . , ..
	//			printf("find gereral dic = %s\n",entry -> d_name);//for test
				strcat(start_dir,"/");
				strcat(start_dir,entry -> d_name);

	//		printf("next startdir = %s\n",start_dir);
				FindLargestFile(start_dir,largest,size);
			}	
		}
		else if(S_ISREG(buf.st_mode)){
			if(buf.st_size > *size){
				*size = buf.st_size;
	//			printf("largest에 넣기 전 start_dir = %s\n",start_dir);
				strncpy(largest, start_dir,strlen(start_dir)-1);
				strncpy(largest,entry->d_name,strlen(entry->d_name)-1);
			}
		}
	}
	*/

	//updated code
	DIR* dr;
	struct dirent* de;
	struct stat file;
	char dir[MAX_PATH];

	if((dr = opendir(start_dir)) == NULL) return;

	while((de = readdir(dr)) != NULL){
		lstat(de -> d_name, &file);

		if(S_ISDIR(file.st_mode)){
		char new_start_dir[MAX_PATH];
			if(!strcmp(".",de -> d_name) || !strcmp("..", de -> d_name)) continue;
		snprintf(new_start_dir, sizeof(new_start_dir),"%s/%s",start_dir,de->d_name);
		FindLargestFile(new_start_dir, largest, size);
		}
		else{
			if(*size < (unsigned int)file.st_size){
				sprintf(largest,"%s/%s", start_dir, de ->d_name);
				*size = (unsigned int)file.st_size;
			}
		}
	}
	closedir(dr);
}








