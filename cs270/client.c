//Hayden Lepla
// Hw6
// cs270
// client.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>

#define DEFAULT_PROTOCOL 0

int client();
int playgame(int);

int main(int argc, char *argv[])
{
  client();
  
}


int client()
{
  int clientfd, serverlen, result;
  struct sockaddr_un serveraddr;
  struct sockaddr* serverSockAddrPtr;

  serverSockAddrPtr = (struct sockaddr*) &serveraddr;
  serverlen = sizeof(serveraddr);

  clientfd = socket(AF_UNIX,SOCK_STREAM,DEFAULT_PROTOCOL);
  serveraddr.sun_family = AF_UNIX;
  strcpy(serveraddr.sun_path, "lightbulb");

  do
    {
      result = connect(clientfd,serverSockAddrPtr,serverlen);
      if(result == -1)
        sleep(1); // wait and try again
    } while(result == -1);

  playgame(clientfd); // start game
   close(clientfd); // close the socket
   exit(0);
}

int playgame(int clientfd)
{
  char send_server[10] , recv_server[100], c_move;
  int n, rand_result;

   static char* intro = "Welcome to Rock, Scissors, Paper!\n";
   static char* instructions = "Input r -> Rock\n s -> Scissors\n p -> for paper\n q -> for exit\n ";  static char* input = "Enter your command: ";

   puts(intro);
   puts (instructions);
   puts(input);


   while(1)
     {
       scanf("%c",send_server);

       if(send_server[0] == '\n')
         {
           continue ;
         }

       rand_result = rand() % 3 ; // generate the computers choice
       char moves[4] = "rps";

       c_move = moves[rand_result];
       send_server[1] = c_move ;

       write(clientfd,send_server,strlen(send_server)+1);
       recv(clientfd,recv_server,100,0);
       puts(recv_server);
     }

}
