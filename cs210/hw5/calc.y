%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sym.h"
%}

%union {
    double dval;
    struct sym * symptr;
} 

%token <symptr> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression
%% /* end of declarations*/

statement_list
    : statement '\n'
    | statement_list statement '\n'
    ;

statement
: NAME '=' expression { 
  if($1->constant == 1)
    {
      printf("assign to const\n");
    }
  else
    $1->value = $3;}
| '?' {printf("num-syms: %d\n",num_syms(sym_tbl)) ; print_tree(sym_tbl);}
| expression { printf("= %g\n", $1); }
;

expression
    : expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
| expression '/' expression { 
  if($3 == 0)
    {
      printf("divide by zero\n"); 
      break ;
    }
   else
     {
       $$ = $1 / $3;
     }
  }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER
    | NAME { $$ = $1->value; } 
    ;

  %% /* end of rules*/

  
  int main()
  {
    sym_lookup("PI",1)->value = 3.14159 ;
    sym_lookup("PHI",1)->value = 1.61803 ;
    return yyparse();  
    
  }

struct sym * sym_lookup(char * s, int constant)
{
  char * p;
  struct sym * sp = sym_tbl;
  
  while(1)
    {
      if (sp->name && strcmp(sp->name, s) == 0)
	return sp;
      
      else if (sp->name && strcmp(sp->name , s) < 0)
	{
	  sp= sp->left;
	  continue;
	}
      else if (sp->name && strcmp(sp->name,s) > 0)
	{
	  sp=sp->right;
	  continue;
	}
      
      sp->left = malloc(sizeof(struct sym));
      sp->right = malloc(sizeof(struct sym));
      sp->constant = constant ;
      
      sp->name = strdup(s);
      return sp; 
    }
  
  yyerror("Too many symbols");
  exit(-1);
  return NULL; /* unreachable */
  
}

void print_tree(struct sym * sp)
{
  
  if(sp->name != NULL)
    {
      print_tree(sp->right) ;
      printf("\t%s => %lg\n",sp->name,sp->value);
      print_tree(sp->left);
      
    }
  
}

int num_syms(struct sym *sp)
{
  if(sp->name != NULL)
    {
      return 1 + num_syms(sp->right) + num_syms(sp->left);
    }
  
}


