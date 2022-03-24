#include "sh-builtins.h"
#include "shell.h"
#include "history.h"

int builtin_dirs(){
    char * cwd = NULL;
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    return 0;
}

int builtin_cd(){
    return chdir(argv[1]);
}

int builtin_history(){
    if(argc > 1){
        char * p;
        int his_id = (int)strtol(argv[1], &p, 10); //his_id should be a natural number
        if(his_id <= 0 | his_id > HISTORY_SIZE){
            printf("No such command in history");
            return -1;
        }
        int pos;
        pos = (his_top - his_id + HISTORY_SIZE) % HISTORY_SIZE;
        if(history[pos]){
            printf("%s\n", history[pos]);
            return 0;
        }
        printf("No such command in history");
        return -1;
    }
    int cnt = 0;
    char * buf[HISTORY_SIZE];
    for (int i = 0; i < HISTORY_SIZE; i++){
        int pos = (his_top - i - 1 + HISTORY_SIZE) % HISTORY_SIZE;
        if(history[pos]){
            buf[cnt] = history[pos];
            cnt ++;
        }
    }
    while(cnt > 0){
        printf("%d %s", cnt, buf[cnt - 1]);
        cnt --;
    }
    return 0;
}