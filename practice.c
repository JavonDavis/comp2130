#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;	
	int k = 0;
	i = fork();
	if(i==0)
	{
		for(k=0;k<50;k++)
		{
			printf("Hello\n");
		}
		
	}
	else
	{
		if(k+1!=50)
			wait(NULL);
		printf("Well done my child\n");
	}
}
