#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "commands.h"
#include "main.h"

void change_directory(char *newdirectory)
{


char temp[1000],relpath[1000];
strcpy(temp,newdirectory);
char * temp1 = strtok(temp, " \t\r\n");

int val;
int val1;

newdirectory = strtok(NULL, " \t\r\n");
	
if(newdirectory == NULL || strlen(newdirectory)==0 || (strcmp(newdirectory,"")==0) )
{
	chdir(homepath);
	return;
}

char first = newdirectory[0];
char second = newdirectory[1];

if(strlen(newdirectory)>2){
strcpy(relpath,homepath);
strcat(relpath, "/");
strcat(relpath,&newdirectory[2]);
}

if(strcmp(newdirectory,"~")==0)
{
	chdir(homepath);
}

else if(strcmp(newdirectory,"~/")==0)
	chdir(homepath);

else if(first != '~' && second != '/')
{	
	val = chdir(newdirectory);
	if(val < 0)
		perror("Error");
}
else if(first == '~' && second == '/')
{
    val1 = chdir(relpath);
    if(val1 < 0)
		perror("Error");
}
    return;

}


//----------------------------------------------------------------------


int present_working_directory() {
   char cwd[1000];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}


//----------------------------------------------------------------------

void echo(char * input)
{
char temp[1000];
strcpy(temp,input);

char * token = strtok(NULL, " \t\r\n");
//printf("%s\n",token);

char temp1[1000];

int i;
char a = '\'';
char b = '\"';
int it=0;

if(token == NULL)
	printf("\n");
else{
	int s = strlen(temp);
for(i=5;i<strlen(temp);i++)
{
	if(temp[i]!= '\'' && temp[i]!= '\"' )
        temp1[it++]= temp[i];
}

for(i=0;i<it;i++)
	printf("%c",temp1[i]);
printf("\n");
}
return;

}