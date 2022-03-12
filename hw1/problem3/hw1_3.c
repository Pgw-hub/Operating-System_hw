#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CMD 2048
#define MAX_ARG 256 
void ParseCommand(char *command, int *argc, char *argv[]);

int main() {
    char command[MAX_CMD];
    command[0] = command[MAX_CMD-1] = 0;  // for safety
    int argc = 0;
    char *argv[MAX_ARG] = { NULL };
    while(1){
        printf("$ ");
        fgets(command, MAX_CMD - 1, stdin);
        command[strlen(command)-1] = 0;   // trim \r
        if(strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
            break;
        ParseCommand(command, &argc, argv);
        // TO DO: implement this function


        printf("argc = %d\n", argc); 
        for(int i = 0; i < argc; i++){
            printf("argv[%d] = %s\n", i, argv[i]);
        }
        printf("argv[%d] = %p\n", argc, argv[argc]);
    }
    printf("Bye!\n");
    return 0;
}

void ParseCommand(char *command, int *argc, char *argv[]){
    int i = 1;
    int j = 0;
    int len = strlen(command);
    //put first value to argv
    argv[0] = &command[0];
    while(j <= len){
        if(isspace(command[j]) != 0 || command[j] == '\0'){
            //argc increase
            *argc = *argc + 1;
            //put address to argv array
            argv[i] = &command[j+1];
            i++;
            //put null value to the space
            command[j] = '\0';
            //ignore second space
            while(isspace(command[j]) != 0 || command[j] == '\0'){
                j++;
            }            
        }
        j++;
    }
    argv[*argc] = NULL;
}