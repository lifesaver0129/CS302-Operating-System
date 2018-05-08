#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	printf("My PID: %d\n",getpid());
	sleep(5);
	kill(getpid(),SIGSEGV);
	return 0;
}
