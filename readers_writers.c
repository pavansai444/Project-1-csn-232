#include <stdio.h>
#include <pthread.h>
#include "sem.h"
#define n_readers 7
#define n_writers 5
pthread_t readers[n_readers];
pthread_t writers[n_writers];
int buffer[10];
struct semaphore decider_mutex, mutex, wrt;
int waitwrt=0;
int in_read_count=0;
void * read(void* i){
    int r=(int)i;
    
    
    wait(&decider_mutex);
    printf("reader %d started\n",r);
    wait(&mutex);
     in_read_count++;
    signal(&mutex);
    signal(&decider_mutex);
    /*read*/
    usleep(1);
    printf("read by %d               # number of readers in cs %d\n",r,in_read_count);
    wait(&mutex);
     in_read_count--;
     if((in_read_count==0)&&(waitwrt==1)){
        signal(&wrt);
     }
    signal(&mutex);
   
}
void* write(void* i){
    int w=(int)i;
    
    wait(&decider_mutex);
    printf("writer  %d entered\n",w);
    waitwrt=1;
    wait(&mutex);
    if(in_read_count){
        signal(&mutex);
        wait(&wrt);
    }
    else{
        signal(&mutex);
    }
    
     /*write*/
     usleep(1);
     wait(&mutex);
     printf("written by %d            # number of readers in cs %d\n",w,in_read_count);
     signal(&mutex);
     waitwrt=0;
    signal(&decider_mutex);
    
}
void* createreaders(void* arg){
    printf("CR\n");
    for(int i=0;i<n_readers;i++){
        pthread_create(&readers[i],NULL,&read,(void*)i);
    }
    for(int i=0;i<n_readers;i++){
        pthread_join(readers[i],NULL);
    }

}
void* createwriters(void* arg){
    printf("CW\n");
    for(int i=0;i<n_writers;i++){
        pthread_create(&writers[i],NULL,&write,(void*)i);
    }
    for(int i=0;i<n_writers;i++){
        if(pthread_join(writers[i],NULL)){
            printf("error");
        }
        ;
    }

}


int main() {  
    create(&decider_mutex,1);
    create(&mutex,1);
    create(&wrt,0);
    pthread_t readers_creator;
    pthread_t writers_creator;
    pthread_create(&writers_creator,NULL,&createwriters,NULL);
    pthread_create(&readers_creator,NULL,&createreaders,NULL);
    
    pthread_join(readers_creator,NULL);
    pthread_join(writers_creator,NULL);
    
    
    return 0;                   
}    