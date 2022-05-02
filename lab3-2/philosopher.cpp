#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <synchapi.h>
#include <targetver.h>

#define N 5

SRWLOCK lock;
CONDITION_VARIABLE cond;

int forks[N];

DWORD WINAPI Tphilosopher(LPVOID idp){
    int id = *((int*)idp);
    int left = id;
    int right = (id + 1) % N;
    while(1){
        AcquireSRWLockExclusive(&lock);
        while(!(forks[left] == 0 && forks[right] == 0)){
            SleepConditionVariableSRW(
                &cond, &lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED
            );
        }
        forks[left] = forks[right] = 1;
        printf("get(%d, %d)", id, left);
        printf("get(%d, %d)", id, right);
        ReleaseSRWLockExclusive(&lock);

        AcquireSRWLockExclusive(&lock);
        forks[left] = forks[right] = 0;
        printf("release(%d, %d)", id, left);
        printf("release(%d, %d)", id, right);
        WakeAllConditionVariable(&cond);
        ReleaseSRWLockExclusive(&lock);
    }
    return 0;
}

int main(){
    // initialize
    InitializeSRWLock(&lock);
    InitializeConditionVariable(&cond);
    memset(forks, 0, sizeof(forks));
    HANDLE thread[N];
    int ids[N];
    for (int i = 0; i < N; i ++){
        ids[i] = i;
        thread[i] = CreateThread(0, 0, Tphilosopher, &(ids[i]), 0, 0);
    }
    while(1);
}
