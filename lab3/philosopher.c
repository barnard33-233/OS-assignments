#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int forks[N];
// Assume that philosopher_i want fork_i and (fork_i + 1) % N

void* Tphilosopher(void* idp){
    int id = *((int*)idp);
    int left = id;
    int right = (id + 1) % N;
    while(1){
        pthread_mutex_lock(&mutex);
        while(!((forks[left] == 0) && (forks[right] == 0))){
            pthread_cond_wait(&cond, &mutex);
        }
        forks[left] = 1;
        forks[right] = 1;
        printf("got(%d, %d)\n", id, left);
        printf("got(%d, %d)\n", id, right);
        pthread_mutex_unlock(&mutex);


        pthread_mutex_lock(&mutex);
        printf("release(%d, %d)\n", id, left);
        printf("release(%d, %d)\n", id, right);
        forks[left] = 0;
        forks[right] = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    pthread_t thread[N];
    int id[N];
    memset(forks, 0, sizeof(forks));
    printf("%d\n", N);
    for(int i = 0; i < N; i ++){
        id[i] = i;
        pthread_create(&thread[i], NULL, Tphilosopher, &(id[i]));
    }

    for(int i = 0 ; i < N; i ++){
        void** treturn;
        pthread_join(thread[i], treturn);
    }
}
