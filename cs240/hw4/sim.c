#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int producer(int,long); // takes characters and writes to file
int consumer(int,long); // consumes characters from file
void buffer_stack(int,long,long); // controls entirety of program
char rand_char(); // generates our characters
void avg_buffsize(); // calculates average buffsize
void buff_tracker(struct timeval*, int);

int main(int argc, char *argv[])
{
  if(argc < 4 || (atoi(argv[1])) == 0)
    {
      printf("too few argmuents/invalid time, terminating...\n");
      exit(EXIT_FAILURE);
    }
  else
    {
      srand(time(NULL));
      int interval = atoi(argv[1]); // max time in seconds for program to run
      long int p_time = 1000000*atoi(argv[2]); // time for producers
      long int c_time = 1000000*atoi(argv[3]); // time for consumers

      buffer_stack(interval,p_time,c_time);
    }

  return 0;
}

//time_spec running_total_t, running_time
struct timeval old_time;
struct timeval timer;
struct timeval t_result;
long total_sum=0,total_time=0;

void buffer_stack(int interval,long p_time,long c_time)
{
  char buffer_B[1000];
  int prod_fd[4],cons_fd[4],buff_fd[1],prod_pids[4],cons_pids[4];
  time_t start,end;
  double elapsed=0;
  int n=0;
  char prod_fifo[4][16] ,con_fifo[4][16];
  long increment=0, decrement=0;

  //declare all producer & consumer pipes

  strcpy(prod_fifo[0], "/tmp/prod_fifo1");
  mkfifo(prod_fifo[0],0666);

  strcpy(prod_fifo[1],"/tmp/prod_fifo2");
  mkfifo(prod_fifo[1],0666);

  strcpy(prod_fifo[2],"/tmp/prod_fifo3");
  mkfifo(prod_fifo[2],0666);

  strcpy(prod_fifo[3],"/tmp/prod_fifo4");
  mkfifo(prod_fifo[3],0666);

  strcpy(con_fifo[0],"/tmp/con_fifo1");
  mkfifo(con_fifo[0],0666);

  strcpy(con_fifo[1],"/tmp/con_fifo2");
  mkfifo(con_fifo[1],0666);

  strcpy(con_fifo[2],"/tmp/con_fifo3");
  mkfifo(con_fifo[2],0666);

  strcpy(con_fifo[3],"/tmp/con_fifo4");
  mkfifo(con_fifo[3],0666);

  int i;
  for(i=0;i<4;i++) // spool up producers
    {
      if((prod_pids[i] = fork())==0)
        { int fd = prod_fd[i] = open(prod_fifo[i],O_WRONLY); // open producer fd's
          producer(fd,p_time); // start generating characters
          exit(0);
        }
      else
        {
          prod_fd[i] = open(prod_fifo[i],O_NONBLOCK,O_WRONLY); // parent producer
        }
    }

  for(i=0;i<4;i++) // spool up consumers
    {
      if((cons_pids[i] = fork())==0)
        {
          int fd = cons_fd[i] = open(con_fifo[i],O_RDONLY); // open consumer fd's
          consumer(fd,c_time); // consume the characters!
          exit(0);
        }
      else
        {
          cons_fd[i] = open(con_fifo[i],O_RDWR); // parent consumer
        }
    }

  char tmp[2];

  start=time(NULL); // set time to default for total run time

  gettimeofday(&old_time,NULL);

  while(elapsed <= interval) // loop till max interval time
    {
      end = time(NULL);
      elapsed=difftime(end,start); // compare start and end times
      int empty_flag = 0;

      for(i=0;i<4;i++)// loop through producers
        {
          tmp[0] = '\0';
          buffer_B[0] = '\0';

          read(prod_fd[i],tmp,1); // read from producer fd

          if(tmp[0] != 0) // if tmp isnt empty
            {
              buffer_B[n] = tmp[0];
              buff_tracker(&timer, n);//keep track of how many accesses
              n++; // increment out buffer counter

              if(n > 1000) // if buffer is full
                {
                  printf("Buffer is full!\n");
                  n=999;
                }
            }
        }

      empty_flag = empty_flag ||(tmp[0]!=0); // set flag if empty pipes
      fflush(stdout);

      if(!empty_flag)
        {
          for(i=0;i<4;i++)// loop through consumers
            {
              if(n >0)
                {
                  char temp_buff[2];
                  sprintf(temp_buff,"%c",buffer_B[n-1]);
                  write(cons_fd[i],temp_buff,1);
                  buff_tracker(&timer, n);
                  n--;
                }
            }
        }
    }

  for(i=0;i<4;i++)// terminate the children
    {
      printf("Terminating childern\n");
      kill(prod_pids[i],SIGTERM);
      kill(cons_pids[i],SIGTERM);
      close(prod_fd[i]);
      close(cons_fd[i]);
    }

  avg_buffsize(buffer_B,increment,decrement);
  exit(0);
}

