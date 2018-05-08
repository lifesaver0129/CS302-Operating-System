#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include"read.h"
#include "write.h"
#include <fcntl.h>
#include <sys/stat.h>
pthread_t rehs[600], wrhs[25];
int main(){
	int nw,nr;
    printf("\nEnter the no readers : ");
    scanf("%d",&nr);
    printf("\nEnter the no Writers : ");
    scanf("%d",&nw);
	sem_open("db", O_CREAT|O_EXCL, S_IRWXU, 1);
	sem_open("rc", O_CREAT|O_EXCL, S_IRWXU, 1);
    readcount = 0;

	int buffer = 0;
	int i = 0, j =0, k = 0, r = 0;

	srand(time(0));

	for(i=0;i<nw + nr;i++)
	{
		r = rand()%2;

		if(0 == r)
		{
			if(j<nw)
			{
				pthread_create(&wrhs[j],NULL,writer,&buffer);
				j+=1;
			}else{
				pthread_create(&rehs[j],NULL,reader,&buffer);
				k+=1;
			}
		}
		else{
			if(k<nr)
			{
				pthread_create(&rehs[j],NULL,reader,&buffer);
				k+=1;
			}else{
				pthread_create(&wrhs[j],NULL,writer,&buffer);
				j+=1;
			}
		}
	}
    for (i = 0; i < nw; i++)
		pthread_join (wrhs[i], NULL);
	for (i = 0; i < nr; i++)
		pthread_join (rehs[i], NULL);
}
