#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include "parse.h"
#include "main.h"

void jobs()
{
    for(int i =0;i<1000;i++)
    {
    	if(array[i]>=0 && array[i] < 10000000)
    	{
	int count  = 0;
	printf("[%d] ",++count);
	char staa[100];
	if(procstatus[i])
		strcpy(staa,"Running");
	else
		strcpy(staa,"Stopped");
	printf("%s ",staa);
	printf("%s ",procname[i]);
	printf("[%d]\n",array[i]);
   }
}
}