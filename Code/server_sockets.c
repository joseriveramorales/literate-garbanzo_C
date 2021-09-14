// A simple server using sockets

// The port number used is passed as an argument

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main( int argc, char *argv[]){

    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    // Estructura de soccket addres en donde tengo que establecer el puerto para crearla.
    struct sockaddr_in serv_addr, cli_addr;
    int n ;
    char *z;

    FILE *file;
    if(argc<2){
        fprintf(stderr, "ERROR, no port prvided \n");
        exit(1);
    }

    // Creo mi socket invocando la funcion socket con algunas constantes de parametros.
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd < 0) error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    // Defino el puerto
    portno = atoi(argv[1]);
    // El socket esta en el dominio del internet
    serv_addr.sin_family = AF_INET;
    // El addres sera cualquiera, al final sera el que tenga mi maquina
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Asigno el puerto que ya defini
    serv_addr.sin_port = htons(portno);
    
    
    //Ya el servidor esta listo para recibir conexiones

    // Aqui connecto el socket con una direccion. Una vez hago el binding puedo escuchar 
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0 )
        error("ERROR on binding");
    // Ahora escucho, 5 es el numero de intento de conexiones que seran consideradas hasta que en la 6ta las conexiones seran rechazadas.
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // La funcion accept me da a devolver un socket, este pertenece al cliente. 
    // Aqui uno los dos sockets y tengo presente el mailbox que es newsockfd

    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer, 256);
    // Aqui hago una lectura al mailbox, ya que tengo un buffer pues tengo un NON-blocking synchronization
    n = read(newsockfd, buffer, 255);
    if (n<0) error("ERROR reading from socket");
    printf("Here is the message: %s \n", buffer);

    // Aqui estoy haciendo un write al mailbox
    n = write(newsockfd, " I got your message", 18);
    if(n<0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0;
    
    



}