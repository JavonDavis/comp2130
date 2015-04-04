#include <stdio.h>
#include <unistd.h>

int main()
{

	FILE *fpt;
	
	fpt = fopen("myfile.txt","w");

	int i;
	
	
	i = fork();


	if(i!=0)
	{
	fprintf(fpt,"I am a child\n");
	fprintf(fpt,"I am writing in this file\n");
	fprintf(fpt,"My process id is %d\n",i);
	}
	
}
