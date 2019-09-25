#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "parse.h"
#include "commands.h"
#include "ls.h"
#include "background.h"
#include "main.h"

void background_add(char * input, int procid, int flag)
{
	printf("%d\n",procid);

   int i;
   int flag1 = 0;
   int marker = -1;

   if(flag == 1)
   {
      for(i=0;i<1000;i++)
      { 	
      	if(array[i] < 0)
   		{
   		   array[i] = procid;
   		   // printf("%d ughhh %d \n",i,array[i]);
   		   marker = 1;
   		   procname[i] = input;
            procstatus[i] = 1;
   		   break;
   		}

      }
   }
   return;
}