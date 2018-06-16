#include <stdio.h>
#include <signal.h>

void handler(int signal)
{
	printf("Signal %d Received.Kill me if you can\n",signal);
}

int main(int argc,char *argv[])
{
	signal(SIGINT,handler);
	printf("Put into while 1 loop..\n");
	while(1) { }
	printf("OK!\n");
	return 0;
}
