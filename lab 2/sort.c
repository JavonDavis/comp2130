#include <stdio.h>
#include <string.h>

main()
{
	char word[30];
	
	int i=0,size;
	printf("Please enter a string:\n");
	scanf("%s",word);
	
	int n = strlen(word);
	int values[n];

	for(i=0;i<strlen(word);i++)
	{
		values[i] = (int) word[i];
	}

	//bubble sort
	int j,k;
	for(j=0;j<n;j++)
	{
		for(k=0;k<n-1;k++)
		{
			if(values[k]>values[k+1])
			{
				int temp = values[k+1];
				values[k+1] = values[k];
				values[k]=temp;
			}
		}
	}
	
	for(i=0;i<n;i++)
	{
		printf("%c",values[i]);
	}
	printf("\n",values[i]);

}
