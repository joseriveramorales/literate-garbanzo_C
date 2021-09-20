#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error( const char *msg) {
    perror(msg);
    exit(0);
}

int main( int argc , char *argv[]){

    // Defino cual es el servidor y cual es el puerto
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server ;
    char buffer[256];

    if(argc < 3) {
        fprintf(stderr,"usage %s hostname port \n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    // Creo un socket para mi cliente
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <0) error("ERROR opening socket");

    // Busco el host usando el argumento de entrada, la funcion gethostbyname se encarga de encontrar el IP de la maquina
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host \n");
        exit(0);
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));
    // Inicializo el adddres del servidor
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server ->h_addr ,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);

    // Asigno el puertto del servidor
    serv_addr.sin_port = htons(portno);

    // Invoco la funcion connect usando el socket del cliente y el address del servidor, ahora socketfd es mi buzon
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Error connecting");

        printf(" Please enter a message: ");
        // Asigno los bytes del buffer a 0
        bzero(buffer, 256);
        fgets(buffer,255,stdin);

        // Procedo a escribir al socket 
        n= write(sockfd,buffer,strlen(buffer));
        if(n<0)
            error("ERROR writing to socket");
        
        // Vuelvo y limpio el buffer, porque vuelvo y lo limpio si ahora voy a volver a redefinirlo usando el read?
        // Mi primer pensamiento es que si envio un mensaje mas corto que el anterior puedo tener una mezcla del mensaje anterior y el nuevo mensaje? 
        bzero(buffer,256);
        // Procedo a leer del socket
        n = read(sockfd,buffer, 255);
        if (n<0)
            error("ERROR reading from socket");
        
        printf("%s \n ", buffer); 
        // Cierro conexion
        close(sockfd);
        return 0;
        

}