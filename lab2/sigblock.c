#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*
Copy of sigint2 should be used for lab2.12 and onward
*/

static volatile int got_interrupt = 0;



//infinity loop program
int main(int argc, char* argv[])
{
	//set the end time to current time + 5 seconds
	time_t endTime = time(NULL) + 5;
	sigset_t mask,blocked;
	sigemptyset(&blocked);
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
	sigaddset(&mask,SIGUSR1);
	sigprocmask(SIG_SETMASK,&mask,NULL);
	printf("Entering loop...\n");
	while (time(NULL) < endTime);
	printf("Exiting loop..\n");
	sigpending(&blocked);
	int i = 0;
	while(sigismember(&blocked,++i)>-1)
	{
		if(sigismember(&blocked,i)>0)
			printf("we blocked signal %d\n",i);
	}
	

}


