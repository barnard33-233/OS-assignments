#include "shell.h"
#include "history.h"

int Spliter(char*, char**, int*);

int RecognizeHisSym(char*);//识别历史记录算符，若是则返回查询的条目id,否则返回-1

int GetCmd(){
    // memset(NULL, cmd, CMD_SIZE);
    if(fgets(cmd, CMD_SIZE, stdin) == NULL){
        perror("Error");
        return -1;
    }
    cmd[CMD_SIZE - 1] = '\0';
    int len = strlen(cmd);
    if(cmd[len - 1] == '\n'){
        cmd[len - 1] = '\0';
    }
    return 0;
}

void FreeArgv(){
    for(int i=0;i<argc;i++){
        fprintf(stderr, "\nagrv[%d]=%s length=%ld", i, argv[i],strlen(argv[i]));
        free(argv[i]);
    }
}

int Spliter(char* string, char** tmp_argv, int * tmp_argc){
    char* string_copy = malloc(sizeof(char) * strlen(string));
    tmp_argv = malloc(sizeof(char*) * ARGS_MAX);
    char* out;
    int cnt = 0;
    out = strtok(string_copy, " ");
    tmp_argv[cnt] = malloc(sizeof(char) * strlen(out));
    strcpy(tmp_argv[cnt], out);
    cnt++;

    while (out){
        out = strtok(NULL, " ");
        if(out) {
            tmp_argv[cnt] = malloc(sizeof(char) * strlen(out));
            strcpy(tmp_argv[cnt], out);
        }
        else {
            tmp_argv = NULL;
        }
        cnt ++;
    }
    
    *tmp_argc = cnt;
    free(string_copy);
    return 0;
}

int RecognizeHisSym(char* string){
    if(string[0] == '!'){
        if(strlen(string) == 3 && string[1] == '!'){
            return 1;
        }
        char* endptr;
        long his_id = strtol(string + 1, &endptr, 0);
        if(his_id > 0 && endptr[0] == '\0'){
            return his_id;
        }
        return -1;
    }
    return -1;
}

// TODO：对于超出ARGS_MAX 的特判与错误返回
int AnalyzeCmd(){
    int len = strlen(cmd);
    char* cmd_copy = malloc(sizeof(char) * len);
    strcpy(cmd_copy, cmd);

    int cnt;
    char** tmp_argv;    //存直接对字符串切割的结果
    Spliter(cmd_copy, tmp_argv, &cnt);

    argc = 0;
    for(int i = 0; i < cnt; i++){
        int his_id;

        // 对历史记录字符串进行特殊处理
        if((his_id = RecognizeHisSym(tmp_argv[i])) > 0){
            char* his = GetHistory(his_id);
            if(his == NULL){
                perror("Error");

                free(cmd_copy);
                for(int j = 0; j < cnt; j ++){
                    free(tmp_argv[i]);
                }
                free(tmp_argv);

                return -1;
            }
            int his_argc;
            char** his_argv;
            Spliter(his, his_argv, &his_argc);
            for (int j = 0; j < his_argc; j ++){
                argv[argc] = his_argv[j];
                argc ++;
            }
            free(his_argv);
        }
        // 直接把切割结果拷贝到argv
        else {
            argv[argc] = tmp_argv[i];
            argc ++;
        }
    }
    free(cmd_copy);
    free(tmp_argv);
    return 0;
}

char* FormStdCmd(){
    int len = CMD_SIZE;
    char* std_cmd = malloc(sizeof(char) * CMD_SIZE);
    std_cmd[0] = '\0';
    for(int i = 0; i < argc; i ++){
        if(strlen(std_cmd) + strlen(argv[i]) >= len){
            len = len * 2;
            std_cmd = realloc(std_cmd, len);
        }
        strcat(std_cmd, argv[i]);    
    }
    return std_cmd;
}

void InfoArg(){
    fprintf(stderr, "argc: %d\n", argc);
    for(int i = 0; i < argc; i++){
        fprintf(stderr, "%s\n", argv[i]);
    }
}

// int AnalyzeCmd(){
//     int len = strlen(cmd);
//     //split cmd by blank,count each argv[]'s length
//     char *copy;//strtok function will distroy cmd's integrality,so use copy.
//     copy=(char*)malloc(len);
//     strcpy(copy,cmd);
//     char *ptr;
//     int ArgvMark=0;
//     ptr=strtok(copy," ");
//     while(ptr!=NULL){
//         argv[ArgvMark]=(char*)malloc(sizeof(strlen(ptr)));
//         strcpy(argv[ArgvMark],ptr);
//  //       printf("%d: ",ArgvMark);
//  //       printf("ptr=%s lenP=%ld ",ptr,strlen(ptr));
//  //       printf("copy=%s\n",copy);
//         ptr=strtok(NULL," ");
//         ArgvMark++;
//     }
//     //eliminate the last few blanks
//     if(strcmp(argv[ArgvMark-1]," ")==0){
//         free(argv[ArgvMark-1]);
//         ArgvMark--;
//     }
//     free(copy);
//     return ArgvMark;
// }
