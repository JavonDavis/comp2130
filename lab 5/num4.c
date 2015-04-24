#include <stdio.h>

int main(int argc, char *argv[])
{
	if(!fork())
	{
		int i =0;
		while(i<50)
		{
			printf("%d:Hello\n",++i);
		}
		
	}
	else
	{
		printf("Please say hello 50 times\n");
		wait(NULL);
		printf("Well done my child\n");
	}

}