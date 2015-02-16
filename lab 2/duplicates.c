#include <stdio.h>

main(int argc, char *argv[])
{
	int i,k=0,row=0;
	int array[argc][2];
	for(i=1;i<argc;i++)
	{
		for(k=i+1;k<argc;k++)
		{
			if(strcmp(argv[k],argv[i])==0)
			{
				printf("positions %d and %d match\n",k,i);
			}
		}
	}
	
}
