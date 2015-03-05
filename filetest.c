#include <stdio.h>

int main()
{
	int x,s;
	s=0;
	while (1){
		printf("#? ");
		scanf("%d",&x);
		if (x == 0)
		break;
		s=s+x;
		printf(" sum=%d\n",s);
	}


}