#include "shell.h"
#include "history.h"
#include "sh-builtins.h"

char cmd[CMD_SIZE];
char * argv[ARGS_MAX];
int argc;

int main(){
    InitHistory();
    while(1){
        if(PrintPrompt()){
            return -1;
        }

        if(GetCmd()){
            perror("Error");
            continue;
        }
        fprintf(stderr, "%s", cmd);//for test and debug

        //解析命令
        
        int cmd_stat = Command();
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
    char prompt[PROMPT_SIZE] = "";
    strcat(prompt, "[");
    strcat(prompt, user_name);
    strcat(prompt, " ");
    strcat(prompt, current_dir);
    strcat(prompt, "]$ ");
    printf("%s", prompt);

    return 0;
}

int GetCmd(){
    if(fgets(cmd, CMD_SIZE, stdin) == NULL){
        perror("Error");
        return -1;
    }
    cmd[CMD_SIZE - 1] = '\0';
    return 0;
}

pid_t Createp(){
/*
 * create a child process to execute command.
 *
 * return value of this function:
 * 0 for fail to create child process
 * -1 for child process fail to execute
 * other positive intiger(pid_t) for success to execute 
 * (and return value is the pid of child)
 */
    pid_t pid;
    pid = fork();
    if(pid == 0){
        execvp(argv[0], argv);
    }
    else if(pid > 0){
        return wait(NULL);
    }
    else{
        perror("Error");
        return 0;
    }
}

int Command(){
    char* name = argv[0];
    int run = 0;
    //traverse the transfer table and call builtin command func.
    for(int i = 0; i < builtin_cnt; i++){
        if(strcmp(name, builtin_name[i]) == 0){
            int (*builtin)(void) = builtin_func;
            if(builtin()){
                perror("Error");
                return -1;
            }
            run = 1;
        }
    }
    if(!run){
        pid_t cpid = Createp();
        if (cpid > 0){
            return 0;
        }
        else{
            return -1;
        }
    }
}
