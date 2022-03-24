#ifndef MYSH_HAS_BUILTINS_H

#define MYSH_HAS_BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int builtin_cd(void);
int builtin_dirs(void);
int builtin_history(void);

#endif