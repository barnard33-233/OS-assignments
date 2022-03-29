#include "sh-builtins.h"
#include "shell.h"
#include "history.h"

int (*builtin_func[])(void) = {
    builtin_exit,
    builtin_cd,
    builtin_dirs,
    builtin_history
};

char *builtin_name[] = {
    "exit",
    "cd",
    "dirs",
    "history"
};

const int builtin_cnt = 4;

int builtin_dirs(){
    if (argc != 1){
        return -1;
    }
    char * cwd = NULL;
    cwd = getcwd(NULL, 0);
    if (cwd){
        printf("%s\n", cwd);
        return 0;
    }
    return -1;
}

int builtin_cd(){
    if(argc == 2){
        return chdir(argv[1]);
    }
    return -1;
}

int builtin_history(){
    if(argc > 2){
        return -1;
    }
    else if(argc == 2){
        char * p;
        int his_id = (int)strtol(argv[1], &p, 10); //his_id should be a natural number
        if((his_id <= 0) || (his_id > HISTORY_SIZE)){
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

int builtin_exit(){
    ExitHistory();
    printf("Bye :-)\n");
    exit(0);
}