#include "history.h"
#include "shell.h"

char * history[HISTORY_SIZE]; //remember to free this before exit
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
    if(!(his_cmd = malloc(size * sizeof(char)))){
        perror("GetHistory malloc error");
        return NULL;
    }
    strcpy(his_cmd, history[pos]);
    return his_cmd;
}

int SaveHistory(char* std_cmd){
    char * new_cmd;
    size_t size = strlen(std_cmd) + 1;
    new_cmd = malloc(size * sizeof(char));
    if(!new_cmd){
        perror("SaveHistory malloc error");
        return -1;
    }
    strcpy(new_cmd, std_cmd);
    if(!history[his_top]){
        free(history[his_top]);
    }
    history[his_top] = new_cmd;
    his_top = (his_top + 1) % HISTORY_SIZE;
    return 0;
}

void ExitHistory(){
    for(int i = 0; i < HISTORY_SIZE; i++){
        if(!history[i]){
            free(history[i]);
        }
    }
}

#ifdef DEBUG
int InfoHistory(){
    fprintf(stderr, "his_top: %d\n", his_top);
    for(int i = 0; i < HISTORY_SIZE; i++){
        if(history[i]){
            fprintf(stderr, "%3d: %s", i, history[i]);
        }
        else{
            fprintf(stderr, "%3d, NULL", i);
        }
        if(i == his_top){
            fprintf(stderr, "\t<-\n");
        }
        else{
            fprintf(stderr, "\n");
        }
    }
    return 0;
}

#else
int InfoHistory(){
    fprintf(stderr, "Not define DEBUG\n");
    return 0;
}
#endif