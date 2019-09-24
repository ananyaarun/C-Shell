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
#include "history.h"

void history_command(char * input)
{
	char *temp = malloc (1 + strlen(input));
	strcpy(temp,input);

	char * token = strtok(NULL, " \t\r\n");
	int i;
	int tot;
	if(size >= 10)
			tot = 10;
		else
			tot = size;

	if(token == NULL)
	{
		

		for(i=size-tot;i<size;i++)
		{
			printf("%s\n",hist[i]);
		}
	}
	else 
	{
		int j = atoi(token);
		if(size >= j)
		{
			for(i=size-j;i<size;i++)
			{
				printf("%s\n",hist[i]);
			}
		}
		else
		{	
			//printf("%d\n",tot);
			for(i=size-tot;i<size;i++)
			{
				printf("%s\n",hist[i]);
			}
        }

	}

	return;
}

