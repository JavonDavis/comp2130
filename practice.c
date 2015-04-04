#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sum = 0;
	int num;
	
	scanf("%d",&num);
	while(num!=0)
	{
		sum+=num;
		scanf("%d",&num);
	}
	
	printf("The sum of the numbers is %d",sum);

}
