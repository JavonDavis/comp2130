#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int n, *m;
	n = 5;
	m =&n;
	int i;
	i = fork();
	if(i==0)
	{
		int l;
		l=8;
		m = &l;
		printf("Hello %d\n",*m);
		
	}
	else
	{
		wait(NULL);
		printf("Well done my child%d\n",*m);
	}
}
