#include <stdio.h>

int x;

int foo(int x) {
	if( x == 0 ) {
		int x = 4;
		return x;
	}
	
	return x;
}

int main() {
	x = 1;
	x = foo(0);
	printf("x is %d\n", x);
	return 0;
}
