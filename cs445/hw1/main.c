#include "linked.h"
#include "string.h"

extern int line_num;
extern char *saved_yyin;

void lexerr(char *s)
{
  extern int errors;
  errors++;

  fprintf(stderr, "%s: lexical error", s);

  fprintf(stderr, ", token = \"%s\"\n", yytext);
}

void print(TokenL *HEAD)
{
  TokenL *p = HEAD;
  printf("Category         Text          Lineno          Filename         Ival/Sval\n");
  printf("---------------------------------------------------------------------------\n");
  while(p != NULL)
    {
      printf("\n");
      printf("%-20i",p->t->category);
      printf("%-20s",p->t->text);
      printf("%-20i",p->t->lineno);
      printf("%-20s",p->t->filename);
      printf("%-20i",p->t->ival);
      printf("%-20lg",p->t->dval);
      printf("%-20s",p->t->sval);
      p=p->next;
      printf("\n");
    }
}

// generates a node to store info about lexemes
Token *mallocate_token(int lexemes)
{
  Token *tnode_new = (Token*) malloc(sizeof(Token));

  tnode_new->category = lexemes;
  tnode_new->text = strdup(yytext);
  tnode_new->lineno = line_num;
  tnode_new->filename = strdup(saved_yyin);

  if(lexemes == INTLITERAL)
    {
      tnode_new->ival = atoi(yytext);
    }

  if(lexemes == FLOATLITERAL)
    {
      tnode_new->dval = atof(yytext);
    }

  if(lexemes == STRGLITERAL)
    {
      //newline, tab, double quote, backlash
      char *strg;
      char *h, *o;
      strg = strdup(yytext);
      o = strg;
      h = yytext;

      h = h + 1;

      while(*h !='\0')
        {
          if(*h == '\\')
            {
              h = h + 1;

              if(*h == 'n')
                {
                  *o = '\n';
                }
              
              else if(*h == 't')
                {
                  *o = '\t';
                }
              
              else if(*h == '\\')
                {
                  *o = '\\';
                }
              else if(*h == '"')
                {
                  *o = '"';
                }
              printf("what is strg: %s\n",strg);
            }
          *o = *h;
          h = h + 1;
          o = o + 1;
        }

      o = o - 1;
      *o = '\0';
      tnode_new->sval = strg;
    }
  return tnode_new;
}



//generates a linked list that points to our Token struct
TokenL *add_node(TokenL *end, Token *new)
{
  if(end->t == NULL)
    {
      end->t = new;
    }

  else
    {
      TokenL *newnode = (TokenL *) malloc(sizeof(TokenL));
      newnode->t = new;
      newnode->next = NULL;
      end->next = newnode;
      end= end->next;
    }

  return end;


}
