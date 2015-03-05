#include <stdio.h>

int main()
{
	FILE *fpt;
	int byte_val;
	char text[80];

	fpt = fopen("out.txt","r");

	byte_val = fread(text,1,80,fpt);

	printf("%d\n", byte_val);
	fclose(fpt);
}