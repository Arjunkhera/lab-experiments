#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// for printing the error message
void error(char *msg){
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]){

  int n,sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;

  // accept port number as an argument
  if (argc < 2){
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("ERROR opening socket");

  // set all values in server address structure to zero
  bzero((char *) &serv_addr, sizeof(serv_addr));
  // store the port number
  portno = atoi(argv[1]);

  // address family is always AF_INET
  serv_addr.sin_family = AF_INET;
  // get the IP address of the machine
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  // convert port number from host byte order to network byte order
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  // listen for connections
  listen(sockfd,5);

  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0)
    error("ERROR on accept");

  // set all values of buffer to zero
  bzero(buffer,256);
  // read data into the buffer from the client descriptor
  n = read(newsockfd,buffer,255);
  if (n < 0)
    error("ERROR reading from socket");

  printf("Here is the message: %s\n",buffer);
  n = write(newsockfd,"I got your message",18);
  if (n < 0)
    error("ERROR writing to socket");

  return 0;
}
