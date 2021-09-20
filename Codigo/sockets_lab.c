#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <sys/un.h>
#include <signal.h>
#include <stdarg.h>

// compile by running gcc code.c -o executableName
// execute by ./executableName


// Prototypes for internal functions and utilities
void error(const char *fmt, ...);
int runClient(char *clientName, int numMessages, char **messages);
int runServer();
void serverReady(int signal);

bool serverIsReady = false;

// Prototypes for functions to be implemented by students
void server();
void client(char *clientName, int numMessages, char *messages[]);

void verror(const char *fmt, va_list argp)
{
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
}

void error(const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    verror(fmt, argp);
    va_end(argp);
    exit(1);
}

int runServer(int port) {
    int forkPID = fork();
    if (forkPID < 0)
        error("ERROR forking server");
    else if (forkPID == 0) {
        server();
        exit(0);
    } else {
        printf("Main: Server(%d) launched...\n", forkPID);
    }
    return forkPID;
}

int runClient(char *clientName, int numMessages, char **messages) {
    fflush(stdout);
    printf("Launching client %s...\n", clientName);
    int forkPID = fork();
    if (forkPID < 0)
        error("ERROR forking client %s", clientName);
    else if (forkPID == 0) {
        client(clientName, numMessages, messages);
        exit(0);
    }
    return forkPID;
}

void serverReady(int signal) {
    serverIsReady = true;
}

#define NUM_CLIENTS 2
#define MAX_MESSAGES 5
#define MAX_CLIENT_NAME_LENGTH 10

struct client {
    char name[MAX_CLIENT_NAME_LENGTH];
    int num_messages;
    char *messages[MAX_MESSAGES];
    int PID;
};

// Modify these to implement different scenarios
struct client clients[] = {
        {"Uno", 3, {"Mensaje 1-1", "Mensaje 1-2", "Mensaje 1-3"}},
        {"Dos", 3, {"Mensaje 2-1", "Mensaje 2-2", "Mensaje 2-3"}}
};

int main() {
    signal(SIGUSR1, serverReady);
    int serverPID = runServer(getpid());
    while(!serverIsReady) {
        sleep(1);
    }
    printf("Main: Server(%d) signaled ready to receive messages\n", serverPID);

    for (int client = 0 ; client < NUM_CLIENTS ; client++) {
        clients[client].PID = runClient(clients[client].name, clients[client].num_messages,
                                        clients[client].messages);
    }

    for (int client = 0 ; client < NUM_CLIENTS ; client++) {
        int clientStatus;
        printf("Main: Waiting for client %s(%d) to complete...\n", clients[client].name, clients[client].PID);
        waitpid(clients[client].PID, &clientStatus, 0);
        printf("Main: Client %s(%d) terminated with status: %d\n",
               clients[client].name, clients[client].PID, clientStatus);
    }

    printf("Main: Killing server (%d)\n", serverPID);
    kill(serverPID, SIGINT);
    int statusServer;
    pid_t wait_result = waitpid(serverPID, &statusServer, 0);
    printf("Main: Server(%d) terminated with status: %d\n", serverPID, statusServer);
    return 0;
}



//*********************************************************************************
//**************************** EDIT FROM HERE *************************************
//#you can create the global variables and functions that you consider necessary***
//*********************************************************************************

#define PORT_NUMBER 36192

bool serverShutdown = false;

void shutdownServer(int signal) {
    //Indicate that the server has to shutdown
    serverShutdown = true;
    //Wait for the children to finish
    while(wait(NULL) > 0);
    //Exit
    exit(EXIT_SUCCESS);
}

void client(char *clientName, int numMessages, char *messages[])
{
    struct sockaddr_in serv_addr;
    struct hostent *server ;
    int sockfd, n;
    char buffer[256];
    //Open the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <0) error("ERROR opening socket");

    //Connect to the server
    bzero((char *) &serv_addr, sizeof(serv_addr));
        // Inicializo el adddress del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NUMBER);

    server = gethostbyaddr(&serv_addr, sizeof(serv_addr), 0);

    bcopy((char *)server ->h_addr ,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);

        // Invoco la funcion connect usando el socket del cliente y el address del servidor, ahora socketfd es mi buzon
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Error connecting");


    //For each message, write to the server and read the response
            // Aqui itero usando numMessages y el arreglo messages 

    for(int i =0; i<numMessages ; i++){
        // Write to the server
        strcpy(buffer, messages[i]);
        n = write(sockfd, buffer, strlen(messages[i]));
       if(n<0) error("ERROR writing to socket");
        if(n==0) {
            close(sockfd);
            return;
        }
        
        // read the response
        n = read(sockfd,buffer, 255);
        if (n<0) error("ERROR reading from socket");
        printf("Client %s(%d): Return message: %s\n", clientName, getpid(), buffer);
    }

    //Accept connection and create a child proccess to read and write
    
    printf("Client %s(%d): Return message: %s\n", clientName, getpid(), buffer);
    fflush(stdout);
    sleep(1);
    //Close socket
     close(sockfd);

}

void server()
{
    int sockfd, newsockfd, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    //Handle SIGINT so the server stops when the main process kills it
    signal(SIGINT, shutdownServer);
    
    //Open the socket
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd < 0) error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr)); // Asigno a 0 los espacios del serv_addr
             // El socket esta en el dominio del internet
    serv_addr.sin_family = AF_INET;
            // El addres sera cualquiera, al final sera el que tenga mi maquina
    serv_addr.sin_addr.s_addr = INADDR_ANY;
            // Asigno el puerto que ya defini usando # de est
    serv_addr.sin_port = htons(PORT_NUMBER);

    

    //Bind the socket
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0 ) 
        error("ERROR on binding");

            // Ahora escucho, 5 es el numero de intento de conexiones que seran consideradas hasta que en la 6ta las conexiones seran rechazadas.
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    kill(getppid(), SIGUSR1); // send signal ready to receive messages to the parent process id
    
    //Accept connection and create a child proccess to read and write

            // La funcion accept me da a devolver un socket, este pertenece al cliente. 
            // Aqui junto los dos sockets y tengo presente el mailbox que es newsockfd
    while((newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen)) >=0 ){
        if (newsockfd <0) error("ERROR on accept");
    }
    bzero(buffer, 256);
    pid_t pid = fork();
    if (pid < 0) {
      fprintf(stderr, "Fork failed!\n");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0){
        close(sockfd);
        bzero(buffer,256);
        // child process should read and write
        int n = read(newsockfd, buffer, 255);
        if (n<0) error("ERROR reading from socket");
        printf("Server child(%d): got message: %s\n", getpid(), buffer); //expected output 

        if (n == 0 ) {
            // Si el read me devuelve 0, fue que el cliente cerro la conexion
            close(sockfd);
            close(newsockfd);
        }

        n = write(newsockfd, buffer, strlen(buffer));
        if(n<0) error("ERROR writing to socket");

    }

    //Close socket
    close(newsockfd);
    close(sockfd);
}