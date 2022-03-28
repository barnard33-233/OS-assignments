#ifndef SHELL_H

#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PROMPT_SIZE 1024
#define CMD_SIZE 1024
#define ARGS_MAX 128

extern char cmd[CMD_SIZE];
extern char * argv[ARGS_MAX];
extern int argc;

int PrintPrompt(void);// print a prompt
int GetCmd(void);// read a line from stdin and save it to `cmd`

//TODO
// int AnalyzeCmd(void);
int Command(void);

#endif