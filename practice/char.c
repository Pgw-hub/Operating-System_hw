#include <stdio.h>

//there is no string type in C, so we usually use char*

int main(){

    char* name = "paekgeonwoo";

    printf("%s\n",name);
    printf("%d\n",name);

    printf("%s\n",name+1);
}