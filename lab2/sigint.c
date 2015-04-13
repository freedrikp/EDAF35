#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
static volatile int got_interrupt = 0;

void sighandler(int i)
{
	signal(i,SIG_IGN);
	got_interrupt = 1;
	signal(SIGINT,sighandler);
}
//infinity loop program
int main(int argc, char* argv[])
{
	signal(SIGINT,sighandler);
	while(1)
	{
		if(got_interrupt)
		{
				printf("Here we got an interrupt\n");
				got_interrupt = 0;
		}
	}
	return 0;
}


