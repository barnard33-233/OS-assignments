#ifndef HISTORY_H

#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_SIZE 10

extern char* history[HISTORY_SIZE];
extern int his_top;

int InitHistory(void);
int SaveHistory(void);
char* GetHistory(int num);

#endif