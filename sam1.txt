#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <sys/dir.h>  
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <time.h>

#include "parse.h"
#include "commands.h"
#include "main.h"
#include "ls.h"

void list_command(char * input)
{
DIR *cur;
struct dirent *files;
struct stat fstat;
char buf[512];
char date[512];

char temp[1000];
strcpy(temp,input);

input = strtok(NULL, " \t\n\r");

char tempa[1000];
if(input != NULL)
strcpy(tempa,input);

char a,b;
int check =0 ;

if(strlen(tempa)>2)
{
check = 1;
a= tempa[0];
b= tempa[1];
}

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

int dirname = 0;
char dir[1000];
char tempdir[1000];
char dirf[1000];

if(input == NULL)
	flag1 = 1;
// else if(strcmp(input,"-l")==0 || (a == '-' && b == 'l') && (strcmp(input,"-la")!=0))
	else if((strcmp(input,"-l")==0))
	{flag2 = 1;}

else if((strcmp(input,"-a")==0))
	flag3 = 1;
else if((strcmp(input,"-la")==0) || (strcmp(input,"-al")==0))
	flag4 = 1;
else
{
	dirname = 1;
	strcpy(dir,input);
}

input = strtok(NULL, " \t\n\r");

if(input != NULL)
{
	dirname = 1;
	strcpy(dir,input);
}

char first = dir[0];
char second = dir[1];

if(dirname == 0 || dir == NULL)
{
	getcwd(tempdir, sizeof(tempdir));
    strcpy(dirf, tempdir);
}
else if(strcmp(dir,"~")==0)
	strcpy(dirf,homepath);
else if(strcmp(dir,"~/")==0)
	strcpy(dirf,homepath);
else if((strlen(dir)>2) && (first == '~') && (second == '/'))
{
	strcpy(dirf,homepath);
	strcat(dirf, &dir[1]);
}
else
{
	getcwd(tempdir, sizeof(tempdir));
	strcpy(dirf,tempdir);
	strcat(dirf,"/");
	strcat(dirf,dir);
}
    
//printf("%s\n",dirf);
//printf("%d\n",flag2);

char tempp[1000];
char tep;
int i=0;

// if(strcmp(dirf,"-a")==0)
// {
//     for(i=0;i<strlen(dirf)-3;i++)
//     {
//     	tempp[i] = dirf[i];
//     }
//     strcpy(dirf,tempp);
//     printf("%s\n",dirf);
// 	flag2 = 1;
// }
// if(strcmp(dirf,"-l")==0)
// 	flag3 = 1;

cur=opendir(dirf);
int check2 = 0;
if(cur==NULL && flag2 == 0  && flag3 == 0)
		{
			check2=1;
			printf("cannot access %s :no such directory\n", dirf);
			return;
}

if(flag1 == 1 && check2 == 0)
{
while((files=readdir(cur))!=NULL)
		{
			if((strcmp(files->d_name , ".")!=0) && (strcmp(files->d_name,"..")!=0))
				printf("%s\n",files->d_name);
		}

}

else if (flag2 == 1 && check2 == 0)
{
	// printf("hi\n");
	while((files=readdir(cur))!=NULL)
			{
			if((strcmp(files->d_name , ".")!=0) && (strcmp(files->d_name,"..")!=0))
			{
        			stat(files->d_name, &fstat);
					printf( (S_ISDIR(fstat.st_mode)) ? "d" : "-");
					printf( (fstat.st_mode & S_IRUSR) ? "r" : "-");
					printf( (fstat.st_mode & S_IWUSR) ? "w" : "-");
					printf( (fstat.st_mode & S_IXUSR) ? "x" : "-");
					printf( (fstat.st_mode & S_IRGRP) ? "r" : "-");
					printf( (fstat.st_mode & S_IWGRP) ? "w" : "-");
					printf( (fstat.st_mode & S_IXGRP) ? "x" : "-");
					printf( (fstat.st_mode & S_IROTH) ? "r" : "-");
					printf( (fstat.st_mode & S_IWOTH) ? "w" : "-");
					printf( (fstat.st_mode & S_IXOTH) ? "x" : "-");
                    printf("\t");

					uid_t usr_id = fstat.st_uid; 
                    gid_t grp_id = fstat.st_gid;
                    struct group *grp = getgrgid(grp_id);
                    struct passwd *usr;
                    usr = getpwuid(fstat.st_uid);
                    strftime(date, sizeof(date), "%b %d %H:%M", localtime(&(fstat.st_mtime)));
    
                    printf("%s\t", usr->pw_name);
                    printf("%s\t", grp->gr_name);
                    printf("%ld\t", fstat.st_size);
                    printf("%s\t",date);
                    printf("%s\n", files->d_name);
					  
}
}
}


else if (flag3 == 1 && check2 == 0)
{
	while((files=readdir(cur))!=NULL)
			{
			
                    printf("%s\n", files->d_name);
					  
}
}

else if (flag4 == 1 && check2 == 0)
{
	while((files=readdir(cur))!=NULL)
			
			
			{
        			stat(files->d_name, &fstat);
					printf( (S_ISDIR(fstat.st_mode)) ? "d" : "-");
					printf( (fstat.st_mode & S_IRUSR) ? "r" : "-");
					printf( (fstat.st_mode & S_IWUSR) ? "w" : "-");
					printf( (fstat.st_mode & S_IXUSR) ? "x" : "-");
					printf( (fstat.st_mode & S_IRGRP) ? "r" : "-");
					printf( (fstat.st_mode & S_IWGRP) ? "w" : "-");
					printf( (fstat.st_mode & S_IXGRP) ? "x" : "-");
					printf( (fstat.st_mode & S_IROTH) ? "r" : "-");
					printf( (fstat.st_mode & S_IWOTH) ? "w" : "-");
					printf( (fstat.st_mode & S_IXOTH) ? "x" : "-");
                    printf("\t");

					uid_t usr_id = fstat.st_uid; 
                    gid_t grp_id = fstat.st_gid;
                    struct group *grp = getgrgid(grp_id);
                    struct passwd *usr;
                    usr = getpwuid(fstat.st_uid);
                    strftime(date, sizeof(date), "%b %d %H:%M", localtime(&(fstat.st_mtime)));
    
                    printf("%s\t", usr->pw_name);
                    printf("%s\t", grp->gr_name);
                    printf("%ld\t", fstat.st_size);
                    printf("%s\t",date);
                    printf("%s\n", files->d_name);
					  
}

}

else
{
	while((files=readdir(cur))!=NULL)
		{
			if((strcmp(files->d_name , ".")!=0) && (strcmp(files->d_name,"..")!=0))
				printf("%s\n",files->d_name);
		}

}

return;
}

//-------------------------------------------------------------


 
