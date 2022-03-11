#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define FILE_NAME "test.txt"
#define LENGTH 128
#define BUFFER_SIZE 200


int ReadTextLine(int fd, char str[], int max_len);

int main() {
 	char buffer[BUFFER_SIZE];
 	int fd = 0;
	int buffer_size = 0;
	int buffer_pos = 0;
    // writing file
    char out_buffer[LENGTH] = { 0 };
	strcpy(out_buffer, "Hello, World!");
    printf("Writing \"%s\" into file \"%s\".\n", out_buffer, FILE_NAME);
    fd = open(FILE_NAME, O_CREAT | O_WRONLY,S_IRWXU);
    if(fd < 0){
        printf("Failed to open %s to write.\n", FILE_NAME);
        return -1;
    }
    write(fd, out_buffer, LENGTH);
    close(fd);
    // writing file
    printf("Reading file \"%s\".\n", FILE_NAME);
    char in_buffer[LENGTH] = { 0 };
    fd = open(FILE_NAME, O_RDONLY);
    if(fd < 0){
        printf("Failed to open %s to read.\n", FILE_NAME);
    return -1;
    }
    read(fd, in_buffer, LENGTH);
    close(fd);
    printf("Read \"%s\" from file \"%s\".\n", in_buffer,FILE_NAME);
    // ReadTextLine(fd,in_buffer,10);
    return 0;
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

