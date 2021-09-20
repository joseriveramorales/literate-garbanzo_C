/* Example of use of fork system call */

// compile by running gcc code.c -o executableName
// execute by ./executableName


#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

main()
{
  pid_t pid = fork();

      // Here an error occurred and the process exits with an exit code of 1.
  if (pid < 0) {
      fprintf(stderr, "Fork failed!\n");
      exit(EXIT_FAILURE);
  }
      // For the child process to execute. 
  else if (pid==0) {
      // Here the child executes the (ps) command to display the process status. Here we can see the multiple processes running on a linux system.
    printf("Displaying process id %i \n", getpid());
    printf("Displaying my parents process id %i \n", getppid());
    execlp("/bin/ps", "ps", NULL);
    printf("Still around...\n");
  }
      // For the parent process to execute. 
  else {
      // Code to make the parent process wait for any child to finish, 
      // (in this case there's only one child). 
      wait(NULL);
      // Code to get the child's pid from the parent process 
      printf("The child's pid is %i \n", pid);
      
      exit(EXIT_SUCCESS);
  }
}