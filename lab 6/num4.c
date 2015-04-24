#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//made process B sleep for 1 and process A sleep for 2 so it can be more noticable

int main(int argc, char * argv[])
{
	void handler(int);
	signal(SIGUSR1,handler);

	if(fork())
	{

    	if(fork())
    	{
    		wait(NULL);
    	}
    	else
    	{
    		int count =0;
    		while(count!=80)
			{
				count++;
				printf("chil2:%d\n", count);
				sleep(1);

			}
			kill(0,SIGUSR1);
    	}
    	wait(NULL);
    }
	else 
	{
		int count =0;
		while(count!=50)
		{
			count++;
			sleep(2);
			printf("chil1:%d\n", count);
		}
	}
}

void handler(int signum)
{
	printf("Finished count\n");
	exit(SIGUSR1);
}