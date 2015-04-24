#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
	char *args[3];
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execvp("ls",args);
	printf("Command did not execute\n");
}