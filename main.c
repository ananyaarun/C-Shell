#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "main.h"
#include "parse.h"
#include "background.h"

char *homepath;
int homepathlength = 0;
int array[1000];
char *directoryname;
char * procname[1000];
int procstatus[1000];
int proccount[1000];
char hostname[1024];
struct passwd *pw;
char hist[100][100];
int size=0;
int parentpid;
int childpid;

void display_promt()
{

  int pathlength = 0;
  int i =0;
  int flag = 0;

  directoryname = getcwd(NULL,0);
  for(i=0;i<homepathlength;i++)
  	if(directoryname[i]!= homepath[i])
  	{
  		flag = 1;
  		pathlength++;
  		break;
  	}

  if(i >= homepathlength)
    printf("<%s%s@%s%s:~%s%s%s>","\x1B[1;34m",pw->pw_name,hostname,"\x1B[0m","\x1B[1;32m",&directoryname[i],"\x1B[0m");
  else 
    printf("<%s%s@%s%s:%s%s%s>","\x1B[1;34m",pw->pw_name,hostname,"\x1B[0m","\x1B[1;32m",directoryname,"\x1B[0m");

return;

}

void get_commands() {

    int count;
    count = 0;
    char *bufferinput;
    bufferinput = '\0';
    int flag;
    flag = 0;
    size_t buffersize;
    buffersize = 0;
    int chk;
    chk = 0;


    getline(&bufferinput, &buffersize, stdin);

    
    char i;
    int len = strlen(bufferinput);
    for(i=bufferinput[0];i!= 0;i++)
    {
    	if(i == 72){
    		chk = 1;
    		count++;
    	}
    }
    
    if(*bufferinput=='\0' || *bufferinput == '\n') { flag = 1; return;}

    if(*bufferinput != '\0' && *bufferinput != '\n' && chk != 1)
    {
        parse_command(bufferinput);
    }
    else
    {
    	int index;
    	if(len == 4)
    		index = 0;
    	else
    		index = (len-4)/3;
    	//printf("%s\n",hist[size - index - 1]);
        parse_command(hist[size - index - 1]);
    }

    return;
}

void check_bg()
{
int i;
i =0;
pid_t bg;
int status;
while((bg=waitpid(-1, &status, WNOHANG))>0)
    {
        
        for(i=0; i<1000; i++)
        {
            if(array[i]==bg)

            {
                printf("%s with pid %d exited normally\n",procname[i],bg);
                array[i] = 100000000;
                break;
            }
        }
    }

return;

}


int main()
{
  parentpid=getpid();

int i;
for (i=0;i<1000;i++)
  array[i] = -10000;

homepath = getcwd(NULL,0);
homepathlength = strlen(homepath);

  uid_t uid;
  uid = geteuid();
  pw = getpwuid(uid);

  hostname[1023] = '\0';
  gethostname(hostname, 1023);

  signal(SIGINT, SIG_IGN);  
  signal(SIGSTOP, SIG_IGN); 
  signal(SIGTSTP, SIG_IGN); 

 while(1)
 {
    check_bg();
 	display_promt();
 	get_commands();
 }
 return 0;
}


