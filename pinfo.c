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
#include "pinfo.h"

void pinfo_command(char * input)
{

pid_t pidinfo; 
char buf[1000],ch;

char stats[1000];
char exec[1000];
char * line_buffer = malloc(1000 * sizeof(char)); 
	
long unsigned int virtual_mem = 0;

char *temp = malloc (1 + strlen(input));
strcpy(temp,input);

char * token = strtok(NULL, " \t\r\n");

if(token == NULL)
{
pidinfo = getpid();
printf("Pid-- %d\n", pidinfo);
}
int pidstring;

if(token != NULL)
{
pidstring = atoi(token);
pidinfo = pidstring;
printf("Pid-- %d\n",pidstring);
}
	
	sprintf(stats, "/proc/%d/stat", pidinfo);
	sprintf(exec, "/proc/%d/exe", pidinfo);

	FILE* fp = fopen(stats, "r");
	if(!fp) 
	{
        printf("Error: Process doesn't exist\n");
		//fclose(fp);
		return;
	}

    if(fp)
    {
		fscanf(fp, "%s", buf);
		fscanf(fp, "%s", buf);
		fscanf(fp," %c", &ch);
        printf("Process status -- %c\n", ch);
        fscanf(fp, "%lu", &virtual_mem);
		printf("Virtual memory -- %lu kB\n", virtual_mem);

		fclose(fp);
    }

    long long int len = readlink(exec, line_buffer, 1000);
    if (len < 0)
        printf("Error: Permission Denied\n");
    if(len >= 0) 
    {
        line_buffer[len] = '\0';
        int i;
        int flag = 0;
         for(i=0;i<homepathlength;i++)
  	if(line_buffer[i]!= homepath[i])
  	{
  		flag = 1;
  		break;
  	}

        if(i>= homepathlength)
        printf("Executable Path -- ~%s\n", &line_buffer[i]);
        else
        printf("Executable Path -- ~%s\n", line_buffer);

    }
return;
}





