#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	void handler(int);

	signal(SIGSEGV,handler);
	signal(SIGSEGV,SIG_IGN);

    char *word;

    int loc;

	strcpy(word,"hello");
}

void handler(int signum)
{
	printf("Segmentation fault fool\n");
	exit(SIGSEGV);
}