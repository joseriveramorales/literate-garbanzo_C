#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compile by running gcc code.c -o executableName
// execute by ./executableName

int main () {

    char file_str[] = "https://www.c-programming-simple-steps.com/support-files/return-statement.zip";
    char options_str[] = " -q";
    char command[300] = "wget ";
    char display_command[] = "ls | grep return";
    //copy the command to download the file
    strcat(command, file_str);
    strcat(command,options_str);
    
    //execute the command
    system(command);
    //copy the commmand to list the files
    //execute the command
    system(display_command);

    return(0);
} 