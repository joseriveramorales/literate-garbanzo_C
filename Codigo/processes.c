#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// compile by running gcc code.c -o executableName
// execute by ./executableName


// Hello Fork 

int main () {
    pid_t pid;
    // fork a child process
    int counter =0;
    for (int i =0; i < 2; i++)
    {   
        pid = fork();
    }
    
    counter++;
    if (pid <0 ){
        // error occurred
        fprintf(stderr, "Fork Failed");
        exit(-1);

    }
    else if (pid == 0) {
        // child process

        execlp("/bin/ls", "ls", NULL);

    }
    else {
        // I'm in the parent process
        // I want the parent to wait for the child process to finish

        wait(NULL);
        printf("Child finished execution! \n ");
        printf("\n This is the counter for every process that executed %d \n ", counter);
        exit(0);
    }
}