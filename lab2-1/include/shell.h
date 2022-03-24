#ifndef SHELL_H

#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT_SIZE 1024
#define CMD_SIZE 1024
#define ARGS_MAX 128

char cmd[CMD_SIZE];
char * argv[ARGS_MAX];
int argc;

int PrintPrompt(void);
int GetCmd(void);

#endif