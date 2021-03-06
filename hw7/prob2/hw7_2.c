/*

	This program drops down multiple balls by multiple threads.
	There is a critical region specified by the top and bottom coordinates.

	Mission: 
		[IMPORTANT] Read this code carefully and fully understand.
		Modify the code to ensure that only T balls can enter the critical region at a time.
			hw7_1.c: T = 1
				use a mutex (pthread_mutex_t)
			hw7_2.c: T is specified by the command line argument
				use a counting semaphore (sem_t)

	Hints) 
		1. Pass the top and bottom coordinates of the critical section to the threads through the ThreadParam structure
		2. Declare a mutex or semaphore as a global variable
		3. Initialize the mutex or semaphore
		4. When a ball enters the critical region, wait the mutex or semaphore (entry section)
		4. When a ball leaves the critical region, signal the mutex or semaphore (exit section)
		5. If the thread breaks the loop while the ball is in the critical region, signal the mutex or semaphore to release other threads.
		6. After the threads finishes, destroy the mutex or semaphore.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>
// TO DO: if necessary, include more header files
#include <semaphore.h>
#include "Console.h"

#define TRUE 1
#define FALSE 0
#define MAX_THREAD 30

typedef struct {
	int thread_idx;
	int no_thread;
	int screen_height;
	int x;
	int delay;

	// TO DO: add fields to pass the vertical coordinates of the critical region
	int y;
} ThreadParam;

int thread_cont = TRUE;			// global variable to control the loop in the thread function

void* ThreadFn(void *vParam);

// TO DO: declare a mutex or semaphore as a global variable
sem_t semaphore;

int main(int argc, char *argv[])
{
	srand(time(NULL));
	clrscr();

	int no_thread = 0;
	int no_ticket = 0;
	if(argc > 2){
		no_thread = atoi(argv[1]);	
		no_ticket = atoi(argv[2]);
	}
	else{
		printf("input 2 argument : <no_thread> <no_ticket>");
		exit(-1);
	}

	if(no_thread > MAX_THREAD)
		no_thread = MAX_THREAD;
	else if(no_thread == 0)
		no_thread = 5;

	// TO DO: initialize the mutex or semaphore.
	//		on failure, display an error message and quit
	semaphore = sem_open("semaphore",O_CREAT, 0777, no_ticket);
	if(semaphore == SEM_FAILED){
		perror("error");
		exit(-1);	
	}
	sem_unlink("semaphore");
	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	// the top and bottom coordinates of the critical region
	int critical_top = screen_height / 3;
	int critical_bottom = screen_height * 2 / 3;

	// mark the critical region by horizontal lines
	DrawLine(1, critical_top, screen_width, critical_top, '-');
	DrawLine(1, critical_bottom, screen_width, critical_bottom, '-');
	
	pthread_t tid[MAX_THREAD];
	ThreadParam param[MAX_THREAD];

	for(int i = 0; i < no_thread; i++){
		param[i].thread_idx = i;
		param[i].no_thread = no_thread;
		param[i].screen_height = screen_height;
		param[i].x = screen_width * (i + 1) / (no_thread + 1);
		param[i].delay = rand() % 300;

		// TO DO: add code to store the vertical coordinates of the critical region in param[i]
		param[i].y = 1;
		pthread_create(&tid[i], NULL, ThreadFn, &param[i]);
	}

	PrintXY(1, screen_height + 1, "Press Enter to quit!\n");
	getchar();

	// termainte the threads
	thread_cont = FALSE;

	for(int i = 0; i < no_thread; i++)
		pthread_join(tid[i], NULL);

	// TO DO: destroy mutex or semaphore
	sem_destroy(&semaphore);
	clrscr();
	gotoxy(1, 1);
	printf("Bye!\n");

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	//int y = 1;
	int oldy = 1;
	while(thread_cont){
		// TO DO: implement entry section here 
		if(param -> y == (param -> screen_height / 3)) sem_wait(semaphore);
		gotoxy(param->x, oldy);
		putchar(' ');

		gotoxy(param->x, param -> y);
		putchar('*');

		fflush(stdout);

		// TO DO: implement exit section here 
		if(param -> y == (param -> screen_height * 2 / 3)) sem_post(semaphore);
		oldy = param ->  y;
		param -> y++;

		if(param -> y > param->screen_height)
			param -> y = 1;

		gotoxy(1, 1);
		fflush(stdout);
		usleep(param->delay * 1000);
	}

	// TO DO: if current broke loop in the critical region, unlock mutex
	sem_post(semaphore);
	return NULL;
}

