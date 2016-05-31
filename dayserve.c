#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define MY_PORT_NUMBER 49999

int main(int argc, char *argv[]){
  struct sockaddr_in servAddr;
  struct sockaddr_in clientAddr;
  struct hostent* hostEntry;
  int length = sizeof(struct sockaddr_in);
  char* hostName;
  int listenfd;
  int connectfd;
  time_t seconds;
  char *date;

  /* Make a socket */
  if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("listendfd < 0");
    exit(1);
  }
  /* Bind the socket to a port */
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(MY_PORT_NUMBER);
  servAddr.sin_addr.s_addr = htons(INADDR_ANY);
  
  if((bind(listenfd, (struct sockaddr *) &servAddr, sizeof(servAddr))) < 0){
    perror("bind");
    exit(1);
  }

  /* Listen and Accpet connections */
  listen(listenfd,1); //sets up connection queue one level deep
  while(1){
    waitpid(-1, NULL, WNOHANG);
    if ((connectfd = accept(listenfd,(struct sockaddr *) &clientAddr, &length)) < 0){
      perror("connectfd < 0");
      exit(1);
    }
    if(fork()){
      close(connectfd);
    }
    else{
      close(listenfd);
      break;
    }
  }

  /* Getting a text host name */
  if ((hostEntry = gethostbyaddr(&(clientAddr.sin_addr),sizeof(struct in_addr), AF_INET)) == NULL){
    fprintf(stderr, "hostEntry == NULL");
    exit(1);
  }
  
  /* print host name and send date */
  hostName = hostEntry->h_name;
  printf("%s\n",hostName);
  seconds = time(NULL);
  date = ctime(&seconds);
  write(connectfd,date,strlen(date));
  close(connectfd);
  return 0;
}
