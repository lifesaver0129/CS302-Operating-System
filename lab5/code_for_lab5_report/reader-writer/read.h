#include<stdio.h>
#include <unistd.h>
#include <time.h>
#include<semaphore.h>
#include<pthread.h>


extern  sem_t db,rc;
extern int readcount;

void *reader(int *buffer){
    sem_wait(&rc);
    if (readcount ==0 ){
        sem_wait(&db);
    }
    readcount+=1;
    sem_post(&rc);
    printf("\nReader Inside..%d\n", *buffer);
    sleep (3);
    sem_wait(&rc);
    readcount-=1;
    if (readcount ==0 ){
        sem_post(&db);
    }
    sem_post(&rc);
}

