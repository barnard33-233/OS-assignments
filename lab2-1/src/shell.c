#include "shell.h"
#include "history.h"
#include "sh-builtins.h"
// #include "test1-0.c"

#ifdef DEBUG
extern int testmain(void);
#endif

char cmd[CMD_SIZE];
char * argv[ARGS_MAX];
int argc;

int main(){
    #ifdef DEBUG
    testmain();
    return 0;
    #endif
    InitHistory();
    while(1){
        if(PrintPrompt()){
            return -1;
        }

        if(GetCmd()){
            perror("Error");
            continue;
        }
        fprintf(stderr, "%s\n", cmd);//for test and debug

        
        
        //int cmd_stat = Command();
        //历史记录

        
    }
    return 0;
}

int PrintPrompt(){
    char * user_name;
    char * current_dir;

    user_name = getlogin();
    current_dir = getcwd(NULL, 0);
    if (!current_dir || !user_name){
        perror("Error");
        return -1;
    }
    printf("[%s %s]$ ", user_name, current_dir);
    return 0;
}
