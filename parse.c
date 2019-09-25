#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include "parse.h"
#include "commands.h"
#include "ls.h"
#include "background.h"
#include "main.h"
#include "pinfo.h"
#include "history.h"
#include "environment.h"
#include "job.h"

int z_flag = 0;
const char * compare1 = "<";
const char * compare2 = ">";
const char * compare3 = ">>";
char * globaltoken;

void parse_command(char * input)
{
	char * temp = malloc (1 + strlen(input));
	strcpy(temp,input);

	char * commandset[1000];

	char * token = strtok(temp, ";\n");
	int index = 0;

	while (token != NULL)
	{
		commandset[index++] = token;
		token = strtok(NULL, ";\n");
	}

	int i;
	for(i=0;i<index;i++)
	{
		pipe_command(commandset[i],0,0);
	}

	return;
}

void pipe_command( char * input, int var1, int var2)
{
	int x = dup(0);
	int y = dup(1);
	int fdin = dup(0);
	int fdout;
	char tempchar[1000];
	int i;
	int flag1;
	int flag2;
	int check;
	check = 0;
	int check1;
	check1 = 0;
	char * temp = malloc (1 + strlen(input));
	strcpy(temp,input);

	char * commandpipe[2000];

	char * token = strtok(temp, "|");
	if(token==NULL) 
		return;

	int index = 0;

	while (token != NULL)
	{
		commandpipe[index++] = token;
		token = strtok(NULL, "|");
	}	

	for(i=0;i<index;i++)
	{
		check = dup2(fdin,0);
		if(check == -1)
		{
			printf("Error , Something went wrong\n");
		}
		close(fdin);

		if(i+1 == index)
		{
			fdout = dup(y);
		}
		else
		{
			int piping[2];
			if(pipe(piping) < 0)
			{
				printf("Sorry piping failed");
			}
			fdout = piping[1];
			fdin = piping[0];
		}
		check1 = dup2(fdout,1);
		if(check1 < 0 && check1 == -1)
		{
			printf("Error , Something went wrong\n");
		}
		close(fdout);

		flag1 = 0;
		flag2 = 0;

		if(strchr(commandpipe[i], '<')!=NULL) // loop later
			flag1 = 1;
		if(strchr(commandpipe[i], '>')!=NULL) 
			flag2 = 1;

		if(flag1 != 0 || flag2 != 0)
			redirection_command(commandpipe[i],flag1,flag2);
		else
			exc_command(commandpipe[i]);
	}

	if(dup2(x, 0) <0) 
	{
		printf("error\n");
		return;
	}        

	if(dup2(y, 1)<0) 
	{
		printf("error\n");
		return;
	}  

	close(x);
	close(y);

	return; 

}

