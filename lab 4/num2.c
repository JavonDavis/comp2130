#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convertToBinary(int num)
{
	int tmp = num;
	int decimal[100],binary[100];
	int i=0,j=0;
	while (tmp!=0)
	{
		binary[i++] = tmp%2;
		tmp/=2;
	}
	
	for(j=i-1;j>=0;j--)
	{
		printf("%d", binary[j]);
	}
}


int main(int argc, char * argv[])
{
	if(argc!=2)
	{
		printf("Usage: number to convert to binary\n");
		return 1;
	}
	int num = atoi(argv[1]);
	printf("Binary value of %d is ",num);
	convertToBinary(num);
	printf("\n");
}