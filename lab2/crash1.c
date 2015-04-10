#include <stdio.h>
#include <stdlib.h>

//Segmantation fault program
int main(int argc, char* argv[])
{
	char* a = "foo";
	a[0] = 'h';
	return 0;
}
