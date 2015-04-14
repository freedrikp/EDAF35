#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

bool print = false;

void handler(int i){
	print = true;
}

//infinity loop program
int main(int argc, char* argv[])
{
	signal(SIGINT,handler);
	while(1){
		if ( print ){
	 		printf("Stop pressing me!\n");
			print = false;
		}
	}
	return 0;
}
