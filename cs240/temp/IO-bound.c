// IO-bound.c
// Created by Hayden Lepla

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  FILE *fp;
  time_t start,end;
  double elapsed=0;

  start = time(NULL); // set start to be in default position 

  do
    {
      end = time(NULL);
      elapsed = difftime(end,start); // check difference in time between start and end

      fp = fopen("/home/llamadelrey/cs240/hw1/io.txt","w"); // open io.txt
      int r = rand() % 100; // generate random number
      fprintf(fp,"Integer is: %d",r); // insert random number into file
      fclose(fp); // close file

    }while(elapsed <= 300.0); // end loop after 5 minutes 

  printf("Done!\n");
}
