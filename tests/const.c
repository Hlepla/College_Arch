#include "stdio.h"
#include "stdlib.h"

#define  CONST 5 

int main()
{
  const int number = 4 ;

  printf("Const is: %d and number is: %d \n",CONST,number);

    CONST = CONST + 1;
    number++;

  printf("Const is now: %d and number is: %d \n",CONST,number);

  return 0;

}
