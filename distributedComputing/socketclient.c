#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// for printing the error message
void error(char *msg){
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]){

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  if(argc < 3){
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0)
    error("ERROR opening socket");

  // return a pointer to a hostent struct for the given host
  server = gethostbyname(argv[1]);

  if(server == NULL){
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  // set all values in client address structure to zero
  bzero((char *) &serv_addr, sizeof(serv_addr));

  // address family is always AF_INET
  serv_addr.sin_family = AF_INET;

  bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
  // convert port number from host byte order to network byte order
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  // set all values of buffer to zero
  bzero(buffer,256);

  printf("Please enter the message: ");
  fgets(buffer,255,stdin);

  // write the message to the socket
  n = write(sockfd,buffer,strlen(buffer));
  if (n < 0)
    error("ERROR writing to socket");

  // set all values of buffer to zero
  bzero(buffer,256);

  // read the message to the socket
  n = read(sockfd,buffer,255);
  if (n < 0)
    error("ERROR reading from socket");

  //  print the received message
  printf("%s\n",buffer);

  return 0;
}
