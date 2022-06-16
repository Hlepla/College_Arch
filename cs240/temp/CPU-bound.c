// CPU-bound.c
// Created by Hayden Lepla

#include <stdio.h>
#include <time.h>

int main()
{
  int i=0 ;
  time_t start,end;
  double elapsed=0;

  start = time(NULL); // set the start to default position

  do
    {
      end = time(NULL);
      elapsed = difftime(end,start); // compare the differences between start and end times
      i++;

    }while(elapsed <= 300.0); // end loop after 5 minutes

  printf("done!\n");
  printf("i's value is: %d\n",i);
}
