//run_in_term.cc

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "run-free.h"

int createScript(char *s)
{
  FILE *fp;
  unsigned int cLen;
  int retval = 0;
  int wLen = 0;

  //create file
  fp = fopen(RF_RUN_IN_TERM_NAME, "w");
  
  //get string lengths
  cLen = strlen(s)+1+strlen(RF_KBHIT_FILE_NAME);
  char *cL = new char[cLen];
  memset(cL, '\0',cLen);

  //format commandline
  //sprintf(cL, "%s;%s;rm %s", s, RF_KBHIT_FILE_NAME, RF_RUN_IN_TERM_NAME);
  sprintf(cL, "%s;%s", s, RF_KBHIT_FILE_NAME);

  //write command line to file
  if((wLen = fwrite(cL, cLen, 1, fp)) != 1)
    {
      printf("%d:%d\n",cLen,wLen);
      retval = -1;
    }

  fclose(fp);			// close file
  delete [] cL;			// delete array

  if(retval == 0)
    {
      //make file shell executable
      //if(chmod(RF_RUN_IN_TERM_NAME, S_IXUSR) != 0)
      //if(chmod(RF_RUN_IN_TERM_NAME, S_ISUID | S_IWUSR | S_IXUSR) != 0)
      if(chmod(RF_RUN_IN_TERM_NAME, S_IXUSR | S_IWUSR | S_IRUSR ) != 0)
	{
	  printf("ERROR IN CHMOD\n");
	  retval = -1;
	}
    }

  return retval;
}

int cleanUpScript()
{
  //see if file exists and delete file
  if(unlink(RF_RUN_IN_TERM_NAME) != 0)
    {
      printf("run-free ERROR: unlink failed");
      return -1;
    }
  
  return 0;
}




