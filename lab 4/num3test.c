#include <stdio.h>

int main(int argc, char * argv[])
{
	int i,j;
	j =0;
	for(i=1;i<100;i=i<<1)
	{
		if(i%5 >1)
			j = j|i;
		printf("%d %d\n",i,j );
	}
}
