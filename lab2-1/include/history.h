/*
 * header for history feature
 * API
*/
#ifndef HISTORY_H

#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_SIZE 10
//change this macro to extend the size of history

extern char* history[HISTORY_SIZE];
extern int his_top;

int InitHistory(void);// should be called before everything start
int SaveHistory(void);//save cmd to history
char* GetHistory(int num);// get a history id==num

#endif