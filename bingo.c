#include <stdio.h>
main()
{
	char s[80];
	while (1){
		scanf("%s",s);
		if (strcmp(s,"sum=5") == 0)
			printf("Bingo!\n");
		else if (strcmp(s,"sum=12") == 0)
		 break;
	}
}
