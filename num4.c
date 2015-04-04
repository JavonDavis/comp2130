#include <stdio.h>
#include <unistd.h>

int main()
{
	char *greet = "Hello";
	char *success = "Well done my child";
	int k=0;
	int i;

	i = fork();
	
	if(i!=0)
	{
	for(k=0;k<49;k++)
	{	
		printf("%s\n",greet);
		k++;
	}
	}	

	printf("%s\n",success);
}
