#include <stdio.h>

main(){

	FILE *fpt;

	int c,buf[4];

	fpt=fopen("/dev/psaux","r");

	while (1){

		c=fread(buf,4,1,fpt);

		printf("Read %d bytes: %d\n",c,buf[0]);

	}

	fclose(fpt);

}

