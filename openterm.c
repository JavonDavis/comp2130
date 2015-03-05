#include <stdio.h>

int main()
{
	FILE *fpt;
	fpt=fopen("/dev/pts/1","w");
	fprintf(fpt, "Hello WOrld");
	fclose(fpt);
}