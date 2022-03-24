#include "shell.h"

int main(){
    while(1){
        if(PrintPrompt()){
            return -1;
        }

        if(GetCmd()){
            perror("Error");
            continue;
        }
        printf("%s", cmd);//for test and debug

        //解析命令
        
        //历史记录

        //创建进程
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
