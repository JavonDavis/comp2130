#include <stdio.h>
#include "integer.h"

main()
{
	int n,sum=0;
	printf("Please enter a number with at most 10 digits\n");
	scanf("%d",&n);
	
	if(n>0)
	{
		if(n%10000000000>0)
		{
			printf("Number too large");
			return;
		}
		else
			while(n>0)
			{
				sum+=(n%10);
				n/=10;
			}
		printf("The sum is of the digits are %d\n",sum);
		return;
	}
	printf("This number is not a positive integer");
}

