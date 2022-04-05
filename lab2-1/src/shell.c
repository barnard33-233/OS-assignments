#include "shell.h"
#include "history.h"
#include "sh-builtins.h"
// #include "test1-0.c"
// #include "test2.c"

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
            perror("Get command error");
            continue;
        }
        // fprintf(stderr, "%s\n", cmd);//for test and debug

        if(AnalyzeCmd()){
            perror("Analyze cmd error");
            FreeArgv();
            continue;
        }

        if(!Command()){
            char* std_cmd = FormStdCmd();
            SaveHistory(std_cmd);
            free(std_cmd);
        }

        FreeArgv();
    }
    return 0;
}

int PrintPrompt(){
    char * user_name;
    char * current_dir;

    user_name = getlogin();
    current_dir = getcwd(NULL, 0);
    if (!current_dir || !user_name){
        perror("prompt error");
        return -1;
    }
    printf("[%s %s]$ ", user_name, current_dir);
    return 0;
}
