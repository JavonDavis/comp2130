#include <stdio.h>
#include <string.h>
#include <stdbool.h>

main()
{
	
	char name[50],first[25],last[25];
	bool isLastName = false;
	printf("What is your name? ");
	scanf("%s",name);

	int i,k=0;

	
	first[0] = name[0];
	for (i=1; i<strlen(name); i++)
	{	
		if(isupper(name[i]))
			isLastName = true;
		if(!isLastName)
			first[i] = name[i];
		else 
		{
			last[k] = name[i];
			k++;
		}
	}
	int fLen = strlen(first);
	first[fLen-1] = \0';
	printf("%s %s\n",first,last);

}
