/* Hayden Lepla
   hw2
   parser.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makearg(char s[] , char **args[]) ;


int main()
{
  char string[256], **argv ;
  int argc =0  ;

  fgets(string,256,stdin) ; // read in arguments

  printf("string is: %s",string) ;

  argc = makearg(string, &argv) ;

  for (int i=0 ; i < argc ; ++i)
    {

      printf("argument[%d] is: %s \n" , i , argv[i]) ;

    }

  printf("Total number of arguments is: %d \n", argc) ;

}

int makearg(char s[] , char **args[])
{
  char **char_pointer , *token ;
  int i=0 ;
  char_pointer = (char **)malloc(10*sizeof(char**)) ; // allocate space 


  token = strtok(s, " ") ; // parse each token up to whitespace

  if(token == NULL)
    {
      return -1 ;

    }

  while(token != NULL)
    {
      char_pointer[i] = token ;
      token = strtok(NULL, " ") ;
      i++ ;
    }

  *args = char_pointer ;

  return i ; // the number of arguments

}
