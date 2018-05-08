// cat
# include <stdio.h>

int main(void){
    int c;
    while (1){
        c = getchar();
        if (c == EOF)
            break;
        putchar(c);
    }
}

// signal
void sig_handler(int sig) {
    if(sig == SIGINT)
     printf(“\nCtrl + C\n”); }

 int main(void) {
     signal(SIGINT, sig_handler);
     printf(“Press enter\n“);
     getchar();
     printf(“End of program\n”);
 }

