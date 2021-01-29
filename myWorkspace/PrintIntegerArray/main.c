#include <stdio.h>

int main(void)
{
	int initintvec[]={10,20,30,40,50};
	for( int i = 0; i < sizeof(initintvec) / sizeof(int); i++)
	{
		printf("%d ", initintvec[i]);
	}
	return 0;
}