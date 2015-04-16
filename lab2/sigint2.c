#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
static volatile int got_interrupt = 0;


void sig_usr2_handler(int sig)
{
	printf("we got USR2 signal\n");
}

void sig_int_handler(int sig)
{
	struct sigaction new_action2;
	sigemptyset(&new_action2.sa_mask);
	new_action2.sa_handler = &sig_usr2_handler;
	sigaction(SIGUSR2,&new_action2,NULL);
	struct sigaction usr_action, prev_usr_action;
	usr_action.sa_handler = SIG_IGN;
	sigaction(SIGUSR1,&usr_action,&prev_usr_action);
	while(1);

}

void sig_usr1_handler(int sig)
{
	printf("we got USR1 signal\n");
}
//infinity loop program
int main(int argc, char* argv[])
{
	struct sigaction new_action, usr1_action;
	sigemptyset(&new_action.sa_mask);
	sigemptyset(&usr1_action.sa_mask);
	new_action.sa_handler = &sig_int_handler;
	usr1_action.sa_handler = &sig_usr1_handler;
	sigaction(SIGINT,&new_action,NULL);
	sigaction(SIGUSR1,&usr1_action,NULL);
	while(1);
	return 0;
}


