#include <stdio.h>
#include <signal.h>

int main(int argc,char *argv[])
{
	signal(SIGINT,SIG_IGN);
	printf("Put into while 1 loop..\n");
	while(1) { }
	printf("OK!\n");
	return 0;
}