void redirection_command( char * input , int var1,int var2)
{
	int exflag;
	exflag = 0;
	int x = dup(0);
	int i;
	i  = 0 ;
	int y = dup(1);

	char exec[1000];
	exec[0] = '\0';

	char * temp = malloc (1 + strlen(input));
	strcpy(temp,input);

	char * commandredirect[2000];

	char * token = strtok(temp, " \t\r\n");
	if(token==NULL) 
		return;

	int index = 0;

	while (token != NULL)
	{
		commandredirect[index++] = token;
		token = strtok(NULL, " \t\r\n");
	}

	if(var1 == 1)
	{
		for(i=0; i<index; i++)
		{
			if(strcmp(commandredirect[i], compare1)==0)
			{
				if(!commandredirect[i+1]) 
				{
					printf("Wrong syntax expected something after <\n");
					return;
				}

				int filed;
				filed = open(commandredirect[i+1], O_RDONLY);

				if(filed < 0)
				{
					printf("Can't open file\n");
					return;
				}
				x = dup(0);

				int temp1 = dup2(filed, 0);

				if(temp1 == -1)
				{
					printf("Error\n"); 
					break;
				}

				close(filed);
				break;
			}

			strcat(exec, commandredirect[i]);
			strcat(exec, " ");

		}
	}

	while(i< index)
	{
		int filed1;
		int chk;
		chk = 0;

		if(strcmp(commandredirect[i], compare2)==0 && (var1 == 1 || var2 == 1)) 
		{
			filed1 = open(commandredirect[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(filed1 < 0)
				{
					printf("Can't open file\n");
					return;
				}
			chk = 1;
		}

		if(strcmp(commandredirect[i], compare3)==0 && (var1 == 1 || var2 == 1)) 
		{
			filed1 = open(commandredirect[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(filed1 < 0)
				{
					printf("Can't open file\n");
					return;
				}
			chk =1;
		}

		if(chk == 1)
		{
			if(!commandredirect[i+1]) 
			{
				printf("Wrong syntax expected something after <\n");
				return;
			}

			y = dup(1);

			int temp2 = dup2(filed1, 1);

			if(temp2 == filed1)
			{
				printf("Error\n"); 
				break;
			}

			close(filed1);
			break;
		}

		if(var1 == 0 && var2 == 1) 
		{
			strcat(exec, commandredirect[i]);
			strcat(exec, " ");
		}

		i = i+ 1;
	} 
	exc_command(exec);

	if(dup2(x, 0) <0) 
	{
		printf("error\n");
		return;
	}        

	if(dup2(y, 1)<0) 
	{
		printf("error\n");
		return;
	}  

	close(x);
	close(y);

	return; 

}

void ctrlz_handler(int sig) {

int flag;
flag = 0;

	if(getpid() == parentpid)
		flag = 1;
	else
		return;
	z_flag = 1;
    // signal(SIGTSTP, ctrlz_handler); 
} 


void ctrlc_handler(int sig) {
	int flag;
	flag = 0;
	int temp;
	temp = getpid();
	if(temp == parentpid)
		flag = 1;
	else
		return;

	if(childpid > 0)
	{
		kill(childpid, SIGINT);
	}
     signal(SIGINT, ctrlc_handler);
}

void ctrlzhandler2() {
	if(z_flag)
	{
		if(childpid != 0)
		{	
			//kill(childpid, SIGTTIN);
			int temp=0;
			setpgid(childpid, childpid);	
			temp = childpid;
			kill(childpid, SIGSTOP);
			background_add(globaltoken , temp, 1);	
			for(int i=0;i<1000;i++)
			{
				if(temp == array[i])
				{
					printf("hdh%s\n",procname[i]);
					procstatus[i] = 0;
					break;
				}
			}		
		}
	}
}
void exc_command(char * input)
{
	char * temp = malloc (1 + strlen(input));
	strcpy(temp,input);

	char * temp1 = malloc (1 + strlen(input));
	strcpy(temp1,input);

	char * token = strtok(temp, " \t\r\n");
	if(token == NULL) return;
	char * bgtoken = malloc (1 + strlen(token));
	strcpy(bgtoken,token);

	int check = 0;
	int length = 0;
	z_flag = 0;
	length = strlen(input);
	int i;
	for(i=0;i< length;i++)
	{
		if(input[i]=='&')
		{
			input[i] = '\0';
			check = 1;
			break;
		}

	}

	int length1 = 0;
	length1 = strlen(token);
	int j;
	for(j=0;j< length1;j++)
	{
		if(token[i]=='&')
		{
			token[i] = '\0';
			check = 1;
			break;
		}

	}

	char * command[1000];
	int count = 0;

	int retval = 0;
	int marker = 0;

	// signal(SIGINT, ctrlc_handler);
 //    signal(SIGTSTP, ctrlz_handler);

	if(token == NULL) return;
	if(strcmp(token,"exit")==0)
	{
		exit(0);
		marker = 1;
	}
	if(strcmp(token,"quit")==0)
	{
		exit(0);
		marker = 1;
	}
	if(strcmp(token,"cd")==0)
	{
		strcpy(hist[size++],temp1);
		change_directory(temp1);
		marker = 1;
	}
	if(strcmp(token,"pwd")==0)
	{
		strcpy(hist[size++],temp1);
		present_working_directory();
		marker = 1;
	}
	if(strcmp(token,"echo")==0)
	{
		strcpy(hist[size++],temp1);
		echo(temp1);
		marker = 1;
	}
	if(strcmp(token,"ls")==0)
	{
		strcpy(hist[size++],temp1);
		list_command(temp1);
		marker = 1;
	}
	if(strcmp(token,"pinfo")==0)
	{
		strcpy(hist[size++],temp1);
		pinfo_command(temp1);
		marker = 1;
	}
	if(strcmp(token,"history")==0)
	{
		strcpy(hist[size++],temp1);
		history_command(temp1);
		marker = 1;

	}
	if(strcmp(token,"setenv")==0)
	{
		strcpy(hist[size++],temp1);
		func_set(temp1);
		marker = 1;

	}
	if(strcmp(token,"unsetenv")==0)
	{
		strcpy(hist[size++],temp1);
		func_unset(temp1);
		marker = 1;

	}
	if(strcmp(token,"jobs")==0)
	{
		strcpy(hist[size++],temp1);
		jobs();
		marker = 1;

	}
	if(strcmp(token,"kjob")==0)
	{
		strcpy(hist[size++],temp1);
		kjob(temp1);
		marker = 1;

	}
	if(strcmp(token,"bg")==0)
	{
		strcpy(hist[size++],temp1);
		bg(temp1);
		marker = 1;

	}
	if(strcmp(token,"fg")==0)
	{
		strcpy(hist[size++],temp1);
		fg(temp1);
		marker = 1;

	}
	if(marker == 0)
	{
		strcpy(hist[size++],temp1);

		int status;
		pid_t proc = fork();
		childpid = proc;
		if(proc < 0) 
			printf("failed to create fork\n");

        globaltoken = token;
		// signal(SIGINT, ctrlc_handler);
  //       signal(SIGTSTP, ctrlz_handler); 


		if(proc == 0)
		{

			while(token!=NULL)
			{
				command[count++] = token;
				token = strtok(NULL, " \t\n\r");
			}
			retval = execvp(command[0],command);

			if(retval < 0)
			{ fprintf(stderr, "No command %s found ", command[0]); _exit(0); }
		}
		else
		{
			if(check==1) background_add(input,proc,check);
		} 

		if(proc > 0 && check == 0) 
		{
			signal(SIGINT, ctrlc_handler);
    		signal(SIGTSTP, ctrlz_handler);
			while(waitpid(proc, &status, WNOHANG)!=proc && !z_flag);
			ctrlzhandler2();
		}

	}
	z_flag = 0;
	return;
}
