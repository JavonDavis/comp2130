#include <stdio.h>
#include <unistd.h>

int main()
{
	char *arg[] = {"ls","-l",NULL}; 	
	
	execvp(arg[0],arg);

}
