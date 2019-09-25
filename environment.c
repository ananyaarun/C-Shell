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

void func_set(char * input)
{

  char * value;
  int chk;
  chk =0;
  int chk1 = 0;
  char * var;
  char * temp = malloc (1 + strlen(input));
  strcpy(temp,input);

  input = strtok(NULL, " \t\r\n");
  if(input == NULL)
  {
  	printf("setenv has 0 arguments. Not valid\n");
  	return;
  }
  var = input;
  input = strtok(NULL, " \t\r\n");
  
  if(input != NULL)
  {
    value = input;
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
printf("setenv has more than 2 arguments. Not valid\n");
  }

  if(chk == 1 && chk1 == 0)
  {
  	printf("%s\n",var);
  	printf("%s\n",value);

  	setenv(var, value, 1);
  }
  else
  	setenv(var, "", 1);

  return;
}


void func_unset(char * input)
{
	char * var;
	char * temp = malloc (1 + strlen(input));
  strcpy(temp,input);

input = strtok(NULL, " \t\r\n");
  if(input == NULL)
  {
  	printf("wrong usage of unsetenv. Not valid\n");
  	return;
  }
  var = input;
  
  unsetenv(var);
  return;
	
}