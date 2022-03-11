#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "/proc/cpuinfo"	
#define BUFFER_SIZE 500


int ReadTextLine(int fd, char str[], int max_len);

int buffer_size = 0;
int buffer_pos =0;
char buffer[BUFFER_SIZE];

int main(){

	//opening cpuinfo
	int fd = open(FILE_NAME,O_RDONLY);
	if(fd == -1){
		printf("file opening fail");
	}
	else{
		printf("file opening success\n");
	}

	//reading cpuinfo
	int ret = 0;
	string core;
	string modelname;
	while(ret != EOF){
		ret = ReadTextLine(fd,buffer,BUFFER_SIZE);
		//printf("reading byte = %d",ret);
		sscanf(buffer,"cpu cores :%s model name :%s",)
		printf("Read string is %s\n",buffer);
	}
}

// global variables
  int ReadTextLine(int fd, char str[], int max_len) {
      int i = 0;
      int j = 0;
    int ret = 0;
  // if current position is 0, reset buffer size and pos
  if(lseek(fd, 0, SEEK_CUR) == 0)
      buffer_pos = buffer_size = 0;
  while(j < max_len - 1){
      if(buffer_pos == buffer_size){
          buffer[0] = 0;
          buffer_size = read(fd,  buffer,  BUFFER_SIZE);
          buffer_pos = 0;
      }
      if(buffer_size == 0){
          if(j == 0)
              ret = EOF;
          break;
          }
      while(j < max_len - 2 && buffer_pos < buffer_size){
          str[j++] = buffer[buffer_pos++];
          if(str[j - 1] == '\0' || str[j - 1] == 10){
              j--;               // to remove LF
              max_len = j;   // to terminate outer loop
              break;// break inner loop
              }
          }
      }
      str[j] = 0;
      return ret;
  }

