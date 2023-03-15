#include<pthread.h>

struct semaphore{
    int value;
    pthread_cond_t ConditionVar;
    pthread_mutex_t MutexVar;
};

void create(struct semaphore* sem,int input){
    sem->value=input;
    sem->ConditionVar=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
    sem->MutexVar=(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}
void wait(struct semaphore* sem){
    pthread_mutex_lock(&(sem->MutexVar));
    sem->value--;
    if(sem->value<0){
        pthread_cond_wait(&(sem->ConditionVar),&(sem->MutexVar));
    }
        pthread_mutex_unlock(&(sem->MutexVar));    
}
void signal(struct semaphore* sem){    
    pthread_mutex_lock(&(sem->MutexVar));
    sem->value++;
    if(sem->value<=0){
        pthread_cond_signal(&(sem->ConditionVar));
    }
    pthread_mutex_unlock(&(sem->MutexVar));
}
