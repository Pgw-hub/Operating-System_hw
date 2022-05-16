#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* myturn(){
	while(1){
		sleep(1);
		printf("myturn\n");
	}
}

void yrturn(){
	while(1){
		printf("yr turn\n");
		sleep(1);
	}
}

int main(){
	pthread_t newthread;
	pthread_create(&newthread, NULL, myturn, NULL);
	yrturn();
return 0;	
}
