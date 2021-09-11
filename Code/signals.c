// Sample program to handle signals

#include <signal.h>
#include <stdio.h>

void * myhandler(int myint){
    printf("\nSignal Handled!\n\n");
    exit(0);

}

int main() {
    signal(SIGINT, (void*) myhandler) ;
    signal(SIGTERM, (void*) myhandler) ;

    while(1){
        printf("Doing Nothing ...\n");
        sleep(1);
    }
}