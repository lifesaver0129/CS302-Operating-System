//提交了一个运行时间超过100毫秒的作业
#include <stdio.h>

int main(int argc,char *argv[])
{
	int i=0;
	for(i=0;i<argc;i++)
	{
		printf("%s\n",argv[i]);
	}

	sleep(120);//休息120秒

	return 0;
}