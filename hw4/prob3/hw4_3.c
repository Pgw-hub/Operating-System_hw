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
#include <termios.h>

#define BUFFER_SIZE 128
#define FILENAME "hw4_3_21901023.shm"
#define TRUE 1
#define FALSE 0

typedef struct{
	char buffer[BUFFER_SIZE];
	int in, out;
} KeyBuffer;

//functions
void Producer(int shm_fd);
void Consumer(int shm_fd);

void InitBuffer(KeyBuffer *buf);
int IsEmpty(KeyBuffer *buf);
int IsFull(KeyBuffer *buf);
int GetKeyCount(KeyBuffer *buf);

void InsertKey(KeyBuffer *buf, char key);
void DeleteKey(KeyBuffer *buf);

int main(){
	
	//define shared memory
	char* name = FILENAME;
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
	ftruncate(shm_fd, sizeof(KeyBuffer));	
	
	//making child process
	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr, "fork failed\n");
		exit(-1);
	}
	//child(Consumer)
	else if(pid == 0){
		for(int i =0; i<3; i++){
			printf("hello from child %d\n",i);
		}
		//if the input size is over 3 then start
		Consumer(shm_fd);
		shm_unlink(FILENAME);
	}
	//parent(Producer)
	else{
		//wait(NULL);
		for(int i=0; i<3; i++){
			printf("hello from parent %d\n",i);
		}
		Producer(shm_fd);
	}
}


void Producer(int shm_fd){
	char key;
	KeyBuffer *k = mmap( 0, sizeof(KeyBuffer), PROT_WRITE | PROT_READ,MAP_SHARED, shm_fd, 0);
	InitBuffer(k);
	printf("Type keys. Press ESC to end.\n");
	while(1){
		scanf("%c",&key);
		if(key == 'q') break;
		InsertKey(k,key);
		getchar();
		printf("[Producer] inserting key = %c (IsEmpty = %d, IsFull = %d, KeyCount = %d, in = %d, out = %d\n",key,IsEmpty(k),IsFull(k),GetKeyCount(k),k -> in,k -> out);
	}		
}

void InitBuffer(KeyBuffer *buf){
	buf->in = 0;
	buf->out = 0;
	//printf("hello from producer/initbuffer\n");
}

void InsertKey(KeyBuffer *buf,char key){
	//sprintf(&(buf->buffer)[buf->in],"%c",key);
	buf -> buffer[buf -> in] = key;
	buf -> in = (buf -> in + 1) % BUFFER_SIZE;
	printf("buf status = %s\n",buf->buffer);
//	printf("buf -> in = %d\n\n",buf -> in);
}

void DeleteKey(KeyBuffer *buf){
	char temp;
	temp = buf -> buffer[buf -> out];
	buf -> out = (buf -> out +1) % BUFFER_SIZE;
}

int IsFull(KeyBuffer* buf){
	if(((buf -> in + 1) % BUFFER_SIZE) == buf -> out) return TRUE;
	else return FALSE;
}

int IsEmpty(KeyBuffer* buf){
	if( buf -> in == buf -> out) return TRUE;
	else return FALSE;
}

int GetKeyCount(KeyBuffer* buf){
	int size;
	return buf -> in > buf -> out ? (buf -> in - buf -> out) : (buf -> in + BUFFER_SIZE - buf -> out);
}

void Consumer(int shm_fd){
	KeyBuffer *k = mmap( 0, sizeof(KeyBuffer), PROT_WRITE | PROT_READ,MAP_SHARED, shm_fd, 0);
	while(1){
		if(GetKeyCount(k) == 3){
			DeleteKey(k);
			printf("  => [Consumer] deleting key = %c (IsEmpty = %d, IsFull = %d, KeyCount = %d, in = %d, out = %d\n",k -> buffer[k -> out - 1],IsEmpty(k),IsFull(k),GetKeyCount(k),k -> in,k -> out);
		}
	}
}


