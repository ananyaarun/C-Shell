myshell: main.c parse.c commands.c ls.c background.c pinfo.c history.c 
	gcc -o shell main.c parse.c commands.c ls.c background.c pinfo.c history.c environment.c job.c -I.
