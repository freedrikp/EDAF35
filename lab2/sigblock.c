#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*
Copy of sigint2 should be used for lab2.12 and onward
*/

static volatile int got_interrupt = 0;


void sig_usr_handler(int sig)
{
	printf("hellolo\n");
}

void sig_int_handler(int sig)
{
	struct sigaction new_action;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_handler = &sig_usr_handler;
	sigaction(SIGUSR2,&new_action,NULL);
	while(1);

}

static void hdl(int sig, siginfo_t *siginfo, void *context)
{
	//do something
}
//infinity loop program
int main(int argc, char* argv[])
{
	//signal(SIGINT,sig_int_handler);
	struct sigaction new_action;
	sigemptyset(&new_action.sa_mask);
	sigaddset(&new_action.sa_mask,SIGUSR1);
	new_action.sa_handler = &sig_int_handler;
	sigaction(SIGINT,&new_action,NULL);
	while(1);
	return 0;
}


