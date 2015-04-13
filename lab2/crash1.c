#include <stdio.h>
//Segmantation fault program
int main()
{
	char* a = "foo";
	a[0] = 'h';
	return 0;
}
