#include <stdio.h>

int main()
{
	int a =0, b=0,sum=0;
	printf("input two integers: ");
	scanf("%d %d",&a, &b);
	sum = a +b;
	for(int i=0; i <10; i++){
		printf("%d +%d = %d\n" ,a,b,sum);
	}
	return 0;
}
