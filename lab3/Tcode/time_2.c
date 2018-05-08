#include <stdio.h>
int main (void) {
	int x = 0;
	for (int i = 1; i <= 10000; i++) {
		x = x + i;
		printf ("x = %d\n", x);
	}
	return 0;
}
