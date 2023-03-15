#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define n_pros 10
#define n_cons 10
int buffer[10];
sem_t full;
sem_t empty;
sem_t m;
sem_t p_sync;
sem_t c_sync;
int prod=0;
int cons=0;
int t=5;
int e=5;
void * producer(void* pn){
    int p=(int)pn;
    
    while(1){
        sem_wait(&p_sync);
        if(t>0){
            t--;
            sem_post(&p_sync);
            sem_wait(&empty);
            sem_wait(&m);
            buffer[prod]=10-prod;
            printf("producer %d produced %d in %d\n",p,10-prod,prod);
            prod=(prod+1)%10;
            sem_post(&m);
            sem_post(&full);
        }
        else{
            sem_post(&p_sync);
            break;
        }
    }   
}
void* consumer(void * cn){
    int c=(int)cn;
    while(1){
        sem_wait(&c_sync);
        if(e>0){
            e--;
            sem_post(&c_sync);
            sem_wait(&full);
            sem_wait(&m);
            printf("consumer %d consumed %d from %d\n",c,buffer[cons],cons);
            cons=(cons+1)%10;
            sem_post(&m);
            sem_post(&empty);
         }
         else{
            sem_post(&c_sync);
            break;
         }
    }
}
int main() {  
    sem_init(&full,0,0);
    sem_init(&empty,0,10);
    sem_init(&m,0,1);
    sem_init(&p_sync,0,1);
    sem_init(&c_sync,0,1);
    pthread_t producer_thread[n_pros];
    pthread_t consumer_thread[n_cons];
    for(int i=0;i<n_pros;i++){
        pthread_create(&producer_thread[i],NULL,&producer,(void*)i);
    }
    for(int i=0;i<n_cons;i++){
        pthread_create(&consumer_thread[i],NULL,&consumer,(void*)i);
    }
    for(int i=0;i<n_pros;i++){
         pthread_join(producer_thread[i],NULL);
    }
    for(int i=0;i<n_cons;i++){
        pthread_join(consumer_thread[i],NULL);
        
    }

    
    
   
    
    
    
    return 0;                   
}    
