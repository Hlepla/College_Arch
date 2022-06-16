#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> // data types
#include <sys/stat.h> // data returned by the stat funtion
#include <errno.h> // for error codes
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>


void retrieve_stat(struct dirent* dir_entry);
int retrieve_guess(struct dirent* dir_entry, char dirname[]);

int main(int argc, char **argv)
{
  FILE *fp ;
  struct dirent *dirEntry;
  DIR *dp;
  char filename[256], dirname[1024];

  if(getcwd(dirname,sizeof(dirname)) != NULL) // find the current directory path
    {
      fprintf(stdout, "Current working dir: %s\n", dirname);
    }

  else
    {
      perror("getcwd() error");
      return 0;
    }

  if(argc > 1 && (strcmp(argv[1],"-t") == 0)) // if the "-t" option
    {
      printf("Argv[1] is: %s\n",argv[1]);
      if((dp = opendir(dirname)) == NULL)
        return -1;

      while((dirEntry = readdir(dp)) != NULL)
        {
          printf("%s\n",dirEntry->d_name);
          retrieve_stat(dirEntry);
        }
      closedir(dp);

    }
  else if (argc > 1 && (strcmp(argv[1],"-f") == 0 )) // if the "-f" option
    {
      printf("Argv[1] is: %s\n",argv[1]);
      if((dp = opendir(dirname)) == NULL)
        return -1;

      while((dirEntry = readdir(dp)) != NULL)
        {
          printf("%s\n",dirEntry->d_name);
          retrieve_guess(dirEntry,dirname);
        }
      closedir(dp);

    }

  else // if no options given, just print
    {
      if((dp = opendir(dirname)) == NULL)
        return -1;

      while((dirEntry = readdir(dp)) != NULL)
        {
          printf("%s\n",dirEntry->d_name);
        }
      closedir(dp);
    }
}


void retrieve_stat(struct dirent* dir_entry)
{
  struct stat buffer;

  if(!stat(dir_entry->d_name, &buffer))
    {
      printf("Date Modified:   %s",ctime(&buffer.st_mtime));
      printf("Date Accessed:   %s",ctime(&buffer.st_atime));
      printf("Last status change: %s\n",ctime(&buffer.st_ctime));
    }
  else
    {
      printf("stuff\n");

    }
}

int retrieve_guess(struct dirent* dir_entry,char dirname[1024])
{
  FILE *fp ;
  char curr , prev, char_line[256];
  int buffer[128], i=0 ;

  fp = fopen(dir_entry->d_name,"r");

  if(fp == NULL)
    {
      printf("An error has occured! Perhaps missing a file? \n");
    }

  fscanf(fp,"%s",char_line);

  struct stat buf;
  if(!stat(dir_entry->d_name,&buf))
    {
      if(S_ISREG(buf.st_mode)) // ignore directories
        {
          if((strcmp(char_line,"%!PS-Adobe")==0)) // check for postscript file
            {
              printf("Type: postscript file\n");
              goto end ;

            }
          fseek(fp,SEEK_SET,0); // reset file pointer to zero

          if(fgetc(fp) == 127 && fgetc(fp) == 'E' && fgetc(fp) == 'L' && fgetc(fp) == 'F') // check for elf file
            {
              printf("Type: ELF file\n");
              goto end;
            }

          while(1) // check for DOS file
            {
              prev = curr;
              if((curr = fgetc(fp)) != EOF)
                {
                  if((curr > 128) || ((curr == 10) && (prev != 13)))
                    {
                      fseek(fp,SEEK_SET,0);
                      break;
                    }
                }

              else
                {
                  printf("Type: DOS file\n");
                  break;
                }

            }

          fseek(fp,SEEK_SET,0);

          int ASCII_flag = 1;

          while((curr = fgetc(fp)) != EOF) // itterate through file to check for ASCII
            {
              if (curr > 128 || curr < 0)
                ASCII_flag = 0;

            }

          if(ASCII_flag == 1 )
            {
              printf("Type: ASCII file\n");
              goto end;
            }

          fseek(fp,SEEK_SET,0);
          prev = fgetc(fp);


        }

    end: ;

    }
}
