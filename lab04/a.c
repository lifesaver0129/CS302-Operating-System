#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
int main(int argc, char * argv[]) {
    
    char * c = "This is CS302-----An operating system course.\n";
    // specify no buffering for stderr
    setbuf(stderr, NULL);
    
    while (* c != '\0') {
        fputc(* c, stderr);
        c++;
        sleep(1);
    }
    return 0;
}
