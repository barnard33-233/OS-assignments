/*
 * built in commands
 * 
 */
#ifndef MYSH_HAS_BUILTINS_H

#define MYSH_HAS_BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int builtin_cd(void);
/*
 * command cd:
 * cd <directory>
 * argc == 2
 */


int builtin_dirs(void);
/*
 * command dirs:
 * dirs
 * argc == 1
 */


int builtin_history(void);
/*
 * command history:
 * 1. history
 * argc == 1
 * 2. history <number>
 * argc == 2
 */

//int exit(void); TODO
//To release resources
#endif