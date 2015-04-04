#include <stdio.h> 

 

int main()

{

	FILE *fpt;

	fpt=fopen("/dev/pts/2","w");

	fprintf(fpt,"Hello terminal.");

	fclose(fpt);

}

