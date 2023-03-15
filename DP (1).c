#include <stdio.h>
#include <pthread.h>
#include "sem.h"
#define n 10
pthread_t philosopher[n];
int threadid[n];
sem_t fork[n];
void * even_philosopher(void* tid){
    long t=(long)tid;
    wait(&fork[t]);
    wait(&fork[(t+1)%n]);
     //eat//
     printf("ate by %d\n",t);
    wait(&fork[(t+1)%n]);
    wait(&fork[t]);
}
void * odd_philosopher(void* tid){
    long t=(long)tid;
    wait(&fork[(t+1)%n]);
    wait(&fork[t]);
     //eat//
     printf("ate by %d\n",t);
    wait(&fork[t]);
    wait(&fork[(t+1)%n]);
    
   
}
int main() {
    for(int i=0;i<n;i++){
        create(&fork[i],0,1);
    }
    for(int i=0;i<n;i++){
        threadid[i]=i;
        if(i%2==0){
            pthread_create(&philosopher[i],NULL,even_philosopher,(void*)threadid[i]);
        }
        else{
            pthread_create(&philosopher[i],NULL,odd_philosopher,(void*)threadid[i]);
        }
        
    }
    for( int i=0;i<n;i++){
        pthread_join(philosopher[i],NULL);
    }
    return 0;                   
}