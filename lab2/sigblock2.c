#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


static volatile int proceed = 1;

void sig_alarm_handler(int sig)
{
	proceed = 0;
}

//infinity loop program
int main(int argc, char* argv[])
{
	//set the end time to current time + 5 seconds
	struct sigaction alarm_act;
	sigemptyset(&alarm_act.sa_mask);
	alarm_act.sa_handler = &sig_alarm_handler;
	sigaction(SIGALRM,&alarm_act,NULL);
	unsigned long long counter = 0;
	alarm(10);
	printf("Entering loop...\n");
	while (proceed) ++counter;
	printf("Exiting loop..\n");
	printf("result %llu\n",counter);
	

}


