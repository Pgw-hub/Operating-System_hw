#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	printf("[new child] pid = %d, ppid = %d\n",getpid(),getppid());
	for(int i = 1; i <= 3; i++){	
		printf("[new child] %d\n",i);
		sleep(1);
	}
}
