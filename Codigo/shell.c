#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// compile by running gcc code.c -o executableName
// execute by ./executableName


#define TOKEN_DELIMETERS " \t\r\n\a"
#define DEFAULT_SIZE 1024

char *history[DEFAULT_SIZE];
char *argv[DEFAULT_SIZE];
int hist_count = 0;
int hist_num = 0;
int position = 0;
short isHistNum = 0;

void read_line(char *line){
    if(isHistNum){
        line = memcpy(line,history[hist_num-1],DEFAULT_SIZE);
        printf("\n");
    }
    else{
        fgets(line, DEFAULT_SIZE, stdin);
    }
    isHistNum = 0;
    memcpy(history[hist_count],line,DEFAULT_SIZE);
    hist_count++;
}
// Technical debt
void parse_line(char *line,char *argv[]){
    char *token;
    position = 0;
    token = strtok(line,TOKEN_DELIMETERS);
    while(token!=NULL){
        argv[position] = token;
        position++;
        token =strtok(NULL,TOKEN_DELIMETERS);
    }

}

int nat_history(char *argv[]){
    if(position==2){
        hist_num = atoi(argv[1]);
        for(int k = 1; k<=hist_count;k++){
            if(hist_num == k){
                isHistNum = 1;
            }
        }
    }
    if(isHistNum==0){
        for(int i =0; i <hist_count;i++)
            printf(" %d %s\n",(i+1),history[i]);
    }
    return 1;
}

int nat_help(char *argv[]){

    printf("\nThe following commands are supported: \n     help: displays a message explaining how to use the CLI \n      exit: closes the CLI \n     cd: executes the cd (change directory) command \n      history: without parameters, the history command shows a list of all executed commands. \n");
    return 1;
}

int nat_cd( char *argv[]){
    char* options;
    int pid = fork();
    if (pid == 0)
        execlp("cd", options, NULL);
    else 
        wait(NULL);
}

void execute(char *argv[]){

    // Check if command is valid as a native command
    char *line = (char*)malloc(DEFAULT_SIZE);

        char* comando = argv[0];
        char* options;
        int i = 1;
        while(argv[i] != NULL){
            options = strcat(options, argv[i]);
            i++;
        }
        int pid = fork();
        if (pid == 0)
            execlp(comando, options, NULL);
        else 
            wait(NULL);
    }


int main(int argc, char *argv[]){
    char exit_command[5]; strcpy(exit_command, "exit");
    char hist[8];	strcpy(hist, "history");
    char cd_command[3]; strcpy(cd_command, "cd");
    char help_command[5]; strcpy (help_command, "help");
    int valid = 0;
    char *line = (char*)malloc(DEFAULT_SIZE);
    for(int i = 0;i<DEFAULT_SIZE;i++)
        history[i] = (char*)malloc(DEFAULT_SIZE);
    long size;
    char *buf;
    char *ptr;
    while(1){
        printf("Shell->");
        read_line(line);
        parse_line(line,argv);
        if(strcmp(argv[0], exit_command) == 0){
            exit(0);
        }else if(strcmp(argv[0], hist) == 0){
            nat_history(argv);
        } else if(strcmp(argv[0], help_command) == 0) {
            nat_help(argv);
        } else if(strcmp(argv[0], cd_command) == 0) {
            nat_cd(argv);
        }
        else 
            execute(argv);
    }
}