// #include <stdio.h>
#include "shell.h"
#include "sh-builtins.h"
#include "history.h"

int testmain(){
    FILE* fcommand;
    char fname[20] = "./test/command1.dat";
    fcommand = fopen(fname, "r");
    InitHistory();
    for(int i = 0; i <= 10; i++){
        fscanf(fcommand, "%s", cmd);
        // argc = 2;
        // argv[0] = "ls";
        // argv[1] = "-al";
        int ret = SaveHistory(cmd);
        fprintf(stderr, "SaveHistory return %d\n", ret);
        char* hiscmd = GetHistory(1);
        fprintf(stderr, "GetHistory hiscmd: %s\n", hiscmd);
        InfoHistory();
        free(hiscmd);
        fprintf(stderr, "----------------------\n");
    }
    fclose(fcommand);
    builtin_exit();
    return 0;
}