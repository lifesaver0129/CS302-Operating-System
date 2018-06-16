/* pipe_withfork2.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
    int pipefds[2];
      pid_t pid;
    char buf[30];
    //create pipe
    if(pipe(pipefds) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
      memset(buf,0,30);
      pid = fork();
    if (pid > 0) {
      printf(" PARENT write in pipe\n");
    //parent close the read end
          close(pipefds[0]);
    //parent write in the pipe write end                 
      write(pipefds[1], "CSCI3150", 9);
    //after finishing writing, parent close the write end
          close(pipefds[1]);
    //parent wait for child                
      wait(NULL);                         
    }else {  
      //child read from the pipe read end until the pipe is empty   
      while(read(pipefds[0], buf, 1)==1)   
        printf("CHILD read from pipe -- %s\n", buf);
      //after finishing reading, child close the read end
      close(pipefds[0]);
      printf("CHILD: EXITING!");
      exit(EXIT_SUCCESS);
    }
    return 0;
}
