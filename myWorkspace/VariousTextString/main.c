#include <stdio.h>

int main(void)
{
	char animal1[] = "Monkey";
	char animal2[] = {'M','o','n','k','e','y',0};
	char animal3[] = {77,111,110,107,101,121,0};
	printf("%s\n", animal1);
	printf("%s\n", animal2);
	printf("%s\n", animal3);
	return 0;
}