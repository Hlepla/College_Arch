// Hayden Lepla
// Hw6
// cs270
// server.c

#include <stdio.h>
#include <stdlib.h>
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
#define READ 0
#define WRITE 1

int start_game(int);
int Play_score(int);
int AI_score(int);

int main(int argc, char *argv[])
{
  int server, client, serverlen, clientlen;
  struct sockaddr_un serverAddr; // server address
  struct sockaddr_un clientAddr; // client address
  struct sockaddr* serverSockAddrPtr; // ptr to server address
  struct sockaddr* clientSockAddrPtr; // prt to client address

  signal(SIGCHLD,SIG_IGN); // ignore death of child signals to prevent zombies

  serverSockAddrPtr = (struct sockaddr*) &serverAddr;
  serverlen = sizeof(serverAddr);

  clientSockAddrPtr = (struct sockaddr*) &clientAddr ;
  clientlen = sizeof(clientAddr);

  server = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
  serverAddr.sun_family = AF_UNIX; // set domain type

  strcpy (serverAddr.sun_path, "lightbulb"); // set name
  unlink("lightbulb");
  bind(server,serverSockAddrPtr,serverlen); // create file
  listen(server, 4);


  while(1)
    {
      client = accept(server, clientSockAddrPtr, &clientlen);

       if(fork() == 0)
         {
           start_game(client);;
         }

       else
         close(client);
    }

}

int start_game(int client)
{
  int fd , player_point=0, AI_point=0 , game_counter = 0;
  char choice,reply_client[100], input_buff[100];

  while(1)
    {

  recv(client,input_buff,100,0); // read input from user/client

  puts(&input_buff[0]);

  switch(input_buff[0])
    {

    case 'r': // r=1

      if(input_buff[1])
        {
          if(input_buff[1] == 'r')
            {
              sprintf(reply_client,"Rock vs Rock: Tie! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);

            }
          else if(input_buff[1] == 's')
            {
              player_point = Play_score(player_point);
              sprintf(reply_client,"Rock vs Scissors: Rock wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }
          else // (input_buff[0] == 3)
            {
              AI_point = AI_score(AI_point);
              sprintf(reply_client,"Rock vs Paper: Paper wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);

            }
          break;

        }
    case 's': // s = 2

      if(input_buff[1])
        {
          if(input_buff[1] == 's')
            {
              sprintf(reply_client,"Scissors vs Scissors: Tie! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }
          else if(input_buff[1] == 'r')
            {
              AI_point = AI_score(AI_point);
              sprintf(reply_client,"Scissors vs Rock: Rock wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }

          else //(input_buff[0] == 3)
            {
              player_point = Play_score(player_point);
              sprintf(reply_client,"Scissors vs Paper: Scissors wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }

          break;
        }
    case 'p': // p = 3

      if(input_buff[1])
        {
          if(input_buff[1] == 'p')
            {
              sprintf(reply_client,"Paper vs Paper: Tie! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }

          else if(input_buff[1] == 'r')
            {
             player_point = Play_score(player_point);
             sprintf(reply_client,"Paper vs Rock: Paper wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter);
            }

          else // (input_buff[0] == 2)
            {
              AI_point = AI_score(AI_point);
              sprintf(reply_client,"Paper vs Scissors: Scissors wins! (COMP Score: %d , PLAYER Score: %d , Game Counter: %d) \n",AI_point,player_point,game_counter); 
            }

          break;
        }
    case 'q':

      sprintf(reply_client,"Thanks for playing! Exiting...\n");
      send(client,reply_client,strlen(reply_client)+1, 0);
      close(client);
      exit(0);

    default:

      sprintf(reply_client,"Invalid command, please try again..\n");
      break;

    }
  send(client,reply_client,strlen(reply_client)+1, 0);
  game_counter++;
    }
}

int Play_score(int player_point)
{
  player_point++;
  return player_point;

}

int AI_score(int AI_point)
{
  AI_point++;
  return AI_point;
}
