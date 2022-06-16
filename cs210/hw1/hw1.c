/*
 * Created by Hayden Lepla
 * hw1.c
`* Lexer for CCX files
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void comment(char *prev , char *curr , FILE *fp) ;
int Keyword(char *prev , char *curr , FILE *fp, char *key_word[]) ;
int operator(char *prev , char *curr , FILE *fp , char sing_oper[] , char *multi_oper[]);
int is_operator(char *prev , char *curr) ;
void numeric_lit(char *prev , char *curr , FILE *fp);
int string(char *prev,char *curr,FILE *fp) ;
void character_lit(char *prev , char *curr , FILE *fp) ;
int unk(char *prev , char *curr , FILE *fp);

int main(int argc, char *argv[])
{

      FILE *fp ;
      char current  ;
      char prev;
      char char_line[256] ;
      typedef enum {false , true} bool ;

      char *key_word[34] = {"accessor", "and", "array",
                           "begin" , "bool" , "case" , "else" , "elsif",
                           "end", "exit" , "function" , "if" , "in" , "integer" ,
                            "interface" , "is" , "loop","module" , "mutator" , "natural" , "null" ,
                           "of" , "or" , "others" , "out" , "positive" , "procedure" ,
                            "return" , "struct" , "subtype" , "then" , "type", "when" , "while" } ;

      char sing_oper[17] = { '.', '<', '>', '(', ')',
                             '+', '-', '*', '/', '|',
                             '&', ';', ',', ':', '[',
                             ']', '=' } ;

      char *multi_oper[10] = {
        ":=", "..", "<<",
        ">>", "<>", "<=", ">=", "**",
        "!=", "=>"
      } ;


      fp =fopen(argv[1], "r"); // read the file only

      if(fp==NULL)
        {
          printf("An error has occured! Perhaps missing a file? \n");
          return -1 ;
        }

      current = fgetc(fp) ;

      while (feof(fp) == 0 )
        {

          prev = current ;
          current = fgetc(fp);

          if(prev == ' ' || prev == '\n' || prev == '\t' || prev == '\r') // check whitespace, newline, etc
            continue;

          else if(prev == '/' && current == '*') // check for comments
            {
              comment(&prev, &current, fp) ;
            }

          else if( isalpha(prev))  // check if current or prev is a letter
            {
              Keyword(&prev,&current,fp,key_word);
            }

         else if(prev >= '0' && prev <= '9') // check for numeric literal (Notice!!! prev is a char, not int)
            {
              numeric_lit(&prev,&current,fp) ;
            }

         else if(prev == '\"') // check for strings
            {
              string(&prev,&current,fp) ;
            }

         else if(prev=='\'') // check for character literals
            {
              character_lit(&prev,&current,fp);

            }

         else if(is_operator(&prev,&current))
           {

             operator(&prev,&current,fp,sing_oper,multi_oper) ; // check for operators
           }

         else
           {
             unk(&prev,&current,fp); // call only if prev or current is unknown
           }


        }

      fclose(fp);

      return 0 ;

}

void comment(char *prev , char *current , FILE *fp)
{
  while(!(*prev == '*' && *current == '/'))
    {
      printf("%c",*prev) ;

      *prev = *current ;
      *current = fgetc(fp) ;
    }
  printf("*/") ;
  printf(" (comment)\n") ;

  *prev = *current ;
  *current = fgetc(fp) ;

}

int Keyword(char *prev , char *current , FILE *fp ,char *key_word[32])
{

  char char_line[256];

  fseek(fp,-2,SEEK_CUR) ; // have pointer go back 2
  fscanf(fp,"%[a-zA-Z_0-9]*",char_line); // grab entire string
  fseek(fp,-1,SEEK_CUR);
  *prev = fgetc(fp) ;
  *current = fgetc(fp) ;

  int i = 0 ;
  while (i < 34)
    {
      if(strcmp(key_word[i], char_line)==0)  // check array for keyword
        {

          printf( "%s" , char_line) ;
          printf(" (keyword)\n") ;
          return 0;
        }
      i++ ;
    }

  printf("%s" , char_line) ;
  printf(" (identifier)\n") ;

}

int is_operator(char *prev,char *current)
{

  switch (*prev)
    {
    case '.':
    case ',':
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '|':
    case '&':
    case ';':
    case '[':
    case ']':
    case '<':
    case '>':
    case '=':
    case ':':
      return 1;
      break;

    case '!':
      if (*current == '=')
        {
          return 1;
        }

      break;
    }

  return 0;
}


int operator(char *prev , char *current , FILE *fp, char sing_oper[17], char *multi_oper[10])
{

  for(int i=0; i < 10 ; i++)
    {
      if(*prev == multi_oper[i][0] && *current == multi_oper[i][1])
        {
          printf("%c%c", *prev,*current) ;
          printf(" (operator)\n") ;
          *prev = *current ;
          *current = fgetc(fp) ;
          return 0 ;
        }

    }

  for (int i=0 ; i < sing_oper[i] ; i++ )
    {

      if( *prev == sing_oper[i] ) // check for single operator
        {

          printf("%c", *prev) ;
          printf(" (operator)\n") ;
          return 0 ;
        }
    }

}

void numeric_lit(char *prev , char *current , FILE *fp)
{
  char char_line[256];

  fseek(fp,-2,SEEK_CUR) ; // have pointer go back 2
  fscanf(fp,"%[a-fA-F_0-9.,#]*",char_line); // grab entire string

  *prev = *current ;
  *current = fgetc(fp) ;

  printf("%s",char_line);
  printf(" (numeric literal)\n");
}



void character_lit(char *prev , char *current , FILE *fp)
{
  do
    {

      printf("%c",*prev) ;

      *prev = *current ;
      *current = fgetc(fp) ;


    }while(!(*prev == '\'' )) ;

  printf("'");
  printf(" (char literal)\n") ;
}

int string(char *prev,char *current,FILE *fp)
{
  int i=1 ;
  char buffer[256];

 *prev = *current;
  *current = fgetc(fp);
  buffer[0]= *prev;

  while(*current != '\"')
    {
      *prev = *current ;
      *current = fgetc(fp);
      buffer[i]= *prev;
      i++ ;
    }

  buffer[i] = *current;
  buffer[i+1] = '\0' ;
  *prev = *current ;
  *current = fgetc(fp) ;

  printf("\"");
  printf("%s",buffer);

  printf(" (string)\n") ;


}

int unk(char *prev , char *current , FILE *fp)
{
  printf("%c%c",*prev,*current);
  printf(" (unknown)\n") ;

  return -1 ;

}
