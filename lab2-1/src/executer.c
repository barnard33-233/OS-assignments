#include "shell.h"
#include "sh-builtins.h"


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
    return 0;
}

int Command(){
    char* name = argv[0];
    int run = 0;
    //traverse the transfer table and call builtin command func.
    for(int i = 0; i < builtin_cnt; i++){
        if(strcmp(name, builtin_name[i]) == 0){
            int (*builtin)(void) = builtin_func[i];
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
    return 0;
}