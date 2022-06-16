// msh.c
// Created by Hayden Lepla
// Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define kill(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

typedef struct history_node // linked list for history function
{
  char *entry; // contents of commands
  int index; // numbering for nodes
  struct history_node *next;
  struct history_node *prev;
}his_list;

typedef struct alias_node
{
  char *alias_entry;
  char *com_entry;
  struct alias_node *next;
}alias_list;

char *getcommand(); // receives input from user
char **parse_command(char *buff); // takes char buffer and parses the arguments
void fork_func(char **tok_array); // once parsed, we run our arguments to the exec function
char *read_file(); //allows shell to read from mshrc file
char *sub_func(char *, his_list *); // allows user to sub commands
alias_list *alias(char *, alias_list *); // allows user to create alias
void check_alias(char *, alias_list*); // check for exsisting alias
void change_path(char *); // allows user to change path
void history(); // prints users command history
void pipe_func(char *); // allows for piping commands
his_list *store_list(char *buff, his_list *, his_list *); // passive command storage
alias_list *store_alias(char *,char*, alias_list *); // allows user to create aliases
alias_list *delete_alias(char *, alias_list *); // allows user to delete aliases
char* get_last_command(char *buff, his_list *, his_list *); // allows use of !digit and !!
char* get_user_command(char *buff, his_list *, his_list *, int); // retrieves index number of list

his_list *head = NULL;
his_list *tail = NULL;

alias_list *top = NULL;

int main()
{
  getcommand();

  return EXIT_SUCCESS;
}

char *getcommand()
{
  int command;
  char temp_char;

  do
    {
      char *buff = malloc(sizeof(char) * 256); // buffer size of 256
      int i=0;

      printf("\n?: "); // print the prompt for the shell
      fflush(stdout);

      while((temp_char = getchar()) != 0xa) // grab argument until the enter key is pushed
    {
      buff[i]=temp_char; // assign our buffer with the arguments entered

      if(strcmp(buff,"exit") == 0) // exit upon the users request
        {
          exit(EXIT_SUCCESS);
        }

      else if(strcmp(buff,"read")==0) // read from file subroutine
        {
          read_file();
          buff = "\0"; // reset buffer
        }
      else if(strcmp(buff,"history")==0) // goto history function
        {
          history();
          buff = "\0";
        }

      else
        {
          i++;
        }

    }

      if(strchr(buff,'!')) // check for ! in buffer
        {
          char *bang;
          bang = get_last_command(buff,head,tail);
          parse_command(bang); // send buffer to be parsed
          buff="\0"; // reset both buffers
          bang="\0";
        }

      if(strchr(buff, '|')) // check for pipes
        {
          pipe_func(buff);
          buff = "\0";
        }

      if(strchr(buff,'^')) // check for substitution
        {
          char *sub;
         sub = sub_func(buff,head);
         parse_command(sub);
         buff = "\0";
         sub = "\0";
        }

      if(strstr(buff,"alias")) // check for alias
        {
          top = alias(buff,top);
          buff = "\0";

        }

      if(strstr(buff,"delete")) // delete alias
        {
          alias_list *new_link;
          new_link = delete_alias(buff,top);
          buff="\0";
        }

      if(strncmp("export PATH=",buff,12)==0)
        {
          change_path(buff+12);
          buff = "\0";
        }

      parse_command(buff); // if none above, parse normally

    }while(1);

}

