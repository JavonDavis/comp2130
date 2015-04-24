#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	if(argc!=2)
	{
		printf("Usage: filename\n");
		return 1;
	}

	FILE *fp;
	char *var;

	var = malloc(sizeof(char) *20);
	fp = fopen(argv[1],"r");
	int found = 0;

	while(fscanf(fp,"%s",var)>0)
	{
		if(!strcmp(var,"/*"))
		{
			found =1;
		}

		if(!strcmp(var,"*/"))
		{
			found =0;
		}
	}

	fclose(fp);
	if(found)
	{
		printf("There is an unclosed comment\n");
	}
	else
		printf("There are no unclosed comments\n");

}