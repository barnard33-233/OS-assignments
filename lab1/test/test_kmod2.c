#include<stdio.h>
#include<syscall.h>

int main(){
    printf("syscall return %d\n", syscall(335));
    return 0;
}