char **parse_command(char *buff)
{
  char *token;
  char *space = " "; // parse the arguments between whitespace
  char **tok_array = malloc(256 * sizeof(char *)); // dynamically allocate a size of 256 for token array
  int i=0;

  head = store_list(buff, head, tail); // store our input commands
  check_alias(buff,top); // check for an entered alias
  token = strtok(buff,space); // grab the first token and separate by whitespace

  while(token != NULL)
    {
      tok_array[i] = token; // store our tokens into the array
      token = strtok(NULL,space); // reset each token
      i++;
    }

  tok_array[i] = NULL; // make sure to end the array with NULL

  fork_func(tok_array);
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

char *read_file()
{
  FILE *fp ;
  char *buff = malloc(sizeof(char) * 256) ,read_char; // allocate space for buffer

  fp = fopen("mshrc","r"); // allow us to read our mshrc file

  if(fp==NULL)
    {
      printf("Error, could not open the file...\n");
      exit(0) ;
    }

  while(1)
    {

      buff[0] = '\0';
      int i=0;

      while((read_char=fgetc(fp)) != 0xa) // read string up to the enter key
        {
          if(read_char == EOF) // exit with ctrl-D
            return 0;

          buff[i]= read_char;
          i++;
        }

      read_char = '\0'; // set the end to be NULL
      buff[i] = '\0';

      parse_command(buff); // send buff to be parsed
      sleep(1); // allow user to see commands executed


    }

  fclose(fp); // close fp when done
}

void history()
{
  printf("printing history\n");
  his_list * first = head;
  his_list * last = head;

  int i=1;

  while(last!=NULL)
    {
      if(last->next == NULL) // check for the last item in list
        {
          while(first != last->next)
            {
              printf("%d.%s \n",first->index,first->entry);
              first = first->next;
            }
          return;
        }

      else
        {
          i++;

          if (i > 20) // stop displaying commands past 20
            {
              first = first->next;
            }
          last = last->next;
        }
    }
}

his_list* store_list(char *buff, his_list *head, his_list *tail)
{
  his_list *curr = head;

  if (head == NULL) // check for the empty case
    {
      head = malloc(sizeof(his_list));
      tail = malloc(sizeof(his_list));

      head->entry = malloc(sizeof(char)*256);

      strcpy(head->entry, buff); // empty the contents to buffer
      head->index = 1; // give the node its first index


      head->next = NULL; // make sure to "ground" the pointers
      head->prev = NULL;

      tail = head; // assign to the last pointer created

      return head;
    }

  while(curr->next != NULL) // find the last node created
    {
      curr = curr->next;
    }


  curr->next = malloc(sizeof(his_list)); // create new node

  curr->next->entry = malloc(sizeof(char)*256);

  (curr->next)->prev = curr; // allow for doublely linked list

  strcpy(curr->next->entry, buff); // copy contents from buffer
  curr->next->index = curr->index+1 ; // increment our index

  curr->next->next = NULL;
  tail = curr; // assign tail to the last node created

  return head;
}

char* get_last_command(char *buff, his_list *head, his_list *tail)
{
  his_list *ptr = head;

  if (ptr == NULL)
    {
      perror("The list is empty, no command found.. \n");
    }

  if(strchr(buff,'!')) // check for the !
  {
    if(strncmp(buff,"!!",2)==0)
      {
        if (ptr->next == NULL) // if only one node exists
          {
            strcpy(buff, ptr->entry);
          }
        else
          {
            while(ptr->next != NULL) // find the last node
              ptr = ptr->next;
            strcpy(buff, ptr->entry);
          }
      }

    else // if !(#) exists
      {
        char *temp = buff + 1 ; // increment pointer to digit

        int num = atoi(temp); // convert string to int

        num++; // offset our counter

        buff = get_user_command(buff,head,tail,num);

      }
  }

  return buff;
}

char * get_user_command(char *buff, his_list *head, his_list *tail, int digit)
{
  his_list *ptr = head;

  while(ptr->next != NULL) // find the last node created
    {
      if(ptr->next->index == digit) // compare if index is the same as !(#)
        {
          strcpy(buff,ptr->entry); // copy contents
          break;
        }

      else
        {
          ptr = ptr->next; // advance through list
        }
    }

  return buff;
}

// credit to Jonathan Leffer for the layout of this function
// Jonathan Leffer (Nov,26 2014) [Computer program]
// Available at http://stackoverflow.com/questions/7292642/grabbing-output-from-exec
// (Accessed 16 March 2017)
void pipe_func(char *buff)
{
  int link[2],i=0,j=0;
  pid_t pid1, pid2;
  char *Pipe = strchr(buff,'|');
  char *comm1_buff = buff; // contents of buffer
  char *comm2_buff = Pipe+1; // contents after the pipe symbol

  char **comm1 = malloc(256 *(sizeof(char *)));
  Pipe[0] = '\0';
  char **comm2 = malloc(256 *(sizeof(char *)));
  int children = 2;
  char* token;

  token = strtok(comm1_buff," "); // seperate the whitespace

  while(token != NULL)
    {
      comm1[i] = token;
      token = strtok(NULL, " ");
      i++;
    }

  comm1[i] = NULL;

  token = strtok(comm2_buff," ");

  while(token != NULL)
    {
      comm2[j] = token;
      token = strtok(NULL, " ");
      j++;

    }

  comm2[j] = NULL;

  if (pipe(link)==-1) // check for pipe1 failure
    kill("pipe1");

  if ((pid1 = fork()) == -1) // check for fork failure
    {
      children--; // prevents process waiting if failure
      kill("fork");
    }

  if(pid1 == 0) // child 1 process
    {
      dup2(link[1], STDOUT_FILENO); // file descriptor for "part 1" of pipe
      close(link[0]);
      close(link[1]);
      if(execvp(comm1[0],comm1) < 0);
      kill("execl1");
    }

  if((pid2 = fork())==-1) // check for pipe2 failure
    {
      children--;
      kill("fork");
    }

  if(pid2 == 0) // child 2 process
    {
      dup2(link[0],STDIN_FILENO); // file descriptor for "part 2" of pipe
      close(link[1]);
      close(link[0]);
      if(execvp(comm2[0],comm2) < 0);
      kill("execl2");
    }

  else // parent code
    {
      close(link[1]);
      close(link[0]);

      while(children) // loop if both children exist
        {
          int* status;
          wait(status);
          children--;
        }

    }
  return;
}

char *sub_func(char *buff, his_list *head)
{
  his_list *ptr = head;
  char * first_com = malloc(256 *(sizeof(his_list)));
  char * args = malloc(256 *(sizeof(his_list)));
  char * second_com= malloc(256 *(sizeof(his_list)));

  if(head == NULL)
    {
      printf("List is empty...\n");
      return NULL;
    }

  while(ptr->next != NULL) // find the last command entered
    {
      ptr = ptr->next;
    }

  if(strrchr(buff,'^')) // find the last instance of ^ in string
    {
      strcpy(first_com,ptr->entry); // copy the command into temp buff
      strtok(first_com," "); //separe the command from whitespace

      if(strchr(ptr->entry,'-')) // check for arguments
        {

          strcpy(args,ptr->entry); // grab arguments

          args = strtok(NULL, " "); // separte the argument
        }

      buff= buff +1; // advance our pointer

      while(1)
        {
          if(*buff == '^') // check for the next carrot
            break;

          else
            buff = buff + 1; // step through buffer
        }

      buff = buff + 1; // ensure we reached the end

      strcpy(second_com,buff);
      strtok(second_com,"\n"); // grab command to the end
    }

  else
    {
      printf("Bad substitution, need ^x^y\n");
      return NULL;
    }

  strcat(second_com, " "); // Leave a space for args
  strcat(second_com,args); // cat the two strings

  return second_com;

}

alias_list *store_alias(char *alias_buff, char *com_buff, alias_list *top)
{
   alias_list *curr = top;

  if (top == NULL) // check for the empty case
    {

      top = malloc(sizeof(alias_list));
      top->alias_entry = malloc(sizeof(char)*256);

      strcpy(top->alias_entry,alias_buff); // empty the contents to buffer

      top->com_entry = malloc(sizeof(char)*256);

      strcpy(top->com_entry,com_buff);

      top->next = NULL; // make sure to "ground" the pointers

      return top;
    }

  while(curr->next != NULL) // find the last node created
    {
      curr = curr->next;
    }

  curr->next = malloc(sizeof(alias_list)); // create new node

  curr->next->alias_entry = malloc(sizeof(char)*256);

  strcpy(curr->next->alias_entry,alias_buff); // copy contents from buffer

  curr->next->com_entry = malloc(sizeof(char)*256);

  strcpy(curr->next->com_entry,com_buff);

  curr->next->next = NULL;

  return top;
}

alias_list *delete_alias(char *buff, alias_list *top)
{
  alias_list *curr = top ;
  alias_list *replace_node ;

  if(curr == NULL)
    {
      printf("List is empty, cannot delete node..\n");
      return NULL;
    }

  if(curr->next == NULL)
    {
      if(strcmp(buff,curr->alias_entry)==0)
        {
          replace_node = curr->next ; // save state of pointer

          free(curr); // remove curr pointer
        }
    }

  while(curr->next != NULL)
    {
      if(strcmp(buff,curr->next->alias_entry)==0)
        {
          replace_node = curr->next ; // save state of pointer

          free(curr->next);
        }
      curr = curr->next ;
    }

  curr->next = replace_node; // unlink from list

  return replace_node;
}

alias_list *alias(char *buff, alias_list *top)
{
  char *temp_buff = malloc(256 *(sizeof(alias_list)));
  char *tmp = malloc(256 *(sizeof(alias_list)));
  char *remove_buff = malloc(256 *(sizeof(alias_list)));
  char *alias_buff = malloc(256 *(sizeof(alias_list)));

  if(strchr(buff,'=') && strchr(buff,'"') && strrchr(buff,'"')) // check for correct syntax
    {
      strcpy(temp_buff,buff);

      remove_buff = strtok(temp_buff,"="); // grab string before =

      remove_buff = remove_buff + 6; // remove whitespace

      strcpy(alias_buff,remove_buff);

      strcpy(temp_buff,buff);

      temp_buff= strtok(NULL,"\n"); // grab string up to "

     strcpy(tmp,temp_buff);

     tmp = tmp + 1; // move past = and first "

     strtok(tmp,"\""); // separate the last "

     top = store_alias(alias_buff,tmp,top); // send to list to store
    }

  else
    {
      printf("Incorrect syntax, please try again...\n");
      return NULL;
    }

  return top;
}

void check_alias(char *buff, alias_list *top)
{
  alias_list *curr = top ;
  char *com_buff = (char *)malloc(256);

  if(top == NULL) // if list is empty do nothing
    {
      return;
    }


  if(curr->next == NULL) // check for first node
    {
      if(strcmp(buff,curr->alias_entry)==0)
        {
          strcpy(com_buff,curr->com_entry);
          parse_command(com_buff);
        }
    }

  while(curr->next !=NULL)
    {
      if(strcmp(buff,curr->next->alias_entry)==0) // find alias in list
        {
          strcpy(com_buff,curr->next->com_entry); // copy contents from list
          parse_command(com_buff); // send alias to be executed
        }

      curr = curr->next ;
    }
  // if no alias found, do nothing.
}
void change_path(char *buff)
{
  char *New_path = (char *)malloc(2650);
  char *Old_path = (char *)malloc(2650);

  Old_path = strdup(getenv("PATH")); // Store what the current path is

  New_path = buff + 5; // grab the new path

  strcat(Old_path,New_path); // cat the Paths together

  strcpy(New_path,Old_path); // put contents into new path

  setenv("PATH",New_path,1); // Overwrite the path with new one

  printf("Now printing the path: \n");

  system("echo $PATH"); // showing the appended path

}
