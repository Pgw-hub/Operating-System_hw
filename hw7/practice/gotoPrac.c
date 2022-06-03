#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int lasti=0,lastj=0;

void goback(int x,int y)
{
	printf("\033[%dA",x);
	printf("\033[%dD",y);
}

void gotoxy(int x,int y)
{
	extern int lasti, lastj;
	goback(lasti, lastj);
	int i;
	for(i=0;i<x;i++)
		printf("\n");
	for(i=0;i<y;i++)
		printf("\t");
	lasti=x;
	lastj=y;
}

int main ()
{
int i=0;
while(1){
	i=i+1;
	gotoxy(12,5);
	printf("hello i=%d\r",i); //display text
	gotoxy(10,5);
	printf("hello i-1=%d\r",i-1);
	usleep(3*1000);
}
}
