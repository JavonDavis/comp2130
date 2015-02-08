#include <stdio.h>
#include <math.h>
#include <string.h>
#include "integer.h"


main(int argc, char *argv[])
{
	int i;
	//check if inputs are integers
	for(i=1;i<argc;i++)
	{
		if(!isInteger(argv[i]))
		{
			printf ("Arguments must be integers\n");
			return;
		}
	}
	
	
	
	// if only two inputs
	if(argc==3)
	{
		while(1)
		{
			int num1 = atoi( argv[1]); // get first
			int num2 = atoi( argv[2]); //get second

			//second number can't be greater than first
			if(num2>num1)
			{
				printf("INVALID ARGS FOR DIVISION: arg2 must not be greater than arg1\n");
				break;
			}
			
			//divisior cannot be 0
			if(num2==0)
			{
				printf("INVALID ARGS FOR DIVISION: arg2 cannot be 0\n");
				break;
			}		
		
			double quotient = (double) num1/(double) num2;

			printf("Result of division:%.2f\n",quotient);
			break;
		}
	}
	printf("Number of arguments:%d\n",argc-1);

	//display all inputs
	for(i=1;i<argc;i++)
	{
		printf("%s\n",argv[i]);
	}
}
