#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MY_PORT_NUMBER 49999

int main(int argc, char *argv[]){
  struct sockaddr_in servaddr;
  struct hostent* hostEntry;
  struct in_addr **pptr;
  int socketfd;
  char date[25];

  /* Making a connection from a client */
  if((socketfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
    perror("socketfd < 0");
    exit(1);
  }

  /* Set up the address of the server */
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(MY_PORT_NUMBER);

  if ((hostEntry = gethostbyname(argv[1])) == NULL){
    fprintf(stderr, "hostEntry == NULL");
    exit(1);
  }

  pptr = (struct in_addr **) hostEntry->h_addr_list;
  memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
  
  /* Connect to the server */
  if((connect(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0){
    perror("connect < 0");
    exit(1);
  }

  /* print date */
  read(socketfd, date, 25);
  for(int i = 0; i < 25; i++){
    printf("%c", date[i]); 
  }
  close(socketfd);

  return 0;

}
