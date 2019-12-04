# C- Shell 
## Assignment 3 By 20171019

## Usage
- make
- ./shell

## Features
- shell prompt
- cd , echo, pwd commands
- ls command with flags -l -a -la -al
- background and foreground process
- pinfo command
- history n command
- input output redirection
- piping
- piping with redirection
- jobs handling (fg,bg,overkill,kjobs etc)
- ctrl z and ctrl c signal handling
- setenv and unsetenv

## Files

### background.c
- function to maintain an array of newly added background process

### commands.c
- implementation of cd, pwd and echo command

### environment.c
- implementation of setenv and unsetenv

### history.c
- implementation of history and history n command

### job.c
- implementation of jobs, kjobs, bg , fg and overkill commands

### ls.c
- implementation of the ls command with its various flags

### main.c
- main shell file that in a while loop calls the prompt, gets input from user and checks for finished background process

### parse.c
- parses the input based on tokenization, piping and redirection (;) and calls functions for the respective commands accordingly after parsing

### pinfo.c
- implementation of the pinfo and pinfo pid command
