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
	int count = 0;
    for(int i =0;i<1000;i++)
    {
    	if(array[i]>=0 && array[i] < 10000000)
    	{
	
	printf("[%d] ",++count);
	proccount[i] = count;
	char staa[100];
	if(procstatus[i]!=0)
		strcpy(staa,"Running");
	if(procstatus[i]==0)
		strcpy(staa,"Stopped");
	printf("%s ",staa);
	printf("%s ",procname[i]);
	printf("[%d]\n",array[i]);
   }
}
}

void jobs1()
{
	//printf("ehjehuje\n");
	int count = 0;
    for(int i =0;i<1000;i++)
    {
    	if(array[i]>=0 && array[i] < 10000000)
    	{
	
	//printf("[%d] ",++count);
	proccount[i] = count;
	char staa[100];
	if(procstatus[i]!=0)
		strcpy(staa,"Running");
	if(procstatus[i]==0)
		strcpy(staa,"Stopped");
	//printf("%s ",staa);
	//printf("%s ",procname[i]);
	//printf("[%d]\n",array[i]);
   }
}
}




void kjob(char * input)
{
  int one;
  int chk;
  chk =0;
  int chk1 = 0;
  int two;
  char * temp = malloc (1 + strlen(input));
  strcpy(temp,input);

  input = strtok(NULL, " \t\r\n");
  if(input == NULL)
  {
  	printf("expected 2 arguments Not valid\n");
  	return;
  }
  sscanf(input, "%d", &two);
  input = strtok(NULL, " \t\r\n");
  
  if(input != NULL)
  {
    sscanf(input, "%d", &one);
    chk = 1;
  }

  if(input != NULL)
  {
      input = strtok(NULL, " \t\n\r");
      if(input != NULL)
      chk1 = 1;
  }

  if(chk1 == 1)
  { 
    printf("expected 2 arguments. Not valid\n");
  }
int tempp =0;
  // printf("%d %d\n",one,two);
for(int i =0;i<1000;i++)
{
	if(two == proccount[i])
	tempp = i;
}
//printf("%d %d\n",array[tempp],one);

  int val = kill(array[tempp], one);
}

void fg(char * input)
{
// 	int count =0;

// 	for(int i =0;i<1000;i++)
//     {
//     	if(array[i]>=0 && array[i] < 10000000)
//     	{
	
// 	//printf("[%d] ",++count);
// 	proccount[i] = count;
// }
// }
	//jobs1();
   int var;
	char * temp = malloc (1 + strlen(input));
  strcpy(temp,input);

input = strtok(NULL, " \t\r\n");
  if(input == NULL)
  {
  	printf("wrong usage of fg. Not valid\n");
  	return;
  }
  int tempp = 0;
  	sscanf(input, "%d", &var);
	// printf("%d\n",var);
  	for(int i=0; i<1000; i++)
    {
    	// printf("%d\n",proccount[i]);
        if(var==proccount[i])
        {
        	tempp = array[i];
            array[i] = 100000000;
            proccount[i] = 100000000;
            //printf("huwdhu11111111111\n");
            break;
        }
    }
    //printf("DBUG1: %d\n", tempp);
    kill(tempp, SIGCONT);
           int status;
			//signal(SIGINT, ctrlc_handler);
    		//signal(SIGTSTP, ctrlz_handler);

            while(waitpid(tempp, &status, WNOHANG)!=tempp);
			//ctrlzhandler2();


}





void bg(char * input)
{
// 	int count =0;
// 	for(int i =0;i<1000;i++)
//     {
//     	if(array[i]>=0 && array[i] < 10000000)
//     	{
	
// 	//printf("[%d] ",++count);
// 	proccount[i] = count;
// }
// }
	 int var;
	char * temp = malloc (1 + strlen(input));
  strcpy(temp,input);

input = strtok(NULL, " \t\r\n");
  if(input == NULL)
  {
  	printf("wrong usage of bg. Not valid\n");
  	return;
  }
  sscanf(input, "%d", &var);
int tempp =0;
  // printf("%d %d\n",one,two);
for(int i =0;i<1000;i++)
{
	if(var == proccount[i])
	tempp = i;
}
procstatus[tempp] = 1;
kill(array[tempp], SIGCONT);
}





void overkill(char *input) {

    int i = 0;

    for(i=0; i<1000; i++)
    {
        if(array[i]>=0 && array[i] <= 1000000)
        {
            kill(array[i], 9);
            array[i] = 100000000; 
        }
    }

    return;
}