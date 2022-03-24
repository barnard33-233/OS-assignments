#include "history.h"
#include "shell.h"

char * history[HISTORY_SIZE];
int his_top;

int InitHistory(){
    for(int i = 0; i < HISTORY_SIZE; i++){
        history[i] = NULL;
    }
    his_top = 0;
    return 0;
}

char* GetHistory(int num){
    if(num > HISTORY_SIZE){
        return NULL;
    }
    int pos = (his_top - num + HISTORY_SIZE) % HISTORY_SIZE;
    
    char * his_cmd;
    size_t size = strlen(history[pos]) + 1;
    if(his_cmd = malloc(size * sizeof(char))){
        perror("Error");
        return NULL;
    }
    strcpy(his_cmd, history[pos]);
    return his_cmd;
}

int SaveHistory(){
    char * new_cmd;
    size_t size = strlen(cmd) + 1;
    new_cmd = malloc(size * sizeof(char));
    if(!new_cmd){
        perror("Error");
        return -1;
    }
    strcpy(new_cmd, cmd);
    if(!history[his_top]){
        free(history[his_top]);
    }
    history[his_top] = new_cmd;
    his_top ++;
    return 0;
}