#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(){
	struct timeval startTime, endTime;
	double diffTime;

	printf("[parent] before fork(), pid = %d, ppid = %d\n",getpid(),getppid());
	
	gettimeofday(&startTime,NULL);
	int f_return = fork();

	if(f_return < 0){
		fprintf(stderr,"fork Failed\n");
		exit(-1);
	}
	else if(f_return == 0){
		printf("[child] pid = %d, ppid = %d, child_pid = %d\n",getpid(),getppid(),f_return);
		execl("/home/geonwoo/hw/hw3/prob2/hw3_2b","/home/geonwoo/hw/hw3/prob2/hw3_2b",NULL);
	}
	
	else{
		wait(NULL);
	}
	gettimeofday(&endTime,NULL);
	diffTime = (endTime.tv_sec - startTime.tv_sec) +((endTime.tv_usec - startTime.tv_usec)/1000000.0);
	printf("[parent] pid = %d, ppid = %d, child_pid = %d, running time =%.6f\n",getpid(),getppid(),f_return,diffTime);
}

