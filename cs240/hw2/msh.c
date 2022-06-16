// msh.c
// Created by Hayden Lepla
// Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void getcommand(); // receives input from user
void parse_command(char *buff); // takes char buffer and parses the arguments
void fork_func(char **tok_array); // once parsed, we run our arguments to the exec function


int main()
{
  getcommand();

  return EXIT_SUCCESS;
}

void getcommand()
{
  int command;
  char temp_char;

  do
    {
      char buff[256] = "\0"; // reset buffer after each loop
      int i=0;
      printf("\n?: "); // print the prompt for the shell

      while((temp_char = getchar()) != 0xa) // grab argument until the enter key is pushed
        {
          buff[i]=temp_char; // assign our buffer with the arguments entered

          if(strcmp(buff,"exit") == 0) // exit upon the users request 
            {
              exit(EXIT_SUCCESS);
            }

          else
            {
              i++;
            }
        }

      parse_command(buff); // send buffer to be parsed

    }while(1); // loop indefinitely

}

void parse_command(char buff[])
{
  char *token;
  char *space = " "; // parse the arguments between whitespace
  char **tok_array = malloc(256 * sizeof(char *)); // dynamically allocate a size of 256 for token array
  int i=0;

  token = strtok(buff,space); // grab the first token and separate by whitespace

  while(token != NULL)
    {
      tok_array[i] = token; // store our tokens into the array
      token = strtok(NULL,space); // reset each token
      i++;
    }

  tok_array[i] = NULL; // make sure to end the array with NULL

  fork_func(tok_array); // pass the data structure to be run


}

void fork_func(char **tok_array)
{
  pid_t catch;
  int *child_status;

  catch = fork(); // create the child process

  if(catch == -1) // check for bad fork
    {
       printf("An error has occurred...\n");
       exit(EXIT_FAILURE);
    }

  else if(catch == 0) // child process
     {
       if(execvp(tok_array[0],tok_array) < 0) // run the system call to run our command and argument. If return value is < 0, print error.
         {
           printf("%s\n",strerror(2)); // print the error message for missing directory/file
         }

       exit(0);
     }

  else // parent code
    {
      catch = wait(child_status); // wait so we dont create zombies
    }
}
