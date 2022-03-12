#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "/proc/cpuinfo"
#define FILE_NAME2 "/proc/meminfo"
#define FILE_NAME3 "/proc/loadavg"
#define BUFFER_SIZE 500


int ReadTextLine(int fd, char str[], int max_len);

int buffer_size = 0;
int buffer_pos =0;
char buffer[BUFFER_SIZE];

int main(){

	//opening cpuinfo
	int fd = open(FILE_NAME,O_RDONLY);
	if(fd == -1){
		printf("file opening FAIL2");
	}
	else{
	//	printf("file opening success\n");

	}

	//reading cpuinfo
	int ret = 0;
	char core[30];
	char modelname1[20];
	int check1 = 0;
	int check2 = 0;
	while(ret != EOF){
		ret = ReadTextLine(fd,buffer,BUFFER_SIZE);	
		if(check1 == 0){
			check1 = sscanf(buffer,"model name :%s",modelname1);
		}
		if(check2 == 0){
			check2 = sscanf(buffer,"cpu cores :%s",core);
		}
		if(check1 == 1  && check2 ==1){
			printf("# of processor cores = %s\n",core);
			printf("CPU model = %s\n",modelname1);
			break;
		}
	}
	close(fd);

	//opening meminfo
	int fd2 = open(FILE_NAME2,O_RDONLY);
	if(fd2 == -1){
		printf("file opening FAIL");
	}
	else{
	//	printf("file2 opening success\n");
	}

	ret = 0;
	char memtotal[30];
	check1 = 0;
	while(ret != EOF){
		ret = ReadTextLine(fd2,buffer,BUFFER_SIZE);	
		if(check1 == 0){
			check1 = sscanf(buffer,"MemTotal :%s",memtotal);
			if(check1 == 1){
				printf("MemTotal = %s\n",memtotal);
				break;
			}
		}
	}

	//opening loadinfo
	int fd3 = open(FILE_NAME3,O_RDONLY);
	if(fd == -1){
		printf("file opening FAIL");
	}
	else{
	//	printf("file3 opening success\n");
	}

	ret = 0;
	check1 = 0;
	char loadavg1[20];
	char loadavg2[20];
	char loadavg3[20];
	ret = ReadTextLine(fd3,buffer,BUFFER_SIZE);
	sscanf(buffer,"%s %s %s",loadavg1,loadavg2,loadavg3);
	printf("loadavg = %s,loadavg2 = %s, loadavg3 = %s",loadavg1,loadavg2,loadavg3);
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