int producer(int fd,long p_time)
{
    char temp[2] = "\0\0";
    struct timespec pro_time1,pro_time2;
    struct timeval time_bef, time_aft,time_result;
    long total;
    pro_time1.tv_nsec= 1000000; // for nanoseconds
    pro_time1.tv_sec=0; // for seconds

    while(1)
      {
        gettimeofday(&time_bef,NULL); // record current time

        pro_time1.tv_nsec = (double)rand()/(double)RAND_MAX*p_time; //assign random time interval

        nanosleep(&pro_time1,NULL); // sleep the child

        sprintf(temp,"%c",rand_char());
        write(fd,temp,1); // write to our producer fd

         gettimeofday(&time_aft,NULL);

        timersub(&time_aft,&time_bef,&time_result); // record the time difference
        total = 1000 *time_result.tv_sec+time_result.tv_usec/1000;

        printf("Producer %i: value = %c, tp=%ldms\n",fd,temp[0],total);
        fflush(stdout);
      }

    exit(0);
}

int consumer(int fd,long c_time)
{
  char temp[2] = "\0\0";
  struct timespec con_time1,con_time2,time_bef;
  long total;
  con_time1.tv_nsec=1000000;
  con_time1.tv_sec=0;

  while(1)
    {
      clock_gettime(CLOCK_MONOTONIC_RAW,&time_bef); // read current time

      con_time1.tv_nsec = (double)rand()/(double)RAND_MAX*c_time; // assign random time interval

      nanosleep(&con_time1,NULL); // sleep our consumers

      read(fd,temp,1);

      if(temp[0] != '\0')
        {
          struct timespec time_diff;
          clock_gettime(CLOCK_MONOTONIC_RAW,&time_diff);

          long change_ms = (time_diff.tv_sec - time_bef.tv_sec) *1000 +
            (time_diff.tv_nsec - time_bef.tv_nsec) / 1000000 ;

          total = change_ms;

          printf("Consumer %i: value = %c, tc=%ldms\n",fd,temp[0],total);
          fflush(stdout);
        }
    }

  exit(0);
}

char rand_char()
{
  char product[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char x;
  int i = rand() % 26 ; // select a number between 1 & 26
  x=product[i];
  return x; // return our character
}


void buff_tracker(struct timeval* timer, int buffer_size)
{
  gettimeofday(timer,NULL);

  //struct timeval t_result;

  timersub(timer,&old_time,&t_result);

  old_time.tv_sec = timer->tv_sec; // update old time with the current time
  old_time.tv_usec = timer->tv_usec;

  long micro_time = 1000000*t_result.tv_sec + t_result.tv_usec; // convert to microseconds
  total_sum += micro_time*buffer_size;
  total_time += micro_time;

}
void avg_buffsize()
{
  long avg = total_sum / (float)total_time;
  printf("total_sum: %ld, total_time: %ld\n", total_sum, total_time);

  printf("Average Buffer size: %ld\n",avg);
}
