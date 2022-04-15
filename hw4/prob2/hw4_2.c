#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>


typedef struct{
	char name[32];
	char id[32];
	char major[32];
}Student;

#define SIZE 1024
#define FILENAME "hw4_2_21901023.shm"

int main(){

	char* sname[4] = {"Peter Parker","Natasha Romanoff","Clark Kent","Diana Prince"};
	char* sid[4] = {"2200001","2200002","2200003","2200004"};
	char* smajor[4] = {"Computer Science", "Electric Engineering", "GLS", "CSEE"};
	int N = sizeof(sname)/sizeof(sname[0]);

	//setting shared memory

	//char* name = "hw4_2_21901023.shm";
	char* name = FILENAME;
	int shm_fd;
	shm_fd = shm_open(name,O_CREAT|O_RDWR,0666);
	ftruncate(shm_fd, SIZE * sizeof(Student));
	
	//making child process
	pid_t pid = fork();
	if(pid  < 0 ){
		fprintf(stderr, "fork failed\n");
		exit(-1);
	}
	
	//child 
	else if(pid == 0){
		Student *s = mmap(0, SIZE * sizeof(Student), PROT_READ, MAP_SHARED, shm_fd, 0);
		
		for(int i=0; i < N; i++){
			printf("name =  %s, ID = %s, major = %s\n",s[i].name,s[i].id,s[i].major);
		}
	}

	//parent
	else{
		wait(NULL);
		Student *s = mmap(0, SIZE * sizeof(Student), PROT_WRITE, MAP_SHARED, shm_fd, 0);
		//여기에 구조체 값 넣기
		for(int i=0; i < N; i++){
			strcpy(s[i].name,sname[i]);
			strcpy(s[i].id,sid[i]);
			strcpy(s[i].major,smajor[i]);
		}
		//printf("hello parent. my name is  %s\n and my id is %s\n",s[0].name,s[0].id);

	}
}





