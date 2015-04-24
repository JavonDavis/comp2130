#include <stdio.h>

int main(int argc, char * argv[])
{

	FILE *fp = fopen("myfile.txt","w");
	
	if(!fork())
	{	
		fprintf(fp,"I am a child\n");
		fprintf(fp,"I am writing in this file\n");
		fprintf(fp,"My process if is %d",getpid());
		fclose(fp);
	}
}
