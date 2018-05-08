#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,char* argv[])
{
	int res;
	printf("Before fork():PID[%d]\n",getpid());
	res = fork();
	printf("The value of res is %d\n",res);
	if(res == 0)
	{
		printf("I am child! PID: [%d]\n",getpid());
	}
	else
	{
		printf("I am parent! PID: [%d]\n",getpid());
	}
	printf("Program Terminated!\n");

	return 0;
}
