#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	printf("Before Fork, My PID: [%d]\n",getpid());
	fork();
	printf("After Fork, My PID: [%d]\n",getpid());
	return 0;
}
