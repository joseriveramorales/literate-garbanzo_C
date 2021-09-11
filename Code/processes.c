#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// compile by running gcc code.c -o executableName
// execute by ./executableName

int main () {
    pid_t pid;
    // fork a child process

    pid = fork();

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
        exit(0);
    }
}